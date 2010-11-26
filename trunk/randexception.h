#ifndef RANDEXCEPTION_H
#define RANDEXCEPTION_H

#include <string>
#include <exception>

class RandException : public exception
{
public:
    inline RandException(string message) { super(message); }
};

#endif // RANDEXCEPTION_H
