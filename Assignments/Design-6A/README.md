![Design 6A hardware image](Design-6A/DESIGN-6A(Z123367).png)

### Source code

```
#include <LiquidCrystal.h>

#define RS 9
#define EN 8
#define DB4 4
#define DB5 5
#define DB6 6
#define DB7 7
#define nitems(x) (sizeof(x)/sizeof(x[0]))



LiquidCrystal lcd(RS, EN, DB4, DB5, DB6, DB7);

const char *pattern[] = {
  "Hello World",
  "Testing",
  "3rd string",
  "laalaalala",
  "Last string",
  "What if it's too big?"
};

void setLcd(const char *pat) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(pat);
}

void setup() {
 Serial.begin(9600);
 lcd.begin(16, 2);
 lcd.clear();
}

int counter = 0;

void loop() {
 setLcd(pattern[counter]);
 lcd.setCursor(0, 1);
 lcd.print(millis() / 1000);
 counter++;
 if(counter == nitems(pattern)) {
   counter = 0;
 }
 delay(1000);
}
```
