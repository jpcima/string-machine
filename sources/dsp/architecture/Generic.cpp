//------------------------------------------------------------------------------
// This file was generated using the Faust compiler (https://faust.grame.fr),
// and the Faust post-processor (https://github.com/jpcima/faustpp).
//
// Source: {{file_name}}
// Name: {{name}}
// Author: {{author}}
// Copyright: {{copyright}}
// License: {{license}}
// Version: {{version}}
//------------------------------------------------------------------------------

#include "{{Identifier}}.hpp"
#include <cmath>

class {{Identifier}}::BasicDsp {
public:
    virtual ~BasicDsp() {}
};

//------------------------------------------------------------------------------
// Begin the Faust code section

namespace {

template <class T> inline T min(T a, T b) { return (a < b) ? a : b; }
template <class T> inline T max(T a, T b) { return (a > b) ? a : b; }

class Meta {
public:
    // dummy
    void declare(...) {}
};

class UI {
public:
    // dummy
    void openHorizontalBox(...) {}
    void openVerticalBox(...) {}
    void closeBox(...) {}
    void declare(...) {}
    void addButton(...) {}
    void addCheckButton(...) {}
    void addVerticalSlider(...) {}
    void addHorizontalSlider(...) {}
    void addVerticalBargraph(...) {}
};

typedef {{Identifier}}::BasicDsp dsp;

} // namespace

#define FAUSTPP_VIRTUAL // do not declare any methods virtual
#define FAUSTPP_PRIVATE public // do not hide any members
#define FAUSTPP_PROTECTED public // do not hide any members

// define the DSP in the anonymous namespace
#define FAUSTPP_BEGIN_NAMESPACE namespace {
#define FAUSTPP_END_NAMESPACE }

{{class_code}}

//------------------------------------------------------------------------------
// End the Faust code section

{{Identifier}}::{{Identifier}}()
    : fDsp(new {{class_name}})
{
    {{class_name}} &dsp = static_cast<{{class_name}} &>(*fDsp);
    dsp.instanceResetUserInterface();
}

{{Identifier}}::~{{Identifier}}()
{
}

void {{Identifier}}::init(float sample_rate)
{
    {{class_name}} &dsp = static_cast<{{class_name}} &>(*fDsp);
    dsp.classInit(sample_rate);
    dsp.instanceConstants(sample_rate);
    dsp.instanceClear();
}

void {{Identifier}}::clear() noexcept
{
    {{class_name}} &dsp = static_cast<{{class_name}} &>(*fDsp);
    dsp.instanceClear();
}

void {{Identifier}}::process(
    {% for i in range(inputs) %}const float *in{{i}},{% endfor %}
    {% for i in range(outputs) %}float *out{{i}},{% endfor %}
    unsigned count) noexcept
{
    {{class_name}} &dsp = static_cast<{{class_name}} &>(*fDsp);
    float *inputs[] = {
        {% for i in range(inputs) %}const_cast<float *>(in{{i}}),{% endfor %}
    };
    float *outputs[] = {
        {% for i in range(outputs) %}out{{i}},{% endfor %}
    };
    dsp.compute(count, inputs, outputs);
}

const char *{{Identifier}}::parameter_label(unsigned index) noexcept
{
    switch (index) {
    {% for w in active %}
    case {{loop.index}}:
        return {{cstr(w.label)}};
    {% endfor %}
    default:
        return 0;
    }
}

const char *{{Identifier}}::parameter_short_label(unsigned index) noexcept
{
    switch (index) {
    {% for w in active %}
    case {{loop.index}}:
        return {{cstr(default(w.meta.abbrev,""))}};
    {% endfor %}
    default:
        return 0;
    }
}

const char *{{Identifier}}::parameter_symbol(unsigned index) noexcept
{
    switch (index) {
    {% for w in active %}
    case {{loop.index}}:
        return {{cstr(cid(default(w.meta.symbol,w.label)))}};
    {% endfor %}
    default:
        return 0;
    }
}

