#include <Servo.h>

Servo myservo1;
Servo myservo2;

Servo belt1;
Servo belt2;

int potpin = 0;
int val;
int POS = 0;

int MIN = 150;
int MAX = 200;
int STOP = 0;

int MAX_MOTOR = 500;
int MIN_MOTOR = 400;

void setup() {
  Serial.begin(9600); // set the baud rate to 9600

  // make 10 RIGHT motor
  myservo1.attach(10,1100,2000);

  // make 11 LEFT motor
  myservo2.attach(11,1100,2000);

  // make 5 and 6 BELT motor
  belt1.attach(5,1100,2000);
  belt2.attach(6,1100,2000);
}

void loop() {
  if (Serial.available() >= 2) { // check if 2 bytes are available

    byte highByte = Serial.read(); // read the high byte
    byte lowByte = Serial.read(); // read the low byte
    
    // combine the two bytes to form a 16-bit value
    int num = ((highByte << 8) | lowByte);

    // do something with the value
    Serial.print("Value read: ");
    Serial.println(num);

    int first_digit = num / 10000;

    if (first_digit == 1){

      // we are running the motors: 
       int second_digit = (num % 10000) / 1000;
       int third_digit = (num % 1000) / 100;
       int fourth_digit = (num % 100) / 10;
       int fifth_digit = num % 10;


       double left_percent = (second_digit * 10) + third_digit;
       double right_percent = (fourth_digit * 10) + fifth_digit;

       if (left_percent == 0 && right_percent==0){

         myservo1.write(STOP);
         myservo2.write(STOP);

       } else if (left_percent == 0){

         double right_val =  MIN + ((right_percent/100) * (MAX - MIN));
         myservo1.write(right_val);
         myservo2.write(STOP);

       } else if (right_percent == 0){


         double left_val =  MIN + ((left_percent/100) * (MAX - MIN));
         myservo2.write(left_val);
         myservo1.write(STOP);

       } else {

         double right_val =  MIN + ((right_percent/100) * (MAX - MIN));
         double left_val =  MIN + ((left_percent/100) * (MAX - MIN));

         myservo1.write(right_val);
         myservo2.write(left_val);

         Serial.print("writing to the right  ");
         Serial.println(right_val);
         Serial.print("writing to the left  ");
         Serial.println(left_val);
       }

    } else if(first_digit == 2){


      int fourth_digit = (num / 10) % 10;
      int fifth_digit = num % 10;

      int motor_percent = (10*fourth_digit) + fifth_digit;

      double motor_write = MIN_MOTOR + ((motor_percent/100) * (MAX_MOTOR - MIN_MOTOR));

      if (motor_percent == 0){

        belt1.write(STOP);
        belt2.write(STOP);

      } else {
        // these should always be the same speed 
        belt1.write(motor_write);
        belt2.write(motor_write);
        myservo1.write(STOP);
        myservo2.write(STOP);
        // we are controlling the belt motors 
      }
    }
  }
}

// int poop = 0;
// void loop() {
//   if (Serial.available() >= 2) { // check if 2 bytes are available
//     while (true)
//     {
//       belt1.write(poop);
//       belt2.write(poop);
//       Serial.println(poop);
//       poop = poop + 1;
//     }
//   }
// }

