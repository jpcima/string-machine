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

#include "OscillatorBlepRect.h"
#include <cstring>

static float _pulse [] =
{
    0.000000,  0.000366,  0.001458,  0.003117,  0.005028,  0.006756,  0.007806,  0.007704,
    0.006086,  0.002778, -0.002139, -0.008292, -0.015022, -0.021434, -0.026492, -0.029153,
    -0.028511, -0.023957, -0.015297, -0.002869,  0.012417,  0.029105,  0.045302,  0.058853,
    0.067578,  0.069533,  0.063273,  0.048113,  0.024337, -0.006682, -0.042487, -0.079654,
    -0.114036, -0.141088, -0.156243, -0.155364, -0.135210, -0.093843, -0.030932,  0.052092,
    0.152049,  0.264172,  0.382359,  0.499585,  0.608450,  0.701808,  0.773391,  0.818353,
    0.833670,  0.818353,  0.773391,  0.701808,  0.608450,  0.499585,  0.382359,  0.264172,
    0.152049,  0.052092, -0.030932, -0.093843, -0.135210, -0.155364, -0.156243, -0.141088,
    -0.114036, -0.079654, -0.042487, -0.006682,  0.024337,  0.048113,  0.063273,  0.069533,
    0.067578,  0.058853,  0.045302,  0.029105,  0.012417, -0.002869, -0.015297, -0.023957,
    -0.028511, -0.029153, -0.026492, -0.021434, -0.015022, -0.008292, -0.002139,  0.002778,
    0.006086,  0.007704,  0.007806,  0.006756,  0.005028,  0.003117,  0.001458,  0.000366,
    0.000000
};

void OscillatorBlepRect::init(double sampleRate)
{
    _fsam = sampleRate;
    clear();
}

void OscillatorBlepRect::clear()
{
    _p = 0.0;
    _x = _y = _z = _d = 0;
    _w = 0;
    _b = 0.5;
    _j = _k = 0;
    memset (_f, 0, (FILLEN + NCOEFF) * sizeof (float));
}

void OscillatorBlepRect::process(float *outp, const float *freq, const float *sync, const float *wavm, unsigned len)
{
    int    i, j, k, n;
    float  a, b, db, d, p, r, t, w, dw, x, y, z, *f;
    float  tsam = 1.0 / _fsam;

    float filt = _filt;
    float wave = _wave;
    float wmod = _wmod;

    --freq;
    --wavm;

    p = _p;
    w = _w;
    b = _b;
    x = _x;
    y = _y;
    z = _z;
    d = _d;
    j = _j;
    k = _k;

    a = 0.2 + 0.8 * filt;
    do
    {
        n = (len > 24) ? 16 : len;
        freq += n;
        wavm += n;
        len -= n;

        t = *freq * tsam;
        if (t < 1e-5) t = 1e-5;
        if (t > 0.5) t = 0.5;
        dw = (t - w) / n;
        t = 0.5 * (1.0 + wave + *wavm * wmod);
        if (t < 0.02) t = 0.02;
        if (t > 0.98) t = 0.98;
        db = (t - b) / n;

        while (n--)
        {
            w += dw;
            b += db;
            p += w;
            t = k ? 1.0 : b;
            while (p >= t)
            {
                if (k)
                {
                    k = 0;
                    p -= 1.0;
                    r = NPHASE * p / w;
                    t = b;
                    i = (int) r;
                    r -= i;
                    f = _f + j;
                    while (i < NPHASE * NCOEFF)
                    {
                        *f++ += r * _pulse [i + 1 ] + (1 - r) * _pulse [i];
                        i += NPHASE;
                    }
                }
                else
                {
                    k = 1;
                    r = NPHASE * (p - t) / w;
                    t = 1.0;
                    i = (int) r;
                    r -= i;
                    f = _f + j;
                    while (i < NPHASE * NCOEFF)
                    {
                        *f++ -= r * _pulse [i + 1 ] + (1 - r) * _pulse [i];
                        i += NPHASE;
                    }
                }
            }
            x -= w * (0.01 * y + 0.2 * x);
            x += _f [j];
            y += 6.3 * w * x;
            z += a * (x - z);
            *outp++ = z;
            d += 0.01 * (y * *sync++ - d);
            if (++j == FILLEN)
            {
                j = 0;
                memcpy (_f, _f + FILLEN, NCOEFF * sizeof (float));
                memset (_f + NCOEFF, 0,  FILLEN * sizeof (float));
            }
        }
    }
    while (len);

    _p = p;
    _w = w;
    _b = b;
    _x = x;
    _y = y;
    _z = z;
    _d = d;
    _j = j;
    _k = k;
}

