#define BAUD_RATE 9600
#define MAX_BYTES 3
 
typedef enum {S_IDLE, S_READ, S_WRITE} state;
state next_state = S_IDLE;  
state current_state;
 
void setup() {
  Serial.begin(BAUD_RATE);
}
 
void loop() {
  current_state = next_state;
  echo_fsm();
}
 
void echo_fsm(){
  switch(current_state){
    case S_IDLE:
      next_state = (Serial.available() >= MAX_BYTES) ? S_READ : S_IDLE;
      break;
    case S_READ:
 
      int  digit;
      byte incoming_byte;
 
      for(int i = 0; i < MAX_BYTES; i++){
        incoming_byte = Serial.read();
        digit = utf8_to_digit(incoming_byte);
        Serial.print(digit);
      }
 
      next_state = S_WRITE;
      break;  
    case S_WRITE:
      Serial.println();
      next_state = S_IDLE;
      break;
  }
}
 
int utf8_to_digit(byte incoming_byte){
  switch(incoming_byte){
    case 0x30: return 0;
    case 0x31: return 1;
    case 0x32: return 2;
    case 0x33: return 3;
    case 0x34: return 4;
    case 0x35: return 5;
    case 0x36: return 6;
    case 0x37: return 7;
    case 0x38: return 8;
    case 0x39: return 9;
    default:   return 0;
  }
}
