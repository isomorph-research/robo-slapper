

#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include "robotarm.h"

Adafruit_7segment matrix = Adafruit_7segment();

const uint8_t C_char = 0x39;
const uint8_t L_char = 0x38;
const uint8_t R_char = 0x50;

const int green_pin = 2;
const int blue_pin = 3;
const int yellow_pin = 18;
const int orange_pin = 19;

const int done_pin = 7;

const int degree_offset = 5;

volatile movement *queue[1024];
volatile int pos;

void setup() {
  Serial.begin(9600);
  Serial.println("Embyr Technologies ROBO-SLAPPER");
  Serial.println("booting...");
  delay(1500);
  matrix.begin(0x70);

  pos = 0;
  pinMode(green_pin, INPUT_PULLUP);
  pinMode(blue_pin, INPUT_PULLUP);
  pinMode(yellow_pin, INPUT_PULLUP);
  pinMode(orange_pin, INPUT_PULLUP);
  pinMode(done_pin, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(green_pin), green_button, FALLING);
  attachInterrupt(digitalPinToInterrupt(blue_pin), blue_button, FALLING);
  attachInterrupt(digitalPinToInterrupt(yellow_pin), yellow_button, FALLING);
  attachInterrupt(digitalPinToInterrupt(orange_pin), orange_button, FALLING);

  int failure = 1;
  while(failure) {
      failure = init_arm();
  }
  Serial.println("ready");
}

void loop() {
  if(digitalRead(done_pin) == LOW) {
    Serial.println("performing movement");
    run_movement();
  }
}

void green_button() {
  Serial.println("green");
  if(pos < 1024) {
    movement *mvt = new movement;
    mvt->direction = RIGHT;
    mvt->degrees = degree_offset;
    queue[pos] = mvt;
    pos++;
  }
  return;
}

void blue_button() {
  Serial.println("blue");
  if(pos < 1024) {
    movement* mvt = new movement;
    mvt->direction = DOWN;
    mvt->degrees = degree_offset;
    queue[pos] = mvt;
    pos++;
  }
  return;
}

void yellow_button() {
  Serial.println("yellow");
  if(pos < 1024) {
    movement *mvt = new movement;
    mvt->direction = UP;
    mvt->degrees = degree_offset;
    queue[pos] = mvt;
    pos++;
  }
  return;
}

void orange_button() {
  Serial.println("orange");
  if(pos < 1024) {
    movement *mvt = new movement;
    mvt->direction = LEFT;
    mvt->degrees = degree_offset;
    queue[pos] = mvt;
    pos++;
  }
  return;
}

void run_movement() {
  if(pos == 0) {
    return;
  }
  Direction prev_dir = INVALID;
  int display_num = 0;
  bool new_dir = false;
  Serial.println(pos);
  for(int i = 0; i < pos; i++) {
    switch(queue[i]->direction) {
      case LEFT:
        Serial.println("LEFT");
        arm_left(queue[pos]->degrees);
        if(prev_dir == LEFT) {
          Serial.println("...");
          new_dir = false;
          display_num += queue[pos]->degrees;
        } else {
          display_num = queue[pos]->degrees;
          new_dir = true;
        }
        prev_dir = LEFT;
        Serial.println(display_num);
        break;

      case DOWN:
        Serial.println("DOWN");
        arm_down(queue[pos]->degrees);
        if(prev_dir == DOWN) {
          Serial.println("...");
          new_dir = false;
          display_num += queue[pos]->degrees;
        } else {
          display_num = queue[pos]->degrees;
          new_dir = true;
        }
        prev_dir = DOWN;
        Serial.println(display_num);
        break;

      case UP:
        Serial.println("UP");
        arm_up(queue[pos]->degrees);
        if(prev_dir == UP) {
          Serial.println("...");
          new_dir = false;
          display_num += queue[pos]->degrees;
        } else {
          display_num = queue[pos]->degrees;
          new_dir = true;
        }
        prev_dir = UP;
        Serial.println(display_num);
        break;

      case RIGHT:
        Serial.println("RIGHT");
        arm_right(queue[pos]->degrees);
        if(prev_dir == RIGHT) {
          Serial.println("...");
          new_dir = false;
          display_num += queue[pos]->degrees;
        } else {
          display_num = queue[pos]->degrees;
          new_dir = true;
        }
        prev_dir = RIGHT;
        Serial.println(display_num);
        break;
    }
    if(new_dir){
      matrix.print(0x0000, HEX);
      matrix.writeDisplay();
      delay(750);
    }
    matrix.print(display_num, DEC);
    matrix.writeDisplay();
    delay(250);
    delete(queue[pos]);
  }
  matrix.writeDigitRaw(0, 0x00);
  matrix.writeDigitRaw(1, C_char);
  matrix.writeDigitRaw(3, L_char);
  matrix.writeDigitRaw(4, R_char);
  matrix.writeDisplay();
  delay(1500);
  matrix.writeDigitRaw(0,0);
  matrix.writeDigitRaw(1,0);
  matrix.writeDigitRaw(3,0);
  matrix.writeDigitRaw(4,0);
  pos = 0;

  return;
}
