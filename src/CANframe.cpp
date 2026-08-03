#include <iostream>
#include "CANframe.hpp"
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>
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

bool CANFrame::operator==(const CANFrame &other) const
{
    if (getID() != other.getID())
    {
        return false;
    }
    if (getDLC() != other.getDLC())
    {
        return false;
    }
    for (uint8_t i = 0; i < getDLC(); i++)
    {
        if (getData(i) != other.getData(i))
        {
            return false;
        }
    }
    return true;
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
    cout << "\n";
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
    cout << "max ID    : " << hex << uppercase << maxID << endl;
    cout << "max Count : " << dec << maxCount << endl;
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

void findDuplicateFrames(const vector<CANFrame> &frames)
{

    for (size_t i = 0; i < frames.size(); i++)
    {
        for (size_t j = i + 1; j < frames.size(); j++)
        {

            if (frames[i] == frames[j])
            {
                cout << "Duplicate found\n";
                frames[i].print();
            }
        }
    }
}

void searchByDataByte(const vector<CANFrame> &frames, uint8_t searchByte)
{
    for (const CANFrame &frame : frames)
    {
        for (uint8_t i = 0; i < frame.getDLC(); i++)
        {
            if (frame.getData(i) == searchByte)
            {
                frame.print();
                break;
            }
        }
    }
}

void searchByIDRange(const vector<CANFrame> &frames, uint32_t startID, uint32_t endID)
{
    for (const CANFrame &frame : frames)
    {
        if (frame.getID() >= startID && frame.getID() <= endID)
        {
            frame.print();
        }
    }
}

void searchByDLCRange(const vector<CANFrame> &frames, uint8_t minDLC, uint8_t maxDLC)
{
    for (const CANFrame &frame : frames)
    {
        if (frame.getDLC() >= minDLC && frame.getDLC() <= maxDLC)
        {
            frame.print();
        }
    }
}

void sortFramesByID(vector<CANFrame> &frames)
{

    sort(frames.begin(), frames.end(),
         [](const CANFrame &a, const CANFrame &b)
         {
             return a.getID() < b.getID();
         });
}

void sortFramesByDLC(vector<CANFrame> &frames)
{
    sort(frames.begin(), frames.end(),
         [](const CANFrame &a, const CANFrame &b)
         {
             return a.getDLC() < b.getDLC();
         });
}

void printAllFrames(const vector<CANFrame> &frames)
{
    for (const auto &frame : frames)
    {
        frame.print();
    }
}

void printSummary(const vector<CANFrame> &frames)
{
    map<uint32_t, uint32_t> idCount;
    for (const CANFrame &frame : frames)
    {
        idCount[frame.getID()]++;
    }
    cout << "===== Summary =====\n";
    cout << "Total Frames : " << frames.size() << endl;
    cout << "Unique IDs: " << idCount.size() << endl;
    printMostFrequentID(frames);
}

void exportFrames(const vector<CANFrame> &frames)
{
    ofstream file("output.txt");
    if (!file.is_open())
    {
        cout << "Cannot open file";
        return;
    }

    for (const CANFrame &frame : frames)
    {
        // write frame to file
        file << hex << frame.getID() << " ";
        file << dec << static_cast<int>(frame.getDLC()) << " ";
        for (uint8_t i = 0; i < frame.getDLC(); i++)
        {
            file << hex << static_cast<int>(frame.getData(i)) << " ";
        }
        file << "\n";
    }
    file.close();
}


void importFrames(vector<CANFrame>& frames)
{

  ifstream file("../sample_data/can_log.txt");
    if (!file.is_open())
    {
        cout << "Cannot open file\n";
        return;
    }

    string line;

    while (std::getline(file, line))
    {
        stringstream ss(line);

        uint32_t id;
        uint32_t dlc;

        ss >> hex >> id;
        ss >> dec >> dlc;

        CANFrame frame(id, dlc);

        cout << "ID  : " << hex << id << endl;
        cout << "DLC : " << dec << dlc << endl;

        cout << "Data: ";

        string byte;
        int index = 0;
        while (ss >> byte)
        {
            int value = stoi(byte, nullptr, 16);
            frame.setData(index, value);
            cout << byte << " ";
            index++;
        }

        cout << "\n\n";
        frames.push_back(frame);
    }
}