#ifndef EMBEDPYTHON_H
#define EMBEDPYTHON_H
#include <python2.7/Python.h>

class embedpython
{
public:
    embedpython();
    void execit(const char* code);
};

#endif // EMBEDPYTHON_H
