#include <stdint.h>

#include <avr/io.h>

#include <util/twi.h>

#include <util/delay.h>

#include <avr/pgmspace.h>

//m1 is the direction motor
//m2 is the power motor
// L is left 
// R is right
// F is forward
// B is Backward

int m1L = 13; 
int m1R = 12; 
int m2F = 11; 
int m2B = 10; 
int l1 = 9; //l1 is the green LED
int l2 = 8; //l2 is the red LED

void setup() {
  // put your setup code here, to run once:

  pinMode(m1L, OUTPUT);
  pinMode(m1R, OUTPUT);
  pinMode(m2F, OUTPUT);
  pinMode(m2B, OUTPUT);
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  steerLeft();
  delay(1000);
  steerRight();
  delay(1000);
  stop();
  delay(1000);
  goForward();
  delay(1000);
  goBackward();
  delay(1000);
  stop();
  delay(1000);

}


void steerLeft(){
    digitalWrite(l1, 1);
    digitalWrite(l2, 0);
    digitalWrite(m1L, 1);
    digitalWrite(m1R, 0);
  };
  
  void steerRight(){
    digitalWrite(l1, 1);
    digitalWrite(l2, 0);
    digitalWrite(m1L, 0);
    digitalWrite(m1R, 1);
  };

  void goForward() {
    digitalWrite(l1, 1);
    digitalWrite(l2, 0);
    digitalWrite(m2F, 1);
    digitalWrite(m2B, 0);
  };
  
  void goBackward() {
    digitalWrite(l1, 1);
    digitalWrite(l2, 0);
    digitalWrite(m2F, 0);
    digitalWrite(m2B, 1);
  };

  void stop() {
    digitalWrite(l1, 0);
    digitalWrite(l2, 1);
    digitalWrite(m1L, 0);
    digitalWrite(m1R, 0);
    digitalWrite(m2F, 0);
    digitalWrite(m2B, 0);
  }
