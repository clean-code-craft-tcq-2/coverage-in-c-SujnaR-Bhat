#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits")
{
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(60, 35, 45) == TOO_HIGH);
  REQUIRE(inferBreach(50, 45, 65) == NORMAL);
}

TEST_CASE("infers the breach according to cooling type") 
{
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -1) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -2) == TOO_LOW);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -3) == TOO_LOW);
  
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 20) == NORMAL);
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING,20) == NORMAL);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 20) == NORMAL);
  
  REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 46) == TOO_HIGH); 
  REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 36) == TOO_HIGH);
  REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 41) == TOO_HIGH);
}


TEST_CASE("Evaluate the breach type and send alerts")
{
  AlertTarget alert_target ;
  BatteryCharacter batteryChar;
 
  alert_target  = TO_EMAIL;
  batteryChar.coolingType = PASSIVE_COOLING;
  checkAndAlert( alert_target, batteryChar, 42);
  
   
  alert_target = TO_CONTROLLER;
  batteryChar.coolingType = PASSIVE_COOLING;
  checkAndAlert( alert_target, batteryChar, -1);
 
  
  alert_target = TO_EMAIL;
  batteryChar.coolingType = HI_ACTIVE_COOLING;
  checkAndAlert( alert_target, batteryChar, 22);
 
  
  alert_target = TO_CONTROLLER;
  batteryChar.coolingType = HI_ACTIVE_COOLING;
  checkAndAlert( alert_target, batteryChar, 52);
 
  
 alert_target = TO_EMAIL;
  batteryChar.coolingType = MED_ACTIVE_COOLING;
  checkAndAlert( alert_target, batteryChar, -6);

  
  alert_target = TO_CONTROLLER;
  batteryChar.coolingType = MED_ACTIVE_COOLING;
  checkAndAlert( alert_target, batteryChar, 38);
  
}


