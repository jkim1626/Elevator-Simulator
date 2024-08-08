// Student ID Code Block
// Programmer: Jonathan Kim
// Programmer's ID: 1780039

#ifndef PANEL_H
#define PANEL_H

// C++ Libraries
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Panel
{
  struct Button
  {
    string label;
    bool lit;
    int sequence;
    static int count;
  };

  vector<Button> buttons;

public:
  void addButton(string);
  void press(string);
  void clear(string);
  string getFirstLit() const;
  bool isLit(string) const;
  bool areAnyLit() const;
  friend ostream &operator<<(ostream &, const Panel &);
};

#endif