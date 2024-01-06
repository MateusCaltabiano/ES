#include <LiquidCrystal.h>
#include <math.h>

#define RS 9
#define EN 8
#define DB4 4
#define DB5 5
#define DB6 6
#define DB7 7
#define DATA_IN 10
#define INT_IN 2
#define SELECT_IN 3
#define GREEN 13
#define YELLOW 12
#define RED 11

LiquidCrystal lcd(RS, EN, DB4, DB5, DB6, DB7);

void setup()
{
 Serial.begin(9600);
 lcd.begin(16, 2);
 lcd.clear();
 
 pinMode(DATA_IN, INPUT);
 pinMode(INT_IN, INPUT);
 pinMode(SELECT_IN, INPUT);
 pinMode(GREEN, OUTPUT);
 pinMode(YELLOW, OUTPUT);
 pinMode(RED, OUTPUT);
  
 attachInterrupt(digitalPinToInterrupt(INT_IN), on_data, FALLING);
 attachInterrupt(digitalPinToInterrupt(SELECT_IN), on_select, FALLING);
}

int binaryDistance[11] = {0};
int counter = 0;
int state = -1;

void on_data()
{
  binaryDistance[counter++] = digitalRead(DATA_IN);
}

void on_select()
{
  counter = 0;
  int distance = binToDec(binaryDistance);
  if(binaryDistance[9] == 0 && binaryDistance[10] == 0){
    state = 0;
  } else if(binaryDistance[9] == 0 && binaryDistance[10] == 1){
    state = 1;
  } else if(binaryDistance[9] == 1 && binaryDistance[10] == 0) {
    state = 2;
  } else {
    state = 3;
  }
  updateLCD(distance);
  updateLED();
}

int binToDec(int binaryDistance[11])
{
  int distance = 0;
  
  for(int i = 0; i < 9; i++){
    distance += pow(2, i) * binaryDistance[i];
  }
  
  return distance;
}

void updateLCD(int distance)
{
  if(state == 3){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("OFF");
    return;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  lcd.setCursor(0, 1);
  if(distance >= 100){
    lcd.print((float)distance/100.0);
  	lcd.setCursor(4, 1);
  	lcd.print("m");
  } else {
    lcd.print(distance);
    lcd.setCursor(2, 1);
    lcd.print("cm");
  }
}

void updateLED()
{
  for(int i = 11; i < 14; i++){
    digitalWrite(i, LOW);
  }
  
  if(state == 0){
    for(int i = 11; i < 14; i++){
      digitalWrite(i, HIGH);
    }
  } else if(state == 1){
      digitalWrite(GREEN, HIGH);
      digitalWrite(YELLOW, HIGH);
  } else if(state == 2){
    digitalWrite(GREEN, HIGH);
  } else {
    return;
  }
}

void loop()
{
  //Serial.println(binToDec(binaryDistance));
  delay(1000);
}
