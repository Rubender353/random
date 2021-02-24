#include <iostream>
#include <map>
#include <string>
#include <string_view>

// hashmap of all the vkeycodes
int keystate()
{
    // Create a map shift mapping shift key codes to values
    std::map<int, std::string> shiftKeys { {0x30, ")"}, {0x31, "!"}, {0x32, "@"},
    {0x33,"#"},{0x34,"$"},{0x35,"%"},{0x36,"^"},{0x37,"&"},{0x38,"*"},{0x39,"("}
    };
    // to do map of other keys
    std::map<std::string, std::string> otherKeys { {0x30, ")"},
}