![Lesson 7A Hardware image](/Lesson7/Lesson7-A.png)

### Source code for leftmost board

```
#define DATA_OUT 6
#define INT_OUT 7
#define INT_IN 2
#define LED_A 13
#define LED_B 12

int led = 2;

void setup()
{
 pinMode(LED_A, OUTPUT);
 pinMode(LED_B, OUTPUT);
 pinMode(INT_OUT, OUTPUT);
 pinMode(DATA_OUT, OUTPUT);
 pinMode(INT_IN, INPUT_PULLUP);
 attachInterrupt(digitalPinToInterrupt(INT_IN),
 on_push, FALLING);
 digitalWrite(INT_OUT, HIGH);
 digitalWrite(DATA_OUT, LOW);
 update_led();
}

void on_push()
{
 digitalWrite(DATA_OUT, (led & 1) ? HIGH : LOW);
 digitalWrite(INT_OUT, LOW);
 digitalWrite(INT_OUT, HIGH);
 led >>= 1;
 led &= 0x03;
 update_led();
}

void update_led()
{
 digitalWrite(LED_A, (led >> 1) & 1 ? HIGH : LOW);
 digitalWrite(LED_B, (led >> 0) & 1 ? HIGH : LOW);
}

void loop()
{
 delay(1000); 
}
```

### Source code for rightmost board

```
#define LED_C 13
#define LED_D 12
#define INT_IN 2
#define DATA_IN 3

int led = 1;

void setup() 
{
 pinMode(LED_C, OUTPUT);
 pinMode(LED_D, OUTPUT);
 pinMode(DATA_IN, INPUT_PULLUP);
 pinMode(INT_IN, INPUT_PULLUP);
 attachInterrupt(digitalPinToInterrupt(INT_IN), on_data, FALLING);
 update_led();
}

void on_data()
{
 int s;
 led >>= 1;
 led &= 0x03;
 s = digitalRead(DATA_IN);
 if (s == HIGH) {
 	led |= 2;
 }
 update_led();
}

void update_led()
{
 digitalWrite(LED_C, (led >> 1) & 1 ? HIGH : LOW);
 digitalWrite(LED_D, (led >> 0) & 1 ? HIGH : LOW);
}

void loop()
{
 delay(1000); 
}
```
