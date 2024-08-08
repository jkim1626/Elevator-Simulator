// Student ID Code Block
// Programmer: Jonathan Kim
// Programmer's ID: 1780039

#ifndef Rider_h
#define Rider_h

struct Rider
{
  const int from, to;
  const bool goingUp, goingDown;
  Rider(int, int);
  Rider &operator=(const Rider &);
};

#endif
