# string-machine

This is a virtual-analog string ensemble synthesizer.

This implementation is based on a digital model designed by Peter Whiting.

## Download

Get from [Open Build Service](https://software.opensuse.org/download.html?project=home%3Ajpcima&package=string-machine).

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
