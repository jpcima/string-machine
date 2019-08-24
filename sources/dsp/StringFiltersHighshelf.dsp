import("stdfaust.lib");
msp = library("maxmsp.lib");

process(x) = msp.highShelf(x, cutoff, gain, 1./sqrt(2.)) with {
  cutoff = hslider("[1]Cutoff [unit:Hz] [scale:log] [symbol:cutoff]", 1000., 10., 10000., 1.);
  gain = hslider("[2]Gain [unit:dB] [symbol:gain]", 3., 1., 10., 0.1);
};
