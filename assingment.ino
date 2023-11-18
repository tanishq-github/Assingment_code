#include <muTimer.h>  // included library for creatinf time delay.

#include <Arduino_BuiltIn.h>  // built in library for default functions.

bool LED1 = false, LED2 = false;  // LED statuses for 2 different blinking states ie 250ms and 500 ms.

const int lm35 = A0;  // initializing the Analog pin 0 (A0) as analog input from LM35 sensor.

float temp_deg = 0.0;  // initializing temperature value to 0 (in °C).

const float temp_thresh = 30.0;  // initializing threshold temperature value to 30 (in °C).

float temp_raw = 0.0;  // initializing raw (ADC) temperature value to 0.

#define delay1 250  // macro for delay for the temperature<30°C.

#define delay2 500  // macro for delay for the temperature>30°C.

muTimer myTimer1 = muTimer();  // Creating muTimer object for timer 1.

muTimer myTimer2 = muTimer();  // Creating muTimer object for timer 2.

//setup() function is called first, which is used to initialzing peripherals and local variables to be used.

void setup() {

  Serial.begin(9600);              // initializing baud rate for serial monitor to 9600.
  pinMode(LED_BUILTIN, OUTPUT);    // initializing on board pin as output to LED.
  digitalWrite(LED_BUILTIN, LOW);  // initializing on board pin status as 0 to LED.
  pinMode(lm35, INPUT);            // initializing on analog pin A0 as input.
}
// loop() function will run infinetly until stopped by the developer by the program.

void loop() {

  temp_raw = analogRead(lm35);  // Reading adc temperature value.

  temp_deg = (temp_raw * 4.88f);  // Convert adc value to equivalent voltage.

  temp_deg = (temp_deg / 10.0f);

  if (temp_deg < temp_thresh)  // checking if temperature is less than 30°C,if true - blink LED with 250ms delay.
  {

    LED1 = myTimer1.delayOnOff(!LED1, delay1, delay1);  // if LED status passed to delayOnOff() function is 1 then it will keep LED turned on for given delay values and vice versa.

    digitalWrite(LED_BUILTIN, LED1);// turning on or off the LED based on the status (LED=1 is on and LED=0 is off).

  } else if (temp_deg >= temp_thresh)  // checking if temperature is greater than or equal to 30°C,if true - blink LED with 500ms delay.
  {

    LED2 = myTimer2.delayOnOff(!LED2, delay2, delay2);  // if LED status passed to delayOnOff() function is 1 then it will keep LED turned on for given delay values and vice versa.

    digitalWrite(LED_BUILTIN, LED2);// turning on or off the LED based on the status (LED=1 is on and LED=0 is off).
  }
}