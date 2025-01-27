// Student ID Code Block
// Programmer: Jonathan Kim
// Programmer's ID: 1780039

#ifndef FLOOR_H
#define FLOOR_H

// Libraries
#include <iostream>
#include <string>
#include <queue>
using namespace std;

// .h Files
#include "Panel.h"
#include "Rider.h"

class Floor
{
  queue<Rider> upRiders, downRiders;

public:
  Floor(const int, const char *const, const char *const); // elevation (inches above ground) of floor, name and label
  operator int() const { return elevation; }
  static const char *const UP;
  static const char *const DOWN;
  static int TOP, BOTTOM;
  Panel panel;
  const string name;   // name of floor, for example: Mezzanine
  const string label;  // as it appears on the button panel
  const int elevation; // inches above ground level
  void addRider(const Rider &r);
  bool hasUpRider() const { return !upRiders.empty(); }
  bool hasDownRider() const { return !downRiders.empty(); }
  Rider removeUpRider();
  Rider removeDownRider();
  unsigned int getNumberOfUpRiders() const { return upRiders.size(); }
  unsigned int getNumberOfDownRiders() const { return downRiders.size(); }
  int findElevation() { return elevation; }
  // for external reporting
  friend ostream &operator<<(ostream &, const Floor &); // say name, location, #'s of up / down riders waiting
};

#endif
