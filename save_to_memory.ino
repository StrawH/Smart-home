//#include <ESP8266WiFi.h>
//#include <BlynkSimpleEsp8266.h>
#include <EEPROM.h>

char auth[] = "YourAuthToken";
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";
int pinValue;

int adcValue = 0;
double adcVoltage(int adcValue);
double currentValue(int offsetVoltage, int sensitivity );
int buttonValue;
double voltage;
double current;

int EEPROM_SIZE = 1;
float lastCurrentValue = 0;

void setup()
{
  // wait for power stable
  delay(10);
  Serial.begin(9600);
  //  Blynk.begin(auth, ssid, pass);
  EEPROM.begin();
  lastCurrentValue = EEPROM.read(0);
  Serial.println(lastCurrentValue);
}

void loop()
{
  //  Blynk.run();
  adcValue = analogRead(A0);
  buttonValue = digitalRead(6);
  voltage = adcVoltage(adcValue);
  current = currentValue(2500, 66);
  Serial.print("\t Voltage(mV) = ");       Serial.println(voltage);
  Serial.print("\t Current = ");           Serial.println(current);
  Serial.print("\t lastCurrentValue = ");  Serial.println(lastCurrentValue);
  //save current value to memory
  EEPROM.write(0, lastCurrentValue);

  // uncomment this condition when using app
  //  if (pinValue == 1 || buttonValue == HIGH) {
  if (current > lastCurrentValue ) {
    Serial.println("working ... ");
    digitalWrite (6, HIGH);
    lastCurrentValue = current;
  }
  //  }
  delay(500);
}

//------------------------------------------------------------------------------------------------ -
// current sensor functions
double adcVoltage(int adcValue ) {
  double adcVoltagex = (adcValue / 1024.0) * 5000;
  return adcVoltagex;
}
double currentValue(int offsetVoltage, int sensitivity ) {
  double currentValuex = ((adcVoltage(adcValue) - offsetVoltage) / sensitivity);
  return currentValuex;
}
//------------------------------------------------------------------------------------------------ -
