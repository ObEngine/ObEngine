Define Flag (Particle);
Define Flag (Lock);

Particles:
    //Bases
    {@}rainbowColor
        r:"(sin@(t))^2 * 255"
        g:"(sin@(t+pi/2))^2 * 255"
        b:"(sin@(t+pi/4))^2 * 255"
        a:"255"
    {@}infiniteBound
        lowerBound:"0"
        upperBound:"t+1"
    {@}baseParticle
        size:"5"
        lifetime:"-1"
        precision:0.01
    //Particles
    @rainbowSine
        size:2
        x:"sin@(t/10) * 1920 - i"
        y:"500 + (cos@(t * 5 + i/100) * 40)"
        lowerBound:"0"
        upperBound:"t+1"
        r:"abs@(cos@(t*3+i/90)) * 255"
        g:"abs@(cos@(t*6+i/60)) * 255"
        b:"abs@(cos@(t*9+i/30)) * 255"
        a:"255"
        lifetime:"-1"
        trailLength:"20"
        precision:0.03
    @heartCurve:rainbowColor,infiniteBound,baseParticle
        x:"(16*(sin@(t - (precision*i)))^3) * size + offsetX + (rand * diffusion)"
        y:"((13*cos@(t - (precision*i)) - 5*cos@(2*t - (precision*i)) - 2*cos@(3*t - (precision*i)) - cos@(4*t - (precision*i))) * size) * (-1) + offsetY + (rand * diffusion)"
        trailLength:"500"
        trailAlpha:"1.007"
    @heartCurveInverted:rainbowColor,infiniteBound,baseParticle
        x:"(16*(sin@(t))^3) * size + offsetX + (rand * diffusion)"
        y:"((13*cos@(t) - 5*cos@(2*t) - 2*cos@(3*t) - cos@(4*t)) * size) + offsetY + (rand * diffusion)"
        trailLength:"500"
        trailAlpha:"1.007"
    @circle:rainbowColor,infiniteBound,baseParticle
        x:"cos@(t+(pi*delay)) * csize + offsetX"
        y:"sin@(t+(pi*delay)) * csize + offsetY"
        trailLength:"500"
        trailAlpha:"1.007"
    @playerTrail:infiniteBound,rainbowColor
        size:2
        x:"offsetX + 130"
        y:"offsetY + 170"
        lifetime:"-1"
        trailLength:"500"
        trailAlpha:"1.007"
        precision:0.01
    @thirdDParabole:rainbowColor
        size:"2"
        x:"(16*(cos@(t - (precision*rand*2)))^3) * 5 + 500"
        y:"(13*cos@(t - (precision * rand)) - 5*cos@(2*t) - 2*cos@(3*t) - cos@(4*t)) * 5 + 500"
        lowerBound:"0"
        upperBound:"t+1"
        a:"255"
        lifetime:"-1"
        trailLength:"600"
        trailAlpha:"1.004"
        precision:0.01
    @refractingNova:rainbowColor
        size:"2"
        x:"sin@(t-(precision*t*20)) * (i/t) + 500"
        y:"cos@(t-(precision*t*20)) * (i/t) + 500"
        lowerBound:"0"
        upperBound:"t+1"
        a:"255"
        lifetime:"-1"
        trailLength:"500"
        trailAlpha:"1.003"
        precision:0.01
    @spirograph:baseParticle,rainbowColor,infiniteBound
        x:"(R-r)*cos@(t) + p*cos@((R-r)*t/r) + 500"
        y:"(R-r)*sin@(t) - p*sin@((R-r)*t/r) + 500"
        trailAlpha:"1.002"
        trailLength:"600"
    @testLel
        x:"sin@(t/10) * 1920 - i"
        y:"500 + (cos@(t * 5 + i/100) * 40)"
        r:"(sin@(t - i*precision*t))^2 * 255"
        g:"(sin@(t+pi/2 - i*precision*t))^2 * 255"
        b:"(sin@(t+pi/4 - i*precision*t))^2 * 255"
        a:"255"
        lifetime:"-1"
        trailLength:"20"
        precision:0.03
    @testLol
        size:2
        x:"(7*((sin@(7.32*t))/(1+cos@(1.42*t)^2)))"
        y:"(7 * cos@(1.42*t) * sin@(7.32*t)^4)"
        lowerBound:"-3"
        upperBound:"3"
        r:"(sin@(t))^2 * 255"
        g:"(sin@(t+pi/2))^2 * 255"
        b:"(sin@(t+pi/4))^2 * 255"
        a:"255"
        lifetime:"-1"
        trailLength:"400"
        trailAlpha:"1.004"
        precision:0.01
    @rectangleTest
        size:2
        x:"(bound@(t,lowerBound,lowerBound/2) * (t) + bound@(t,0,upperBound/2) * (squareSize-t)) + offsetX"
        y:"(bound@(t,lowerBound/2,0) * (t) + bound@(t,upperBound/2,upperBound) * (squareSize-t)) + offsetY"
        lowerBound:"-squareSize"
        upperBound:"squareSize"
        r:"(sin@(t))^2 * 255"
        g:"(sin@(t+pi/2))^2 * 255"
        b:"(sin@(t+pi/4))^2 * 255"
        a:"255"
        lifetime:"-1"
        trailLength:"400"
        trailAlpha:"1.004"
        precision:0.01
    @sinPhys
        size:2
        x:"t*freq"
        y:"10*sin@(t)*15 + 500"
        lowerBound:"0"
        upperBound:"1920/freq"
        r:"255"
        g:"0"
        b:"0"
        a:"255"
        lifetime:"-1"
        trailLength:"2000"
        trailAlpha:"1.007"
        precision:0.01
    @missa
        size:2
        x:"t"
        y:"bound@(t,-1,0)*(round@(x)-x+ceil@(x)-x)+bound@(t,0,1)*((round@(x)-x+ceil@(x)-x)*-1)"
        lowerBound:"-1"
        upperBound:"1"
        r:"255"
        g:"0"
        b:"0"
        lifetime:"-1"
        trailLength:"2000"
        trailAlpha:"1.003"
        precision:0.01
        