// Some modifications have been made to the original file:
// - Code was placed in a "tgui" namespace to avoid conflicts if a TGUI user also uses NanoSVG in their project
// - All floats were replaced by doubles (to get rid of warnings about implicit conversions and promotions)
// - Some other c++ compiler warnings were fixed, mainly about usage of old-style casts

/*
 * Copyright (c) 2013-14 Mikko Mononen memon@inside.org
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 * claim that you wrote the original software. If you use this software
 * in a product, an acknowledgment in the product documentation would be
 * appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 * misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * The polygon rasterization is heavily based on stb_truetype rasterizer
 * by Sean Barrett - http://nothings.org/
 *
 */

#ifndef NANOSVGRAST_H
#define NANOSVGRAST_H

namespace tgui
{
    struct NSVGrasterizer;

/* Example Usage:
	// Load SVG
	NSVGimage* image;
	image = nsvgParseFromFile("test.svg", "px", 96);

	// Create rasterizer (can be used to render multiple images).
	struct NSVGrasterizer* rast = nsvgCreateRasterizer();
	// Allocate memory for image
	unsigned char* img = malloc(w*h*4);
	// Rasterize
	nsvgRasterize(rast, image, 0,0,1, img, w, h, w*4);
*/

// Allocated rasterizer context.
NSVGrasterizer* nsvgCreateRasterizer();

// Rasterizes SVG image, returns RGBA image (non-premultiplied alpha)
//   r - pointer to rasterizer context
//   image - pointer to image to rasterize
//   tx,ty - image offset (applied after scaling)
//   scale - image scale
//   dst - pointer to destination image data, 4 bytes per pixel (RGBA)
//   w - width of the image to render
//   h - height of the image to render
//   stride - number of bytes per scaleline in the destination buffer
void nsvgRasterize(NSVGrasterizer* r,
				   NSVGimage* image, double tx, double ty, double scale,
				   unsigned char* dst, int w, int h, int stride);

void nsvgRasterizeFull(NSVGrasterizer* r, NSVGimage* image,
						double tx, double ty, double scalex, double scaley,
						unsigned char* dst, int w, int h, int stride);

// Deletes rasterizer context.
void nsvgDeleteRasterizer(NSVGrasterizer*);

}

#endif // NANOSVGRAST_H

#ifdef NANOSVGRAST_IMPLEMENTATION

#include <math.h>

namespace tgui
{

#define NSVG__SUBSAMPLES	5
#define NSVG__FIXSHIFT		10
#define NSVG__FIX			(1 << NSVG__FIXSHIFT)
#define NSVG__FIXMASK		(NSVG__FIX-1)
#define NSVG__MEMPAGE_SIZE	1024

typedef struct NSVGedge {
	double x0,y0, x1,y1;
	int dir;
	struct NSVGedge* next;
} NSVGedge;

typedef struct NSVGpoint {
	double x, y;
	double dx, dy;
	double len;
	double dmx, dmy;
	unsigned char flags;
} NSVGpoint;

typedef struct NSVGactiveEdge {
	int x,dx;
	double ey;
	int dir;
	struct NSVGactiveEdge *next;
} NSVGactiveEdge;

typedef struct NSVGmemPage {
	unsigned char mem[NSVG__MEMPAGE_SIZE];
	int size;
	struct NSVGmemPage* next;
} NSVGmemPage;

typedef struct NSVGcachedPaint {
	char type;
	char spread;
	double xform[6];
	unsigned int colors[256];
} NSVGcachedPaint;

struct NSVGrasterizer
{
	double px, py;

	double tessTol;
	double distTol;

	NSVGedge* edges;
	int nedges;
	int cedges;

	NSVGpoint* points;
	int npoints;
	int cpoints;

	NSVGpoint* points2;
	int npoints2;
	int cpoints2;

	NSVGactiveEdge* freelist;
	NSVGmemPage* pages;
	NSVGmemPage* curpage;

	unsigned char* scanline;
	int cscanline;

