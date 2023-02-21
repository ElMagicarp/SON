import("stdfaust.lib");

main = fi.low_shelf(lowLevel,400):fi.high_shelf(highLevel,8000): *(gain)
with{
    main(x) = hgroup("FUN MIX",x);
    lowLevel = main(hslider("Low",0,-40,40,0.1));
    highLevel = main(hslider("High",0,-40,40,.1));
    gain = main(hslider("Volume",0.5,0,1,.1));
};

process = main:>ef.echo1s <:dm.freeverb_demo;
