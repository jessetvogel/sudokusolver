#ifndef sudoku_hpp
#define sudoku_hpp

typedef int cell;

#define DIGIT_UNKNOWN (0)
#define POSSIBLE_ALL (0x1ff)
#define POSSIBLE_FROM_DIGIT(d) (1 << (d - 1))
#define POSSIBLE_CERTAIN(p) ((p) == 0x1 || (p) == 0x2 || (p) == 0x4 || (p) == 0x8 || (p) == 0x10 || (p) == 0x20 || (p) == 0x40 || (p) == 0x80 || (p) == 0x100)
#define POSSIBLE_TO_DIGIT(p) (p == 0x1 ? 1 : (p == 0x2 ? 2 : (p == 0x4 ? 3 : (p == 0x8 ? 4 : (p == 0x10 ? 5 : (p == 0x20 ? 6 : (p == 0x40 ? 7 : (p == 0x80 ? 8 : (p == 0x100 ? 9 : 0)))))))))

#include <string>

class Sudoku {
    
    cell possibilities[81];
    
public:
    
    Sudoku();
    
    bool load(std::string);
    
    bool filled();
    bool valid();
    void clone(Sudoku&);
    
    inline void setPossible(int position, int possible) { possibilities[position] = possible; }
    inline int getPossible(int position) { return possibilities[position]; }
        
};

#endif
