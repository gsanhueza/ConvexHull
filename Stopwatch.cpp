#include "Stopwatch.h"

Stopwatch::Stopwatch()
{
}

void Stopwatch::start()
{
    m_start = std::chrono::system_clock::now();
}

int Stopwatch::end()
{
    m_end = std::chrono::system_clock::now();

    int elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(m_end - m_start).count();

    return elapsed;
}