const char *{{Identifier}}::parameter_unit(unsigned index) noexcept
{
    switch (index) {
    {% for w in active %}
    case {{loop.index}}:
        return {{cstr(w.unit)}};
    {% endfor %}
    default:
        return 0;
    }
}

const {{Identifier}}::ParameterRange *{{Identifier}}::parameter_range(unsigned index) noexcept
{
    switch (index) {
    {% for w in active %}
    case {{loop.index}}: {
        static const ParameterRange range = { {{w.init}}, {{w.min}}, {{w.max}} };
        return &range;
    }
    {% endfor %}
    default:
        return 0;
    }
}

bool {{Identifier}}::parameter_is_trigger(unsigned index) noexcept
{
    switch (index) {
    {% for w in active %}{% if (w.type == "button" or existsIn(w.meta, "trigger")) %}
    case {{loop.index}}:
        return true;
    {% endif %}{% endfor %}
    default:
        return false;
    }
}

bool {{Identifier}}::parameter_is_boolean(unsigned index) noexcept
{
    switch (index) {
    {% for w in active %}{% if (w.type == "button" or w.type == "checkbox") or existsIn(w.meta, "boolean") %}
    case {{loop.index}}:
        return true;
    {% endif %}{% endfor %}
    default:
        return false;
    }
}

bool {{Identifier}}::parameter_is_integer(unsigned index) noexcept
{
    switch (index) {
    {% for w in active %}{% if (w.type == "button" or w.type == "checkbox") or (existsIn(w.meta, "integer") or existsIn(w.meta, "boolean")) %}
    case {{loop.index}}:
        return true;
    {% endif %}{% endfor %}
    default:
        return false;
    }
}

bool {{Identifier}}::parameter_is_logarithmic(unsigned index) noexcept
{
    switch (index) {
    {% for w in active %}{% if w.scale == "log" %}
    case {{loop.index}}:
        return true;
    {% endif %}{% endfor %}
    default:
        return false;
    }
}

float {{Identifier}}::get_parameter(unsigned index) const noexcept
{
    {{class_name}} &dsp = static_cast<{{class_name}} &>(*fDsp);
    switch (index) {
    {% for w in active %}
    case {{loop.index}}:
        return dsp.{{w.var}};
    {% endfor %}
    default:
        (void)dsp;
        return 0;
    }
}

void {{Identifier}}::set_parameter(unsigned index, float value) noexcept
{
    {{class_name}} &dsp = static_cast<{{class_name}} &>(*fDsp);
    switch (index) {
    {% for w in active %}
    case {{loop.index}}:
        dsp.{{w.var}} = value;
        break;
    {% endfor %}
    default:
        (void)dsp;
        (void)value;
        break;
    }
}

{% for w in active %}
float {{Identifier}}::get_{{cid(default(w.meta.symbol,w.label))}}() const noexcept
{
    {{class_name}} &dsp = static_cast<{{class_name}} &>(*fDsp);
    return dsp.{{w.var}};
}

void {{Identifier}}::set_{{cid(default(w.meta.symbol,w.label))}}(float value) noexcept
{
    {{class_name}} &dsp = static_cast<{{class_name}} &>(*fDsp);
    dsp.{{w.var}} = value;
}
{% endfor %}

float {{Identifier}}::get_passive(unsigned index) const noexcept
{
    {{class_name}} &dsp = static_cast<{{class_name}} &>(*fDsp);
    switch (index) {
    {% for w in passive %}
    case NumParameters + {{loop.index}}:
        return dsp.{{w.var}};
    {% endfor %}
    default:
        (void)dsp;
        return 0;
    }
}

{% for w in passive %}
float {{Identifier}}::get_{{cid(default(w.meta.symbol,w.label))}}() const noexcept
{
    {{class_name}} &dsp = static_cast<{{class_name}} &>(*fDsp);
    return dsp.{{w.var}};
}

void {{Identifier}}::set_{{cid(default(w.meta.symbol,w.label))}}(float value) noexcept
{
    {{class_name}} &dsp = static_cast<{{class_name}} &>(*fDsp);
    dsp.{{w.var}} = value;
}
{% endfor %}
