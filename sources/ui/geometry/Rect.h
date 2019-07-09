//          Copyright Jean Pierre Cimalando 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE.md or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#include "Point.h"
#include <algorithm>
#include <iostream>

template <class T> class RectT;
typedef RectT<int> Rect;
typedef RectT<double> RectF;

template <class T> struct Rect_Traits;

//------------------------------------------------------------------------------
template <class T>
class RectT : public Rect_Traits<T>::storage_type {
public:
    typedef typename Rect_Traits<T>::storage_type storage_type;

    RectT() : storage_type{} {}
    RectT(storage_type s) : storage_type(s) {}
    RectT(T x, T y, T w, T h) : storage_type{x, y, w, h} {}

    template <class U> RectT<U> to() const {
        return RectT<U>(T(this->x), T(this->y), T(this->w), T(this->h));
    }

    T top() const { return this->y; }
    T left() const { return this->x; }
    T bottom() const { return this->y + this->h - 1; }
    T right() const { return this->x + this->w - 1; }
    T xcenter() const { return this->x + (this->w - 1) / 2; }
    T ycenter() const { return this->y + (this->h - 1) / 2; }
    PointT<T> origin() const { return {this->x, this->y}; }
    PointT<T> size() const { return {this->w, this->h}; }
    RectT<T> intersect(const RectT<T> &r) const {
        RectT<T> ri;
        ri.x = std::max(this->x, r.x);
        ri.y = std::max(this->y, r.y);
        ri.w = std::min(this->right(), r.right()) - ri.x + 1;
        ri.h = std::min(this->bottom(), r.bottom()) - ri.y + 1;
        return ri;
    }
    RectT<T> unite(const RectT<T> &r) const {
        RectT<T> ri;
        ri.x = std::min(this->x, r.x);
        ri.y = std::min(this->y, r.y);
        ri.w = std::max(this->right(), r.right()) - ri.x + 1;
        ri.h = std::max(this->bottom(), r.bottom()) - ri.y + 1;
        return ri;
    }
    RectT<T> from_top(T q) const {
        return RectT<T>(this->x, this->y, this->w, q);
    }
    RectT<T> from_bottom(T q) const {
        return RectT<T>(this->x, this->y + this->h - q, this->w, q);
    }
    RectT<T> from_left(T q) const {
        return RectT<T>(this->x, this->y, q, this->h);
    }
    RectT<T> from_right(T q) const {
        return RectT<T>(this->x + this->w - q, this->y, q, this->h);
    }
    RectT<T> take_from_top(T q) {
        RectT<T> r = from_top(q);
        this->y += q;
        this->h -= q;
        return r;
    }
    RectT<T> take_from_bottom(T q) {
        RectT<T> r = from_bottom(q);
        this->h -= q;
        return r;
    }
    RectT<T> take_from_left(T q) {
        RectT<T> r = from_left(q);
        this->x += q;
        this->w -= q;
        return r;
    }
    RectT<T> take_from_right(T q) {
        RectT<T> r = from_right(q);
        this->w -= q;
        return r;
    }
    RectT<T> &chop_from_top(T q) {
        take_from_top(q);
        return *this;
    }
    RectT<T> &chop_from_bottom(T q) {
        take_from_bottom(q);
        return *this;
    }
    RectT<T> &chop_from_left(T q) {
        take_from_left(q);
        return *this;
    }
    RectT<T> &chop_from_right(T q) {
        take_from_right(q);
        return *this;
    }
    RectT<T> from_center(T qx, T qy) {
        return RectT<T>(
            this->x + (this->w - qx) / 2, this->y + (this->h - qy) / 2, qx, qy);
    }
    RectT<T> from_hcenter(T q) {
        return RectT<T>(this->x + (this->w - q) / 2, this->y, q, this->h);
    }
    RectT<T> from_vcenter(T q) {
        return RectT<T>(this->x, this->y + (this->h - q) / 2, this->w, q);
    }
    RectT<T> repositioned(const PointT<T> &p) const {
        return RectT<T>(p.x, p.y, this->w, this->h);
    }
    RectT<T> resized(const PointT<T> &p) const {
        return RectT<T>(this->x, this->y, p.x, p.y);
    }
    RectT<T> off_by(const PointT<T> &p) const {
        return RectT<T>(this->x + p.x, this->y + p.y, this->w, this->h);
    }
    RectT<T> expanded(const PointT<T> &p) const {
        return RectT<T>(this->x - p.x, this->y - p.y,
                        this->w + 2 * p.x, this->h + 2 * p.y);
    }
    RectT<T> expanded(T q) const {
        return expanded(PointT<T>(q, q));
    }
    RectT<T> reduced(const PointT<T> &p) const {
        return expanded(PointT<T>(-p.x, -p.y));
    }
    RectT<T> reduced(T q) const {
        return expanded(-q);
    }
};

//------------------------------------------------------------------------------
template <class T> struct Rect_Traits {
    struct storage_type { T x, y, w, h; };
};

//------------------------------------------------------------------------------
template <class T, class Ch>
std::basic_ostream<Ch> &operator<<(std::basic_ostream<Ch> &o, const RectT<T> &r) {
    return o << "{" << r.x << ", " << r.y << ", " << r.w << ", " << r.h << "}";
}
