#ifndef CANFRAME_HPP
#define CANFRAME_HPP
#include <cstdint> //this i am used for fixed width integer types like uint8_t, uint16_t, etc. because embedded systems often require precise control over the size of data types to ensure compatibility and efficient memory usage.
#include <vector>//this prevent from multiple inclusion of the header file

class CANFrame
{
private:
    uint32_t id;
    uint8_t dlc;
    uint8_t data[8]; // i made everything private so that the user cannot modify the data directly and can protocol does support only 8 bytes of data
 
    void initializeData();

    public:
       CANFrame();                    // Default constructor
    CANFrame(uint32_t canID, uint8_t canDLC);      // Overloaded constructor
    void setID(uint32_t newID);
    void setData(uint8_t index, uint8_t value);

    uint32_t getID()const;
    uint8_t getDLC();
    uint8_t getData(uint8_t index);
    
};

uint32_t countFramesByID(const std::vector <CANFrame>& frames, uint32_t search_id);
uint8_t countFramesByDLC(const vector<CANFrame>& frames, uint32_t search_dlc);
void printFramesByID(const vector<CANFrame>& frames, uint8_t search_dlc);

































#endif  