# GameboyEmulator
------

### Installation (Currently windows only)
1. Open project in visual studio (>2015)
2. Build project, download SDL2.dll and place into same folder that the executable is created in in (e.g. /bin/debug)
3. either run through visual studio or by opening the .exe directly
4. Place the rom in the same file as the .exe

### Notes:
* Currently only intended to work with Tetris.
How to change the rom to be loaded, change this line
```c++
  CPU* processor = new CPU("tetris.gb");
```
* No roms are included in this project
