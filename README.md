# example code to flash/debug rp2040 / Pico with an stlink and vscode debugging

# Ubuntu
Requires: 
- build probe code for your stlink with https://github.com/blackmagic-debug/blackmagic (precompiled in binaries/)
  - `meson setup build --cross-file cross-file/stlink.ini -Dtargets=rp -Dbmd_bootloader=false` 
  - `meson compile -C build`
  - this is for stlink-v2
- build stlink-tool from https://github.com/jeanthom/stlink-tool
  - git submodule update --init
  - make
- flash stlink:
  - ${path}/stlink-tool ${blackmagic_path}/build/blackmagic_stlink_firmware.bin
- cortex debug plugin, with gdb-multilib
- default pico-sdk tools, like cmake
- set the paths in launch.json and tasks.json of the binaries

Tested on Ubuntu 22.04.


# Windows
Requires: 
- flash stlink with stlink-tool:
  - download from https://github.com/sakana280/stlink-tool/releases/download/1.0-Win64/stlink-tool.exe
  - ./binaries/stlink-tool ./binaries/blackmagic_stlink_firmware.bin
  - use zadig to fix stlink driver (libusbK), https://zadig.akeo.ie/ , only that one!
- install arm toolchain for gdb (https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads), make sure it gets added to your path or you need to change the path in launch.json to an absolute path.
- install cortex debug plugin
- install raspberry pi pico plugin
- start vscode as "Pico - Visual Studio Code" to fix the env vars.
- set the paths in launch.json and tasks.json of some of the binaries

# how it works
- task `build` will compile the code for the rp2040
- task `triggerBMPAndBuild` includes the `build` task and then triggers the stlink into probe mode. By default it starts in DFU mode (for flashing new probe code).
- Launch config `BMP Debug` uses this last task and starts cortex-debug with the USB connection. This also flashes the rp2040.

# Only flashing
- also build the blackmagic app
  - `meson setup build -Dprobe=''` (might need to delete build directory before)
  - `meson compile -C build`
- `${path}/stlink-tool` to trigger DFU.
- `./build/blackmagic --device /dev/ttyACM0 ../RPi-Pico-Baremetal/test_cmake/build/hello_world.bin -w -V` Change path to device and path to bin, must be the bin!
- Somehow flashing again doesn't work, second time it will.
