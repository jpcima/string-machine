cmake_minimum_required(VERSION 3.7)
project(string-machine)

add_subdirectory("dpf")

###
dpf_add_plugin(string-machine
  TARGETS lv2 vst2
  UI_TYPE cairo
  FILES_DSP
    "plugins/string-machine/StringMachinePlugin.cpp"
  FILES_UI
    "plugins/string-machine/StringMachineUI.cpp"
    "plugins/string-machine/Artwork.cpp"
    "sources/ui/components/KnobSkin.cpp"
    "sources/ui/components/SkinSlider.cpp"
    "sources/ui/components/SkinToggleButton.cpp"
    "sources/ui/components/SkinTriggerButton.cpp"
    "sources/ui/components/SkinIndicator.cpp"
    "sources/ui/components/PlotView.cpp"
    "sources/ui/FontEngine.cpp"
    "sources/ui/Fontstash.cpp"
    "sources/ui/Cairo++.cpp"
  FILES_COMMON
    "plugins/string-machine/StringMachineShared.cpp"
    "plugins/string-machine/StringMachinePresets.cpp"
    "sources/StringOsc.cpp"
    "sources/StringSynth.cpp"
    "sources/StringFilters.cpp"
    "sources/SolinaChorus.cpp"
    "sources/SolinaChorusStereo.cpp"
    "sources/MidiDefs.cpp"
    "sources/bbd/bbd_line.cpp"
    "sources/bbd/bbd_filter.cpp"
    "sources/dsp/AHDSREnvelope.cpp"
    "sources/dsp/Delay3Phase.cpp"
    "sources/dsp/Delay3PhaseStereo.cpp"
    "sources/dsp/OnePoleFilter.cpp"
    "gen/dsp/Delay3PhaseDigital.cpp"
    "gen/dsp/Delay3PhaseDigitalStereo.cpp"
    "gen/dsp/LFO3PhaseDual.cpp"
    "gen/dsp/StringFiltersHighshelf.cpp"
    "gen/dsp/NoiseLFO.cpp"
    "gen/dsp/PwmOscillator.cpp"
    "gen/dsp/AsymWaveshaper.cpp"
    "thirdparty/vco/OscillatorBlepRect.cpp")

target_include_directories(string-machine
  PUBLIC
    "plugins/string-machine/meta"
    "sources"
    "gen"
    "thirdparty/blink"
    "thirdparty/vco"
    "thirdparty/fontstash"
    "thirdparty/stb"
    "thirdparty/pl_list")

if(MSVC)
  target_compile_options(string-machine PUBLIC "/fp:fast")
  target_compile_definitions(string-machine PRIVATE _USE_MATH_DEFINES)
else()
  target_compile_options(string-machine PUBLIC "-ffast-math")
endif()

###
dpf_add_plugin(string-machine-chorus
  TARGETS lv2 vst2
  FILES_DSP
    "plugins/string-machine-chorus/ChorusPlugin.cpp"
  FILES_COMMON
    "plugins/string-machine-chorus/ChorusShared.cpp"
    "sources/SolinaChorus.cpp"
    "sources/bbd/bbd_line.cpp"
    "sources/bbd/bbd_filter.cpp"
    "sources/dsp/Delay3Phase.cpp"
    "gen/dsp/Delay3PhaseDigital.cpp"
    "gen/dsp/LFO3PhaseDual.cpp")

target_include_directories(string-machine-chorus
  PUBLIC
    "plugins/string-machine-chorus/meta"
    "sources"
    "gen"
    "thirdparty/blink")

if(MSVC)
  target_compile_options(string-machine-chorus PUBLIC "/fp:fast")
else()
  target_compile_options(string-machine-chorus PUBLIC "-ffast-math")
endif()

###
dpf_add_plugin(string-machine-chorus-stereo
  TARGETS lv2 vst2
  FILES_DSP
    "plugins/string-machine-chorus-stereo/StereoChorusPlugin.cpp"
  FILES_COMMON
    "plugins/string-machine-chorus-stereo/StereoChorusShared.cpp"
    "sources/SolinaChorus.cpp"
    "sources/SolinaChorusStereo.cpp"
    "sources/bbd/bbd_line.cpp"
    "sources/bbd/bbd_filter.cpp"
    "sources/dsp/Delay3Phase.cpp"
    "sources/dsp/Delay3PhaseStereo.cpp"
    "gen/dsp/Delay3PhaseDigital.cpp"
    "gen/dsp/Delay3PhaseDigitalStereo.cpp"
    "gen/dsp/LFO3PhaseDual.cpp")

target_include_directories(string-machine-chorus-stereo
  PUBLIC
    "plugins/string-machine-chorus-stereo/meta"
    "sources"
    "gen"
    "thirdparty/blink")

if(MSVC)
  target_compile_options(string-machine-chorus-stereo PUBLIC "/fp:fast")
else()
  target_compile_options(string-machine-chorus-stereo PUBLIC "-ffast-math")
endif()
