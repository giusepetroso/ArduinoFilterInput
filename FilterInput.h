/*
  FilterInput.h - Library for filtering inputs.
  Created by Giuse Petroso, 2020.
  Released into the public domain.
*/
#ifndef FilterInput_h
#define FilterInput_h

#include "Arduino.h"

class FilterInput
{
public:
  FilterInput(unsigned long filterOn, unsigned long filterOff, bool debug);
  int watch(int input);

private:
  int _inputState, _lastInput, _filterState, _lastFilter;
  unsigned long _filterOn, _filterOff, _filterOnTime, _filterOffTime;
  bool _debug;
  void _watchInput();
  void _debugLogs();
};

#endif
