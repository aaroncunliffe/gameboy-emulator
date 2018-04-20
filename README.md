# GameboyEmulator
------

### Installation (Currently windows only)
1. Open project in visual studio (>2015)
2. Place the x86 SDL2 folder inside the empty lib folder
3. Build project, move SDL2.dll from the dependencies folder and place into same folder that the executable is created in in (e.g. /bin/debug)
4. Either run through visual studio or by opening the .exe directly
5. Place the rom in the same file as the .exe

### Notes:
* Currently only works with ROM only or MBC1 games

How to change the rom to be loaded, change this line in the "main.cpp" file
```c++
    processor->SetRom("tetris.gb")
```
Or execute through the command line with the ROM file as the second argument (can also drag the gameboy file into the .exe file)

* No roms are included in this repository
* Download SDL2 from https://www.libsdl.org/download-2.0.php

### Screenshots
<img src="https://github.com/Aaroncunliffe/GameboyEmulator/blob/master/Screenshots/CustomROM.png" width="300"> <img src="https://github.com/Aaroncunliffe/GameboyEmulator/blob/master/Screenshots/BlarggsTestRom.png" width="300">
<img src="https://github.com/Aaroncunliffe/GameboyEmulator/blob/master/Screenshots/TetrisMenu.png" width="300"> <img src="https://github.com/Aaroncunliffe/GameboyEmulator/blob/master/Screenshots/TetrisGameplay.png" width="300">
<img src="https://github.com/Aaroncunliffe/GameboyEmulator/blob/master/Screenshots/SuperMarioLandTitleScreen.png" width="300"> <img src="https://github.com/Aaroncunliffe/GameboyEmulator/blob/master/Screenshots/SuperMarioLandGameplay.png" width="300">
<img src="https://github.com/Aaroncunliffe/GameboyEmulator/blob/master/Screenshots/ZeldaTitleScreen.png" width="300"> <img src="https://github.com/Aaroncunliffe/GameboyEmulator/blob/master/Screenshots/ZeldaSaveFile.png" width="300"> <img src="https://github.com/Aaroncunliffe/GameboyEmulator/blob/master/Screenshots/ZeldaGameplay.png" width="300">

See more screenshots in the Screenshots folder
