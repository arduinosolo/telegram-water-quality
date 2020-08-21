#ifndef PH_H
#define PH_H

#include <Arduino.h>

class Ph
{

private:
  const int ITTERATION = 100;
  const int DELAY_US = 100;
  const double ADC_EQ = 3.3 / 4096.0;

  int pin;
  double rawVoltage = 0.00;
  double realVoltage = 0.00;
  double totalItteration = 0.00;
  double pH = 0.00;

  void read();
  void itteration();
  void calculatePh();

public:
  Ph(int pin);
  void init();
  double getValue();
};

#endif