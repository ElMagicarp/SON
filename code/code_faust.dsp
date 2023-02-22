import("stdfaust.lib");
main = fi.low_shelf(lowLevel,400):fi.high_shelf(highLevel,8000): *(gain)
with{
    main(x) = hgroup("FUN MIX",x);
    lowLevel = main(hslider("low",0,-40,40,0.1));
    highLevel = main(hslider("high",0,-40,40,.1));
    gain = main(hslider("volume",0.5,0,1,.1));
};
pitchShift = ef.transpose(1000,10,hslider("shift", 0, -12, +12, 0.1));
delay = hslider("delay", 0, 0, 1000, 10);


process = + ~ (@(delay)*(0.75)), (main:pitchShift);