void OscillatorBlepRect::process(float *outp, const float *freq, const float *sync, unsigned len)
{
    int    i, j, k, n;
    float  a, b, db, d, p, r, t, w, dw, x, y, z, *f;
    float  tsam = 1.0 / _fsam;

    float filt = _filt;
    float wave = _wave;
    float wmod = _wmod;

    constexpr float wavm = 0.0;

    --freq;

    p = _p;
    w = _w;
    b = _b;
    x = _x;
    y = _y;
    z = _z;
    d = _d;
    j = _j;
    k = _k;

    a = 0.2 + 0.8 * filt;
    do
    {
        n = (len > 24) ? 16 : len;
        freq += n;
        len -= n;

        t = *freq * tsam;
        if (t < 1e-5) t = 1e-5;
        if (t > 0.5) t = 0.5;
        dw = (t - w) / n;
        t = 0.5 * (1.0 + wave + wavm * wmod);
        if (t < 0.02) t = 0.02;
        if (t > 0.98) t = 0.98;
        db = (t - b) / n;

        while (n--)
        {
            w += dw;
            b += db;
            p += w;
            t = k ? 1.0 : b;
            while (p >= t)
            {
                if (k)
                {
                    k = 0;
                    p -= 1.0;
                    r = NPHASE * p / w;
                    t = b;
                    i = (int) r;
                    r -= i;
                    f = _f + j;
                    while (i < NPHASE * NCOEFF)
                    {
                        *f++ += r * _pulse [i + 1 ] + (1 - r) * _pulse [i];
                        i += NPHASE;
                    }
                }
                else
                {
                    k = 1;
                    r = NPHASE * (p - t) / w;
                    t = 1.0;
                    i = (int) r;
                    r -= i;
                    f = _f + j;
                    while (i < NPHASE * NCOEFF)
                    {
                        *f++ -= r * _pulse [i + 1 ] + (1 - r) * _pulse [i];
                        i += NPHASE;
                    }
                }
            }
            x -= w * (0.01 * y + 0.2 * x);
            x += _f [j];
            y += 6.3 * w * x;
            z += a * (x - z);
            *outp++ = z;
            d += 0.01 * (y * *sync++ - d);
            if (++j == FILLEN)
            {
                j = 0;
                memcpy (_f, _f + FILLEN, NCOEFF * sizeof (float));
                memset (_f + NCOEFF, 0,  FILLEN * sizeof (float));
            }
        }
    }
    while (len);

    _p = p;
    _w = w;
    _b = b;
    _x = x;
    _y = y;
    _z = z;
    _d = d;
    _j = j;
    _k = k;
}

