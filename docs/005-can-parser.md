# Problem 001 - Parsing CAN Frames

## Problem

Read CAN frames from a log file and store them for processing.

Example:

```text
100 2 AA BB
200 4 10 20 30 40
300 1 FF
```

## Approach

1. Open the file.
2. Read CAN ID.
3. Read DLC.
4. Read exactly DLC number of data bytes.
5. Store each frame in `std::vector<CANFrame>`.

## Data Structure

```cpp
struct CANFrame
{
    int id;
    int dlc;
    std::vector<std::string> data;
};
```

## Key Learning

Instead of creating multiple variables such as `frame1`, `frame2`, and `frame3`, use `std::vector<CANFrame>` so the parser can store any number of CAN frames dynamically.

## Current Status

- Parsed a single CAN frame.
- Parsed multiple CAN frames.
- Stored frames dynamically using `std::vector`.

## Next Step

- Search by CAN ID.
- Decode CAN messages.
- Generate statistics.
