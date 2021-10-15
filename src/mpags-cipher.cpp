#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "runCaesarCipher.hpp"
#include "fileProcess.hpp"

//#include "runCaesarCipher.hpp"

bool processCommandLine(const std::vector<std::string>& args, bool& helpRequested,
                        bool& versionRequested,
                        std::string& inputFileName, std::string& outputFileName,int& key, bool& encrypt) {
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
        } else if (args[i] == "-k") {
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -k requires a key number"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                return 1;
            } else {
                // Got key value, so assign value and advance past it
                key = std::stoi(args[i + 1]);
                ++i;
            }
        } else if (args[i] == "-e") {
                encrypt = true;
                ++i;
        } else if (args[i] == "-d") {
                encrypt = false;
                ++i;
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
    bool encrypt{true};
    std::string inputFile{""};
    std::string outputFile{""};
    int key{5};
    // Process command line arguments - ignore zeroth element, as we know this
    // to be the program name and don't need to worry about it
    
    processCommandLine(cmdLineArgs,helpRequested,versionRequested,inputFile,outputFile,key,encrypt);

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
            << "  -k INT           Desired key for encryption\n"
            << "                   5 will be used if not supplied\n\n"
            << "  -d               Use at end, uses decrypt mode\n"
            << "                   Encrypt mode will be used if not supplied\n\n"
            << "  -e               Use at end, uses encrypt mode\n"
            << "                   Encrypt mode will be used if not supplied\n\n"
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

    //Process the files, cipher them and then output
    std::string InputText{InputfileProcess(inputFile)};
    InputText = runCaesarCipher(InputText, key, encrypt);
    OutputfileProcess(outputFile,InputText);

    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}

