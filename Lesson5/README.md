![Lesson 5 Hardware image](/Lesson5/Lesson5.png)

### Source code

```

#define PIN_SW 7

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(PIN_SW, INPUT_PULLUP);
  Serial.begin(9600);
}



/*
void loop()
{
  for(int i = 8; i < 14; i++){
    digitalWrite(i, HIGH);
    Serial.println((String)i + " HIGH");
    delay(1000);
    digitalWrite(i, LOW);
    Serial.println((String)i + " LOW");
    delay(1000);
  }
}
*/

const char *pattern[] = {
  "010101",
  "101010",
  "000111",
  "111000",
  "000001",
  "000010",
  "000100",
  "001000",
  "010000",
  "100000"
};

void setLed(const char *pattern) 
{
  for(int i = 0; i < 7; i++) {
    int pin = i + 8;
    if(pattern[i] == '0') {
	  digitalWrite(pin, LOW);
      //Serial.println((String)pin + " LOW");
    } else {
      digitalWrite(pin, HIGH);
      //Serial.println((String)pin + " HIGH");
    }
  }
}

void loop() 
{
  while(digitalRead(PIN_SW) == LOW) {
	for(int i = 0; i < sizeof(pattern)/sizeof(pattern[0]); i++) {
      if(digitalRead(PIN_SW) == HIGH) {
        setLed("000000");
        break;
      }
      setLed(pattern[i]);
      delay(1000);
    }
  }
  	
}

```

![Lesson 5 Temperature Hardware image](/Lesson5/Lesson5-TemperatureSensing.png)

### Source code

```

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  
  TCCR1A = 0;
  TCCR1B = (1 << WGM12) | (1 << CS12);
  OCR1A = 31250 - 1;
}

void setLed(int temperature)
{
  for(int i = 9; i < 14; i++) {
    digitalWrite(i, LOW);
  }
  if(temperature < 0)
    digitalWrite(13, HIGH);
  else if (temperature >= 0 && temperature < 30)
    digitalWrite(12, HIGH);
  else if (temperature >= 30 && temperature < 60)
    digitalWrite(11, HIGH);
  else if (temperature >= 60 && temperature < 90)
    digitalWrite(10, HIGH);
  else if (temperature >= 90)
    digitalWrite(9, HIGH);
}
  
void loop()
{
  int reading, temp;
  float voltage;
  reading = analogRead(A0);
  voltage = reading * 5.0/1024.0;
  temp = (voltage-0.5)*100;
  Serial.println(temp);
  setLed(temp);
  delay(100);
}

```
