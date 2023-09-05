#include <ESP32Servo.h>
#include <analogWrite.h>
//#include <tone.h>
#include <ESP32Tone.h>
#include <ESP32PWM.h>

#define OPEN_CLAW  1
#define CLOSE_CLAW 2
#define FORE_UP  3
#define FORE_DOWN  4
#define MAIN_UP  5
#define MAIN_DOWN 6
#define STOP  7
#define CMD_BUFF_LEN  6

#define SERVO_PIN 26
#define SERVO_F 32
#define SERVO_M 33
Servo servoMotor;
Servo servoMotor2;
Servo servoMotor3;
int hold = 0;
int pos = 0;
int pos_c = 90;
int pos_f = 90;
int pos_m = 45;
int angle_c = 180;
int angle_o = 90;
int angle_w = 145;
int angle_s = 45;
int angle_u = 170;
int angle_d = 90;
char c;
char str[CMD_BUFF_LEN];
uint8_t idx = 0;
uint8_t state = OPEN_CLAW;

void setup() {
  Serial.begin(115200);
  servoMotor.attach(SERVO_PIN);
  servoMotor.write(pos_c);
  servoMotor2.attach(SERVO_F);
  servoMotor2.write(pos_f);
  servoMotor3.attach(SERVO_M);
  servoMotor3.write(pos_m);
  delay(100);
  //  Serial.println("'O' to open, 'C' to close: ");
  //  while (Serial.available() == 0) {
  //    Serial.print(".");
  //    delay(500);
  //  }
  //  while (Serial.available() > 0) {
  //    Serial.read(); //Empty the read buffer
  //  }
  Serial.println("'1' for claw, '2' for forearm, '3' for main arm");
}

void loop() {

  if (Serial.available() > 0) {
    c = Serial.read();
    if (c != '\n') {
      str[idx++] = c;
    }
    else {
      str[idx] = '\0';

      state = interpret(str[0]);

      idx = 0;
    }
  }
  switch (state) {
    case 1:
      open_c();
      break;

    case 2:
      close_c();
      break;

    case 3:
      up_f();
      break;

    case 4:
      down_f();
      break;

    case 5:
      up_m();
      break;

    case 6:
      down_m();
      break;

    case 7:
      stop_c();
      break;

    default:
      stop_c();
      break;
  }

}

void down_m() {
  pos = servoMotor3.read();
  if (pos < angle_s) {
    while (pos < angle_s) {
      pos += 1;
      servoMotor3.write(pos);
      if (Serial.available() > 0) {
        break;
      }
      delay(15);
    }
  } else if (pos > angle_s) {
    while (pos > angle_s) {
      pos -= 1;
      servoMotor3.write(pos);
      if (Serial.available() > 0) {
        break;
      }
      delay(15);
    }
  }
}

void up_m() {
  pos = servoMotor3.read();
  if (pos < angle_w) {
    while (pos < angle_w) {
      pos += 1;
      servoMotor3.write(pos);
      if (Serial.available() > 0) {
        break;
      }
      delay(15);
    }
  } else if (pos > angle_w) {
    while (pos > angle_w) {
      pos -= 1;
      servoMotor3.write(pos);
      if (Serial.available() > 0) {
        break;
      }
      delay(15);
    }
  }
}

void down_f() {
  pos = servoMotor2.read();
  if (pos < angle_d) {
    while (pos < angle_d) {
      pos += 1;
      servoMotor2.write(pos);
      if (Serial.available() > 0) {
        break;
      }
      delay(15);
    }
  } else if (pos > angle_d) {
    while (pos > angle_d) {
      pos -= 1;
      servoMotor2.write(pos);
      if (Serial.available() > 0) {
        break;
      }
      delay(15);
    }
  }
}

void up_f() {
  pos = servoMotor2.read();
  if (pos < angle_u) {
    while (pos < angle_u) {
      pos += 1;
      servoMotor2.write(pos);
      if (Serial.available() > 0) {
        break;
      }
      delay(15);
    }
  } else if (pos > angle_u) {
    while (pos > angle_u) {
      pos -= 1;
      servoMotor2.write(pos);
      if (Serial.available() > 0) {
        break;
      }
      delay(15);
    }
  }
}

void open_c() {
  pos = servoMotor.read();
  if (pos < angle_o) {
    while (pos < angle_o) {
      pos += 1;
      servoMotor.write(pos);
      if (Serial.available() > 0) {
        break;
      }
      delay(15);
    }
  } else if (pos > angle_o) {
    while (pos > angle_o) {
      pos -= 1;
      servoMotor.write(pos);
      if (Serial.available() > 0) {
        break;
      }
      delay(15);
    }
  }
  //  servoMotor.write(90);
}

void close_c() {
  pos = servoMotor.read();
  if (pos < angle_c) {
    while (pos < angle_c) {
      pos += 1;
      servoMotor.write(pos);
      if (Serial.available() > 0) {
        break;
      }
      delay(15);
    }
  } else if (pos > angle_c) {
    while (pos > angle_c) {
      pos -= 1;
      servoMotor.write(pos);
      if (Serial.available() > 0) {
        break;
      }
      delay(15);
    }
  }
  //  servoMotor.write(180);
}

void stop_c() {
  hold = servoMotor.read();
  Serial.println(hold);
  servoMotor.write(hold+1);
}

uint8_t interpret(char c) {
  switch (c) {
    case 'O': return OPEN_CLAW;
    case 'C': return CLOSE_CLAW;
    case 'o': return OPEN_CLAW;
    case 'c': return CLOSE_CLAW;
    case 'D': return FORE_DOWN;
    case 'U': return FORE_UP;
    case 'd': return FORE_DOWN;
    case 'u': return FORE_UP;
    case 'W': return MAIN_UP;
    case 'S': return MAIN_DOWN;
    case 'w': return MAIN_UP;
    case 's': return MAIN_DOWN;
    case 'k': return STOP;
    case 'K': return STOP;
    default: Serial.println("UNKNOWN");
  }
  return state;
}
