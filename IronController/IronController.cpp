
#include "IronController.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#define _BV(bit) (1 << (bit))

#define pinA 3  // Connected to CLK on KY-040
#define pinApin PIND
#define pinAreg PIND3
#define pinB 4  // Connected to DT on KY-040
#define pinBpin PIND
#define pinBreg PIND4
#define pinC 5  // Connected to SW on KY-040

#define SO 8    // MISO
#define TC_0 9  // CS Pin of MAX6607
#define SCK 10  // Serial Clock

#define MOSFET 6  // Serial Clock

volatile unsigned long long lastTime;

int position = 0;
int target = 100;

void encoderStep() {
	unsigned long long millisVal = millis();
	if (millisVal - lastTime > 100) {
		// if the knob is rotating, we need to determine direction
		// We do that by reading pin B.
		if ((pinBpin & _BV(pinBreg)) != (pinApin & _BV(pinAreg))) { // Means pin A Changed first - We're Rotating Clockwise
			target += pow(10,position);
		} else {  // Otherwise B changed first and we're moving CCW
			target -= pow(10,position);
		}
	}
	lastTime = millisVal;
}
float read_temp(int pin) {
  unsigned int value = 0;
  int error_tc;
  float temp;

    digitalWrite(pin, LOW); // Enable device

    /* Cycle the clock for dummy bit 15 */
    digitalWrite(SCK, HIGH);
    digitalWrite(SCK, LOW);

    /* Read bits 14-3 from MAX6675 for the Temp
       Loop for each bit reading the value and
       storing the final value in 'temp'
    */
    for (int i = 11; i >= 0; i--) {
      digitalWrite(SCK, HIGH); // Set Clock to HIGH
      value += digitalRead(SO) << i;  // Read data and add it to our variable
      digitalWrite(SCK, LOW); // Set Clock to LOW
    }

    /* Read the TC Input inp to check for TC Errors */
    digitalWrite(SCK, HIGH); // Set Clock to HIGH
    error_tc = digitalRead(SO); // Read data
    digitalWrite(SCK, LOW); // Set Clock to LOW

    digitalWrite(pin, HIGH); //Disable Device


  /*
     Keep in mind that the temp that was just read is on the digital scale
     from 0[ch730]C to 1023.75[ch730]C at a resolution of 2^12.  We now need to convert
     to an actual readable temperature (this drove me nuts until I figured
     this out!).  Now multiply by 0.25.

  */

  temp = (value * 0.25); // Multiply the value by 25 to get temp in [ch730]C

  if (error_tc != 0) {
    return 9999;
  } else {
    return temp;
  }
}

void setup()
{
	pinMode (pinA,INPUT);
	pinMode (pinB,INPUT);
	pinMode (pinC,INPUT);
	digitalWrite(pinC, HIGH);

	pinMode(MOSFET, OUTPUT);

	pinMode(SO, INPUT);
	pinMode(SCK, OUTPUT);
	pinMode(TC_0, OUTPUT);
	digitalWrite(TC_0, HIGH);

	attachInterrupt(digitalPinToInterrupt(3), encoderStep, CHANGE);

	lcd.init();
	lcd.backlight();

	lcd.setCursor(0,0);
	lcd.print("Get: ");
	lcd.setCursor(0,1);
	lcd.print("Set: ");
}



int buttonLastState = 1;
unsigned long long buttonTime = 0;
unsigned long long loopNo = 0;

void loop()
{
	if((digitalRead(pinC) == 0) && ((millis() - buttonTime) > 100) && (buttonLastState == 1)){
		position = (position+1)%3;
		buttonTime = millis();
	}
	buttonLastState = digitalRead(pinC);

	float temp = read_temp(TC_0);
	lcd.setCursor(5,0);
	if(temp < 100) lcd.print(' ');
	if(temp < 10) lcd.print(' ');
	lcd.print(temp);

	lcd.setCursor(5,1);
	if(target < 100) lcd.print(' ');
	if(target < 10) lcd.print(' ');
	lcd.print(target);
	lcd.print("   ");

	if((loopNo % 4) < 2){
		lcd.setCursor(7 - position,1);
		lcd.print(' ');
	}

	analogWrite(MOSFET,constrain(10*(target - temp),0,255));
	delay(200);
	loopNo++;
}
