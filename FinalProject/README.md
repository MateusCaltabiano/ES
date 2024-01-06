![Final project hardware image](/FinalProject/Ultrasonic_Parking_Sensor.png)

### Source code for leftmost board

```
#define pingPin 7
#define echoPin 6
#define BUTTON_IN 2
#define DATA_OUT 12
#define INT_OUT 11
#define SELECT_OUT 10
#define BUZZER 13
#define OFF -1
#define ON 0
#define CLOSE 1
#define MEDIUM 3
#define FAR 4

void setup()
{
  Serial.begin(9600);
  pinMode(pingPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_IN, INPUT_PULLUP);
  pinMode(DATA_OUT, OUTPUT);
  pinMode(INT_OUT, OUTPUT);
  pinMode(SELECT_OUT, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_IN), on_push, FALLING);
  pinMode(BUZZER, OUTPUT);
  
  TCCR1A = 0;
  TCCR1B = (1 << WGM12) | (1 << CS12);
  OCR1A = 31250 - 1;
  TIMSK1 |= (1 << OCIE1A);
}

int state = OFF;

ISR(TIMER1_COMPA_vect)
{
  unsigned int duration, cm;
  unsigned int binaryDistance[11] = {0};
  if(state == OFF){
    buzzer();
    digitalWrite(SELECT_OUT, HIGH);
    binaryDistance[9] = 1;
    binaryDistance[10] = 1;
    for(int i = 0; i < 11; i++) { //Sends the distance bit by bit
      digitalWrite(INT_OUT, HIGH);
      digitalWrite(DATA_OUT, binaryDistance[i]);
      //Serial.print(digitalRead(DATA_OUT));
      digitalWrite(INT_OUT, LOW);
      delay(10);
    }
    digitalWrite(SELECT_OUT, LOW);
    
    return;
  }  

  //The sound ping is triggered by a HIGH pulse of 2 or more microseconds.
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  //A HIGH pulse whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  if(cm <= 50) {
    state = CLOSE;
    binaryDistance[9] = 0;
    binaryDistance[10] = 0;
  } else if(cm > 50 && cm < 200) {
    state = MEDIUM;
    binaryDistance[9] = 0;
    binaryDistance[10] = 1;
  } else {
    state = FAR;
    binaryDistance[9] = 1;
    binaryDistance[10] = 0;
  }
    
  //Serial.print(cm);
  //Serial.println("cm");
  buzzer();
  
  decToBin(cm, binaryDistance);
  
  digitalWrite(SELECT_OUT, HIGH); //Sends signal to start receiving
  
  for(int i = 0; i < 11; i++) { //Sends the distance bit by bit
    digitalWrite(INT_OUT, HIGH);
    digitalWrite(DATA_OUT, binaryDistance[i]);
    //Serial.print(digitalRead(DATA_OUT));
    digitalWrite(INT_OUT, LOW);
    delay(10);
  }
  //Serial.println();
  
  digitalWrite(SELECT_OUT, LOW); //Sends signal to stop receiving  
}

void decToBin(unsigned int distance, unsigned int binaryDistance[])
{  
  int counter = 0;
  while(distance != 0) {
    binaryDistance[counter++] = distance % 2;
    distance /= 2;
  }
}

void on_push()
{
  if(state == OFF){
    state = ON;
  } else {
    state = OFF;
  }
}

void buzzer()
{
  if(state == CLOSE){
    tone(BUZZER, 1000);
  } else if(state == MEDIUM){ 
    tone(BUZZER, 500);
  } else if(state == FAR) {
    tone(BUZZER, 250);
  } else {
    noTone(BUZZER);
  }
}

unsigned int microsecondsToCentimeters(unsigned int microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}

void loop()
{
  delay(1000);
}
```

### Source code for rightmost board

```
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
```
