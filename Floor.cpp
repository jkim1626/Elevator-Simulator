// Student ID Code Block
// Programmer: Jonathan Kim
// Programmer's ID: 1780039

// .h Files
#include "Floor.h"
#include "Rider.h"
#include "Panel.h"
#include "Building.h"

// C++ Libraries
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

// C Libraries
#include <climits>

const char *const Floor::UP = "Up";
const char *const Floor::DOWN = "Down";
int Floor::TOP = INT_MIN;    // defined in climits
int Floor::BOTTOM = INT_MAX; // also in climits

Floor::Floor(const int elevation, const char *const name, const char *const label)
    : panel(), name(name), label(label), elevation(elevation)
{
  panel.addButton(UP);
  panel.addButton(DOWN);
  if (TOP < elevation)
  {
    TOP = elevation;
  }

  if (elevation < BOTTOM)
  {
    BOTTOM = elevation;
  }
}

void Floor::addRider(const Rider &r)
{
  if (r.goingUp)
  {
    this->upRiders.push(r);
    panel.press(UP);
  }
  else if (r.goingDown)
  {
    this->downRiders.push(r);
    panel.press(DOWN);
  }
  else
    throw "ADD_RIDER ERROR!";
}

Rider Floor::removeUpRider()
{
  if (upRiders.empty())
  {
    throw logic_error("No up rider on the floor");
  }
  Rider localCopy = upRiders.front();
  upRiders.pop();
  return localCopy;
}

Rider Floor::removeDownRider()
{
  if (downRiders.empty())
  {
    throw logic_error("No up rider on the floor");
  }
  Rider localCopy = upRiders.front();
  upRiders.pop();
  return localCopy;
}

ostream &operator<<(ostream &out, const Floor &floor)
{
  // Floor label
  out.setf(ios::right);
  out.width(3);
  out << floor.label;
  out.unsetf(ios::right);

  // Floor name
  out.setf(ios::right);
  out.width(15);
  out << floor.name;
  out.setf(ios::right);

  // "at"
  out << " at";

  // Elevation
  out.setf(ios::right);
  out.width(7);
  out << floor.elevation << "\"";
  out.unsetf(ios::right);

  // "Up/Down"
  out << "  Up/Down:";

  // Up/Down Ratio
  out.setf(ios::right);
  out.width(5);
  out << floor.getNumberOfUpRiders() << "/" << floor.getNumberOfDownRiders();
  out.unsetf(ios::right);

  // Buttons
  out << setw(13) << right << "Buttons: ";

  if (floor.hasUpRider())
  {
    out << "[Up]";
  }
  if (floor.hasDownRider())
  {
    out << "[Down]";
  }

  return out;
}
