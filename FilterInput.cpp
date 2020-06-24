/*
  FilterInput.cpp - Library for filtering and delaying digital inputs.
  Created by Giuse Petroso, 2020.
  Released into the public domain.
*/
#include "Arduino.h"
#include "FilterInput.h"

FilterInput::FilterInput(int pin, int filterOn, int filterOff, int delayOn, int delayOff, bool debug = false)
{
  pinMode(pin, INPUT);
  _pin = pin;
  _filterOn = filterOn;   //milliseconds should pass for setting filter
  _filterOff = filterOff; //milliseconds should pass for unsetting filter
  _delayOn = delayOn;     //milliseconds should pass for setting return value
  _delayOff = delayOff;   //milliseconds should pass for unsetting return value
  _filterState = 0;
  _delayState = 0;
  _filterOnTime = 0;
  _filterOffTime = 0;
  _delayOnTime = 0;
  _delayOffTime = 0;
  _debug = debug;
}

int FilterInput::watch()
{
  // read the digital input
  int input = digitalRead(_pin);

  // rising edge
  bool risingEdge = input == 1 && _filterState == 0;
  if (risingEdge)
    _filterOnTime = millis();

  // falling edge
  bool fallingEdge = input == 0 && _filterState == 1;
  if (fallingEdge)
    _filterOffTime = millis();

  // filter state management
  if (input == 1)
  {
    if (millis() - _filterOnTime >= _filterOn)
      _filterState = 1;
  }
  else
  {
    if (millis() - _filterOffTime >= _filterOff)
      _filterState = 0;
  }

  if (_debug)
  {
    Serial.print("INPUT: ");
    Serial.print(input);
    Serial.print(" | FILTER ON TIME: ");
    Serial.print(millis() - _filterOnTime);
    Serial.print(" | FILTER STATE: ");
    Serial.print(_filterState);
    Serial.print(" | FILTER OFF TIME: ");
    Serial.print(millis() - _filterOnTime);
    Serial.print(" | FILTER STATE: ");
    Serial.print(_filterState);
    Serial.println("");
  }
}
