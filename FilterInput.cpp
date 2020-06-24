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
  _inputState = 0;
  _lastInput = 0;
  _lastFilter = 0;
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
  _watchInput(); // watch the input and manage the filter state
  _watchFilter(); // watch the filter and manage the delay state
  if (_debug)
    _debugLogs(); // print debug stuff
  return _delayState; // return the delay state
}
void FilterInput::_debugLogs()
{
  Serial.print("INPUT: ");
  Serial.print(_inputState);
  // Serial.print(" | FON: ");
  // Serial.print(millis() - _filterOnTime);
  // Serial.print(" / ");
  // Serial.print(_filterOn);
  // Serial.print(" | FOFF: ");
  // Serial.print(millis() - _filterOffTime);
  // Serial.print(" / ");
  // Serial.print(_filterOff);
  Serial.print(" | F: ");
  Serial.print(_filterState);
  // Serial.print(" | TON: ");
  // Serial.print(millis() - _delayOnTime);
  // Serial.print(" / ");
  // Serial.print(_delayOn);
  // Serial.print(" | TOFF: ");
  // Serial.print(millis() - _delayOffTime);
  // Serial.print(" / ");
  // Serial.print(_delayOff);
  Serial.print(" | T: ");
  Serial.print(_delayState);
  Serial.println("");
}

void FilterInput::_watchInput()
{
  // read the digital input
  _inputState = digitalRead(_pin);

  // input rising edge
  bool risingEdge = _inputState == 1 && _lastInput == 0;
  if (risingEdge)
    _filterOnTime = millis();

  // input falling edge
  bool fallingEdge = _inputState == 0 && _lastInput == 1;
  if (fallingEdge)
    _filterOffTime = millis();

  // set input state
  _lastInput = _inputState;

  // filter state management
  if (_inputState == 1)
  {
    if (millis() - _filterOnTime >= _filterOn)
      _filterState = 1;
  }
  else
  {
    if (millis() - _filterOffTime >= _filterOff)
      _filterState = 0;
  }
}

void FilterInput::_watchFilter()
{
  // filter rising edge
  bool risingEdge = _filterState == 1 && _lastFilter == 0;
  if (risingEdge)
    _delayOnTime = millis();

  // filter falling edge
  bool fallingEdge = _filterState == 0 && _lastFilter == 1;
  if (fallingEdge)
    _delayOffTime = millis();

  // set filter state
  _lastFilter = _filterState;

  // delay state management
  if (_filterState == 1)
  {
    if (millis() - _delayOnTime >= _delayOn)
      _delayState = 1;
  }
  else
  {
    if (millis() - _delayOffTime >= _delayOff)
      _delayState = 0;
  }
}