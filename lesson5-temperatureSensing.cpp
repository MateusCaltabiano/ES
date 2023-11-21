void setup()
{
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  
  TCCR1A = 0;
  TCCR1B = (1 << WGM12) | (1 << CS12);
  OCR1A = 31250 - 1;
}

void setLed(int temperature)
{
  for(int i = 9; i < 14; i++) {
    digitalWrite(i, LOW);
  }
  if(temperature < 0)
    digitalWrite(13, HIGH);
  else if (temperature >= 0 && temperature < 30)
    digitalWrite(12, HIGH);
  else if (temperature >= 30 && temperature < 60)
    digitalWrite(11, HIGH);
  else if (temperature >= 60 && temperature < 90)
    digitalWrite(10, HIGH);
  else if (temperature >= 90)
    digitalWrite(9, HIGH);
}
  
void loop()
{
  int reading, temp;
  float voltage;
  reading = analogRead(A0);
  voltage = reading * 5.0/1024.0;
  temp = (voltage-0.5)*100;
  Serial.println(temp);
  setLed(temp);
  delay(100);
}
