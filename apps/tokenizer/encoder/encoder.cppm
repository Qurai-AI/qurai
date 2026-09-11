module;


#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <iomanip> 

export module encoder;
export void encode(const std::string& text){
    

    std::vector<std::string> tokens;
    std::string current;
    
    if (!text.empty()) {
        bool is_space = std::isspace(static_cast<unsigned char>(text[0]));
        
        for (char c : text) {
            bool current_is_space = std::isspace(static_cast<unsigned char>(c));
            
            if (current_is_space != is_space) {
                tokens.push_back(current);
                current.clear();
                is_space = current_is_space;
            }
            current += c;
        }
        if (!current.empty()) {
            tokens.push_back(current);
        }
    }

    for (const auto& token : tokens) {
        std::cout << "\"" << token << "\"\n";
    }
    



    std::vector<uint8_t> bytes(text.begin(), text.end());

    for (size_t i = 0; i < bytes.size(); i++) {
        std::cout << static_cast<int>(bytes[i]) << std::endl;
    }

    for (size_t i = 0; i < bytes.size(); i++) {
        std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') 
                  << static_cast<int>(bytes[i]) << std::endl;
    }

    
}