// COMSC-200
// Final Project - Assignment 15 (Elevator v5)
// The instructor's solutions file

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include <cstdlib>
#include <ctime>

#include "Rider.h"
#include "Building.h"
#include "Floor.h"
#include "Panel.h"
#include "Elevator.h"

int main()
{
  cout << "Programmer: Jonathan Kim\n"
       << "Programmer's ID: 1780039\n"
       << "File: " << __FILE__;

  srand(time(0));
  rand();

  for (int i = 0;; i++)
  {
    cout << "-----------------------------------------------\n";
    cout << "-- Time " << i << " ---------------------------\n";
    for (int elevator = 0; elevator < Building::ELEVATORS; elevator++)
      cout << Building::elevators[elevator] << endl;

    for (int floor = 0; floor < Building::FLOORS; floor++)
      cout << Building::floors[floor] << endl;

    double myArrivalRate = 3; // you choose!
    Building::action(i < 300 ? myArrivalRate : 0);

    cin.get();
  }
}

/*
g++ -c -std=c++11 Rider.cpp -Wall

g++ -c -std=c++11 Elevator.cpp -Wall

g++ -c -std=c++11 Building.cpp -Wall

g++ -c -std=c++11 Floor.cpp -Wall

g++ -c -std=c++11 Panel.cpp -Wall

g++ -std=c++11 -o ElevatorTEST ElevatorV5.cpp Rider.o Elevator.o Building.o Floor.o Panel.o -Wall

./ElevatorTEST
*/