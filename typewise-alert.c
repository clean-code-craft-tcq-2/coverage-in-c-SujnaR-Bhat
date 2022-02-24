#include "typewise-alert.h"
#include <stdio.h>

double parameterlimits[6] = {PASSIVE_COOLING_LOWER_LIMIT , PASSIVE_COOLING_UPPER_LIMIT, HIACTIVE_COOLING_LOWER_LIMIT, HIACTIVE_COOLING_UPPER_LIMIT ,
  MEDACTIVE_COOLING_LOWER_LIMIT, MEDACTIVE_COOLING_UPPER_LIMIT};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC)
{
  int lowerLimit = parameterlimits[coolingType *2];
  int upperLimit = parameterlimits[coolingType *2+1];
      
  return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
    BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );
      if(alertTarget == TO_CONTROLLER)
      {
       sendToController(breachType);
      }
     if (alertTarget == TO_EMAIL) 
     {
      sendToEmail(breachType);
     }
}

void sendToController(BreachType breachType) 
{
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) 
{
  const char* recepient = "a.b@c.com";

    if( breachType == TOO_LOW)
    {
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
    }
    if( breachType == TOO_HIGH)
    {
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
    }
   
}
