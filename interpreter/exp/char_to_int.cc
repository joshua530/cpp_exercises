#include <iostream>

#ifndef __CHAR_TO_INT_FUNC
#define __CHAR_TO_INT_FUNC

int charToInt(char c)
{
    // c is not a valid integer
    if (int(c) < 48 || int(c) > 57)
        return INT8_MIN;

    return c - '0';
}

#endif
