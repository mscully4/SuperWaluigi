#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

void load_map(const string& path, vector<vector<int>> &map) {
  ifstream file;
  file.open(path);
  if (file) {
    string line;
    vector<int> array;
    int x;
    while (getline(file, line)) {
      for (int z=0; z < line.length(); ++z) {
        if (isdigit(line[z])) {
	  array.push_back(line[z] - '0');
	}
      }
      map.push_back(array);
      array = {};
    }
  file.close();
  }
}
