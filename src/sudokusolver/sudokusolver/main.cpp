#include <iostream>
#include "sudoku.hpp"
#include "solver.hpp"
#include "printer.hpp"
#include "timer.hpp"

int main() {
    // Try to load sudoku
    Sudoku sudoku;
    if(!sudoku.load("../examples/sudoku_1.txt")) {
        std::cout << "Failed to load sudoku" << std::endl;
        return 0;
    }
    
    // Print sudoku before solving
    Printer::printFancy(sudoku);
    
    // Solve it and time
    Timer timer;
    timer.start();
    
    Solver solver(sudoku);
    solver.solve();
    
    double timeElapsed = timer.getSeconds();
    std::cout << std::endl;
    
    // Print sudoku after solving    
    Printer::printFancy(sudoku);

    std::cout << std::endl << "Time elapsed: " << (timeElapsed * 1000) << "ms " << std::endl << std::endl;
    
    return 0;
}
