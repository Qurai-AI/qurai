

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <iomanip> 

import encoder;

int main() {

    std::string text = " Привет, мир! С++";
    Encoder tokenizer_encode(text);

    const auto& encoded_batch = tokenizer_encode.convert_to_tokens();

    tokenizer_encode.print_batch(encoded_batch);


    

    return 0;
}
