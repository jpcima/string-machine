// SPDX-License-Identifier: GPL-2.0-or-later
/*
  Copyright (C) 2019 Jean Pierre Cimalando

  Adapted from vco-plugins source code
*/
/*
  Copyright (C) 2003 Fons Adriaensen

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#pragma once

class OscillatorBlepRect {
public:
    void init(double sampleRate);
    void clear();
    void process(float *outp, const float *freq, const float *sync, const float *wavm, unsigned len);
    void process(float *outp, const float *freq, const float *sync, unsigned len);
    void process(float *outp, const float *freq, unsigned len);
    void process(float *outp, float freq, unsigned len);

private:
    enum { NPHASE = 8, NCOEFF = 12, FILLEN = 256 };

    float   _fsam;
    float   _p, _w, _b, _x, _y, _z, _d;
    float   _f [FILLEN + NCOEFF];
    int     _j, _k;

    float _filt = 1.0;
    float _wave = 0.0;
    float _wmod = 0.0;
};
