void setup()
{
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  
  TCCR1A = 0;
  TCCR1B = (1 << WGM12) | (1 << CS10) | (1 << CS12);
  OCR1A = 23437.5 - 1;
  TIMSK1 |= (1 << OCIE1A);
}

ISR(TIMER1_COMPA_vect) {
  digitalWrite(8, !digitalRead(8));
}


void setLed(int temperature)
{
  for(int i = 9; i < 14; i++) {
  	digitalWrite(i, LOW);
  }
  if(temperature <= 0)
    digitalWrite(13, HIGH);
  else if(temperature > 0 && temperature <= 30)
    digitalWrite(12, HIGH);
  else if(temperature > 30 && temperature <= 60)
    digitalWrite(11, HIGH);
  else if(temperature > 60 && temperature <= 90)
    digitalWrite(10, HIGH);
  else
    digitalWrite(9, HIGH);
}

void loop()
{
  float temp = (analogRead(A0) * 5.0/1024.0 - 0.5) * 100;
  setLed(temp);
  delay(100);
}


