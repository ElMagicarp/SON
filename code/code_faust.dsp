import("stdfaust.lib");
main = fi.low_shelf(lowLevel,200) : fi.high_shelf(highLevel,8000)
with{
    main(x) = hgroup("FUN MIX",x);
    lowLevel = main(hslider("Low",0,-40,40,0.1));
    highLevel = main(hslider("High",0,-40,40,.1));
};

process = main;