	unsigned char* bitmap;
	int width, height, stride;
};

NSVGrasterizer* nsvgCreateRasterizer()
{
	NSVGrasterizer* r = static_cast<NSVGrasterizer*>(malloc(sizeof(NSVGrasterizer)));
	if (r == nullptr) goto error;
	memset(r, 0, sizeof(NSVGrasterizer));

	r->tessTol = 0.25;
	r->distTol = 0.01;

	return r;

error:
	nsvgDeleteRasterizer(r);
	return nullptr;
}

void nsvgDeleteRasterizer(NSVGrasterizer* r)
{
	NSVGmemPage* p;

	if (r == nullptr) return;

	p = r->pages;
	while (p != nullptr) {
		NSVGmemPage* next = p->next;
		free(p);
		p = next;
	}

	if (r->edges) free(r->edges);
	if (r->points) free(r->points);
	if (r->points2) free(r->points2);
	if (r->scanline) free(r->scanline);

	free(r);
}

static NSVGmemPage* nsvg__nextPage(NSVGrasterizer* r, NSVGmemPage* cur)
{
	NSVGmemPage *newp;

	// If using existing chain, return the next page in chain
	if (cur != nullptr && cur->next != nullptr) {
		return cur->next;
	}

	// Alloc new page
	newp = static_cast<NSVGmemPage*>(malloc(sizeof(NSVGmemPage)));
	if (newp == nullptr) return nullptr;
	memset(newp, 0, sizeof(NSVGmemPage));

	// Add to linked list
	if (cur != nullptr)
		cur->next = newp;
	else
		r->pages = newp;

	return newp;
}

static void nsvg__resetPool(NSVGrasterizer* r)
{
	NSVGmemPage* p = r->pages;
	while (p != nullptr) {
		p->size = 0;
		p = p->next;
	}
	r->curpage = r->pages;
}

static unsigned char* nsvg__alloc(NSVGrasterizer* r, int size)
{
	unsigned char* buf;
	if (size > NSVG__MEMPAGE_SIZE) return nullptr;
	if (r->curpage == nullptr || r->curpage->size+size > NSVG__MEMPAGE_SIZE) {
		r->curpage = nsvg__nextPage(r, r->curpage);
	}
	buf = &r->curpage->mem[r->curpage->size];
	r->curpage->size += size;
	return buf;
}

static int nsvg__ptEquals(double x1, double y1, double x2, double y2, double tol)
{
	double dx = x2 - x1;
	double dy = y2 - y1;
	return dx*dx + dy*dy < tol*tol;
}

static void nsvg__addPathPoint(NSVGrasterizer* r, double x, double y, int flags)
{
	NSVGpoint* pt;

	if (r->npoints > 0) {
		pt = &r->points[r->npoints-1];
		if (nsvg__ptEquals(pt->x,pt->y, x,y, r->distTol)) {
			pt->flags = static_cast<unsigned char>(pt->flags | flags);
			return;
		}
	}

	if (r->npoints+1 > r->cpoints) {
		r->cpoints = r->cpoints > 0 ? r->cpoints * 2 : 64;
		r->points = static_cast<NSVGpoint*>(realloc(r->points, sizeof(NSVGpoint) * r->cpoints));
		if (r->points == nullptr) return;
	}

	pt = &r->points[r->npoints];
	pt->x = x;
	pt->y = y;
	pt->flags = static_cast<unsigned char>(flags);
	r->npoints++;
}

static void nsvg__appendPathPoint(NSVGrasterizer* r, NSVGpoint pt)
{
	if (r->npoints+1 > r->cpoints) {
		r->cpoints = r->cpoints > 0 ? r->cpoints * 2 : 64;
		r->points = static_cast<NSVGpoint*>(realloc(r->points, sizeof(NSVGpoint) * r->cpoints));
		if (r->points == nullptr) return;
	}
	r->points[r->npoints] = pt;
	r->npoints++;
}

static void nsvg__duplicatePoints(NSVGrasterizer* r)
{
	if (r->npoints > r->cpoints2) {
		r->cpoints2 = r->npoints;
		r->points2 = static_cast<NSVGpoint*>(realloc(r->points2, sizeof(NSVGpoint) * r->cpoints2));
		if (r->points2 == nullptr) return;
	}

	memcpy(r->points2, r->points, sizeof(NSVGpoint) * r->npoints);
	r->npoints2 = r->npoints;
}

static void nsvg__addEdge(NSVGrasterizer* r, double x0, double y0, double x1, double y1)
{
	NSVGedge* e;

	// Skip horizontal edges
	if (y0 == y1)
		return;

	if (r->nedges+1 > r->cedges) {
		r->cedges = r->cedges > 0 ? r->cedges * 2 : 64;
		r->edges = static_cast<NSVGedge*>(realloc(r->edges, sizeof(NSVGedge) * r->cedges));
		if (r->edges == nullptr) return;
	}

	e = &r->edges[r->nedges];
	r->nedges++;

	if (y0 < y1) {
		e->x0 = x0;
		e->y0 = y0;
		e->x1 = x1;
		e->y1 = y1;
		e->dir = 1;
	} else {
		e->x0 = x1;
		e->y0 = y1;
		e->x1 = x0;
		e->y1 = y0;
		e->dir = -1;
	}
}

static double nsvg__normalize(double *x, double* y)
{
	double d = sqrt((*x)*(*x) + (*y)*(*y));
	if (d > 1e-6) {
		double id = 1.0 / d;
		*x *= id;
		*y *= id;
	}
	return d;
}

static double nsvg__absf(double x) { return x < 0 ? -x : x; }

static void nsvg__flattenCubicBez(NSVGrasterizer* r,
								  double x1, double y1, double x2, double y2,
								  double x3, double y3, double x4, double y4,
								  int level, int type)
{
	double x12,y12,x23,y23,x34,y34,x123,y123,x234,y234,x1234,y1234;
	double dx,dy,d2,d3;

	if (level > 10) return;

	x12 = (x1+x2)*0.5;
	y12 = (y1+y2)*0.5;
	x23 = (x2+x3)*0.5;
	y23 = (y2+y3)*0.5;
	x34 = (x3+x4)*0.5;
	y34 = (y3+y4)*0.5;
	x123 = (x12+x23)*0.5;
	y123 = (y12+y23)*0.5;

	dx = x4 - x1;
	dy = y4 - y1;
	d2 = nsvg__absf(((x2 - x4) * dy - (y2 - y4) * dx));
	d3 = nsvg__absf(((x3 - x4) * dy - (y3 - y4) * dx));

	if ((d2 + d3)*(d2 + d3) < r->tessTol * (dx*dx + dy*dy)) {
		nsvg__addPathPoint(r, x4, y4, type);
		return;
	}

	x234 = (x23+x34)*0.5;
	y234 = (y23+y34)*0.5;
	x1234 = (x123+x234)*0.5;
	y1234 = (y123+y234)*0.5;

	nsvg__flattenCubicBez(r, x1,y1, x12,y12, x123,y123, x1234,y1234, level+1, 0);
	nsvg__flattenCubicBez(r, x1234,y1234, x234,y234, x34,y34, x4,y4, level+1, type);
}

static void nsvg__flattenShape(NSVGrasterizer* r, NSVGshape* shape, double scalex, double scaley)
{
	int i, j;
	NSVGpath* path;

	for (path = shape->paths; path != nullptr; path = path->next) {
		r->npoints = 0;
		// Flatten path
		nsvg__addPathPoint(r, path->pts[0]*scalex, path->pts[1]*scaley, 0);
		for (i = 0; i < path->npts-1; i += 3) {
			double* p = &path->pts[i*2];
			nsvg__flattenCubicBez(r, p[0]*scalex,p[1]*scaley, p[2]*scalex,p[3]*scaley, p[4]*scalex,p[5]*scaley, p[6]*scalex,p[7]*scaley, 0, 0);
		}
		// Close path
		nsvg__addPathPoint(r, path->pts[0]*scalex, path->pts[1]*scaley, 0);
		// Build edges
		for (i = 0, j = r->npoints-1; i < r->npoints; j = i++)
			nsvg__addEdge(r, r->points[j].x, r->points[j].y, r->points[i].x, r->points[i].y);
	}
}

enum NSVGpointFlags
{
	NSVG_PT_CORNER = 0x01,
	NSVG_PT_BEVEL = 0x02,
	NSVG_PT_LEFT = 0x04
};

static void nsvg__initClosed(NSVGpoint* left, NSVGpoint* right, NSVGpoint* p0, NSVGpoint* p1, double lineWidth)
{
	double w = lineWidth * 0.5;
	double dx = p1->x - p0->x;
	double dy = p1->y - p0->y;
	double len = nsvg__normalize(&dx, &dy);
	double px = p0->x + dx*len*0.5, py = p0->y + dy*len*0.5;
	double dlx = dy, dly = -dx;
	double lx = px - dlx*w, ly = py - dly*w;
	double rx = px + dlx*w, ry = py + dly*w;
	left->x = lx; left->y = ly;
	right->x = rx; right->y = ry;
}

static void nsvg__buttCap(NSVGrasterizer* r, NSVGpoint* left, NSVGpoint* right, NSVGpoint* p, double dx, double dy, double lineWidth, int connect)
{
	double w = lineWidth * 0.5;
	double px = p->x, py = p->y;
	double dlx = dy, dly = -dx;
	double lx = px - dlx*w, ly = py - dly*w;
	double rx = px + dlx*w, ry = py + dly*w;

	nsvg__addEdge(r, lx, ly, rx, ry);

	if (connect) {
		nsvg__addEdge(r, left->x, left->y, lx, ly);
		nsvg__addEdge(r, rx, ry, right->x, right->y);
	}
	left->x = lx; left->y = ly;
	right->x = rx; right->y = ry;
}

static void nsvg__squareCap(NSVGrasterizer* r, NSVGpoint* left, NSVGpoint* right, NSVGpoint* p, double dx, double dy, double lineWidth, int connect)
{
	double w = lineWidth * 0.5;
	double px = p->x - dx*w, py = p->y - dy*w;
	double dlx = dy, dly = -dx;
	double lx = px - dlx*w, ly = py - dly*w;
	double rx = px + dlx*w, ry = py + dly*w;

	nsvg__addEdge(r, lx, ly, rx, ry);

	if (connect) {
		nsvg__addEdge(r, left->x, left->y, lx, ly);
		nsvg__addEdge(r, rx, ry, right->x, right->y);
	}
	left->x = lx; left->y = ly;
	right->x = rx; right->y = ry;
}

#ifndef NSVG_PI
#define NSVG_PI (3.14159265358979323846264338327)
#endif

static void nsvg__roundCap(NSVGrasterizer* r, NSVGpoint* left, NSVGpoint* right, NSVGpoint* p, double dx, double dy, double lineWidth, int ncap, int connect)
{
	int i;
	double w = lineWidth * 0.5;
	double px = p->x, py = p->y;
	double dlx = dy, dly = -dx;
	double lx = 0, ly = 0, rx = 0, ry = 0, prevx = 0, prevy = 0;

	for (i = 0; i < ncap; i++) {
		double a = static_cast<double>(i)/static_cast<double>(ncap-1)*NSVG_PI;
		double ax = cos(a) * w, ay = sin(a) * w;
		double x = px - dlx*ax - dx*ay;
		double y = py - dly*ax - dy*ay;

		if (i > 0)
			nsvg__addEdge(r, prevx, prevy, x, y);

		prevx = x;
		prevy = y;

		if (i == 0) {
			lx = x; ly = y;
		} else if (i == ncap-1) {
			rx = x; ry = y;
		}
	}

	if (connect) {
		nsvg__addEdge(r, left->x, left->y, lx, ly);
		nsvg__addEdge(r, rx, ry, right->x, right->y);
	}

	left->x = lx; left->y = ly;
	right->x = rx; right->y = ry;
}

static void nsvg__bevelJoin(NSVGrasterizer* r, NSVGpoint* left, NSVGpoint* right, NSVGpoint* p0, NSVGpoint* p1, double lineWidth)
{
	double w = lineWidth * 0.5;
	double dlx0 = p0->dy, dly0 = -p0->dx;
	double dlx1 = p1->dy, dly1 = -p1->dx;
	double lx0 = p1->x - (dlx0 * w), ly0 = p1->y - (dly0 * w);
	double rx0 = p1->x + (dlx0 * w), ry0 = p1->y + (dly0 * w);
	double lx1 = p1->x - (dlx1 * w), ly1 = p1->y - (dly1 * w);
	double rx1 = p1->x + (dlx1 * w), ry1 = p1->y + (dly1 * w);

	nsvg__addEdge(r, lx0, ly0, left->x, left->y);
	nsvg__addEdge(r, lx1, ly1, lx0, ly0);

	nsvg__addEdge(r, right->x, right->y, rx0, ry0);
	nsvg__addEdge(r, rx0, ry0, rx1, ry1);

	left->x = lx1; left->y = ly1;
	right->x = rx1; right->y = ry1;
}

static void nsvg__miterJoin(NSVGrasterizer* r, NSVGpoint* left, NSVGpoint* right, NSVGpoint* p0, NSVGpoint* p1, double lineWidth)
{
	double w = lineWidth * 0.5;
	double dlx0 = p0->dy, dly0 = -p0->dx;
	double dlx1 = p1->dy, dly1 = -p1->dx;
	double lx0, rx0, lx1, rx1;
	double ly0, ry0, ly1, ry1;

	if (p1->flags & NSVG_PT_LEFT) {
		lx0 = lx1 = p1->x - p1->dmx * w;
		ly0 = ly1 = p1->y - p1->dmy * w;
		nsvg__addEdge(r, lx1, ly1, left->x, left->y);

		rx0 = p1->x + (dlx0 * w);
		ry0 = p1->y + (dly0 * w);
		rx1 = p1->x + (dlx1 * w);
		ry1 = p1->y + (dly1 * w);
		nsvg__addEdge(r, right->x, right->y, rx0, ry0);
		nsvg__addEdge(r, rx0, ry0, rx1, ry1);
	} else {
		lx0 = p1->x - (dlx0 * w);
		ly0 = p1->y - (dly0 * w);
		lx1 = p1->x - (dlx1 * w);
		ly1 = p1->y - (dly1 * w);
		nsvg__addEdge(r, lx0, ly0, left->x, left->y);
		nsvg__addEdge(r, lx1, ly1, lx0, ly0);

		rx0 = rx1 = p1->x + p1->dmx * w;
		ry0 = ry1 = p1->y + p1->dmy * w;
		nsvg__addEdge(r, right->x, right->y, rx1, ry1);
	}

	left->x = lx1; left->y = ly1;
	right->x = rx1; right->y = ry1;
}

static void nsvg__roundJoin(NSVGrasterizer* r, NSVGpoint* left, NSVGpoint* right, NSVGpoint* p0, NSVGpoint* p1, double lineWidth, int ncap)
{
	int i, n;
	double w = lineWidth * 0.5;
	double dlx0 = p0->dy, dly0 = -p0->dx;
	double dlx1 = p1->dy, dly1 = -p1->dx;
	double a0 = atan2(dly0, dlx0);
	double a1 = atan2(dly1, dlx1);
	double da = a1 - a0;
	double lx, ly, rx, ry;

	if (da < NSVG_PI) da += NSVG_PI*2;
	if (da > NSVG_PI) da -= NSVG_PI*2;

	n = static_cast<int>(ceil((nsvg__absf(da) / NSVG_PI) * static_cast<double>(ncap)));
	if (n < 2) n = 2;
	if (n > ncap) n = ncap;

	lx = left->x;
	ly = left->y;
	rx = right->x;
	ry = right->y;

	for (i = 0; i < n; i++) {
		double u = static_cast<double>(i)/static_cast<double>(n-1);
		double a = a0 + u*da;
		double ax = cos(a) * w, ay = sin(a) * w;
		double lx1 = p1->x - ax, ly1 = p1->y - ay;
		double rx1 = p1->x + ax, ry1 = p1->y + ay;

		nsvg__addEdge(r, lx1, ly1, lx, ly);
		nsvg__addEdge(r, rx, ry, rx1, ry1);

		lx = lx1; ly = ly1;
		rx = rx1; ry = ry1;
	}

	left->x = lx; left->y = ly;
	right->x = rx; right->y = ry;
}

static void nsvg__straightJoin(NSVGrasterizer* r, NSVGpoint* left, NSVGpoint* right, NSVGpoint* p1, double lineWidth)
{
	double w = lineWidth * 0.5;
	double lx = p1->x - (p1->dmx * w), ly = p1->y - (p1->dmy * w);
	double rx = p1->x + (p1->dmx * w), ry = p1->y + (p1->dmy * w);

	nsvg__addEdge(r, lx, ly, left->x, left->y);
	nsvg__addEdge(r, right->x, right->y, rx, ry);

	left->x = lx; left->y = ly;
	right->x = rx; right->y = ry;
}

static int nsvg__curveDivs(double r, double arc, double tol)
{
	double da = acos(r / (r + tol)) * 2.0;
	int divs = static_cast<int>(ceil(arc / da));
	if (divs < 2) divs = 2;
	return divs;
}

static void nsvg__expandStroke(NSVGrasterizer* r, NSVGpoint* points, int npoints, int closed, int lineJoin, int lineCap, double lineWidth)
{
	int ncap = nsvg__curveDivs(lineWidth*0.5, NSVG_PI, r->tessTol);	// Calculate divisions per half circle.
	NSVGpoint left = {0,0,0,0,0,0,0,0}, right = {0,0,0,0,0,0,0,0}, firstLeft = {0,0,0,0,0,0,0,0}, firstRight = {0,0,0,0,0,0,0,0};
	NSVGpoint* p0, *p1;
	int j, s, e;

	// Build stroke edges
	if (closed) {
		// Looping
		p0 = &points[npoints-1];
		p1 = &points[0];
		s = 0;
		e = npoints;
	} else {
		// Add cap
		p0 = &points[0];
		p1 = &points[1];
		s = 1;
		e = npoints-1;
	}

	if (closed) {
		nsvg__initClosed(&left, &right, p0, p1, lineWidth);
		firstLeft = left;
		firstRight = right;
	} else {
		// Add cap
		double dx = p1->x - p0->x;
		double dy = p1->y - p0->y;
		nsvg__normalize(&dx, &dy);
		if (lineCap == NSVG_CAP_BUTT)
			nsvg__buttCap(r, &left, &right, p0, dx, dy, lineWidth, 0);
		else if (lineCap == NSVG_CAP_SQUARE)
			nsvg__squareCap(r, &left, &right, p0, dx, dy, lineWidth, 0);
		else if (lineCap == NSVG_CAP_ROUND)
			nsvg__roundCap(r, &left, &right, p0, dx, dy, lineWidth, ncap, 0);
	}

	for (j = s; j < e; ++j) {
		if (p1->flags & NSVG_PT_CORNER) {
			if (lineJoin == NSVG_JOIN_ROUND)
				nsvg__roundJoin(r, &left, &right, p0, p1, lineWidth, ncap);
			else if (lineJoin == NSVG_JOIN_BEVEL || (p1->flags & NSVG_PT_BEVEL))
				nsvg__bevelJoin(r, &left, &right, p0, p1, lineWidth);
			else
				nsvg__miterJoin(r, &left, &right, p0, p1, lineWidth);
		} else {
			nsvg__straightJoin(r, &left, &right, p1, lineWidth);
		}
		p0 = p1++;
	}

	if (closed) {
		// Loop it
		nsvg__addEdge(r, firstLeft.x, firstLeft.y, left.x, left.y);
		nsvg__addEdge(r, right.x, right.y, firstRight.x, firstRight.y);
	} else {
		// Add cap
		double dx = p1->x - p0->x;
		double dy = p1->y - p0->y;
		nsvg__normalize(&dx, &dy);
		if (lineCap == NSVG_CAP_BUTT)
			nsvg__buttCap(r, &right, &left, p1, -dx, -dy, lineWidth, 1);
		else if (lineCap == NSVG_CAP_SQUARE)
			nsvg__squareCap(r, &right, &left, p1, -dx, -dy, lineWidth, 1);
		else if (lineCap == NSVG_CAP_ROUND)
			nsvg__roundCap(r, &right, &left, p1, -dx, -dy, lineWidth, ncap, 1);
	}
}

static void nsvg__prepareStroke(NSVGrasterizer* r, double miterLimit, int lineJoin)
{
	int i, j;
	NSVGpoint* p0, *p1;

	p0 = &r->points[r->npoints-1];
	p1 = &r->points[0];
	for (i = 0; i < r->npoints; i++) {
		// Calculate segment direction and length
		p0->dx = p1->x - p0->x;
		p0->dy = p1->y - p0->y;
		p0->len = nsvg__normalize(&p0->dx, &p0->dy);
		// Advance
		p0 = p1++;
	}

	// calculate joins
	p0 = &r->points[r->npoints-1];
	p1 = &r->points[0];
	for (j = 0; j < r->npoints; j++) {
		double dlx0, dly0, dlx1, dly1, dmr2, cross;
		dlx0 = p0->dy;
		dly0 = -p0->dx;
		dlx1 = p1->dy;
		dly1 = -p1->dx;
		// Calculate extrusions
		p1->dmx = (dlx0 + dlx1) * 0.5;
		p1->dmy = (dly0 + dly1) * 0.5;
		dmr2 = p1->dmx*p1->dmx + p1->dmy*p1->dmy;
		if (dmr2 > 0.000001) {
			double s2 = 1.0 / dmr2;
			if (s2 > 600.0) {
				s2 = 600.0;
			}
			p1->dmx *= s2;
			p1->dmy *= s2;
		}

		// Clear flags, but keep the corner.
		p1->flags = (p1->flags & NSVG_PT_CORNER) ? NSVG_PT_CORNER : 0;

		// Keep track of left turns.
		cross = p1->dx * p0->dy - p0->dx * p1->dy;
		if (cross > 0.0)
			p1->flags |= NSVG_PT_LEFT;

		// Check to see if the corner needs to be beveled.
		if (p1->flags & NSVG_PT_CORNER) {
			if ((dmr2 * miterLimit*miterLimit) < 1.0 || lineJoin == NSVG_JOIN_BEVEL || lineJoin == NSVG_JOIN_ROUND) {
				p1->flags |= NSVG_PT_BEVEL;
			}
		}

		p0 = p1++;
	}
}

static void nsvg__flattenShapeStroke(NSVGrasterizer* r, NSVGshape* shape, double scalex, double scaley)
{
	int i, j, closed;
	NSVGpath* path;
	NSVGpoint* p0, *p1;
	double miterLimit = shape->miterLimit;
	int lineJoin = shape->strokeLineJoin;
	int lineCap = shape->strokeLineCap;
	double lineWidth = shape->strokeWidth * (scalex+scaley)*0.5;

	for (path = shape->paths; path != nullptr; path = path->next) {
		// Flatten path
		r->npoints = 0;
		nsvg__addPathPoint(r, path->pts[0]*scalex, path->pts[1]*scaley, NSVG_PT_CORNER);
		for (i = 0; i < path->npts-1; i += 3) {
			double* p = &path->pts[i*2];
			nsvg__flattenCubicBez(r, p[0]*scalex,p[1]*scaley, p[2]*scalex,p[3]*scaley, p[4]*scalex,p[5]*scaley, p[6]*scalex,p[7]*scaley, 0, NSVG_PT_CORNER);
		}
		if (r->npoints < 2)
			continue;

		closed = path->closed;

		// If the first and last points are the same, remove the last, mark as closed path.
		p0 = &r->points[r->npoints-1];
		p1 = &r->points[0];
		if (nsvg__ptEquals(p0->x,p0->y, p1->x,p1->y, r->distTol)) {
			r->npoints--;
			p0 = &r->points[r->npoints-1];
			closed = 1;
		}

		if (shape->strokeDashCount > 0) {
			int idash = 0, dashState = 1;
			double totalDist = 0, dashLen, allDashLen, dashOffset;
			NSVGpoint cur;

			if (closed)
				nsvg__appendPathPoint(r, r->points[0]);

			// Duplicate points -> points2.
			nsvg__duplicatePoints(r);

			r->npoints = 0;
 			cur = r->points2[0];
			nsvg__appendPathPoint(r, cur);

			// Figure out dash offset.
			allDashLen = 0;
			for (j = 0; j < shape->strokeDashCount; j++)
				allDashLen += shape->strokeDashArray[j];
			if (shape->strokeDashCount & 1)
				allDashLen *= 2.0;
			// Find location inside pattern
			dashOffset = fmod(shape->strokeDashOffset, allDashLen);
			if (dashOffset < 0.0)
				dashOffset += allDashLen;

			while (dashOffset > shape->strokeDashArray[idash]) {
				dashOffset -= shape->strokeDashArray[idash];
				idash = (idash + 1) % shape->strokeDashCount;
			}
			dashLen = (shape->strokeDashArray[idash] - dashOffset) * (scalex+scaley)*0.5;

			for (j = 1; j < r->npoints2; ) {
				double dx = r->points2[j].x - cur.x;
				double dy = r->points2[j].y - cur.y;
				double dist = sqrt(dx*dx + dy*dy);

				if ((totalDist + dist) > dashLen) {
					// Calculate intermediate point
					double d = (dashLen - totalDist) / dist;
					double x = cur.x + dx * d;
					double y = cur.y + dy * d;
					nsvg__addPathPoint(r, x, y, NSVG_PT_CORNER);

					// Stroke
					if (r->npoints > 1 && dashState) {
						nsvg__prepareStroke(r, miterLimit, lineJoin);
						nsvg__expandStroke(r, r->points, r->npoints, 0, lineJoin, lineCap, lineWidth);
					}
					// Advance dash pattern
					dashState = !dashState;
					idash = (idash+1) % shape->strokeDashCount;
					dashLen = shape->strokeDashArray[idash] * (scalex+scaley)*0.5;
					// Restart
					cur.x = x;
					cur.y = y;
					cur.flags = NSVG_PT_CORNER;
					totalDist = 0.0;
					r->npoints = 0;
					nsvg__appendPathPoint(r, cur);
				} else {
					totalDist += dist;
					cur = r->points2[j];
					nsvg__appendPathPoint(r, cur);
					j++;
				}
			}
			// Stroke any leftover path
			if (r->npoints > 1 && dashState)
				nsvg__expandStroke(r, r->points, r->npoints, 0, lineJoin, lineCap, lineWidth);
		} else {
			nsvg__prepareStroke(r, miterLimit, lineJoin);
			nsvg__expandStroke(r, r->points, r->npoints, closed, lineJoin, lineCap, lineWidth);
		}
	}
}

static int nsvg__cmpEdge(const void *p, const void *q)
{
	const NSVGedge* a = static_cast<const NSVGedge*>(p);
	const NSVGedge* b = static_cast<const NSVGedge*>(q);

	if (a->y0 < b->y0) return -1;
	if (a->y0 > b->y0) return  1;
	return 0;
}


static NSVGactiveEdge* nsvg__addActive(NSVGrasterizer* r, NSVGedge* e, double startPoint)
{
	 NSVGactiveEdge* z;

	if (r->freelist != nullptr) {
		// Restore from freelist.
		z = r->freelist;
		r->freelist = z->next;
	} else {
		// Alloc new edge.
		z = reinterpret_cast<NSVGactiveEdge*>(nsvg__alloc(r, sizeof(NSVGactiveEdge)));
		if (z == nullptr) return nullptr;
	}

	double dxdy = (e->x1 - e->x0) / (e->y1 - e->y0);
//	STBTT_assert(e->y0 <= start_point);
	// round dx down to avoid going too far
	if (dxdy < 0)
		z->dx = static_cast<int>(-floor(NSVG__FIX * -dxdy));
	else
		z->dx = static_cast<int>(floor(NSVG__FIX * dxdy));
	z->x = static_cast<int>(floor(NSVG__FIX * (e->x0 + dxdy * (startPoint - e->y0))));
//	z->x -= off_x * FIX;
	z->ey = e->y1;
	z->next = nullptr;
	z->dir = e->dir;

	return z;
}

static void nsvg__freeActive(NSVGrasterizer* r, NSVGactiveEdge* z)
{
	z->next = r->freelist;
	r->freelist = z;
}

static void nsvg__fillScanline(unsigned char* scanline, int len, int x0, int x1, int maxWeight, int* xmin, int* xmax)
{
	int i = x0 >> NSVG__FIXSHIFT;
	int j = x1 >> NSVG__FIXSHIFT;
	if (i < *xmin) *xmin = i;
	if (j > *xmax) *xmax = j;
	if (i < len && j >= 0) {
		if (i == j) {
			// x0,x1 are the same pixel, so compute combined coverage
			scanline[i] = static_cast<unsigned char>(scanline[i] + ((x1 - x0) * maxWeight >> NSVG__FIXSHIFT));
		} else {
			if (i >= 0) // add antialiasing for x0
				scanline[i] = static_cast<unsigned char>(scanline[i] + (((NSVG__FIX - (x0 & NSVG__FIXMASK)) * maxWeight) >> NSVG__FIXSHIFT));
			else
				i = -1; // clip

			if (j < len) // add antialiasing for x1
				scanline[j] = static_cast<unsigned char>(scanline[j] + (((x1 & NSVG__FIXMASK) * maxWeight) >> NSVG__FIXSHIFT));
			else
				j = len; // clip

			for (++i; i < j; ++i) // fill pixels between x0 and x1
				scanline[i] = static_cast<unsigned char>(scanline[i] + maxWeight);
		}
	}
}

// note: this routine clips fills that extend off the edges... ideally this
// wouldn't happen, but it could happen if the truetype glyph bounding boxes
// are wrong, or if the user supplies a too-small bitmap
static void nsvg__fillActiveEdges(unsigned char* scanline, int len, NSVGactiveEdge* e, int maxWeight, int* xmin, int* xmax, char fillRule)
{
	// non-zero winding fill
	int x0 = 0, w = 0;

	if (fillRule == NSVG_FILLRULE_NONZERO) {
		// Non-zero
		while (e != nullptr) {
			if (w == 0) {
				// if we're currently at zero, we need to record the edge start point
				x0 = e->x; w += e->dir;
			} else {
				int x1 = e->x; w += e->dir;
				// if we went to zero, we need to draw
				if (w == 0)
					nsvg__fillScanline(scanline, len, x0, x1, maxWeight, xmin, xmax);
			}
			e = e->next;
		}
	} else if (fillRule == NSVG_FILLRULE_EVENODD) {
		// Even-odd
		while (e != nullptr) {
			if (w == 0) {
				// if we're currently at zero, we need to record the edge start point
				x0 = e->x; w = 1;
			} else {
				int x1 = e->x; w = 0;
				nsvg__fillScanline(scanline, len, x0, x1, maxWeight, xmin, xmax);
			}
			e = e->next;
		}
	}
}

static double nsvg__clampf(double a, double mn, double mx) { return a < mn ? mn : (a > mx ? mx : a); }

static unsigned int nsvg__RGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	return (r) | (g << 8) | (b << 16) | (a << 24);
}

