import("stdfaust.lib");

process = lfo.output with {
  numPhases = 3;
  lfo = lfoDual(numPhases, f1, f2, d1, d2, ctl.pout1, ctl.pout2);
  ctl = environment {
    f1 = hslider("[1] Rate 1 [symbol:rate1] [unit:Hz]", 6.0, 3.0, 9.0, 0.01);
    d1 = hslider("[2] Depth 1 [symbol:depth1] [unit:%]", 50, 0, 100, 1);
    f2 = hslider("[3] Rate 2 [symbol:rate2] [unit:Hz]", 0.6, 0.3, 0.9, 0.01);
    d2 = hslider("[4] Depth 2 [symbol:depth2] [unit:%]", 50, 0, 100, 1);
    gd = hslider("[5] Global Depth [symbol:globaldepth] [unit:%]", 100, 0, 100, 1);
    pout1 = vbargraph("[6] Phase 1 [symbol:phase1]", 0.0, 1.0);
    pout2 = vbargraph("[7] Phase 2 [symbol:phase2]", 0.0, 1.0);
  };
  f1 = ctl.f1 : tsmooth;
  f2 = ctl.f2 : tsmooth;
  d1 = (ctl.d1 * ctl.gd * 0.0001) : tsmooth;
  d2 = (ctl.d2 * ctl.gd * 0.0001) : tsmooth;
};

tsmooth = si.smooth(ba.tau2pole(t)) with { t = 100e-3; };

lfoDual(N, f1, f2, d1, d2, pout1, pout2) = environment {
  row1 = lfoRow(N, f1, d1);
  row2 = lfoRow(N, f2, d2);
  output = par(i, N, row1LfoOutput(i) + row2LfoOutput(i));
  row1LfoOutput(i) = attach(row1.lfos(i), row1.phases(0) : pout1);
  row2LfoOutput(i) = attach(row2.lfos(i), row2.phases(0) : pout2);
};

lfoRow(N, f, d) = environment {
  phases(i) = phasor(f) : +(startPhases(i)) : wrap;
  startPhases(i) = float(i)/float(N);
  lfos(i) = phases(i) : wave : *(d);
  wave = smallTableSin;
  //wave = approxSin;
};

phasor(f) = p letrec { 'p = wrap(p + f/ma.SR); };

wrap = _ <: (_, int) :> -;
sqr = _ <: (_, _) :> *;

approxSin(pos) = 1.0-2.0*(sqr(sqr(wrap(pos+root)*2.0-1.0)-1.0)) with {
  root = 0.25*(2.0+sqrt(4.0-2.0*sqrt(2.0)));
};

smallTableSin(pos) = lerp(tab, pos, ts) with {
  ts = 128;
  tab(i) = rdtable(ts, os.sinwaveform(ts), i);
};

lerp(tab, pos, size) = (tab(i1), tab(i2)) : si.interpolate(mu) with {
  fracIndex = pos*size;
  i1 = int(fracIndex);
  i2 = (i1+1)%size;
  mu = fracIndex-float(i1);
};
