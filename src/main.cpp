#include <iostream>
#include "CANframe.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
int main()
{
    ifstream file("../sample_data/can_log.txt");
    vector<CANFrame> frames;
    if (!file.is_open())
    {
        cout << "Cannot open file\n";
        return 1;
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

    uint32_t search_id;
    cin >> hex >> search_id;
    cout << "Search ID = " << search_id << '\n';
  uint32_t count_id =  countFramesByID(frames, search_id);
  printFramesByID(frames, search_id);
  cout<<count_id<<endl;

  uint8_t search_dlc;
  cin>>dec>>search_dlc;
  uint32_t count_dlc = countFramesByDLC(frames, search_dlc);
  cout<<count_dlc<<endl;


}