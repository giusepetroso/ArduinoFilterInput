# Arduino Filter Input

This is a simple class for filtering an Arduino input

Implementation example:
```
FilterInput filter(
  100, // milliseconds of delay for ON state
  100, // milliseconds of delay for OFF state
  false // debug flag, will print to serial (must do Serial.begin(9600) in setup function)
);
int filtered = filter.watch(digitalRead(13));
```
