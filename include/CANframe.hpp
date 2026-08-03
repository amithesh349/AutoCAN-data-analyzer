#ifndef CANFRAME_HPP
#define CANFRAME_HPP
#include <cstdint> //this i am used for fixed width integer types like uint8_t, uint16_t, etc. because embedded systems often require precise control over the size of data types to ensure compatibility and efficient memory usage.
#include <vector>  //this prevent from multiple inclusion of the header file
using namespace std;
class CANFrame
{
private:
    uint32_t id;
    uint8_t dlc;
    uint8_t data[8]; // i made everything private so that the user cannot modify the data directly and can protocol does support only 8 bytes of data

    void initializeData();

public:
    CANFrame();                               // Default constructor
    CANFrame(uint32_t canID, uint8_t canDLC); // Overloaded constructor
    void setID(uint32_t newID);
    void setData(uint8_t index, uint8_t value);
    void print() const;
    uint32_t getID() const;
    uint8_t getDLC() const;
    uint8_t getData(uint8_t index) const;
bool operator==(const CANFrame& other) const;
};

uint32_t countFramesByID(const std::vector<CANFrame> &frames, uint32_t search_id);
uint32_t countFramesByDLC(const vector<CANFrame> &frames, uint8_t search_dlc);
void printFramesByID(const vector<CANFrame> &frames, uint32_t search_id);
void printIDStatistics(const vector<CANFrame> &frames);
void printMostFrequentID(const vector<CANFrame>& frames);
void sortbyCount(const vector<CANFrame> &frames);
void findDuplicateFrames(const vector<CANFrame> &frames);
void searchByDataByte(const vector<CANFrame> &frames, uint8_t searchByte);
void searchByIDRange(const vector<CANFrame>& frames, uint32_t startID,uint32_t endID);
void searchByDLCRange(const vector<CANFrame>& frames, uint8_t minDLC, uint8_t maxDLC);
void sortFramesByID(vector<CANFrame> &frames);
void printAllFrames(const vector<CANFrame>& frames);
void sortFramesByDLC(vector<CANFrame> &frames);
void printSummary(const vector<CANFrame>& frames);
void exportFrames(const vector<CANFrame>& frames);
void importFrames(vector<CANFrame>& frames);

#endif
