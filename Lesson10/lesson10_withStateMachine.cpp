// Just slowly adding the powerpoint code to better understand it

#include <LiquidCrystal.h>
#include <stdio.h>

/* State Machine */
enum input_set {
 I_RELEASE,
 I_PRESS,
 I_MAX /* from my understanding, this is just to get the maximum
 		  number of states using the last enumerated item only as
          a "counter";
       */
};

struct input_t {
  enum input_set s;
  char key;
};

enum state_set {
  S_WAIT,
  S_PRESSED,
  S_RELEASED,
  S_MAX
};

struct state_t {
 enum state_set s;
 void (*output)(const char);
};

struct state_t s_next[S_MAX][I_MAX] = {
 [S_WAIT] = {
 [I_RELEASE] = { S_WAIT, do_nothing },
 [I_PRESS] = { S_PRESSED, do_nothing }
 },
 [S_PRESSED] = {
 [I_RELEASE] = { S_RELEASED, do_nothing },
 [I_PRESS] = { S_PRESSED, do_nothing }
 },
 [S_RELEASED] = {
 [I_RELEASE] = { S_WAIT, update_lcd1 },
 [I_PRESS] = { S_WAIT, update_lcd1 }
 }
};

/* Keypad */

char k0; // variable to store pressed character

const char row[] = {13, 12, 11, 10};
const char column[] = {3, 2, 1, 0};
const char key[][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

char scan_keypad() {
  for(int i = 0; i < sizeof(row); i++) {
   digitalWrite(row[i], HIGH); 
  }
  
  for(int i = 0; i < sizeof(row); i++) {
   	digitalWrite(row[i],LOW);
    
    for(int j = 0; j < sizeof(column); j++) {
      if(digitalRead(column[j]) == LOW) {
       return key[i][j]; 
      }
    }
  }
  
  return 0;
}

/* LCD Display */

#define RS 9
#define EN 8
#define DB4 4
#define DB5 5
#define DB6 6
#define DB7 7
LiquidCrystal lcd(RS, EN, DB4, DB5, DB6,
DB7);

char line0[17] = "hello, world";
char line1[17];
char pos1; /* cursor */

void do_nothing(const char c) {
  
}

void update_lcd1(const char c) {
  lcd.setCursor(0, 1);
  /* clear (when text reaches end of LCD space, I guess) */
  if(pos1 == 0) {
	memset(line1, ' ', sizeof(line1));
  }
  line1[pos1] = c;
  /* termination */
  line1[sizeof(line1) - 1] = '\0';
  pos1 = (pos1 + 1) % (sizeof(line1) - 1);
  lcd.print(line1);
}

struct input_t get_input() {
  struct input_t i;
  
  i.key = scan_keypad();
  if(i.key == 0) {
   i.s = I_RELEASE;
   i.key = k0;
  } else {
   i.s = I_PRESS;
   k0 = i.key;
  }
  
  return i;
}

void setup() {
 lcd.begin(16, 2);
 lcd.clear();
 lcd.setCursor(0, 0);
 lcd.print(line0);
 for (int i = 0; i < sizeof(row); i++)
 pinMode(row[i], OUTPUT);
 for (int j = 0; j < sizeof(column); j++)
 pinMode(column[j], INPUT_PULLUP);
} 

/* current state */
struct state_t state = {S_WAIT, NULL};

void loop() {
  struct input_t i;
  
  i = get_input();
  state = s_next[state.s][i.s];
  (*state.output)(i.key);
  delay(50);
}
