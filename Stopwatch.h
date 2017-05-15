#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <chrono>

using namespace std::chrono;

class Stopwatch
{
public:
    void start();
    int end();

private:
    time_point<high_resolution_clock> m_start;
    time_point<high_resolution_clock> m_end;
};

#endif // STOPWATCH_H
