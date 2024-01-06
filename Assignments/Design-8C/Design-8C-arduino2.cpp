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
