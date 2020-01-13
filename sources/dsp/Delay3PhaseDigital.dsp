import("stdfaust.lib");
msp = library("maxmsp.lib");

process(input, mod1, mod2, mod3) = L, R, Mono with {
  L = line1 + line2 - line3;
  R = line1 - line2 - line3;
  Mono = line1 + line2 + line3;

  line1 = aaInput : line(mod1);
  line2 = aaInput : line(mod2);
  line3 = aaInput : line(mod3);

  aaInput = input : antiAlias;

  line(mod) = de.fdelayltv(1, delaybufsize, delay) with {
    delaybufsize = int(ceil(50e-3 * ma.SR));
    delay = (5e-3 + (1e-3 * mod)) * ma.SR;
  };
};

antiAlias = lpf1 : lpf2 : lpf3 with {
  cutoff1 = ba.midikey2hz(122.3);
  cutoff2 = ba.midikey2hz(122.3);
  cutoff3 = ba.midikey2hz(113.5);

  q1 = resonance(0.66);
  q2 = resonance(0.66);
  q3 = resonance(0.54);

  resonance(r) = 1. / (2. - 2. * r);

  lpf1(x) = msp.LPF(x, cutoff1, 0, q1);
  lpf2(x) = msp.LPF(x, cutoff2, 0, q2);
  lpf3(x) = msp.LPF(x, cutoff3, 0, q3);
};