static unsigned int nsvg__lerpRGBA(unsigned int c0, unsigned int c1, double u)
{
	int iu = static_cast<int>(nsvg__clampf(u, 0.0, 1.0) * 256.0);
	int r = (((c0) & 0xff)*(256-iu) + (((c1) & 0xff)*iu)) >> 8;
	int g = (((c0>>8) & 0xff)*(256-iu) + (((c1>>8) & 0xff)*iu)) >> 8;
	int b = (((c0>>16) & 0xff)*(256-iu) + (((c1>>16) & 0xff)*iu)) >> 8;
	int a = (((c0>>24) & 0xff)*(256-iu) + (((c1>>24) & 0xff)*iu)) >> 8;
	return nsvg__RGBA(static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b), static_cast<unsigned char>(a));
}

static unsigned int nsvg__applyOpacity(unsigned int c, double u)
{
	int iu = static_cast<int>(nsvg__clampf(u, 0.0, 1.0) * 256.0);
	int r = (c) & 0xff;
	int g = (c>>8) & 0xff;
	int b = (c>>16) & 0xff;
	int a = (((c>>24) & 0xff)*iu) >> 8;
	return nsvg__RGBA(static_cast<unsigned char>(r), static_cast<unsigned char>(g), static_cast<unsigned char>(b), static_cast<unsigned char>(a));
}

