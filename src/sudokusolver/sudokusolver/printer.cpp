#include "printer.hpp"
#include <iostream>

#define FANCY_DIGIT_WIDTH (8)
#define FANCY_DIGIT_HEIGHT (5)
#define FANCY_HOR_SEP "----------"

std::string Printer::fancyDigits[10] = {
    "                                        ",
    "   _      / |     | |     | |     |_|   ",
    " ____   |___ \\    __) |  / __/  |_____| ",
    " _____  |___ /    |_ \\   ___) | |____/  ",
    " _  _   | || |  | || |_ |__   _|   |_|  ",
    " ____   | ___|  |___ \\   ___) | |____/  ",
    "  __     / /_   | '_ \\  | (_) |  \\___/  ",
    " _____  |___  |    / /    / /    /_/    ",
    "  ___    ( _ )   / _ \\  | (_) |  \\___/  ",
    "  ___    / _ \\  | (_) |  \\__, |    /_/  "
};

void Printer::print(Sudoku& sudoku) {
    for(int row = 0;row < 9; ++row) {
        for(int column = 0;column < 9; ++column) {
            int possible = sudoku.getPossible(9 * row + column);
            if(!POSSIBLE_CERTAIN(possible))
                std::cout << " . ";
            else
                std::cout << ' ' << POSSIBLE_TO_DIGIT(possible) << ' ';
            
            if(column == 2 || column == 5) std::cout << "|";
        }
        std::cout << std::endl;
        if(row == 2 || row == 5) std::cout << "---------+---------+---------" << std::endl;
    }
}

void Printer::printFancy(Sudoku& sudoku) {
    for(int row = 0;row < 9; ++row) {
        for(int fancyLine = 0;fancyLine < FANCY_DIGIT_HEIGHT; ++fancyLine) {
            for(int column = 0;column < 9; ++column) {
                int possible = sudoku.getPossible(9 * row + column);
                std::cout << " " << fancyDigits[POSSIBLE_TO_DIGIT(possible)].substr(FANCY_DIGIT_WIDTH * fancyLine, FANCY_DIGIT_WIDTH) << " ";
                
                if(column == 2 || column == 5) std::cout << "|";
            }
            std::cout << std::endl;
        }
        if(row == 2 || row == 5)
            std::cout << FANCY_HOR_SEP FANCY_HOR_SEP FANCY_HOR_SEP "+" FANCY_HOR_SEP FANCY_HOR_SEP FANCY_HOR_SEP "+" FANCY_HOR_SEP FANCY_HOR_SEP FANCY_HOR_SEP << std::endl;
    }
}