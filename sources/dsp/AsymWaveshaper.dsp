import("stdfaust.lib");

asymclip(k, x) = nl(k,x-z)+z with {
  cubic(x) = x*x*x/3.;
  lm(k) = -1.*sqrt(k*k*k)/(k*k*k); // the local minimum

  kubic(k,x) = x-cubic(k*x);
  nl(k,x)=ba.if(x>0,x,kubic(k,max(x,lm(k))));

  z = 2./3.;
};

process = asymclip(k) : fi.dcblockerat(35.) with {
  k = hslider("[1] Clipping amount [symbol:amount]", 1.0, 0.1, 1.0, 0.01);
};