static inline int nsvg__div255(int x)
{
    return ((x+1) * 257) >> 16;
}

static void nsvg__scanlineSolid(unsigned char* dst, int count, unsigned char* cover, int x, int y,
								double tx, double ty, double scalex, double scaley, NSVGcachedPaint* cache)
{

	if (cache->type == NSVG_PAINT_COLOR) {
		int i, cr, cg, cb, ca;
		cr = cache->colors[0] & 0xff;
		cg = (cache->colors[0] >> 8) & 0xff;
		cb = (cache->colors[0] >> 16) & 0xff;
		ca = (cache->colors[0] >> 24) & 0xff;

		for (i = 0; i < count; i++) {
			int r,g,b;
			int a = nsvg__div255(static_cast<int>(cover[0]) * ca);
			int ia = 255 - a;
			// Premultiply
			r = nsvg__div255(cr * a);
			g = nsvg__div255(cg * a);
			b = nsvg__div255(cb * a);

			// Blend over
			r += nsvg__div255(ia * static_cast<int>(dst[0]));
			g += nsvg__div255(ia * static_cast<int>(dst[1]));
			b += nsvg__div255(ia * static_cast<int>(dst[2]));
			a += nsvg__div255(ia * static_cast<int>(dst[3]));

			dst[0] = static_cast<unsigned char>(r);
			dst[1] = static_cast<unsigned char>(g);
			dst[2] = static_cast<unsigned char>(b);
			dst[3] = static_cast<unsigned char>(a);

			cover++;
			dst += 4;
		}
	} else if (cache->type == NSVG_PAINT_LINEAR_GRADIENT) {
		// TODO: spread modes.
		// TODO: plenty of opportunities to optimize.
		double fx, fy, dx, gy;
		double* t = cache->xform;
		int i, cr, cg, cb, ca;
		unsigned int c;

		fx = (static_cast<double>(x) - tx) / scalex;
		fy = (static_cast<double>(y) - ty) / scaley;
		dx = 1.0 / scalex;

		for (i = 0; i < count; i++) {
			int r,g,b,a,ia;
			gy = fx*t[1] + fy*t[3] + t[5];
			c = cache->colors[static_cast<int>(nsvg__clampf(gy*255.0, 0, 255.0))];
			cr = (c) & 0xff;
			cg = (c >> 8) & 0xff;
			cb = (c >> 16) & 0xff;
			ca = (c >> 24) & 0xff;

			a = nsvg__div255(static_cast<int>(cover[0]) * ca);
			ia = 255 - a;

			// Premultiply
			r = nsvg__div255(cr * a);
			g = nsvg__div255(cg * a);
			b = nsvg__div255(cb * a);

			// Blend over
			r += nsvg__div255(ia * static_cast<int>(dst[0]));
			g += nsvg__div255(ia * static_cast<int>(dst[1]));
			b += nsvg__div255(ia * static_cast<int>(dst[2]));
			a += nsvg__div255(ia * static_cast<int>(dst[3]));

			dst[0] = static_cast<unsigned char>(r);
			dst[1] = static_cast<unsigned char>(g);
			dst[2] = static_cast<unsigned char>(b);
			dst[3] = static_cast<unsigned char>(a);

			cover++;
			dst += 4;
			fx += dx;
		}
	} else if (cache->type == NSVG_PAINT_RADIAL_GRADIENT) {
		// TODO: spread modes.
		// TODO: plenty of opportunities to optimize.
		// TODO: focus (fx,fy)
		double fx, fy, dx, gx, gy, gd;
		double* t = cache->xform;
		int i, cr, cg, cb, ca;
		unsigned int c;

		fx = (static_cast<double>(x) - tx) / scalex;
		fy = (static_cast<double>(y) - ty) / scaley;
		dx = 1.0 / scalex;

		for (i = 0; i < count; i++) {
			int r,g,b,a,ia;
			gx = fx*t[0] + fy*t[2] + t[4];
			gy = fx*t[1] + fy*t[3] + t[5];
			gd = sqrt(gx*gx + gy*gy);
			c = cache->colors[static_cast<int>(nsvg__clampf(gd*255.0, 0, 255.0))];
			cr = (c) & 0xff;
			cg = (c >> 8) & 0xff;
			cb = (c >> 16) & 0xff;
			ca = (c >> 24) & 0xff;

			a = nsvg__div255(static_cast<int>(cover[0]) * ca);
			ia = 255 - a;

			// Premultiply
			r = nsvg__div255(cr * a);
			g = nsvg__div255(cg * a);
			b = nsvg__div255(cb * a);

			// Blend over
			r += nsvg__div255(ia * static_cast<int>(dst[0]));
			g += nsvg__div255(ia * static_cast<int>(dst[1]));
			b += nsvg__div255(ia * static_cast<int>(dst[2]));
			a += nsvg__div255(ia * static_cast<int>(dst[3]));

			dst[0] = static_cast<unsigned char>(r);
			dst[1] = static_cast<unsigned char>(g);
			dst[2] = static_cast<unsigned char>(b);
			dst[3] = static_cast<unsigned char>(a);

			cover++;
			dst += 4;
			fx += dx;
		}
	}
}

