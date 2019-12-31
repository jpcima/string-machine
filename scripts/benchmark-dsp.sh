#!/bin/bash
set -e
set -o pipefail

if test "$#" -ne 1; then
    echo "Please indicate a DSP file to benchmark."
    exit 1
fi

dsp_file="$1"
dsp_file_base=$(basename "$dsp_file")

if test -z "$CXX"; then
    CXX=g++
fi

echo "Using compiler: $CXX" 1>&2

compile_faust() {
    faust "$@" -a bench.cpp -o /tmp/benchmark-dsp.cpp "$dsp_file"
}

compile_cpp_and_run() {
    "$CXX" "$@" -o /tmp/benchmark-dsp /tmp/benchmark-dsp.cpp
    /tmp/benchmark-dsp | awk '{ print $5; }'
}

cat <<EOF
set style data histograms
set style fill solid
set xtic rotate by -45
EOF

echo "plot \"-\" using 2:xtic(1) title \"$dsp_file_base\""

compile_faust
echo "\"-O2\" $(compile_cpp_and_run -O2)"
compile_faust -vec
echo "\"-vec -O2\" $(compile_cpp_and_run -O2)"

compile_faust
echo "\"-O2 -ffast-math\" $(compile_cpp_and_run -O2 -ffast-math)"
compile_faust -vec
echo "\"-vec -O2 -ffast-math\" $(compile_cpp_and_run -O2 -ffast-math)"

compile_faust
echo "\"-O3\" $(compile_cpp_and_run -O3)"
compile_faust -vec
echo "\"-vec -O3\" $(compile_cpp_and_run -O3)"

compile_faust
echo "\"-O3 -ffast-math\" $(compile_cpp_and_run -O3 -ffast-math)"
compile_faust -vec
echo "\"-vec -O3 -ffast-math\" $(compile_cpp_and_run -O3 -ffast-math)"

echo e
