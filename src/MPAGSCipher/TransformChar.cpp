#include <string>

#include "TransformChar.hpp"

std::string transformChar(const char in_char) {
    /* Function to convert letters to uppercase and numbers to 
    words. If the character isn't alphabetic or numeric, it is not returned
        
        const char in_char: Input characters 

        return: String of converted char 
        */

        std::string iText;
            if (std::isalpha(in_char)) {
            iText += std::toupper(in_char);
            //continue;
        }

        // Transliterate digits to English words
        switch (in_char) {
            case '0':
                iText += "ZERO";
                break;
            case '1':
                iText += "ONE";
                break;
            case '2':
                iText += "TWO";
                break;
            case '3':
                iText += "THREE";
                break;
            case '4':
                iText += "FOUR";
                break;
            case '5':
                iText += "FIVE";
                break;
            case '6':
                iText += "SIX";
                break;
            case '7':
                iText += "SEVEN";
                break;
            case '8':
                iText += "EIGHT";
                break;
            case '9':
                iText += "NINE";
                break;
        }
        return iText;
}