static void nsvg__rasterizeSortedEdges(NSVGrasterizer *r, double tx, double ty, double scalex, double scaley, NSVGcachedPaint* cache, char fillRule)
{
	NSVGactiveEdge *active = nullptr;
	int y, s;
	int e = 0;
	int maxWeight = (255 / NSVG__SUBSAMPLES);  // weight per vertical scanline
	int xmin, xmax;

	for (y = 0; y < r->height; y++) {
		memset(r->scanline, 0, r->width);
		xmin = r->width;
		xmax = 0;
		for (s = 0; s < NSVG__SUBSAMPLES; ++s) {
			// find center of pixel for this scanline
			double scany = static_cast<double>(y*NSVG__SUBSAMPLES + s) + 0.5;
			NSVGactiveEdge **step = &active;

			// update all active edges;
			// remove all active edges that terminate before the center of this scanline
			while (*step) {
				NSVGactiveEdge *z = *step;
				if (z->ey <= scany) {
					*step = z->next; // delete from list
//					NSVG__assert(z->valid);
					nsvg__freeActive(r, z);
				} else {
					z->x += z->dx; // advance to position for current scanline
					step = &((*step)->next); // advance through list
				}
			}

			// resort the list if needed
			for (;;) {
				int changed = 0;
				step = &active;
				while (*step && (*step)->next) {
					if ((*step)->x > (*step)->next->x) {
						NSVGactiveEdge* t = *step;
						NSVGactiveEdge* q = t->next;
						t->next = q->next;
						q->next = t;
						*step = q;
						changed = 1;
					}
					step = &(*step)->next;
				}
				if (!changed) break;
			}

			// insert all edges that start before the center of this scanline -- omit ones that also end on this scanline
			while (e < r->nedges && r->edges[e].y0 <= scany) {
				if (r->edges[e].y1 > scany) {
					NSVGactiveEdge* z = nsvg__addActive(r, &r->edges[e], scany);
					if (z == nullptr) break;
					// find insertion point
					if (active == nullptr) {
						active = z;
					} else if (z->x < active->x) {
						// insert at front
						z->next = active;
						active = z;
					} else {
						// find thing to insert AFTER
						NSVGactiveEdge* p = active;
						while (p->next && p->next->x < z->x)
							p = p->next;
						// at this point, p->next->x is NOT < z->x
						z->next = p->next;
						p->next = z;
					}
				}
				e++;
			}

			// now process all active edges in non-zero fashion
			if (active != nullptr)
				nsvg__fillActiveEdges(r->scanline, r->width, active, maxWeight, &xmin, &xmax, fillRule);
		}
		// Blit
		if (xmin < 0) xmin = 0;
		if (xmax > r->width-1) xmax = r->width-1;
		if (xmin <= xmax) {
			nsvg__scanlineSolid(&r->bitmap[y * r->stride] + xmin*4, xmax-xmin+1, &r->scanline[xmin], xmin, y, tx,ty, scalex, scaley, cache);
		}
	}

}

