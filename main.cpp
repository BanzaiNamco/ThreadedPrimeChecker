#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <array>

#include "searchRange.h"
#include "linearSearch.h"

using namespace std;

void getConfig(int &x, int &y, int &variation) {
    ifstream config_file;
    config_file.open("config.txt");
    if (!config_file) {
        cout << "Unable to open file";
        exit(1);
    }
    string line;

    getline(config_file, line);
    x = stoi(line);

    getline(config_file, line);
    y = stoi(line);

    getline(config_file, line);
    variation = stoi(line);

    config_file.close();
};


int main() {
  int x, y, variation;
  getConfig(x, y, variation);

  //Variation List:
  // 1: Straight Division of Search Range + Print Immediately
  // 2: Straight Division of Search Range + Print at the end
  // 3: Threads are for divisibility testing + Print immediately
  // 4: Threads are for divisibility testing + Print at the end

  switch (variation) {
    case 1:
      cout << "Variation 1: Straight Division of Search Range + Print Immediately" << endl;
      SearchRange::runImmediatePrint(x, y);
      break;
    case 2:
      cout << "Variation 2: Straight Division of Search Range + Print at the end" << endl;
      SearchRange::runPrintAtEnd(x, y);
      break;
    case 3:
      cout << "Variation 3: Threads are for divisibility testing + Print immediately" << endl;
      linearSearch::runImmediatePrint(x, y);
      break;
    case 4:
      cout << "Variation 4: Threads are for divisibility testing + Print at the end" << endl;
      linearSearch::runPrintAtEnd(x, y);
      break;
    default:
      cout << "Invalid Variation" << endl;
      exit(1);
  }

  return 0;
}