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