static void nsvg__unpremultiplyAlpha(unsigned char* image, int w, int h, int stride)
{
	int x,y;

	// Unpremultiply
	for (y = 0; y < h; y++) {
		unsigned char *row = &image[y*stride];
		for (x = 0; x < w; x++) {
			int r = row[0], g = row[1], b = row[2], a = row[3];
			if (a != 0) {
				row[0] = static_cast<unsigned char>(r*255/a);
				row[1] = static_cast<unsigned char>(g*255/a);
				row[2] = static_cast<unsigned char>(b*255/a);
			}
			row += 4;
		}
	}

	// Defringe
	for (y = 0; y < h; y++) {
		unsigned char *row = &image[y*stride];
		for (x = 0; x < w; x++) {
			int r = 0, g = 0, b = 0, a = row[3], n = 0;
			if (a == 0) {
				if (x-1 > 0 && row[-1] != 0) {
					r += row[-4];
					g += row[-3];
					b += row[-2];
					n++;
				}
				if (x+1 < w && row[7] != 0) {
					r += row[4];
					g += row[5];
					b += row[6];
					n++;
				}
				if (y-1 > 0 && row[-stride+3] != 0) {
					r += row[-stride];
					g += row[-stride+1];
					b += row[-stride+2];
					n++;
				}
				if (y+1 < h && row[stride+3] != 0) {
					r += row[stride];
					g += row[stride+1];
					b += row[stride+2];
					n++;
				}
				if (n > 0) {
					row[0] = static_cast<unsigned char>(r/n);
					row[1] = static_cast<unsigned char>(g/n);
					row[2] = static_cast<unsigned char>(b/n);
				}
			}
			row += 4;
		}
	}
}


