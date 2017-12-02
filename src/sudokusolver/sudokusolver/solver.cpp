#include "solver.hpp"

bool Solver::solve() {
    restart:
    while(!sudoku.filled() && sudoku.valid()) {
        // Perform algorithm
        algorithm();
        
        // If done, return true
        if(sudoku.filled() && sudoku.valid()) return true;
        
        // Otherwise, use backtracking
        if(!sudoku.filled() && sudoku.valid()) {
            for(int position = 0;position < 81; ++position) {
                for(int digit = 1;digit <= 9; ++digit) {
                    // If this position is already certain, just  continue
                    int possible = sudoku.getPossible(position);
                    if(POSSIBLE_CERTAIN(possible)) continue;
                    
                    if(possible & POSSIBLE_FROM_DIGIT(digit)) {
                        // Make a copy of the sudoku, make an assumption
                        Sudoku copy = sudoku;
                        copy.setPossible(position, POSSIBLE_FROM_DIGIT(digit));
                        
                        // Try to solve this copy
                        Solver solver(copy);
                        if(solver.solve()) {
                            // If succeeded, copy back and return true
                            sudoku.clone(copy);
                            return true;
                        }
                        
                        // If it was not possible to solve, apparantly the assumption was false
                        sudoku.setPossible(position, possible ^ POSSIBLE_FROM_DIGIT(digit));
                        goto restart;
                    }
                }
            }
        }
    }
    
    return false;
}

void Solver::algorithm() {
    bool changed;
    do {
        // Set changed to false
        changed = false;
            
        // If some cell is certain, cells in the same row, column and block cannot be this digit
        for(int position = 0;position < 81; ++position) {
            int possible = sudoku.getPossible(position);
            if(POSSIBLE_CERTAIN(possible)) {
                // Determine the row, column and block of this position
                int row = position / 9;
                int column = position % 9;
                int block = (position / 27) * 3 + (position % 9) / 3;
                
                for(int i = 0;i < 9; ++i) {
                    int positionRow = 9 * row + i;
                    int positionColumn = 9 * i + column;
                    int positionBlock = ((block / 3) * 3 + (i / 3)) * 9 + ((block % 3) * 3 + (i % 3));
                    
                    if(positionRow != position) {
                        int possibleCell = sudoku.getPossible(positionRow);
                        if(possibleCell & possible) {
                            sudoku.setPossible(positionRow, possibleCell ^ possible);
                            changed = true;
                        }
                    }
                    
                    if(positionColumn != position) {
                        int possibleCell = sudoku.getPossible(positionColumn);
                        if(possibleCell & possible) {
                            sudoku.setPossible(positionColumn, possibleCell ^ possible);
                            changed = true;
                        }
                    }
                    
                    if(positionBlock != position) {
                        int possibleCell = sudoku.getPossible(positionBlock);
                        if(possibleCell & possible) {
                            sudoku.setPossible(positionBlock, possibleCell ^ possible);
                            changed = true;
                        }
                    }
                }
            }
        }
        
        // For each cell, if it is the only one in its row, column or block in which some digit is possible, set it
        for(int position = 0;position < 9; ++position) {
            int possible = sudoku.getPossible(position);
            if(POSSIBLE_CERTAIN(possible)) continue;
            
            // Determine the row, column and block of this position
            int row = position / 9;
            int column = position % 9;
            int block = (position / 27) * 3 + (position % 9) / 3;

            int possibleRow = possible;
            int possibleColumn = possible;
            int possibleBlock = possible;
            
            for(int i = 0;i < 9; ++i) {
                int positionRow = 9 * row + i;
                int positionColumn = 9 * i + column;
                int positionBlock = ((block / 3) * 3 + (i / 3)) * 9 + ((block % 3) * 3 + (i % 3));
                
                if(positionRow != position)     possibleRow &= (POSSIBLE_ALL ^ sudoku.getPossible(positionRow));
                if(positionColumn != position)  possibleColumn &= (POSSIBLE_ALL ^ sudoku.getPossible(positionColumn));
                if(positionBlock != position)   possibleBlock &= (POSSIBLE_ALL ^ sudoku.getPossible(positionBlock));
            }
            
            // If there is some possiblity that no other cell has, set it
            int possibleTotal = possibleRow | possibleColumn | possibleBlock;
            if(possibleTotal) {
                sudoku.setPossible(position, possibleTotal);
                changed = true;
            }
        }
    }
    while(changed);
}
