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
