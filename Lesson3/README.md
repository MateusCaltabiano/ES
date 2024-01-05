![](/Lesson3/Lesson3.png)

### Source Code
```
void setup()
{
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);  
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
      Serial.println((String)pin + " LOW");
    } else {
      digitalWrite(pin, HIGH);
      Serial.println((String)pin + " HIGH");
    }
  }
}

void loop() 
{
  for(int i = 0; i < sizeof(pattern)/sizeof(pattern[0]); i++) {
    setLed(pattern[i]);
    delay(500);
  }
}
```
