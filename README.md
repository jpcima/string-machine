# string-machine

This is a virtual-analog string ensemble synthesizer.

This implementation is based on a digital model designed by Peter Whiting.
The improvement of the model adds various abilities, in particular a virtual-analog emulation of the bucket brigade delay circuit.

## Contributors

Thanks to many persons who contribute to improve this project.

- S. M. "sm7x7" for providing presets
- Nicolas Faure "sub26nico" and Erwan Lerale "r1" for testing and feedback
- Olivier Humbert "trebmuh" for creating packages and redistributing

## Download

Get from [Open Build Service](https://software.opensuse.org/download.html?project=home%3Ajpcima&package=string-machine).

## Change log

**0.1.1 (dev)**

This release breaks backwards compatibility.

- envelope generator fixed, rewritten as exponential AHDSR
- adjusted the value domain of controls to be more useful: detune, shape filters
- fixed computation errors regarding the filters
- implemented the bucket brigade delay
- provided two switchable chorus models, digital and BBD
- provided the Solina chorus as independent plugins, 1-in 2-out and 2-in 2-out
- supported dynamic changes of sample rate

**0.1.0**

- initial release

## Build instructions

1. Obtain prerequisites

Install needed packages:

- `git`
- `build-essential`
- `pkg-config`
- `libx11-dev`
- `libgl-dev`
- `libcairo2-dev`
- `libboost-dev`

2. Check out the repository and submodules

```
git clone https://github.com/jpcima/string-machine.git
cd string-machine
git submodule update --init
```

3. Compile

```
make
```

4. Install

To perform a system-wide installation:
```
sudo make install
```

Or, to install only for the current user:
```
make install-user
```
