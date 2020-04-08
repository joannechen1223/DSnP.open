/****************************************************************************
  FileName     [ p2Json.cpp ]
  PackageName  [ p2 ]
  Synopsis     [ Define member functions of class Json and JsonElem ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2018-present DVLab, GIEE, NTU, Taiwan ]
****************************************************************************/
#include <iostream>
#include <string>
#include "p2Json.h"

using namespace std;

// Implement member functions of class Row and Table here
bool
Json::read(const string& jsonFile)
{
   ifstream inFile(jsonFile);
   
   // check existence of the jsonFile
   if (!inFile.good()) {
      return false;
   }

   string sign;
   string key;
   int value;
   inFile >> sign;
   while (sign != "}")
   {
      inFile >> key;
      if (sign == "{" && key == "}")   break;
      inFile >> sign >> value >> sign;
      key.erase(key.begin());
      key.erase(key.end()-1);
      add(key, value);
   }
   
   return true;
}

void
Json::print() {
   bool isFirst = true;
   cout << "{\n";
   for(JsonElem elem: _obj) {
      if (isFirst) {
         isFirst = false;
      } else {
         cout << ",\n";
      }
      cout << "  " << elem;
   }

   if (!_obj.empty()) {
      cout << "\n";
   }
   cout << "}\n";
}

long long
Json::sum() {
   long long sum = 0;
   for (JsonElem elem : _obj) {
      sum += (long long) elem.getValue();
   }
   return sum;
}

double
Json::ave() {
   return sum()/(double)_obj.size();
}

JsonElem
Json::min() {
   int minVal = INT_MAX;
   JsonElem minElem;
   for (JsonElem elem : _obj) {
      if (elem.getValue() <= minVal) {
         minElem = elem;
         minVal = elem.getValue();
      }
   }
   return minElem;
}

JsonElem
Json::max() {
   int maxVal = INT_MIN;
   JsonElem maxElem;
   for (JsonElem elem : _obj) {
      if (elem.getValue() >= maxVal) {
         maxElem = elem;
         maxVal = elem.getValue();
      }
   }
   return maxElem;
}

bool
Json::empty() {
   return _obj.empty();
}

void
Json::add(string key, int value) {
   JsonElem *elem = new JsonElem(key, value);
   _obj.push_back(*elem);
}

string
JsonElem::getKey() {
   return _key;
}

int
JsonElem::getValue() {
   return _value;
}

ostream&
operator << (ostream& os, const JsonElem& j)
{
   return (os << "\"" << j._key << "\" : " << j._value);
}

