#include <iostream>
#include "CANframe.hpp"
#include <vector>
#include <map>
#include <algorithm>
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

uint8_t CANFrame::getData(uint8_t index) const
{
    if (index < 8)
    {
        return data[index];
    }
    return 0; // Return 0 if index is out of bounds
}

void CANFrame::print() const
{
    cout << "\n===== printing frame  =====\n";
    cout << "ID:" << hex << uppercase << getID() << endl;
    cout << "DLC:" << static_cast<int>(getDLC()) << endl;
    cout << "DATA: ";
    for (int i = 0; i < getDLC(); i++)
    {
        cout << hex << uppercase << static_cast<int>(getData(i)) << " ";
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
            cout << "Frame ID = " << hex << frame.getID()
                 << ", Search ID = " << hex << search_id << '\n';
        }
    }
    return count_id;
}

uint32_t countFramesByDLC(const vector<CANFrame> &frames, uint8_t search_dlc)
{
    uint32_t count_dlc = 1;

    for (const CANFrame &frame : frames)
    {

        if (frame.getDLC() == search_dlc)
        {
            frame.print();
            count_dlc++;
            cout << "Frame DLC = " << frame.getDLC() << ", Search DLC= " << search_dlc << '\n';
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
void printIDStatistics(const vector<CANFrame> &frames)
{
    map<uint32_t, uint32_t> idCount;

    for (const CANFrame &frame : frames)
    {
        idCount[frame.getID()]++;
    }
    cout << "\n===== CAN ID Statistics =====\n";
    for (const auto &item : idCount)
    {
        cout << "ID: " << hex << item.first << " : " << "Count: " << item.second << endl;
    }
}

void printMostFrequentID(const vector<CANFrame> &frames)
{

    uint32_t maxID = 0;
    uint32_t maxCount = 0;
    map<uint32_t, uint32_t> idCount;
    for (const CANFrame &frame : frames)
    {
        idCount[frame.getID()]++;
    }

    for (const auto &item : idCount)
        if (item.second > maxCount)
        {
            maxID = item.first;
            maxCount = item.second;
        }
    cout << "\n===== Most Frequent CAN ID =====\n";
    cout << "ID    : " << hex << uppercase << maxID << endl;
    cout << "Count : " << dec << maxCount << endl;
}

void sortbyCount(const vector<CANFrame> &frames)
{
    vector<pair<uint32_t, uint32_t>> sortedData;
    map<uint32_t, uint32_t> idCount;

    for (const CANFrame &frame : frames)
    {
        idCount[frame.getID()]++;
    }
    for (const auto &item : idCount)
    {
        sortedData.push_back(item);
    }
    sort(sortedData.begin(), sortedData.end(),
         [](const pair<uint32_t, uint32_t> &a,
            const pair<uint32_t, uint32_t> &b)
         {
             return a.second > b.second;
         });
    cout << "\n===== Sorted by Count =====\n";

    for (const auto &item : sortedData)
    {
        cout << "ID: "
             << hex << uppercase << item.first
             << " Count: "
             << dec << item.second
             << endl;
    }
}