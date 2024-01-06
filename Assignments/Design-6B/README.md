![Design 6B Hardware image](/Assignments/Design-6B/DESIGN-6B(Z123367).png)

### Source code

```
#include <LiquidCrystal.h>

#define RS 9
#define EN 8
#define DB4 4
#define DB5 5
#define DB6 6
#define DB7 7

LiquidCrystal lcd(RS, EN, DB4, DB5, DB6, DB7);

void setup()
{
 Serial.begin(9600);
 lcd.begin(16, 2);
 lcd.clear();
}

void setLcd(int temperature)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(String(temperature) + " C");
} 
  

void loop()
{
  int reading, temp;
  float voltage;
  reading = analogRead(A0);
  voltage = reading * 5.0/1024.0;
  temp = (voltage-0.5)*100;
  Serial.println(temp);
  setLcd(temp);
  lcd.setCursor(0, 1);
  lcd.print(String(millis() / 1000) + " seconds");
  delay(100);
}
```
