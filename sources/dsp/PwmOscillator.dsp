import("stdfaust.lib");

process(f) = os.pulsetrain(f, d) with {
  md = hslider("Mod depth [unit:%] [symbol:mod_depth]", 75.0, 0.0, 100.0, 1.0) : *(0.01);
  mf = hslider("Mod frequency [unit:Hz] [scale:log] [symbol:mod_frequency]", 0.25, 0.1, 5.0, 0.01);
  // d = lfo * md + 0.5 * (1.0 - md);
  d = d1 + lfo * md * (d2 - d1) with { d1 = 0.1; d2 = 0.5; };
  lfo = os.lf_trianglepos(mf);
};
