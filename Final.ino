#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int val = 0;
int timer = 0;
int counter = 0;
int state = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin();
  lcd.clear();
  lcd.backlight();
  pinMode(A1, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  val = analogRead(A1);

  // Plot graph
  Serial.println(",0,1000,600");
  Serial.println(val);

  //finger out of sensor
  if (val > 1000) {
    state = 0;
  }
  if (state == 0) {
    counter = 0;
    timer = 0;
    lcd.clear();
    lcd.print("Please put your");
    lcd.setCursor(0, 1);
    lcd.print("finger in sensor");
  }


  //finger in sensor
  if (state == 0 && val < 600) {
    state = 1;
    delay(3000);
  }

  if (state == 1) {
    //count if ADC less than 600
    timer++;
    if (timer < 100) {

      if (val < 600 && state == 1) {
        counter++;
      }
    } else if (timer == 100) {

      if (counter > 30) {
        lcd.clear();
        lcd.print("Glucose Level :");
        lcd.setCursor(0, 1);
        lcd.print(">160");

      }
      else if (counter > 25) {
        lcd.clear();
        lcd.print("Glucose Level :");
        lcd.setCursor(0, 1);
        lcd.print("160-190");
      }
      else if (counter > 20) {
        lcd.clear();
        lcd.print("Glucose Level :");
        lcd.setCursor(0, 1);
        lcd.print("130 - 160");
      }
      else if (counter > 15) {
        lcd.clear();
        lcd.print("Glucose Level :");
        lcd.setCursor(0, 1);
        lcd.print("100 - 130");
      }
      else if (counter > 10) {
        lcd.clear();
        lcd.print("Glucose Level :");
        lcd.setCursor(0, 1);
        lcd.print("70 - 100");
      }
      else if (counter > 0) {
        lcd.clear();
        lcd.print("Glucose Level :");
        lcd.setCursor(0, 1);
        lcd.print("<70");
      }
      else {
        lcd.clear();
        lcd.print("Out of range!!");
      }
    } else {
      timer = 0;
      counter = 0;
    }
  }
  delay(100);

}
