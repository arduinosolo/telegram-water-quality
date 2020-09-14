#ifndef TURBIDITY_H
#define TURBIDITY_H

#include <Arduino.h>

class Turbidity
{

private:
  const int ITTERATION = 100;          // Itteration value
  const int DELAY_US = 100;            // Itteration delay times in us
  const double ADC_EQ = 3.3 / 4096.00; // Real voltage converter
  const double X = -1120.4;            // ADC to NTU variable
  const double Y = 5742.3;
  const double Z = 4352.9;
  const double NTU_2_PPM = 3.0; // Convert NTU to PPM with this variable

  int pin;
  double rawVoltage = 0.00;
  double realVoltage = 0.00;
  double ntu = 0.00;
  double ppm = 0.00;
  double totalItteration = 0.00;

  void read();
  void itteration();
  void adcToPpm();

public:
  Turbidity(int pin);
  void init();
  double getValue();
};

#endif
