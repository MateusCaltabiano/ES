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

![Lesson 7B Hardware image](/Lesson7/Lesson7-B.png)

### Source code for leftmost board

```
#define DATA_IN 5 // data from board 2
#define DATA_OUT 6 // sends data
#define INT_OUT 7 // sends interrupt signal
#define LED_A 13
#define LED_B 12

int led = 2;

void setup()
{
 pinMode(LED_A, OUTPUT);
 pinMode(LED_B, OUTPUT);
 pinMode(INT_OUT, OUTPUT);
 pinMode(DATA_OUT, OUTPUT);
 pinMode(DATA_IN, INPUT_PULLUP);
 attachInterrupt(digitalPinToInterrupt(DATA_IN), on_data, FALLING);
 digitalWrite(INT_OUT, HIGH);
 digitalWrite(DATA_OUT, LOW);
 
 TCCR1A = 0;
 TCCR1B = (1 << WGM12) | (1 << CS12);
 OCR1A = 62500 - 1;
 TIMSK1 |= (1 << OCIE1A);
 
 update_led();
}

ISR(TIMER1_COMPA_vect)
{ 
 digitalWrite(DATA_OUT, (led & 1) ? HIGH : LOW);
 digitalWrite(INT_OUT, LOW);
 digitalWrite(INT_OUT, HIGH);
 int s;
 s = digitalRead(DATA_IN);
 led >>= 1;
 led &= 0x03;
 if(s == HIGH) {
 	led |= 2;
 }
 update_led();
}

void on_data()
{
  int s;
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
#define INT_IN 2 // receives interrupt signal
#define DATA_IN 3 // receives data
#define DATA_OUT 4 // sends data

int led = 1;

void setup()
{
 pinMode(LED_C, OUTPUT);
 pinMode(LED_D, OUTPUT);
 pinMode(DATA_OUT, OUTPUT);
 pinMode(DATA_IN, INPUT_PULLUP);
 pinMode(INT_IN, INPUT_PULLUP);
 attachInterrupt(digitalPinToInterrupt(INT_IN), on_data, FALLING);
 update_led();
}

void on_data()
{
 digitalWrite(DATA_OUT, (led & 1) ? HIGH : LOW);
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
