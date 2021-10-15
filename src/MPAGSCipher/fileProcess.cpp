#include <string>
#include <fstream>
#include <iostream>

#include "fileProcess.hpp"
#include "TransformChar.hpp"


bool fileProcess(const std::string inputFileName, const std::string outputFileName) {
    std::string inputText;
    char inputChar{'x'};

    if (!inputFileName.empty()) {
        std::string inputString{'i'};
        std::ifstream in_file {inputFileName};
        bool in_file_good = in_file.good();

        if (in_file_good) {
            in_file >> inputString;
        } else {
            std::cerr << "Error in opening file" << std::endl;
            return 1;
        }
        //std::cout << inputString << std::endl;
        //std::cout << inputString.size() << std::endl;
        for (std::string::size_type i{0}; i<inputString.size();i++) {
            inputChar = inputString[i];
            inputText += transformChar(inputChar);
            
        }
        in_file.close();
    } else {
        std::cout << "Using Input from keyboard" << std::endl;
        // loop over each character from user input
        while (std::cin >> inputChar) {
            inputText += transformChar(inputChar);
            //std::cout << inputText << std::endl;
        }
        }
    if (!outputFileName.empty()){
        std::cout << "Saving output to file:" << outputFileName << std::endl;
        std::ofstream out_file {outputFileName};
        bool out_file_good = out_file.good();
        if (out_file_good) {
            out_file << inputText;
        } else {
            std::cerr << "Error in saving file" << std::endl;
        }
        out_file.close();
    } else {
        std::cout << inputText << std::endl;
    }
    return 0;
}