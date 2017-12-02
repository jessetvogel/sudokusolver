#ifndef printer_hpp
#define printer_hpp

#include "sudoku.hpp"
#include <string>

class Printer {

public:
    
    static void print(Sudoku&);
    static void printFancy(Sudoku&);
    
    static std::string fancyDigits[10];
};

#endif
