#ifdef OBE_IS_NOT_PLUGIN
#define GLOBE(TYPE, NAME) inline TYPE NAME;
#define GLOBE_GET(NAME) &NAME
#define GLOBE_SYM
#else
#define GLOBE(TYPE, NAME) inline TYPE* NAME ## _PTR = nullptr; inline TYPE& NAME = *NAME ## _PTR;
#define GLOBE_GET(NAME) &NAME ## _PTR
#define GLOBE_SYM *
#endif