#include <iostream>
#include <string>

void decode_message(const std::string& encoded) {
    /*
    Write your logic here to decode the encoded message.
    Parameters:
        encoded (std::string): The encoded message as a string
    Returns:
        None
    */
    for(int i=0;i<encoded.size();i++) {
        if(encoded[i] >= 'a' && encoded[i] <= 'n') {
            int t = encoded[i]-'a';
            std::cout << (char)('n'-t);
        }   
        else {
            int t = encoded[i]-'o';
            std::cout << (char)('z'-t);
            i++;
        }
    }
}

int main() {
    std::string encoded;
    std::getline(std::cin, encoded);
    
    // Call user logic function and print the output
    decode_message(encoded);
    return 0;
}
