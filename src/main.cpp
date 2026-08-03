#include <iostream>
#include "CANframe.hpp"
#include <vector>

using namespace std;

int main()
{
    vector<CANFrame> frames;
    importFrames(frames);

    int choice;

    do
    {
        cout << "\n========== AutoCAN Analyzer ==========\n";
        cout << "1. Print All Frames\n";
        cout << "2. Search by ID\n";
        cout << "3. Count Frames by DLC\n";
        cout << "4. Print ID Statistics\n";
        cout << "5. Most Frequent ID\n";
        cout << "6. Sort by Count\n";
        cout << "7. Find Duplicate Frames\n";
        cout << "8. Search by Data Byte\n";
        cout << "9. Search by ID Range\n";
        cout << "10. Search by DLC Range\n";
        cout << "11. Sort Frames by ID\n";
        cout << "12. Sort Frames by DLC\n";
        cout << "13. Print Summary\n";
        cout << "14. Export Frames\n";
        cout << "15. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            printAllFrames(frames);
            break;

        case 2:
        {
            uint32_t search_id;
            cout << "Enter ID (Hex): ";
            cin >> hex >> search_id;

            cout << "Count : "
                 << countFramesByID(frames, search_id)
                 << endl;

            printFramesByID(frames, search_id);
            break;
        }

        case 3:
        {
            uint8_t search_dlc;
            cout << "Enter DLC: ";
            cin >> dec >> search_dlc;

            cout << "Count : "
                 << countFramesByDLC(frames, search_dlc)
                 << endl;
            break;
        }

        case 4:
            printIDStatistics(frames);
            break;

        case 5:
            printMostFrequentID(frames);
            break;

        case 6:
            sortbyCount(frames);
            break;

        case 7:
            findDuplicateFrames(frames);
            break;

        case 8:
        {
            uint32_t searchByte;

            cout << "Enter Data Byte (Hex): ";
            cin >> hex >> searchByte;

            searchByDataByte(frames,
                             static_cast<uint8_t>(searchByte));
            break;
        }

        case 9:
        {
            uint32_t startID, endID;

            cout << "Start ID (Hex): ";
            cin >> hex >> startID;

            cout << "End ID (Hex): ";
            cin >> hex >> endID;

            searchByIDRange(frames, startID, endID);
            break;
        }

        case 10:
        {
            uint8_t minDLC, maxDLC;

            cout << "Minimum DLC: ";
            cin >> dec >> minDLC;

            cout << "Maximum DLC: ";
            cin >> dec >> maxDLC;

            searchByDLCRange(frames, minDLC, maxDLC);
            break;
        }

        case 11:
            sortFramesByID(frames);
            printAllFrames(frames);
            break;

        case 12:
            sortFramesByDLC(frames);
            printAllFrames(frames);
            break;

        case 13:
            printSummary(frames);
            break;

        case 14:
            exportFrames(frames);
            cout << "Frames exported successfully.\n";
            break;

        case 15:
            cout << "Exiting AutoCAN Analyzer...\n";
            break;

        default:
            cout << "Invalid Choice!\n";
        }

    } while (choice != 15);

    return 0;
}