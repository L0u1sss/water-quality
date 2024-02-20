#include <WiFi.h>
#include <PubSubClient.h>
const char* ssid = ":D";
const char* password = "13october";
const char* mqtt_server = "broker.mqtt-dashboard.com";
const int mqtt_port = 1883;
const char* mqtt_Client = "esp32-555";
const char* mqtt_username = "pi12345678";
const char* mqtt_password = "pi12345678";
WiFiClient espClient;
PubSubClient client(espClient);
char msg[150];
long lastMsg = 0;
int value = 0;

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 20, 2);

#include <TridentTD_LineNotify.h>
#define LINE_TOKEN  "WHjL3kWVPCibJDtYaWeTvRQQ5uqImrY2z4Uub5WUjFo"

#define sw 15
int previousValue = 0;
//ec sersor
#include <OneWire.h>
#define StartConvert 0
#define ReadTemperature 1
const byte numReadings = 20; //the number of sample times
byte ECsensorPin = 35; //EC Meter analog output,pin on analog 0
byte DS18B20_Pin = 2; //DS18B20 signal, pin on digital 2
unsigned int AnalogSampleInterval=25,printInterval=1000,tempSampleInterval=850; //analog sample interval;serial print interval;temperature sample interval
unsigned int readings[numReadings]; // the readings from the analog input
byte ec55 = 0; // the ec55 of the current reading
unsigned long AnalogValueTotal = 0; // the running total
unsigned int AnalogAverage = 0,averageVoltage=0; // the average
unsigned long AnalogSampleTime,printTime,tempSampleTime;
float temperature,ECcurrent,TempCoefficient,CoefficientVolatge;
//Temperature chip i/o
OneWire ds(DS18B20_Pin); // on digital pin 2

//tds sensor
#define TdsSensorPin 34//ขา
#define VREF 5.0 // analog reference voltage(Volt) of the ADC
#define SCOUNT 30 // sum of sample point
int analogBuffer[SCOUNT]; // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBuffertds55 = 0, copytds55 = 0;
float averageVoltageTDS = 0, tdsValueTDS = 0, temperatureTDS = 25;
