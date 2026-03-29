
# CHIP-8 Emulator for Linux

A CHIP-8 emulator written in C++ for Linux, using SDL2. 

# About
This is my first attempt at writing an emulator from scratch. The CHIP-8 is an interpreted programming language developed in the mid-1970s that was originally used on hobbyist microcomputers. This project implements a full CHIP-8 emulator for Linux that is capable of running classic CHIP-8 ROMS.





## Dependencies

- SDL2 development libraries
- make

On Debian/Ubuntu-based systems you can install the dependencies with:
```bash
  sudo apt install build-essential libsdl2-dev
```
For Arch-based systems, you can install the dependencies with:
```bash
    sudo pacman -S base-devel sdl2
```

# Building
Clone the repository and run make from the project root:

```bash
git clone https://github.com/LTAuro84/CHIP8-EMULATOR-LINUX.git
cd CHIP8-EMULATOR-LINUX
make
```

This will create the executable chip8.elf.

# Usage
```bash
./chip8.elf --romFileName <path>
```
This will run the CHIP8 ROM in your file path. 