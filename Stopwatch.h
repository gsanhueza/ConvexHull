#ifndef STOPWATCH_H
#define STOPWATCH_H
#include <chrono>

class Stopwatch
{
public:
    Stopwatch();
    void start();
    int end();

private:
    std::chrono::time_point<std::chrono::system_clock> m_start;
    std::chrono::time_point<std::chrono::system_clock> m_end;
};

#endif // STOPWATCH_H
