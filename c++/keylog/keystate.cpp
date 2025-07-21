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

//TODO: this method uses a struct to hold regular and shift keys and stores it in one unordered_map called keyMap
/*
#include <iostream>
#include <unordered_map>
#include <string>

// Struct to hold normal and shifted key representations
struct KeyRepresentation {
    std::string normal;
    std::string shifted;
};

int main() {
    std::unordered_map<int, KeyRepresentation> keyMap {
        {0x30, {"0", ")"}},  // 0 key: normal "0", shifted ")"
        {0x31, {"1", "!"}},  // 1 key
        {0x32, {"2", "@"}},  // 2 key
        {0x33, {"3", "#"}},
        {0x34, {"4", "$"}},
        {0x35, {"5", "%"}},
        {0x36, {"6", "^"}},
        {0x37, {"7", "&"}},
        {0x38, {"8", "*"}},
        {0x39, {"9", "("}},
        // Add other keys as needed
    };

    int keycode = 0x31; // For example: key '1'
    bool shiftPressed = true;

    auto it = keyMap.find(keycode);
    if (it != keyMap.end()) {
        if (shiftPressed)
            std::cout << "Shifted key: " << it->second.shifted << "\n";
        else
            std::cout << "Normal key: " << it->second.normal << "\n";
    } else {
        std::cout << "Keycode not found\n";
    }

    return 0;
}
*/
