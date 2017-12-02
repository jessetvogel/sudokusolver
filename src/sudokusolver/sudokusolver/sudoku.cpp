#include "sudoku.hpp"
#include <fstream>

Sudoku::Sudoku() {
    // Initially, all digits are possible
    for(int position = 0;position < 81; ++position)
        setPossible(position, POSSIBLE_ALL);
}

bool Sudoku::load(std::string path) {
    // Try to open input file
    std::ifstream input(path);
    if(input.fail()) return false;
    
    // Read file line by line (each line representing a row)
    std::string line;
    for(int row = 0;getline(input, line); ++row) {
        // Read 9 characters, set digits if given
        for(int column = 0;column < 9; ++column) {
            char c = line.at(column);
            setPossible(9 * row + column, (c >= '1' && c <= '9') ? POSSIBLE_FROM_DIGIT(c - '0') : POSSIBLE_ALL);
        }
    }
    
    return true;
}

bool Sudoku::filled() {
    // If any Possible is uncertain, the sudoku is not filled
    for(int position = 0;position < 81; ++position) {
        if(!POSSIBLE_CERTAIN(getPossible(position))) return false;
    }
    return true;
}

bool Sudoku::valid() {
    // Make sure rows, columns and blocks do not contain digits twice, and all numbers are still possible in each of them
    for(int i = 0;i < 9; ++i) {
        
        int certainRow = 0x0;
        int certainColumn = 0x0;
        int certainBlock = 0x0;
        
        int totalPossibleRow = 0x0;
        int totalPossibleColumn = 0x0;
        int totalPossibleBlock = 0x0;
        
        for(int j = 0;j < 9; ++j) {

            int possibleRow = getPossible(9 * j + i);
            int possibleColumn = getPossible(9 * i + j);
            int possibleBlock = getPossible(9 * ((i / 3) * 3 + (j / 3)) + ((i % 3) * 3 + (j % 3)));
            
            totalPossibleRow |= possibleRow;
            totalPossibleColumn |= possibleColumn;
            totalPossibleBlock |= possibleBlock;
            
            // Certain digits can only appear once
            if(POSSIBLE_CERTAIN(possibleRow)) {
                if(certainRow & possibleRow) return false;
                certainRow |= possibleRow;
            }
            
            if(POSSIBLE_CERTAIN(possibleColumn)) {
                if(certainColumn & possibleColumn) return false;
                certainColumn |= possibleColumn;
            }
            
            if(POSSIBLE_CERTAIN(possibleBlock)) {
                if(certainBlock & possibleBlock) return false;
                certainBlock |= possibleBlock;
            }
        }
        
        // All digits should be possible somewhere in the row/column/block
        if(totalPossibleRow != POSSIBLE_ALL) return false;
        if(totalPossibleColumn != POSSIBLE_ALL) return false;
        if(totalPossibleBlock != POSSIBLE_ALL) return false;
    }
    
    return true;
}

void Sudoku::clone(Sudoku& other) {
    // Copy all possibilities
    for(int position = 0;position < 81; ++position)
        possibilities[position] = other.possibilities[position];
}
