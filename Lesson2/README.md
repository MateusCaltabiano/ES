![Lesson 2 Hardware image](/Lesson2/Lesson2.png)

### Source Code

```
void setup()
{
 pinMode(13, OUTPUT);
 pinMode(12, OUTPUT);
 pinMode(11, OUTPUT);
 pinMode(7, OUTPUT);
 pinMode(6, OUTPUT);
 pinMode(5, OUTPUT);
}
void loop()
{
 digitalWrite(13, HIGH);
 delay(200);
 digitalWrite(13, LOW);
 delay(200);
 digitalWrite(11, HIGH);
 delay(200);
 digitalWrite(11, LOW);
 delay(200);
 digitalWrite(6, HIGH);
 delay(200);
 digitalWrite(6, LOW);
 delay(200);
 digitalWrite(12, HIGH);
 delay(200);
 digitalWrite(12, LOW);
 delay(200);
 digitalWrite(7, HIGH);
 delay(200);
 digitalWrite(7, LOW);
 delay(200);
 digitalWrite(5, HIGH);
 delay(200);
 digitalWrite(5, LOW);
 delay(500);
}
```
