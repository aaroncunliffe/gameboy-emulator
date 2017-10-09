# GameboyEmulator
------

### Installation (Currently windows only)
1. Open project in visual studio (>2015)
2. Build project, move SDL2.dll from the dependencies folder and place into same folder that the executable is created in in (e.g. /bin/debug)
3. Either run through visual studio or by opening the .exe directly
4. Place the rom in the same file as the .exe

### Notes:
* Currently only works with ROM only games (No Memory Bank Controller support yet)
How to change the rom to be loaded, change this line in the "main.cpp" file
```c++
    processor->SetRom("tetris.gb")
```
* No roms are included in this repository
* Download SDL2 from https://www.libsdl.org/download-2.0.php
