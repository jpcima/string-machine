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

/*
# GNUplot code of the waveshaping function

# asymmetric soft clipping waveshaper
# k: the curve control parameter (0 excl. to 1)

set key right bottom

cubic(x)=(x*x*x/3)
lm(k)=-sqrt(k*k*k)/(k*k*k) # the local minimum

kubic(k,x)=x-cubic(k*x)
max(a,b)=(a>b)?a:b
nl(k,x)=(x>0)?x:kubic(k,max(x,lm(k)))

z=2./3.;
nl2(k,x)=nl(k,x-z)+z

set xrange [-1:+1]
plot nl2(0.1,x) t "0.1", \
     nl2(0.2,x) t "0.2", \
     nl2(0.3,x) t "0.3", \
     nl2(0.4,x) t "0.4", \
     nl2(0.5,x) t "0.5", \
     nl2(0.6,x) t "0.6", \
     nl2(0.7,x) t "0.7", \
     nl2(0.8,x) t "0.8", \
     nl2(0.9,x) t "0.9", \
     nl2(1.0,x) t "1.0"
*/
