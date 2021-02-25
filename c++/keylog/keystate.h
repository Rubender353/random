// keystate map of vkcodes 
#ifndef keystate_H
#define keystate_H
#include <map>
#include <string>
#include <string_view>

// hashmap of all the vkeycodes
struct keystate
{
    // Create a map shift mapping shift key codes to values
    std::map<int, std::string> shiftKeys { {0x30, ")"}, {0x31, "!"}, {0x32, "@"},
    {0x33,"#"},{0x34,"$"},{0x35,"%"},{0x36,"^"},{0x37,"&"},{0x38,"*"},{0x39,"("}
    };
};
// to do map of other keys
/*
std::map<std::string, std::string> otherKeys{ {0x3, "Cancel"},{0x8, "backspace"},{0x9, "Tab"},
{0x0C, "[CLEAR]"},{0x0D, "[ENTER]"},{0x11, "[CTRL]"},{0x12, "[ALT]"},{0x13, "[PAUSE]"},{0x14, "[CAPS Lock]"},
{0x1B, "[ESC]"},{0x20, "[SPACE]"},{0x21, "[PAGE UP]"},{0x22, "[PAGE DOWN]"},{0x23, "[END]"},{0x24, "[HOME]"},
{0x25, "[LEFT ARROW]"},{0x26, "[UP ARROW]"},{0x27, "[RIGHT ARROW]"},{0x28,"[DOWN ARROW]"},{0x2D,"[INS]"},
{0x2E,"[DEL]"},{0x60,"[NUMPAD 0]"},{0x61,"[NUMPAD 1]"},{0x62,"[NUMPAD 2]"},{0x63,"[NUMPAD 3"},{0x64,"[NUMPAD 4]"},
{0x65,"[NUMPAD 5]"},{0x66,"[NUMPAD 6]"},{0x67,"[NUMPAD 7]"},{0x68,"[NUMPAD 8]"},{0x69,"[NUMPAD 9]"},
{0x6A,"[*]"},{0xB,"[+]"},{0x6D,"[-]"},{0x6E,"[.]"},{0x6F,"[/]"},{0x70,"[F1]"},{0x71,"[F2]"},{0x72,"[F3]"},{0x73,"[F4]"},{0x74,"[F5]"},
{0x75,"[F6]"},{0x76,"[F7]"},{0x77,"[F8]"},{0x78,"[F9]"},{0x79,"[F10]"},{0x7A,"[F11]"},{0x7B,"[F12]"},{0x90,"[NUM LOCK]"},
{0x91,"[SCROLL LOCK]"},{0x,""},{0x,""},{0x,""},
{0x,""}, };*/



/* pseudocode of function that will use this
value is dword in vkcode
do a set of condition checks such as if shift is pressed or not then log thos
for other cases we will use these std::map lookup tables


*/

#endif