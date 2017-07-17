#pragma once
#include "definitions.h"

class Keyboard
{

private:

    bool KeysPressed[0xF] = { false };

public:

    bool GetKey(u8 key) { return KeysPressed[key]; }
    void SetKey(u8 key, bool on) { KeysPressed[key] = on; }


};

// This is the matrix layout for register $FF00:
//
//            P14            P15
//             |              |
// P10------ - O - Right----  O - A
//             |              |
// P11------ - O - Left---- - O - B
//             |              |
// P12------ - O - Up------ - O - Select
//             |              |
// P13------ - O - Down---- - O - Start
//             |              |
