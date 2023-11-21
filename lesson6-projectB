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
