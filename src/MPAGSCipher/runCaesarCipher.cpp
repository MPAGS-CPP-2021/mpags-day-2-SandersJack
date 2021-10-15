#include <string>
#include <map>

#include "runCaesarCipher.hpp"

std::string runCaesarCipher(const std::string& inputText,
                            const size_t key, const bool encrypt) 
{
    char inputChar{'z'};
    std::string outStr;
    int init_pos{},fin_pos{};

    std::map<const int,const char> alpha {{0,'A'},{1,'B'},{2,'C'},{3,'D'},{4,'E'},
        {5,'F'},{6,'G'},{7,'H'},{8,'I'},{9,'J'},{10,'K'},{11,'L'},{12,'M'},
        {13,'N'},{14,'O'},{15,'P'},{16,'Q'},{17,'R'},{18,'S'},{19,'T'},
        {20,'U'},{21,'V'},{22,'W'},{23,'X'},{24,'Y'},{25,'Z'}};

    std::map<const char,const int> revalpha {{'A',0},{'B',1},{'C',2},{'D',3},{'E',4},
        {'F',5},{'G',6},{'H',7},{'I',8},{'J',9},{'K',10},{'L',11},{'M',12},
        {'N',13},{'O',14},{'P',15},{'Q',16},{'R',17},{'S',18},{'T',19},
        {'U',20},{'V',21},{'W',22},{'X',23},{'Y',24},{'Z',25}};

    if (!encrypt){
        inputChar = 'z';
    }  
    for (std::string::size_type i{0}; i<inputText.size(); i++) {
        inputChar = inputText[i];
        init_pos = revalpha[inputChar];
        if (encrypt) {
            fin_pos = init_pos+key;
        } else {
            fin_pos = init_pos-key;
        }
        if (0 <= fin_pos && fin_pos <= 25) {
            outStr += alpha[fin_pos];
        } else if (fin_pos < 0) {
            outStr += alpha[fin_pos+26];
        } else if (fin_pos > 25) {
            outStr += alpha[fin_pos-26];
        } 
    }
    return outStr;
}
