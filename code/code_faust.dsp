import("stdfaust.lib");

equalizer = fi.high_shelf(midLevel,200):fi.low_shelf(lowLevel,200):fi.high_shelf(highLevel-midLevel,8000)
with{
    equalizer(x) = hgroup("Equalizer",x);
    lowLevel = equalizer(hslider("low",0,-40,40,0.1));
    highLevel = equalizer(hslider("high",0,-40,40,.1));
    midLevel = equalizer(hslider("mid",0,-40,40,.1));
};

transp(w, x, s, sig) = de.delay(maxDelay,d,sig)*ma.fmin(d/x,1) + de.delay(maxDelay,d+w,sig)*(1-ma.fmin(d/x,1))
with {
	maxDelay = 3001;
	i = 1 - pow(2, s/12);
	d = i : (+ : +(w) : fmod(_,w)) ~ _;
};

pitchShift = transp(1000,100,hslider("shift", 0, -50, +50, 1));
delay = hslider("echoDelay", 0, 0, 1000, 10);
feedback = hslider("echoFeedback", 0.5, 0, 1, 0.1);
myEcho  = vgroup("echo", +~(de.delay(2000, int(delay*ba.millisec)-1) * feedback));
gain = hslider("volume",0.5,0,1,.1);

main = equalizer:myEcho:pitchShift: *(gain);

process = par(i,2,main);
