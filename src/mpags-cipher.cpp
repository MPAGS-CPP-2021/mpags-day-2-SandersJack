#include <cctype>
#include <iostream>
#include <string>
#include <vector>

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
    return helpRequested,versionRequested;
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
    
    helpRequested, versionRequested = processCommandLine(cmdLineArgs,helpRequested,versionRequested,inputFile,outputFile);

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
    char inputChar{'x'};
    std::string inputText;

    // Read in user input from stdin/file
    // Warn that input file option not yet implemented
    if (!inputFile.empty()) {
        std::cerr << "[warning] input from file ('" << inputFile
                  << "') not implemented yet, using stdin\n";
    }

    // loop over each character from user input
    while (std::cin >> inputChar) {
        inputText += transformChar(inputChar);
    }

    // Print out the transliterated text

    // Warn that output file option not yet implemented
    if (!outputFile.empty()) {
        std::cerr << "[warning] output to file ('" << outputFile
                  << "') not implemented yet, using stdout\n";
    }

    std::cout << inputText << std::endl;

    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}

