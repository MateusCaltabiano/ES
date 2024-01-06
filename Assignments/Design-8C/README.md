![Design-8C Hardware image](/Assignments/Design-8C/DESIGN-8C(z123367).png)

### Source code for leftmost board

```
#include <LiquidCrystal.h>
#include <math.h>

#define RS 9
#define EN 8
#define DB4 4
#define DB5 5
#define DB6 6
#define DB7 7
#define DATA_OUT 11
#define DATA_IN 12
#define INT_OUT 10
#define SELECT_OUT 13
#define BUTTON_IN 3
#define MODE_OUT 2

LiquidCrystal lcd(RS, EN, DB4, DB5, DB6, DB7);

char firstLine[] = "ABCDEFGHIJKLMNOP";
char secondLine[] = "0123456789012345";

void update_lcd()
{
 
 lcd.setCursor(0, 0);
 lcd.print(firstLine);
 lcd.setCursor(0, 1);
 lcd.print(secondLine);
}

void setup()
{
 pinMode(DATA_OUT, OUTPUT);
 pinMode(DATA_IN, INPUT_PULLUP);
 pinMode(INT_OUT, OUTPUT);
 pinMode(SELECT_OUT, OUTPUT);
 pinMode(BUTTON_IN, INPUT_PULLUP);
 attachInterrupt(digitalPinToInterrupt(BUTTON_IN), on_push, FALLING);
 Serial.begin(9600);
 
 lcd.begin(16, 2);
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print(firstLine);
 lcd.setCursor(0, 1);
 lcd.print(secondLine);
 
 TCCR1A = 0;
 TCCR1B = (1 << WGM12) | (1 << CS12);
 OCR1A = 62500 - 1;
 TIMSK1 |= (1 << OCIE1A);
}

unsigned char shift_reg;
char save_line[] = "                ";

ISR(TIMER1_COMPA_vect)
{
 digitalWrite(MODE_OUT, LOW);
 digitalWrite(SELECT_OUT, HIGH);
 memcpy(save_line + 1, firstLine, sizeof(save_line) - 2);
 //Serial.println(save_line);
 shift_reg = firstLine[sizeof(firstLine) - 2];
 //Serial.print(shift_reg);
  for(int i = 0; i < 8; i++) {
   digitalWrite(INT_OUT, HIGH);
   digitalWrite(DATA_OUT, shift_reg & 1);
   //Serial.print(shift_reg & 1);
   digitalWrite(INT_OUT, LOW);
   delay(10);
   shift_reg >>= 1;
   if(digitalRead(DATA_IN) == HIGH) {
   	shift_reg |= 1 << 7;
    //Serial.print(shift_reg);
   }
  }
 //Serial.println(save_line);
 digitalWrite(SELECT_OUT, LOW);
 save_line[0] = shift_reg;
 //Serial.println(save_line[0]);
 //Serial.println(save_line);
 memcpy(firstLine, save_line, sizeof(firstLine));
 //Serial.println(firstLine);
 update_lcd();
}

void on_push()
{
 digitalWrite(MODE_OUT, HIGH);
 digitalWrite(SELECT_OUT, HIGH);
 memcpy(save_line + 1, secondLine, sizeof(save_line) - 2);
 //Serial.println(save_line);
 shift_reg = secondLine[sizeof(secondLine) - 2];
 //Serial.print(shift_reg);
  for(int i = 0; i < 8; i++) {
   digitalWrite(INT_OUT, HIGH);
   digitalWrite(DATA_OUT, shift_reg & 1);
   //Serial.print(shift_reg & 1);
   digitalWrite(INT_OUT, LOW);
   delay(10);
   shift_reg >>= 1;
   if(digitalRead(DATA_IN) == HIGH) {
   	shift_reg |= 1 << 7;
    //Serial.print(shift_reg);
   }
  }
 //Serial.println(save_line);
 digitalWrite(SELECT_OUT, LOW);
 save_line[0] = shift_reg;
 //Serial.println(save_line[0]);
 //Serial.println(save_line);
 memcpy(secondLine, save_line, sizeof(secondLine));
 //Serial.println(firstLine);
 update_lcd();
}

void loop()
{
 delay(1000);
}

```

### Source code for rightmost board

```

#include <LiquidCrystal.h>

#define RS 9
#define EN 8
#define DB4 4
#define DB5 5
#define DB6 6
#define DB7 7
#define DATA_IN 11
#define DATA_OUT 12
#define INT_IN 3
#define SELECT_IN 2
#define MODE_IN 13

LiquidCrystal lcd(RS, EN, DB4, DB5, DB6, DB7);

char firstLine[] = "0123456789012345";
char secondLine[] = "ABCDEFGHIJKLMNOP";
unsigned char shift_reg2;
char save_line[] = "                ";
int is_receiving = 0;

void setup()
{
 pinMode(DATA_IN, INPUT);
 pinMode(DATA_OUT, OUTPUT);
 pinMode(INT_IN, INPUT);
 pinMode(SELECT_IN, INPUT);
 attachInterrupt(digitalPinToInterrupt(INT_IN), on_data, FALLING);
 attachInterrupt(digitalPinToInterrupt(SELECT_IN), on_select, FALLING);
 Serial.begin(9600);
 
 lcd.begin(16, 2);
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print(firstLine);
 lcd.setCursor(0, 1);
 lcd.print(secondLine);
}

void on_data()
{
  if(digitalRead(MODE_IN)) {
    if(digitalRead(SELECT_IN) == LOW) {
        return;
      }
      if(!is_receiving){
        shift_reg2 = secondLine[sizeof(secondLine) - 2];    
      }
      digitalWrite(DATA_OUT, shift_reg2 & 1);
      shift_reg2 >>= 1;
      shift_reg2 |= digitalRead(DATA_IN) << 7;
      is_receiving = 1;
      return;
  }
  if(digitalRead(SELECT_IN) == LOW) {
        return;
      }
      if(!is_receiving){
        shift_reg2 = firstLine[sizeof(firstLine) - 2];    
      }
      digitalWrite(DATA_OUT, shift_reg2 & 1);
      shift_reg2 >>= 1;
      shift_reg2 |= digitalRead(DATA_IN) << 7;
      is_receiving = 1;
}

void on_select()
{
  if(digitalRead(MODE_IN)) {
   is_receiving = 0;
   memcpy(save_line + 1, secondLine, sizeof(save_line) - 2);
   save_line[0] = shift_reg2;
   memcpy(secondLine, save_line, sizeof(secondLine));
  }
  else {
   is_receiving = 0;
   memcpy(save_line + 1, firstLine, sizeof(save_line) - 2);
   save_line[0] = shift_reg2;
   memcpy(firstLine, save_line, sizeof(firstLine));
  }
 
 update_lcd(); 
}

void update_lcd()
{
 lcd.setCursor(0, 0);
 lcd.print(firstLine);
 lcd.setCursor(0, 1);
 lcd.print(secondLine);
}

void loop()
{
 delay(1000); 
}

```
