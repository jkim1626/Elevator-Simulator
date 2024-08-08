// Student ID Code Block
// Programmer: Jonathan Kim
// Programmer's ID: 1780039

// .h Files
#include "Building.h"
#include "Floor.h"
#include "Elevator.h"

// C++ Libraries
#include <iostream>
using namespace std;

// C Libraries
#include <cstdlib>
#include <cmath>

Floor Building::floors[] =
    {
        Floor(0, "First Floor", "1"),    // Elevation 0, name: first floor, title 1
        Floor(100, "Second Floor", "2"), // Elevation 100, name: second floor, title 2
        Floor(200, "Third Floor", "3"),  // Elevation 200, name: third floor, title 3
        Floor(300, "Fourth Floor", "4"), // Elevation 300, name: fourth floor, title 4
        Floor(400, "Fifth Floor", "5"),  // Elevation 400, name: fifth floor, title 5
        Floor(500, "Sixth Floor", "6")}; // Elevation 500, name: sixth floor, title 6
const int Building::FLOORS = sizeof(floors) / sizeof(Floor);
Elevator Building::elevators[] =
    {
        Elevator(10, 20, 0),  // Capacity 10 , Speed += 20, Initial Floor 0
        Elevator(10, 20, 1),  // Capacity 10 , Speed += 20, Initial Floor 1
        Elevator(15, 10, 2),  // Capacity 15 , Speed += 10, Initial Floor 2
        Elevator(20, 10, 3)}; // Capacity 20 , Speed += 10, Initial Floor 3
const int Building::ELEVATORS = sizeof(elevators) / sizeof(Elevator);
// used by Building::placeNewRiders
void Building::getDifferentInts(int &a, int &b)
{
    do
    {
        a = rand() % FLOORS; // range is 0 to (FLOORS-1)
        b = rand() % FLOORS; // range is 0 to (FLOORS-1)
    } while (a == b);        // try again if they are the same
}
// used by Building::placeNewRiders
int Building::getPoisson(double avg)
{
    int arrivals = 0;
    double probOfnArrivals = exp(-avg);                 // requires cmath
    for (double randomValue = (rand() % 1000) / 1000.0; // requires cstdlib
         (randomValue -= probOfnArrivals) > 0.0;
         probOfnArrivals *= avg / ++arrivals)
        ;
    return arrivals;
}
// given an arrival rate, randomly select #of riders to add...
// ...and add them to randomly selected floors with random destinations
void Building::placeNewRiders(double arrivalsPerSecond)
{
    int n = getPoisson(arrivalsPerSecond);
    for (int i = 0; i < n; i++)
    {
        int from, to;
        getDifferentInts(from, to);
        Rider Rider(from, to);
        floors[from].addRider(Rider);
    }
}
// STEP 1 of 9, "Open their door if there is a rider to disembark"
bool Building::openDoorToDisembarkRider(int e)
{
    if (!elevators[e].isOpen())                                                         // if the door is closed...
        for (int f = 0; f < FLOORS; f++)                                                // check each floor to see if its elevation matches
            if (floors[f] == elevators[e] && elevators[e].panel.isLit(floors[f].label)) // ...and the elevator's panel has that floor lit
            {
                elevators[e].openDoorTo(f); // then open the door to that floor
                return true;                // ...and report that an action was taken
            }
    return false; // if I get this far, no action was taken in this function
}
// the "action function" to perform one action per elevator per time step
void Building::action(double arrivalsPerSecond)
{
    placeNewRiders(arrivalsPerSecond);
    // one action per elevator
    for (int e = 0; e < ELEVATORS; e++)
    {
        if (openDoorToDisembarkRider(e))
            continue;

        if (disembarkRider(e))
            continue;

        if (boardRider(e))
            continue;

        if (waitingForMoreRiders(e))
            continue;

        if (doneWaitingMove(e))
            continue;

        if (moveableMove(e))
            continue;

        if (setIdleElevatorInMotion(e))
            continue;

        if (sendIdleElevatorToCallingFloor(e))
            continue;

        elevators[e].goIdle();
    }
}

bool Building::disembarkRider(int elevatorIndex)
{
    if (elevators[elevatorIndex].isOpen() && elevators[elevatorIndex].hasRiderForFloor())
    {
        elevators[elevatorIndex].removeRider();
        return true;
    }
    return false;
}

bool Building::boardRider(int elevatorIndex)
{
    if (elevators[elevatorIndex].isOpen() && !elevators[elevatorIndex].isFull())
    {
        Floor &floor = floors[elevators[elevatorIndex].getFloorIndex()];
        if (elevators[elevatorIndex].goingUp() && floor.hasUpRider())
        {
            Rider rider = floor.removeUpRider();
            elevators[elevatorIndex].board(rider);
            return true;
        }

        else if (elevators[elevatorIndex].goingDown() && floor.hasDownRider())
        {
            Rider rider = floor.removeDownRider();
            elevators[elevatorIndex].board(rider);
            return true;
        }
    }
    return false;
}

bool Building::waitingForMoreRiders(int index)
{
    if (elevators[index].isOpen() && !elevators[index].idle() && !elevators[index].timedOut())
    {
        elevators[index].tickTimer();
        return true;
    }
    return false;
}

bool Building::doneWaitingMove(int index)
{
    if (elevators[index].isOpen() && !elevators[index].idle() && elevators[index].timedOut())
    {
        elevators[index].closeDoor();
        elevators[index].move();
        return true;
    }
    return false;
}

bool Building::moveableMove(int index)
{
    if (elevators[index].isOpen() || elevators[index].idle())
    {
        return false;
    }
    else
    {
        bool temp = elevators[index].move();
        return temp;
    }
}

bool Building::setIdleElevatorInMotion(int index)
{
    if (!elevators[index].idle())
    {
        return false;
    }
    else
    {
        for (int i = 0; i < Building::FLOORS; i++)
        {
            if (elevators[index] != floors[i])
            {
                continue;
            }
            if (floors[i].panel.getFirstLit() == Floor::UP)
            {
                elevators[index].openDoorTo(i);
                elevators[index].setDirectionUp();
                return true;
            }
            else if (floors[i].panel.getFirstLit() == Floor::DOWN)
            {
                elevators[index].openDoorTo(i);
                elevators[index].setDirectionDown();
                return true;
            }
        }
    }

    return false;
}

bool Building::sendIdleElevatorToCallingFloor(int index)
{
    if (!elevators[index].idle())
    {
        return false;
    }
    else
    {
        for (int i = 0; i < FLOORS; ++i)
        {
            if (!floors[i].hasUpRider() && !floors[i].hasDownRider()) // !floors[i].panel.areAnyLit())
            {
                continue;
            }
            if (floors[i] > elevators[index])
            {
                elevators[index].setDirectionUp();
                elevators[index].move();
                return true;
            }
            else if (floors[i] < elevators[index])
            {
                elevators[index].setDirectionDown();
                elevators[index].move();
                return true;
            }
        }
    }
    return false;
}
