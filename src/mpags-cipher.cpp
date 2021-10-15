#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "TransformChar.hpp"

bool processCommandLine(const std::vector<std::string>& args, bool& helpRequested,
                        bool& versionRequested,
                        std::string& inputFileName, std::string& outputFileName) {
    /* Function to interpret command line arguments 

    const std::vector<std::string>& args: Command line arguements
    bool& helpRequested: Is help requested bool
    bool& versionRequested: Is version requested bool
    std::string& inputFileName: Inputfile name String
    std::string& outputFileName: Output file name String

    return: helpRequested, versionRequested
    */

    const std::size_t nCmdLineArgs{args.size()};
    for (std::size_t i{1}; i < nCmdLineArgs; ++i) {
        if (args[i] == "-h" || args[i] == "--help") {
            helpRequested = true;
        } else if (args[i] == "--version") {
            versionRequested = true;
        } else if (args[i] == "-i") {
            // Handle input file option
            // Next element is filename unless "-i" is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -i requires a filename argument"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                return 1;
            } else {
                // Got filename, so assign value and advance past it
                inputFileName = args[i + 1];
                ++i;
            }
        } else if (args[i] == "-o") {
            // Handle output file option
            // Next element is filename unless "-o" is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -o requires a filename argument"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                return 1;
            } else {
                // Got filename, so assign value and advance past it
                outputFileName = args[i + 1];
                ++i;
            }
        } else {
            // Have an unknown flag to output error message and return non-zero
            // exit status to indicate failure
            std::cerr << "[error] unknown argument '" << args[i]
                      << "'\n";
            return 1;
        }
        
    }
    return 0;
}

int main(int argc, char* argv[])
{
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};
    

    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    std::string inputFile{""};
    std::string outputFile{""};

    // Process command line arguments - ignore zeroth element, as we know this
    // to be the program name and don't need to worry about it
    
    processCommandLine(cmdLineArgs,helpRequested,versionRequested,inputFile,outputFile);

    // Handle help, if requested
    if (helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"
            << std::endl;
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (versionRequested) {
        std::cout << "0.1.0" << std::endl;
        return 0;
    }


    // Initialise variables
    std::string inputText;
    char inputChar{'x'};

    if (!inputFile.empty()) {
        std::string inputString{'i'};
        std::ifstream in_file {inputFile};
        bool in_file_good = in_file.good();

        if (in_file_good) {
            in_file >> inputString;
        } else {
            std::cerr << "Error in opening file" << std::endl;
            return 1;
        }
        std::cout << inputString << std::endl;
        for (std::string::size_type i; i<inputString.size();i++) {
            inputChar = inputString[i];
            inputText += transformChar(inputChar);
        }
        in_file.close();
    } else {
        std::cout << "Using Input from keyboard" << std::endl;
        // loop over each character from user input
        while (std::cin >> inputChar) {
            inputText += transformChar(inputChar);
        }
        }
    if (!outputFile.empty()){
        std::cout << "Saving output to file:" << outputFile << std::endl;
        std::ofstream out_file {outputFile};
        bool out_file_good = out_file.good();
        if (out_file_good) {
            out_file << inputText;
        } else {
            std::cerr << "Error in saving file" << std::endl;
        }
    } else {
        std::cout << inputText << std::endl;
    }
    

    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}

