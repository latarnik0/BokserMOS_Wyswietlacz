##include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define N 3

LiquidCrystal_I2C lcd(0x27, 20, 4); 
char temp_name = 'a';
char prev_name = 0;
String name = "";
const int znakPin = 13, enterPin = 12, resetPin = 14, delPin = 15, startPin = 11;
int mode = 0; //trzeba bylo wprowadzic 2 tryby pracy programu z uwagi na bledy


void setup() {
  Wire.begin();
  Wire.setClock(100000);
  pinMode(enterPin, INPUT_PULLUP);
  pinMode(znakPin, INPUT_PULLUP);
  pinMode(resetPin, INPUT_PULLUP);
  pinMode(delPin, INPUT_PULLUP);
  pinMode(startPin, INPUT_PULLUP);
  delay(100);

  lcd.begin(20,4);
  lcd.backlight();
  lcd.blink();
  lcd.setCursor(2, 0);
  lcd.print("! BOXER by MOS !");
  lcd.setCursor(3, 2);
  lcd.print("Podaj swoj nick:");
  lcd.setCursor(N,3);
}

void loop() {
  //TRYB 0 - wpisywanie nicku
  if (mode == 0) {
    int val = analogRead(27);
    int index = map(val, 0, 1023, 0, 25);
    temp_name = 'a' + index;
    delay(1);

    if (temp_name != prev_name) {
      lcd.setCursor(N,3);
      lcd.print(name);
      lcd.setCursor(name.length()+N, 3);
      lcd.print(temp_name);
      prev_name = temp_name;
    }

    if (digitalRead(znakPin) == LOW) {
      name += temp_name;
      lcd.setCursor(N,3);
      lcd.print(name);
      lcd.setCursor(name.length()+N, 3);
      lcd.print(temp_name);

      delay(300);
    }

    if (digitalRead(delPin) == LOW) {
      lcd.setCursor(name.length()+N, 3);
      lcd.print(" ");
      name.remove(name.length()-1, 1);
      lcd.setCursor(N,3);
      lcd.print(name);
      lcd.setCursor(name.length()+N, 3);
      delay(300);
    }

    if (digitalRead(enterPin) == LOW) {
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("! BOXER by MOS !");
      lcd.setCursor(3, 2);
      lcd.print("Twoj nick:");
      lcd.setCursor(N, 3);
      lcd.print(name);
      
      delay(5000);
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print("Start za: ");

      lcd.setCursor(10,2);
      lcd.print("5");
      delay(1000);
      lcd.setCursor(10, 2);
      lcd.print(" ");

      lcd.setCursor(10, 2);
      lcd.print("4");
      delay(1000);
      lcd.setCursor(10, 2);
      lcd.print(" ");

      lcd.setCursor(10, 2);
      lcd.print("3");
      delay(1000);
      lcd.setCursor(10, 2);
      lcd.print(" ");

      lcd.setCursor(10, 2);
      lcd.print("2");
      delay(1000);
      lcd.setCursor(10, 2);
      lcd.print(" ");

      lcd.setCursor(10, 2);
      lcd.print("1");
      delay(1000);
      lcd.print(" ");
      lcd.setCursor(6, 2);
      lcd.print("opuszczanie gruchy");

      mode = 1;  //enter wcisniety - zmiana trybu na pokazanie nicku
      delay(300); 
    }
    if (digitalRead(resetPin) == LOW) {
      name = "";
      temp_name = 'a';
      prev_name = 0;
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("! BOXER by MOS !");
      lcd.setCursor(3, 2);
      lcd.print("Podaj swoj nick: ");
      lcd.setCursor(N, 3);
      mode = 0;
    }
  }

  //TRYB 1 - zatwierdzony nick 
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
      lcd.setCursor(N, 3);
      mode = 0; //reset wcisniety - wracamy do wpisywania nicku
      delay(300);
      }
    }
}


