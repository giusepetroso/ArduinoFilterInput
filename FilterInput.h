/*
  FilterInput.h - Library for filtering and delaying digital inputs.
  Created by Giuse Petroso, 2020.
  Released into the public domain.
*/
#ifndef FilterInput_h
#define FilterInput_h

#include "Arduino.h"

class FilterInput
{
public:
  FilterInput(int pin, int filterOn, int filterOff, int delayOn, int delayOff, bool debug = false);
  int watch();

private:
  int _pin, 
    _filterOn, _filterOff, 
    _delayOn, _delayOff, 
    _filterState, _delayState, 
    _filterOnTime, _filterOffTime, 
    _delayOnTime, _delayOffTime;
  bool _debug;
};

#endif
