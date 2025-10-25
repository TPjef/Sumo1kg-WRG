#include <PS2X_lib.h>  // ไลบรารี PS2
#include <ATX2.h>      // ไลบรารี ATX2 สำหรับใช้ XIO()

PS2X ps2x;

// PS2 Pins
#define PS2_DAT   24
#define PS2_CMD   26
#define PS2_SEL   28
#define PS2_CLK   30

// กำหนด Servo Channel
#define MOTOR_LEFT_CH  2   // SV2 (ซ้าย)
#define MOTOR_RIGHT_CH 1   // SV1 (ขวา)

// ค่าควบคุม servo
#define STOP_PWM     90
#define FORWARD_PWM 166
#define BACKWARD_PWM 32

void setup() {
  Serial.begin(9600);
  XIO();  // เปิดใช้งานพอร์ตของ ATX2

  int error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, true);
  if (error == 0) {
    Serial.println("PS2 controller connected");
  } else {
    Serial.print("PS2 config error: "); Serial.println(error);
  }
}

void loop() {
  ps2x.read_gamepad();

  int leftPWM = STOP_PWM;
  int rightPWM = STOP_PWM;

  if (ps2x.Button(PSB_R2)) {
    // หากกด R2 ให้หยุดทันที
    leftPWM = STOP_PWM;
    rightPWM = STOP_PWM;
  } else if (ps2x.Button(PSB_TRIANGLE)) {
    leftPWM = FORWARD_PWM;
    rightPWM = FORWARD_PWM;
  } else if (ps2x.Button(PSB_CROSS)) {
    leftPWM = BACKWARD_PWM;
    rightPWM = BACKWARD_PWM;
  } else if (ps2x.Button(PSB_PAD_LEFT)) {
    leftPWM = BACKWARD_PWM;
    rightPWM = FORWARD_PWM;
  } else if (ps2x.Button(PSB_PAD_RIGHT)) {
    leftPWM = FORWARD_PWM;
    rightPWM = BACKWARD_PWM;
  }

  // ควบคุมมอเตอร์
  servo(MOTOR_LEFT_CH, leftPWM);
  servo(MOTOR_RIGHT_CH, rightPWM);

  delay(0);
}
