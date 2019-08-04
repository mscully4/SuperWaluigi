#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstring>

using namespace std;

void load_map(const string& path, vector<vector<int>> &map, vector<int> &power_up_counter) {
  ifstream file;
  file.open(path);
    if (file) {
        string line;
        int number, col = 0;
        vector<int> array;
        while (getline(file, line)) {
            for (int z=0; z < line.length(); ++z) {
                if (isdigit(line[z]) && isdigit(line[z + 1])) {
                    number = (line[z] - '0') * 10 + (line[z + 1] - '0');
                    array.push_back(number);
                    if (number == 10) {
                        power_up_counter[0]++;
                    } else if (number == 11) {
                        power_up_counter[1]++;
                    } else if (number == 12) {
                        power_up_counter[2]++;
                    }
                    ++z;
                } else if (isdigit(line[z])) {
                    number = line[z] - '0';
                    array.push_back(number);
                }
            }
            map.push_back(array);
            array = {};
            col++;
        }
        file.close();
    }
}    
 
    