static void nsvg__initPaint(NSVGcachedPaint* cache, NSVGpaint* paint, double opacity)
{
	int i, j;
	NSVGgradient* grad;

	cache->type = paint->type;

	if (paint->type == NSVG_PAINT_COLOR) {
		cache->colors[0] = nsvg__applyOpacity(paint->color, opacity);
		return;
	}

	grad = paint->gradient;

	cache->spread = grad->spread;
	memcpy(cache->xform, grad->xform, sizeof(double)*6);

	if (grad->nstops == 0) {
		for (i = 0; i < 256; i++)
			cache->colors[i] = 0;
	} if (grad->nstops == 1) {
		for (i = 0; i < 256; i++)
			cache->colors[i] = nsvg__applyOpacity(grad->stops[i].color, opacity);
	} else {
		unsigned int ca, cb = 0;
		double ua, ub, du, u;
		int ia, ib, count;

		ca = nsvg__applyOpacity(grad->stops[0].color, opacity);
		ua = nsvg__clampf(grad->stops[0].offset, 0, 1);
		ub = nsvg__clampf(grad->stops[grad->nstops-1].offset, ua, 1);
		ia = static_cast<int>(ua * 255.0);
		ib = static_cast<int>(ub * 255.0);
		for (i = 0; i < ia; i++) {
			cache->colors[i] = ca;
		}

		for (i = 0; i < grad->nstops-1; i++) {
			ca = nsvg__applyOpacity(grad->stops[i].color, opacity);
			cb = nsvg__applyOpacity(grad->stops[i+1].color, opacity);
			ua = nsvg__clampf(grad->stops[i].offset, 0, 1);
			ub = nsvg__clampf(grad->stops[i+1].offset, 0, 1);
			ia = static_cast<int>(ua * 255.0);
			ib = static_cast<int>(ub * 255.0);
			count = ib - ia;
			if (count <= 0) continue;
			u = 0;
			du = 1.0 / static_cast<double>(count);
			for (j = 0; j < count; j++) {
				cache->colors[ia+j] = nsvg__lerpRGBA(ca,cb,u);
				u += du;
			}
		}

		for (i = ib; i < 256; i++)
			cache->colors[i] = cb;
	}

}

