#include <Ph.h>
#include <math.h>

// Public Method

Ph::Ph(int pin)
{
  this->pin = pin;
}

double Ph::getValue()
{
  calculatePh();
  return pH;
}

// Private Method

void Ph::read()
{
  rawVoltage = analogRead(pin);
  realVoltage = rawVoltage * ADC_EQ;
}

void Ph::itteration()
{
  double total = 0;
  read();
  for (int i = 0; i < ITTERATION; i++)
  {
    total = total + realVoltage;
    delayMicroseconds(DELAY_US);
  }
  totalItteration = total / ITTERATION;
}

void Ph::calculatePh()
{
  itteration();
  pH = 14 / totalItteration;
  if (pH < 0)
  {
    pH = 0;
  }
  else if (pH > 14)
  {
    pH = 14;
  }
}