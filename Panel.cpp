// Student ID Code Block
// Programmer: Jonathan Kim
// Programmer's ID: 1780039

// C++ Libraries
#include <iostream>
#include <string>
using namespace std;

// .h Files
#include "Panel.h"

int Panel::Button::count = 0;

void Panel::addButton(string label)
{
  Button temp;
  temp.label = label;
  temp.lit = false;
  buttons.push_back(temp);
}

void Panel::press(string label)
{
  for (int i = 0; i < buttons.size(); i++)
  {
    if (this->buttons[i].label == label)
    {
      this->buttons[i].lit = true;
      Button::count++;
      this->buttons[i].sequence = Button::count;
    }
  }
}

void Panel::clear(string label)
{
  for (int i = 0; i < this->buttons.size(); i++)
  {
    if (this->buttons[i].label == label)
      this->buttons[i].lit = false;
  }
}

string Panel::getFirstLit() const
{
  string firstLit = "";
  int sequence = 0;

  for (int i = 0; i < this->buttons.size(); i++)
  {
    if (this->buttons[i].lit)
    {
      if (sequence == 0)
      {
        sequence = buttons[i].sequence;
        firstLit = buttons[i].label;
      }
      else if (sequence != 0 && sequence > this->buttons[i].sequence)
      {
        sequence = this->buttons[i].sequence;
        firstLit = this->buttons[i].label;
      }
    }
  }
  return firstLit;
}

bool Panel::isLit(string label) const
{
  for (int i = 0; i < buttons.size(); i++)
  {
    if (label == buttons[i].label)
      return buttons[i].lit ? true : false;
  }
  return false;
}

bool Panel::areAnyLit() const
{
  for (int i = 0; i < this->buttons.size(); i++)
  {
    if (this->buttons[i].lit)
      return true;
  }
  return false;
}

ostream &operator<<(ostream &out, const Panel &panel)
{
  for (const Panel::Button &button : panel.buttons)
  {
    if (button.lit)
    {
      out << "[" << button.label << "]";
    }
  }
  return out;
}