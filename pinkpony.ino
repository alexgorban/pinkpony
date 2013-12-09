#include <Servo.h>

const int LEDs[] = {2,3,5,6,7,8,9};
const int EYE_SERVO_PIN = 12;
const int BUTTON_PIN = 11;
const int LIGHT_PIN = 10;

const int MIN_LIGHT = 20;
const int LIGHT_SEQ1_DELAY = 100;
const int EYE_DOWN = 850;
const int EYE_UP = 1900;

Servo eye_servo;

void setup() {
  int led_count = sizeof(LEDs)/sizeof(int);
  for (int i=0; i<led_count; i++) {
    pinMode(LEDs[i], OUTPUT);
  }

  pinMode(BUTTON_PIN, INPUT);
  pinMode(LIGHT_PIN, INPUT);

  eye_servo.attach(EYE_SERVO_PIN);

  Serial.begin(9600);
}

void lights_seq1() {
  static int i = 0; 
  int led_count = sizeof(LEDs)/sizeof(int);
  i = (i+1) % led_count;
  digitalWrite(LEDs[i], HIGH);
  delay(LIGHT_SEQ1_DELAY);
  digitalWrite(LEDs[i], LOW);  
  delay(LIGHT_SEQ1_DELAY);
}

void eyes_close() {
  eye_servo.write(EYE_DOWN);
}

void eyes_open() {
  eye_servo.write(EYE_UP);
}

void blink() {
  eyes_close();
  delay(300);
  eyes_open();
  delay(300);
}

void loop() {
  static int prev_button = LOW;

  int button = digitalRead(BUTTON_PIN);
  if (prev_button != button) {
     blink();
  }
  prev_button = button;

  int light_value = analogRead(LIGHT_PIN);
  Serial.println(light_value);
  if (light_value < MIN_LIGHT) {
     lights_seq1();
  }
}
