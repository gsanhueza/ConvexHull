#include "Stopwatch.h"
#include <iostream>

void Stopwatch::start()
{
    m_start = high_resolution_clock::now();
}

int Stopwatch::end()
{
    m_end = high_resolution_clock::now();

    int elapsed = duration_cast<microseconds>(m_end - m_start).count();

    return elapsed;
}
