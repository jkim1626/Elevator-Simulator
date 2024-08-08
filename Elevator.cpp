// Student ID Code Block
// Programmer: Jonathan Kim
// Programmer's ID: 1780039

// Files
#include "Elevator.h"
#include "Panel.h"
#include "Building.h"

// C++ Libraries
#include <iostream>
#include <vector>
using namespace std;

// C Libraries
#include <cstdlib>

Elevator::Elevator(unsigned int capacity, int speed, int start)
    : doorOpen(false), direction(IDLE), atFloorIndex(-1), timer(3), panel(), speed(speed), CAPACITY(capacity)
{
  // Starting elevation for floor is set to location for elevator
  location = Building::floors[start];
  // Add buttons for each floor's label to the elevator's panel
  for (int i = 0; i < Building::FLOORS; ++i)
  {
    panel.addButton(Building::floors[i].label);
  }
}

void Elevator::openDoorTo(int floorIndex)
{
  // Clear the host elevator's panel button for the referenced floor
  panel.clear(Building::floors[floorIndex].label);
  // Set atFloorIndex to the referenced floor's index
  atFloorIndex = floorIndex;
  // Reset the host elevator's count-down timer
  doorOpen = true;
  resetTimer();
}

void Elevator::board(const Rider &rider)
{
  // Push back the Rider to the host elevator's vector of Riders
  riders.push_back(rider);

  // Access the label for the Rider's destination floor and press the corresponding button on the panel
  panel.press(Building::floors[rider.to].label);

  // If the Rider is going up, set the host elevator's direction to up, otherwise set the direction down
  direction = rider.goingUp ? UP : DOWN;

  // Reset the host elevator's count-down timer
  resetTimer();
}

void Elevator::tickTimer()
{
  if (timer > 0)
  {
    timer--; // Decrement the timer if it's greater than 0
  }
}

void Elevator::resetTimer()
{
  timer = 3; // Reset the timer to its initial value
}

bool Elevator::hasRiderForFloor() const
{
  if (!doorOpen) // Change to doorOpen bool
  {
    return false;
  }
  for (const Rider &r : riders)
  {
    if (r.to == atFloorIndex)
    {
      return true;
    }
  }
  return false;
}

void Elevator::removeRider()
{
  vector<Rider>::iterator it;
  for (it = riders.begin(); it != riders.end(); it++)
  {
    if (it->to == atFloorIndex)
    {
      this->panel.clear(Building::floors[it->to].label);
      this->riders.erase(it); // remove the rider
      this->resetTimer();
      return;
    }
  }
}

bool Elevator::closeDoor()
{
  if (!doorOpen)
  {
    return false;
  }

  Floor &currentFloor = Building::floors[atFloorIndex];
  if (goingUp() && !currentFloor.hasUpRider())
  {
    panel.clear(Building::floors[atFloorIndex].label);
  }
  else if (goingUp() && !currentFloor.hasDownRider())
  {
    panel.clear(Building::floors[atFloorIndex].label);
  }

  doorOpen = false;
  return true;
}

bool Elevator::move()
{
  int topFloor = Floor::TOP;
  int bottomFloor = Floor::BOTTOM;
  int curr = location;
  bool mov = false;

  if (direction == UP)
  {
    for (int i = 0; i < Building::FLOORS; i++)
    {
      int floorElevation = Building::floors[i];
      if (floorElevation <= curr)
      {
        continue;
      }

      int dist = floorElevation - location;
      int time = dist / speed;
      if (time > 1)
      {
        continue;
      }

      if (Building::floors[i].panel.isLit(Floor::UP))
      {
        location += speed;
        openDoorTo(i);
        mov = true;
        break;
      }

      if (panel.isLit(Building::floors[i].label))
      {
        location += speed;
        openDoorTo(i);
        mov = true;
        break;
      }
    }

    if (!mov && curr < topFloor)
    {
      location += speed;
      mov = true;
    }
  }
  else if (direction == DOWN)
  {
    for (int i = 0; i < Building::FLOORS; i++)
    {
      int floorElevation = Building::floors[i];
      if (floorElevation >= curr)
      {
        continue;
      }

      int dist = floorElevation - location;
      int time = dist / speed;
      if (time > 1)
      {
        continue;
      }

      if (Building::floors[i].panel.isLit(Floor::DOWN))
      {
        location -= speed;
        openDoorTo(i);
        mov = true;
        break;
      }

      if (panel.isLit(Building::floors[i].label))
      {
        location -= speed;
        openDoorTo(i);
        mov = true;
        break;
      }
    }

    if (!mov && curr > bottomFloor)
    {
      location -= speed;
      mov = true;
    }
  }
  return mov;
}

void Elevator::goIdle()
{
  direction = IDLE;
}

void Elevator::setDirectionUp()
{
  direction = UP;
}

void Elevator::setDirectionDown()
{
  direction = DOWN;
}

ostream &operator<<(ostream &out, const Elevator &e)
{
  out << "Elevator at ";

  out.setf(ios::right);
  out.width(5);
  out << e.location;
  out.unsetf(ios::right);

  Elevator tempElevator = e;

  out.setf(ios::right);
  out.width(12);
  if (tempElevator.direction == Elevator::IDLE)
    out << "       Idle";
  else if (tempElevator.direction == Elevator::UP)
    out << " going Up";
  else
    out << " going Down";
  out.unsetf(ios::right);

  out.setf(ios::right);
  out.width(3);
  out << tempElevator.riders.size() << " riders ";
  out.unsetf(ios::right);

  if (tempElevator.timedOut() || tempElevator.isFull())
  {
    tempElevator.doorOpen = false;
  }

  if (tempElevator.isOpen())
  {
    out.setf(ios::right);
    out.width(2);
    out << "Door is Open     | " << tempElevator.timer;
    tempElevator.tickTimer();
    out.unsetf(ios::right);
  }
  else
  {
    out.setf(ios::right);
    out.width(2);
    out << "Door is Closed   | 0";
    out.unsetf(ios::right);
  }

  out.setf(ios::right);
  out.width(5);
  out << tempElevator.panel;
  out.unsetf(ios::right);

  return out;
}