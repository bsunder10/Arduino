#include<VirtualWire.h>

#define currsen A0         //current sensor to A0 pin arduino
#define volsen A1          //voltage sensor to A1 pin
#define dataout 12         //RF sensor to 12 pin

//Sending data
char Array[20];
int a, b;

//current sensor
int sensitivity = 66;
int adcvalue = 0;
int offsetvoltage = 2500;
double adcvoltage = 0;
double currentvalue = 0;
float c;

//voltage sensor
float vout = 0;
float vin = 0;
float r1 = 30000.0;
float r2 = 7500.0;
int val = 0;

void setup() {
  Serial.begin(9600);
  //Setting up the GPIO pins
  pinMode(currsen, INPUT);
  pinMode(volsen, INPUT);
  //Setting up the RF Transmitter  
  vw_setup(2000);         //data send speed
  vw_set_tx_pin(dataout);   
}

void loop() {
  //Reading the values of Current
  adcvalue = analogRead(currsen);
  adcvoltage = (adcvalue / 1024.0) * 5000;
  currentvalue = ((adcvoltage - offsetvoltage) / sensitivity);
  
  //Reading the values of Voltage
  val = analogRead(volsen);
  vout = (val * 5.0) / 1024.0;
  vin = vout /(r2/(r1+r2));

  //Display of Float values
  Serial.println(currentvalue);
  //Serial.println(vin);
  Serial.println(adcvoltage);
  Serial.println(adcvalue);
  Serial.println("*********************");
  //Converting the float value to Integer
  a = currentvalue * 100;
  b = vin * 100;

  //Display the integer values
  //Serial.println(a);
  //Serial.println(b);

  
  //sending data through RF
  sprintf(Array, "%d,%d", a, b);
  vw_send((uint8_t *)Array, strlen(Array));
  vw_wait_tx();
  
  delay(1000);  
}
