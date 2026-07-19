#include <iostream>
#include "CANframe.hpp"



int main()
{
    CANFrame frame;
    uint32_t id = frame.getID();
    return 0;
}