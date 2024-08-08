// Student ID Code Block
// Programmer: Jonathan Kim
// Programmer's ID: 1780039

#ifndef ELEVATOR_H
#define ELEVATOR_H

// C++ Libraries
#include <vector>
using namespace std;

// Files
#include "Rider.h"
#include "Floor.h"
#include "Panel.h"

class Elevator
{
  bool doorOpen;
  static const int IDLE = 0;
  static const int UP = 1;
  static const int DOWN = -1;
  // elevator metrics
  int location;  // inches above ground level
  int direction; // equal to IDLE, UP, DOWN
  int atFloorIndex;
  int timer;
  vector<Rider> riders;

public:
  Elevator(unsigned int, int, int);
  operator int() const { return location; }
  Panel panel;
  const int speed; // inches per second, up or down
  const unsigned int CAPACITY;
  // count-down timer before closing door
  void resetTimer();
  void tickTimer();
  bool timedOut() const { return timer == 0; }

  // Door is open/closed, to open to a floor, board riders
  bool isOpen() const { return doorOpen; } // atFloorIndex >= 0
  void openDoorTo(int);
  void board(const Rider &);

  bool hasRiderForFloor() const;
  void removeRider();
  bool isFull() const { return CAPACITY == riders.size(); }
  bool goingUp() const { return direction == UP; }
  bool goingDown() const { return direction == DOWN; }
  int getFloorIndex() const { return atFloorIndex; }
  unsigned int getNumberOfRiders() const { return riders.size(); }

  bool closeDoor();
  bool idle() const { return direction == IDLE; }
  bool move();

  void goIdle();
  void setDirectionUp();
  void setDirectionDown();
  int locate() { return location; }

  friend ostream &operator<<(ostream &, const Elevator &);
};
#endif
