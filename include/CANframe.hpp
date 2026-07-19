#ifndef CANFRAME_HPP
#define CANFRAME_HPP
#include <cstdint> //this i am used for fixed width integer types like uint8_t, uint16_t, etc. because embedded systems often require precise control over the size of data types to ensure compatibility and efficient memory usage.

// this prevent from multiple inclusion of the header file
 
class CANFrame
{
private:
    uint32_t id;
    uint8_t dlc;
    uint8_t data[8]; // i made everything private so that the user cannot modify the data directly and can protocol does support only 8 bytes of data
 
    void initializeData();

    public:
       CANFrame();                    // Default constructor
    CANFrame(uint32_t canID);      // Overloaded constructor

     uint32_t getID(); // Functions to access or modify the data
     void setID(uint32_t newID);

     void setData(uint8_t index, uint8_t value);
     uint8_t getData(uint8_t index);
};




































#endif  