void OscillatorBlepRect::process(float *outp, const float *freq, unsigned len)
{
    int    i, j, k, n;
    float  a, b, db, d, p, r, t, w, dw, x, y, z, *f;
    float  tsam = 1.0 / _fsam;

    float filt = _filt;
    float wave = _wave;
    float wmod = _wmod;

    constexpr float sync = 0.0;
    constexpr float wavm = 0.0;

    --freq;

    p = _p;
    w = _w;
    b = _b;
    x = _x;
    y = _y;
    z = _z;
    d = _d;
    j = _j;
    k = _k;

    a = 0.2 + 0.8 * filt;
    do
    {
        n = (len > 24) ? 16 : len;
        freq += n;
        len -= n;

        t = *freq * tsam;
        if (t < 1e-5) t = 1e-5;
        if (t > 0.5) t = 0.5;
        dw = (t - w) / n;
        t = 0.5 * (1.0 + wave + wavm * wmod);
        if (t < 0.02) t = 0.02;
        if (t > 0.98) t = 0.98;
        db = (t - b) / n;

        while (n--)
        {
            w += dw;
            b += db;
            p += w;
            t = k ? 1.0 : b;
            while (p >= t)
            {
                if (k)
                {
                    k = 0;
                    p -= 1.0;
                    r = NPHASE * p / w;
                    t = b;
                    i = (int) r;
                    r -= i;
                    f = _f + j;
                    while (i < NPHASE * NCOEFF)
                    {
                        *f++ += r * _pulse [i + 1 ] + (1 - r) * _pulse [i];
                        i += NPHASE;
                    }
                }
                else
                {
                    k = 1;
                    r = NPHASE * (p - t) / w;
                    t = 1.0;
                    i = (int) r;
                    r -= i;
                    f = _f + j;
                    while (i < NPHASE * NCOEFF)
                    {
                        *f++ -= r * _pulse [i + 1 ] + (1 - r) * _pulse [i];
                        i += NPHASE;
                    }
                }
            }
            x -= w * (0.01 * y + 0.2 * x);
            x += _f [j];
            y += 6.3 * w * x;
            z += a * (x - z);
            *outp++ = z;
            d += 0.01 * (y * sync - d);
            if (++j == FILLEN)
            {
                j = 0;
                memcpy (_f, _f + FILLEN, NCOEFF * sizeof (float));
                memset (_f + NCOEFF, 0,  FILLEN * sizeof (float));
            }
        }
    }
    while (len);

    _p = p;
    _w = w;
    _b = b;
    _x = x;
    _y = y;
    _z = z;
    _d = d;
    _j = j;
    _k = k;
}

void OscillatorBlepRect::process(float *outp, float freq, unsigned len)
{
    int    i, j, k, n;
    float  a, b, db, d, p, r, t, w, dw, x, y, z, *f;
    float  tsam = 1.0 / _fsam;

    float filt = _filt;
    float wave = _wave;
    float wmod = _wmod;

    constexpr float sync = 0.0;
    constexpr float wavm = 0.0;

    p = _p;
    w = _w;
    b = _b;
    x = _x;
    y = _y;
    z = _z;
    d = _d;
    j = _j;
    k = _k;

    a = 0.2 + 0.8 * filt;
    do
    {
        n = (len > 24) ? 16 : len;
        len -= n;

        t = freq * tsam;
        if (t < 1e-5) t = 1e-5;
        if (t > 0.5) t = 0.5;
        dw = (t - w) / n;
        t = 0.5 * (1.0 + wave + wavm * wmod);
        if (t < 0.02) t = 0.02;
        if (t > 0.98) t = 0.98;
        db = (t - b) / n;

        while (n--)
        {
            w += dw;
            b += db;
            p += w;
            t = k ? 1.0 : b;
            while (p >= t)
            {
                if (k)
                {
                    k = 0;
                    p -= 1.0;
                    r = NPHASE * p / w;
                    t = b;
                    i = (int) r;
                    r -= i;
                    f = _f + j;
                    while (i < NPHASE * NCOEFF)
                    {
                        *f++ += r * _pulse [i + 1 ] + (1 - r) * _pulse [i];
                        i += NPHASE;
                    }
                }
                else
                {
                    k = 1;
                    r = NPHASE * (p - t) / w;
                    t = 1.0;
                    i = (int) r;
                    r -= i;
                    f = _f + j;
                    while (i < NPHASE * NCOEFF)
                    {
                        *f++ -= r * _pulse [i + 1 ] + (1 - r) * _pulse [i];
                        i += NPHASE;
                    }
                }
            }
            x -= w * (0.01 * y + 0.2 * x);
            x += _f [j];
            y += 6.3 * w * x;
            z += a * (x - z);
            *outp++ = z;
            d += 0.01 * (y * sync - d);
            if (++j == FILLEN)
            {
                j = 0;
                memcpy (_f, _f + FILLEN, NCOEFF * sizeof (float));
                memset (_f + NCOEFF, 0,  FILLEN * sizeof (float));
            }
        }
    }
    while (len);

    _p = p;
    _w = w;
    _b = b;
    _x = x;
    _y = y;
    _z = z;
    _d = d;
    _j = j;
    _k = k;
}
