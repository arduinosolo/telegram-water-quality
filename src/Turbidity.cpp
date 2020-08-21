#include <Turbidity.h>
#include <math.h>

// Public Method

Turbidity::Turbidity(int pin)
{
  this->pin = pin;
}

double Turbidity::getValue()
{
  adcToPpm();
  return ppm;
}

// Private Method

void Turbidity::read()
{
  rawVoltage = analogRead(pin);
  realVoltage = rawVoltage * ADC_EQ;
}

void Turbidity::itteration()
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

void Turbidity::adcToPpm()
{
  itteration();
  ntu = (X * sq(totalItteration)) + (Y * totalItteration) - Z;
  ppm = ntu / NTU_2_PPM;
  if (ppm < 0)
  {
    ppm = 0;
  };
}
