#ifndef solver_hpp
#define solver_hpp

#include "sudoku.hpp"

class Solver {
    
    Sudoku& sudoku;
    
public:
    
    Solver(Sudoku& sudoku) : sudoku(sudoku) {};
    
    void algorithm();
    bool solve();
    
};

#endif
