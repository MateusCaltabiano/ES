![Lesson 6-a Hardware image](/Lesson6/Lesson6-projectA.png)

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
![Lesson 6-b Hardware image](/Lesson6/lesson6-projectB.png)

### Source code

```
void setup()
{
  pinMode(13, OUTPUT);
  
  TCCR1A = 0;
  TCCR1B = (1 << WGM12) | (1 << CS12);
  OCR1A = 31250 - 1;
  TIMSK1 |= (1 << OCIE1A);

}

ISR(TIMER1_COMPA_vect)
{ 
  digitalWrite(13, !digitalRead(13));
}

void loop()
{
  delay(1000);
}
```
