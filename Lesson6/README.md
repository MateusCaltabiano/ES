![Lesson 6-a Hardware image](/Lesson6/Lesson%6-projectA.png)

### Source code

```
void setup()
{
  pinMode(2, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), on_push, FALLING);
  Serial.begin(9600);
}

void on_push()
{
  Serial.println(digitalRead(13));
  digitalWrite(13, !digitalRead(13));
}

void loop()
{
  delay(1000);
}
```
