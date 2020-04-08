/****************************************************************************
  FileName     [ p2Main.cpp ]
  PackageName  [ p2 ]
  Synopsis     [ Define main() function ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2016-present DVLab, GIEE, NTU, Taiwan ]
****************************************************************************/
#include <iostream>
#include <string>
#include <iomanip>
#include <unordered_map>
#include "p2Json.h"

using namespace std;

enum Command { PRINT, SUM, AVE, MAX, MIN, ADD, EXIT, UNKNOWN };
unordered_map<string, Command> commands = {
   { "PRINT", PRINT },
   { "SUM", SUM },
   { "AVE", AVE },
   { "MAX", MAX },
   { "MIN", MIN },
   { "ADD", ADD },
   { "EXIT", EXIT },
   { "UNKNOWN", UNKNOWN }
};


int main()
{
   Json json;

   // Read in the csv file. Do NOT change this part of code.
   string jsonFile;
   cout << "Please enter the file name: ";
   cin >> jsonFile;
   if (json.read(jsonFile))
      cout << "File \"" << jsonFile << "\" was read in successfully." << endl;
   else {
      cerr << "Failed to read in file \"" << jsonFile << "\"!" << endl;
      exit(-1); // jsonFile does not exist.
   }

   // TODO read and execute commands
   // read and execute commands
   while (true) {
      cout << "Enter command: ";
      string strCmd;
      cin >> strCmd;
      Command cmd;
      if (commands.find(strCmd) != commands.end()) {
         cmd = commands.at(strCmd);
      } else {
         // commands does not exist.
         cerr << "Error: unknown command: \"" << strCmd << "\"" << endl;
         continue;
      }

      string key;
      int value;

      switch (cmd) {
         case PRINT:
            json.print();
            break;

         case SUM:
            if (json.empty()) {
               cout << "Error: No element found!!" << endl;
               continue;
            }
            cout << "The summation of the values is: " << json.sum() << "." << endl;
            break;

         case AVE:
            if (json.empty()) {
               cout << "Error: No element found!!" << endl;
               continue;
            }
            cout << "The average of the values is: " << fixed << setprecision(1) << json.ave() << "." << endl;
            break;

         case MAX:
            if (json.empty()) {
               cout << "Error: No element found!!" << endl;
               continue;
            }
            cout << "The maximum element is: { " << json.max() << " }." << endl;
            break;
         
         case MIN:
            if (json.empty()) {
               cout << "Error: No element found!!" << endl;
               continue;
            }
            cout << "The minimum element is: { " << json.min() << " }." << endl;
            break;

         case ADD:
            cin >> key >> value;
            json.add(key, value);
            break;

         case EXIT:
            return 0;
            break;

         default:
            break;
      }
   }
}
