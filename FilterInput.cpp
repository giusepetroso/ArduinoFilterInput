/*
  FilterInput.cpp - Library for filtering and delaying digital inputs.
  Created by Giuse Petroso, 2020.
  Released into the public domain.
*/
#include "Arduino.h"
#include "FilterInput.h"

FilterInput::FilterInput(int pin, int filterOn, int filterOff, int delayOn, int delayOff){
  pinMode(pin, INPUT);
  _pin = pin;
  _filterOn = filterOn; 
  _filterOff = filterOff;
  _delayOn = delayOn;
  _delayOff = delayOff;
}

bool FilterInput::watch(){
  // read the digital input
  int input = digitalRead(_pin);

  
}
