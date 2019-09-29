import("stdfaust.lib");

process = no.lfnoise(f) with {
  f = hslider("[1] Frequency [symbol:frequency] [unit:Hz]", 1.0, 0.0, 100.0, 1.0);
};
