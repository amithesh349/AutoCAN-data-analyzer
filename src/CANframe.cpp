
#include "CANframe.hpp"

void CANFrame::initializeData()
{
    for (int i = 0; i < 8; i++)
    {
        data[i] = 0;
    }
}

CANFrame::CANFrame()
    : id(0), dlc(0)
{
    initializeData();
}

CANFrame::CANFrame(uint32_t canID)
    : id(canID), dlc(8)
{
    initializeData();
}

uint32_t CANFrame::getID()
{
    return id;
}

void CANFrame::setID(uint32_t newID)
{
    id = newID;
}

void CANFrame::setData(uint8_t index, uint8_t value)
{
    if (index < 8)
    {
        data[index] = value;
    }
}

uint8_t CANFrame::getData(uint8_t index)
{
    if (index < 8)
    {
        return data[index];
    }
    return 0; // Return 0 if index is out of bounds
}