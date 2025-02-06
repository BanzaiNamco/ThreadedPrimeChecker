#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <stdexcept>

#include "searchRange.h"
#include "linearSearch.h"
#include "primeChecker.h"

using namespace std;

bool getConfig(unsigned int &x, unsigned int &y, unsigned int &variation) {
    ifstream config_file("config.txt");
    if (!config_file) {
        cout << "Error: config.txt not found" << endl;
        return false;
    }

    string line;

    auto parseInteger = [](const string& line2) {
      try {
          int val = stoi(line2);
          if (val <= 0) {
              cout << "Invalid input: must be greater than 0\n";
              return -1;
          }
          return val;
      } catch (const invalid_argument&) {
          cout << "Invalid input: not an integer\n";
          return -1;
      } catch (const out_of_range&) {
          cout << "Invalid input: out of range\n";
          return -1;
      }
      return -1;
    };


    // x = threads
    // y = max number

    getline(config_file, line);
    x = parseInteger(line);

    getline(config_file, line);
    y = parseInteger(line);

    if (x == -1 || y == -1) {
        return false;
    }

    if (x > y) {
      x = y;
    }


    getline(config_file, line);
    variation = parseInteger(line);

    config_file.close();

    return true;
}

int main() {
  unsigned int x, y, variation;
  if(!getConfig(x, y, variation)) {
    cout << "Invalid configuration" << endl;
    return 0;
  }

  //Variation List:
  // 1: Straight Division of Search Range + Print Immediately
  // 2: Straight Division of Search Range + Print at the end
  // 3: Threads are for divisibility testing + Print immediately
  // 4: Threads are for divisibility testing + Print at the end
  cout << "Program Start Time: " << PrimeChecker::getCurrentTime() << endl;

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
  cout << "Program End Time: " << PrimeChecker::getCurrentTime() << endl;

  cout << "Press Enter to close the program" << endl;
  cin.get();

  return 0;
}