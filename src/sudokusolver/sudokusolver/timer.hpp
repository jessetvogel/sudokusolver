#ifndef timer_hpp
#define timer_hpp

#include <ctime>

class Timer {
  
    clock_t startTime;
    
public:
    
    Timer() { startTime = 0; };
    
    inline void start() { startTime = clock(); }
    inline clock_t getTicks() { return clock() - startTime; }
    inline double getSeconds() { return (double) getTicks() / CLOCKS_PER_SEC; }
    
};

#endif
