# example code to flash/debug rp2040 / Pico with an stlink

Requires: 
- build probe code for your stlink with https://github.com/blackmagic-debug/blackmagic (precompiled in binaries/)
  - `meson setup build --cross-file cross-file/stlink.ini -Dtargets=rp -Dbmd_bootloader=false` 
  - this is for stlink-v2
- build stlink-tool from https://github.com/jeanthom/stlink-tool
  - git submodule update --init
  - make
- flash stlink:
  - ${path}/stlink-tool ${blackmagic_path}/build/blackmagic_stlink_firmware.bin
- cortex debug plugin, with gdb-multilib
- default pico-sdk tools, like cmake
- set the paths in launch.json and tasks.json

Tested on Ubuntu 22.04.