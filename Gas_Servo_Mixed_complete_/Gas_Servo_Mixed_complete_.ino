#include <Servo.h>

Servo myservo;

int pos = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(9); //서보 출력 핀
}

void loop() {
  //가스센서 변수명
  float sensor_volt;
  float RS_gas; // 가스에 RS 값
  float ratio; // RS_GAS/RS_air 비율
  float R0;  // R0 via in LPG
  
  int sensorValue = analogRead(A0); //가스센서 입력 핀
  sensor_volt = (float)sensorValue / 1024 * 5.0;
  RS_gas = (5.0 - sensor_volt) / sensor_volt; // omit *RL

  ratio = RS_gas / R0; // ratio = RS/R0

  Serial.print("sensor_volt = ");
  Serial.println(sensor_volt);
  Serial.print("RS_ratio = ");
  Serial.println(RS_gas);
  Serial.print("Rs/R0 = ");
  Serial.println(ratio);

  Serial.print("\n\n");

  delay(1000);
  //서보모터 
  myservo.write(0);
  //가스센서 값 입력받아 서보모터 조절
  if (RS_gas < 0.95 ) {
    myservo.write(180);
    delay(1000);

    myservo.write(0);
    delay(1000);
  }
}

