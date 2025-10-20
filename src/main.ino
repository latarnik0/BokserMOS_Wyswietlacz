#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); 
char temp_name = 'a';
char prev_name = 0;
String name = "";
const int znakPin = 13, enterPin = 12, resetPin = 14;
int mode = 0; //trzeba bylo wprowadzic 2 tryby pracy programu z uwagi na to ze 
              //program po przytrzymaniu i puszczeniu entera wracal do wpisywania nicku
              //ale z wypisanym nickiem gdzie pierwsza litera nicku byla ta sterowana przez potencjometr

void setup() {
  Wire.begin();
  Wire.setClock(100000);
  pinMode(enterPin, INPUT_PULLUP);
  pinMode(znakPin, INPUT_PULLUP);
  pinMode(resetPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  //tryb 0 - wpisywanie nicku
  if (mode == 0) {
    int val = analogRead(27);
    int index = map(val, 0, 1023, 0, 25);
    temp_name = 'a' + index;
    delay(1);

    if (temp_name != prev_name) {
      lcd.setCursor(3, 3);
      lcd.print(" ");
      lcd.setCursor(3, 3);
      lcd.print(temp_name);
      prev_name = temp_name;
    }

    if (digitalRead(znakPin) == LOW) {
      name += temp_name;
      delay(300);  
    }

    if (digitalRead(enterPin) == LOW) {
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("! BOXER by MOS !");
      lcd.setCursor(3, 2);
      lcd.print("Twoj nick:");
      lcd.setCursor(3, 3);
      lcd.print(name);
      mode = 1;  //enter wcisniety - zmiana trybu na pokazanie nicku
      delay(300); 
    }
  }

  //tryb 1 - zatwierdzony nick 
  if (mode == 1) {
    if (digitalRead(resetPin) == LOW) {
      name = "";
      temp_name = 'a';
      prev_name = 0;
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("! BOXER by MOS !");
      lcd.setCursor(3, 2);
      lcd.print("Podaj swoj nick: ");
      lcd.setCursor(3, 3);
      mode = 0; //reset wcisniety - wracamy do wpisywania nicku
      delay(300);
    }
  }
}