/*
static void dumpEdges(NSVGrasterizer* r, const char* name)
{
	double xmin = 0, xmax = 0, ymin = 0, ymax = 0;
	NSVGedge *e = nullptr;
	int i;
	if (r->nedges == 0) return;
	FILE* fp = fopen(name, "w");
	if (fp == nullptr) return;

	xmin = xmax = r->edges[0].x0;
	ymin = ymax = r->edges[0].y0;
	for (i = 0; i < r->nedges; i++) {
		e = &r->edges[i];
		xmin = nsvg__minf(xmin, e->x0);
		xmin = nsvg__minf(xmin, e->x1);
		xmax = nsvg__maxf(xmax, e->x0);
		xmax = nsvg__maxf(xmax, e->x1);
		ymin = nsvg__minf(ymin, e->y0);
		ymin = nsvg__minf(ymin, e->y1);
		ymax = nsvg__maxf(ymax, e->y0);
		ymax = nsvg__maxf(ymax, e->y1);
	}

	fprintf(fp, "<svg viewBox=\"%f %f %f %f\" xmlns=\"http://www.w3.org/2000/svg\">", xmin, ymin, (xmax - xmin), (ymax - ymin));

	for (i = 0; i < r->nedges; i++) {
		e = &r->edges[i];
		fprintf(fp ,"<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:#000;\" />", e->x0,e->y0, e->x1,e->y1);
	}

	for (i = 0; i < r->npoints; i++) {
		if (i+1 < r->npoints)
			fprintf(fp ,"<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:#f00;\" />", r->points[i].x, r->points[i].y, r->points[i+1].x, r->points[i+1].y);
		fprintf(fp ,"<circle cx=\"%f\" cy=\"%f\" r=\"1\" style=\"fill:%s;\" />", r->points[i].x, r->points[i].y, r->points[i].flags == 0 ? "#f00" : "#0f0");
	}

	fprintf(fp, "</svg>");
	fclose(fp);
}
*/

void nsvgRasterizeFull(NSVGrasterizer* r,
				   NSVGimage* image, double tx, double ty, double scalex, double scaley,
				   unsigned char* dst, int w, int h, int stride)
{
	NSVGshape *shape = nullptr;
	NSVGedge *e = nullptr;
	NSVGcachedPaint cache;
	int i;

	r->bitmap = dst;
	r->width = w;
	r->height = h;
	r->stride = stride;

	if (w > r->cscanline) {
		r->cscanline = w;
		r->scanline = static_cast<unsigned char*>(realloc(r->scanline, w));
		if (r->scanline == nullptr) return;
	}

	for (i = 0; i < h; i++)
		memset(&dst[i*stride], 0, w*4);

	for (shape = image->shapes; shape != nullptr; shape = shape->next) {
		if (!(shape->flags & NSVG_FLAGS_VISIBLE))
			continue;

		if (shape->fill.type != NSVG_PAINT_NONE) {
			nsvg__resetPool(r);
			r->freelist = nullptr;
			r->nedges = 0;

			nsvg__flattenShape(r, shape, scalex, scaley);

			// Scale and translate edges
			for (i = 0; i < r->nedges; i++) {
				e = &r->edges[i];
				e->x0 = tx + e->x0;
				e->y0 = (ty + e->y0) * NSVG__SUBSAMPLES;
				e->x1 = tx + e->x1;
				e->y1 = (ty + e->y1) * NSVG__SUBSAMPLES;
			}

			// Rasterize edges
			qsort(r->edges, r->nedges, sizeof(NSVGedge), nsvg__cmpEdge);

			// now, traverse the scanlines and find the intersections on each scanline, use non-zero rule
			nsvg__initPaint(&cache, &shape->fill, shape->opacity);

			nsvg__rasterizeSortedEdges(r, tx,ty, scalex, scaley, &cache, shape->fillRule);
		}
		if (shape->stroke.type != NSVG_PAINT_NONE && (shape->strokeWidth * (scalex+scaley)*0.5) > 0.01) {
			nsvg__resetPool(r);
			r->freelist = nullptr;
			r->nedges = 0;

			nsvg__flattenShapeStroke(r, shape, scalex, scaley);

//			dumpEdges(r, "edge.svg");

			// Scale and translate edges
			for (i = 0; i < r->nedges; i++) {
				e = &r->edges[i];
				e->x0 = tx + e->x0;
				e->y0 = (ty + e->y0) * NSVG__SUBSAMPLES;
				e->x1 = tx + e->x1;
				e->y1 = (ty + e->y1) * NSVG__SUBSAMPLES;
			}

			// Rasterize edges
			qsort(r->edges, r->nedges, sizeof(NSVGedge), nsvg__cmpEdge);

			// now, traverse the scanlines and find the intersections on each scanline, use non-zero rule
			nsvg__initPaint(&cache, &shape->stroke, shape->opacity);

			nsvg__rasterizeSortedEdges(r, tx,ty, scalex, scaley, &cache, NSVG_FILLRULE_NONZERO);
		}
	}

	nsvg__unpremultiplyAlpha(dst, w, h, stride);

	r->bitmap = nullptr;
	r->width = 0;
	r->height = 0;
	r->stride = 0;
}

void nsvgRasterize(NSVGrasterizer* r,
					NSVGimage* image, double tx, double ty, double scale,
					unsigned char* dst, int w, int h, int stride)
{
	return nsvgRasterizeFull(r, image, tx, ty, scale, scale, dst, w, h, stride);
}

}

#endif
