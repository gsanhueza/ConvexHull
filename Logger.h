#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>

using namespace std;
class Logger : public ofstream
{
public:
    explicit Logger(const string& fileName);
};

Logger::Logger(const string& fileName) : ofstream(fileName)
{
}

template <typename T>
Logger& operator<<(Logger& stream, const T& var)
{
    cout << var;
    static_cast<ofstream &>(stream) << var;

    return stream;
};

#endif //LOGGER_H
