#include <iostream>
#include "CANframe.hpp"
#include <vector>
using namespace std;

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

CANFrame::CANFrame(uint32_t canID, uint8_t canDLC)
    : id(canID), dlc(canDLC)
{
    initializeData();
}

uint32_t CANFrame::getID() const
{
    return id;
}

void CANFrame::setID(uint32_t newID)
{
    id = newID;
}
uint8_t CANFrame::getDLC() const
{

    return dlc;
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


void CANFrame::print() const
{

    cout << "ID:" << getID() << endl;
    cout << "DLC:" << getDLC() << endl;
    cout << "DATA: ";
    for (int i = 0; i < getDLC(); i++)
    {
        cout << getData(i) << " ";
    }
    cout << endl;
}


uint32_t countFramesByID(const vector<CANFrame> &frames, uint32_t search_id)
{
    uint32_t count_id = 0;
    for (const CANFrame &frame : frames)
    {
        if (frame.getID() == search_id)
        {
            frame.print();
            count_id++;
            cout << "Frame ID = " << frame.getID()
                 << ", Search ID = " << search_id << '\n';
        }
    }
    return count_id;
}

uint32_t countFramesByDLC(const vector<CANFrame> &frames, uint8_t search_dlc)
{
    uint32_t count_dlc = 0;
    for (const CANFrame &frame : frames)
    {

        if (frame.getDLC() == search_dlc)
        {
            frame.print();
            count_dlc++;
            cout << "Frame DLC = " << frame.getDLC()
                 << ", Search DLC= " << search_dlc << '\n';
        }
    }
    return count_dlc;
}

void printFramesByID(const vector<CANFrame> &frames, uint32_t search_id)
{

   for (const CANFrame &frame : frames)
    {
        if (frame.getID() == search_id)
        {
           frame.print();


        }
    }
}
