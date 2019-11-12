{% block HeaderDescription %}
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
{% endblock %}

{% block HeaderPrologue %}
{% if not (Identifier is defined and
           Identifier == cid(Identifier)) %}
{{fail("`Identifier` is undefined or invalid.")}}
{% endif %}
{% endblock %}

#pragma once
#ifndef {{Identifier}}_Faust_pp_Gen_HPP_
#define {{Identifier}}_Faust_pp_Gen_HPP_

#include <memory>

class {{Identifier}} {
public:
    {{Identifier}}();
    ~{{Identifier}}();

    void init(float sample_rate);
    void clear() noexcept;

    void process(
        {% for i in range(inputs) %}const float *in{{i}},{% endfor %}
        {% for i in range(outputs) %}float *out{{i}},{% endfor %}
        unsigned count) noexcept;

    enum { NumInputs = {{inputs}} };
    enum { NumOutputs = {{outputs}} };
    enum { NumActives = {{active|length}} };
    enum { NumPassives = {{passive|length}} };
    enum { NumParameters = {{active|length + passive|length}} };

    enum Parameter {
        {% for w in active + passive %}p_{{cid(w.meta.symbol|default(w.label))}},
        {% endfor %}
    };

    struct ParameterRange {
        float init;
        float min;
        float max;
    };

    static const char *parameter_label(unsigned index) noexcept;
    static const char *parameter_short_label(unsigned index) noexcept;
    static const char *parameter_symbol(unsigned index) noexcept;
    static const char *parameter_unit(unsigned index) noexcept;
    static const ParameterRange *parameter_range(unsigned index) noexcept;
    static bool parameter_is_trigger(unsigned index) noexcept;
    static bool parameter_is_boolean(unsigned index) noexcept;
    static bool parameter_is_integer(unsigned index) noexcept;
    static bool parameter_is_logarithmic(unsigned index) noexcept;

    float get_parameter(unsigned index) const noexcept;
    void set_parameter(unsigned index, float value) noexcept;

    {% for w in active + passive %}
    float get_{{cid(w.meta.symbol|default(w.label))}}() const noexcept;
    {% endfor %}
    {% for w in active %}
    void set_{{cid(w.meta.symbol|default(w.label))}}(float value) noexcept;
    {% endfor %}

public:
    class BasicDsp;

private:
    std::unique_ptr<BasicDsp> fDsp;

{% block ClassExtraDecls %}
{% endblock %}
};

{% block HeaderEpilogue %}
{% endblock %}

#endif // {{Identifier}}_Faust_pp_Gen_HPP_
