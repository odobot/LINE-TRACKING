// Define the motor output pins
#define LS1 1  // pin attached to the in1 of the left side motors
#define LS2 2  // pin attached to the in2 of the left side motors
#define LEN 3  // pin connected to the enable pin for the left side motors on the L298n
#define RS1 4  // pin attached to the in1 of the right side motors
#define RS2 5  // pin attached to the in2 of the right side motors
#define REN 6  // pin connected to the enable pin for the right side motors on the L298n

// Define the IR Sensor pins
#define RIR 7  // Arduino pin attached to the output pin of the ir sensor on the right
#define LIR 8  // Arduino pin attached to the output pin of the ir sensor on the left

void setup() {
  //Setting the motor pins as output and IR sensor pins as input
  pinMode(LS1, OUTPUT);
  pinMode(LS2, OUTPUT);
  pinMode(LEN, OUTPUT);
  pinMode(RS1, OUTPUT);
  pinMode(RS2, OUTPUT);
  pinMode(REN, OUTPUT);
  pinMode(RIR, INPUT);
  pinMode(LIR, INPUT);
}

void loop() {
  if (!digitalRead(LIR) && !digitalRead(RIR)) {
    //Move forward
    FORWARD(255);
  }

  if ((digitalRead(LIR)) && !digitalRead(RIR)) {
    //Turn left
    TURN_LEFT(255);
  }

  if (!digitalRead(LIR) && (digitalRead(RIR))) {
    //Turn Right
    TURN_RIGHT(255);
  }

  if ((digitalRead(LIR)) && (digitalRead(RIR))) {
    //Stop
    STOP();
  }
}

void RIGHT_MOTOR(int num, int speed) {
  switch (num) {
    case 0:
      {
        //Right motor stop
        digitalWrite(RS1, LOW);
        digitalWrite(RS2, LOW);
      }
    case 1:
      {
        //Right motor forward
        digitalWrite(RS1, HIGH);
        digitalWrite(RS2, LOW);
        analogWrite(REN, speed);
      }
    case 2:
      {
        //Right motor reverse
        digitalWrite(RS1, LOW);
        digitalWrite(RS2, HIGH);
        analogWrite(REN, speed);
      }
  }
}

void LEFT_MOTOR(int num, int speed) {
  switch (num) {
    case 0:
      {
        //Left motor stop
        digitalWrite(LS1, LOW);
        digitalWrite(LS2, LOW);
      }
    case 1:
      {
        //Left motor forward
        digitalWrite(LS1, HIGH);
        digitalWrite(LS2, LOW);
        analogWrite(LEN, speed);
      }
    case 2:
      {
        //Left motor reverse
        digitalWrite(LS1, LOW);
        digitalWrite(LS2, HIGH);
        analogWrite(LEN, speed);
      }
  }
}


void TURN_RIGHT(int speed) {
  RIGHT_MOTOR(0, 0);
  LEFT_MOTOR(1, speed);
}

void TURN_LEFT(int speed) {
  RIGHT_MOTOR(1, speed);
  LEFT_MOTOR(0, 0);
}

void FORWARD(int speed) {
  RIGHT_MOTOR(1, speed);
  LEFT_MOTOR(1, speed);
}

void STOP() {
  RIGHT_MOTOR(0, 0);
  LEFT_MOTOR(0, 0);
}
