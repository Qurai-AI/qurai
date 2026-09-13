module;


#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <iomanip> 

export module encoder;

export class Encoder
{ 
public:

    struct TokensOutput{
        std::string text; ///< Original text fragments
        std::vector<uint8_t> ids; ///< Byte representations as Ids
    };

    // Member Variable 
    std::vector<std::string> tokens; // Stores the split text fragments


    // @brief Constructs the Encoder and slits the text
    // @param Text the source string to tokenize
    Encoder(const std::string& text);

    // @brief Display batch from a vector of TokensOutput
    void print_batch(const std::vector<TokensOutput>& batch);

    // @brief Convert text fragments to IDs
    std::vector<TokensOutput> convert_to_tokens();


};


Encoder::Encoder(const std::string& text)
{
    std::string current;
    
    if (!text.empty()) {
        // Track whether the first character is a space
        bool is_space = std::isspace(static_cast<unsigned char>(text[0]));
        
        for (char c : text) {
            bool current_is_space = std::isspace(static_cast<unsigned char>(c));

            // If text/space type changes, push current chunk and reset
            if (current_is_space != is_space) {
                this->tokens.push_back(current);
                current.clear();
                is_space = current_is_space;
            }
            current += c;
        }
        // Push the last remaining fragment
        if (!current.empty()) {
            this->tokens.push_back(current);
        }
    }
}

std::vector<Encoder::TokensOutput> Encoder::convert_to_tokens(){

    std::vector<Encoder::TokensOutput> result;

    for (const auto& token_txt : this->tokens)
    {
        // Convert string characters to a uint8_t byte vector
        std::vector<uint8_t> bytes(token_txt.begin(), token_txt.end());

        result.emplace_back(TokensOutput{
            token_txt,
            bytes
            
        });
    }

    return result;
    
}

void Encoder::print_batch(const std::vector<TokensOutput>& batch){

    for (const auto& fragment : batch) {
        std::cout << std::endl;
        std::cout << fragment.text << std::endl;

        // Cast uint8_t to int to print numeric values instead of ASCII characters
        for (const auto& token : fragment.ids){
            std::cout << static_cast<int>(token) << ", ";
        }
        std::cout << std::endl;
        
    }
}
