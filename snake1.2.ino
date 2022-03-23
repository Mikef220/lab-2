#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

int JSx = A0;
int JSy = A1;
int Buzzer = 4;

int x;
int y;

int incoming = 0;

Adafruit_MPU6050 mpu;

void setup() {
  
  Serial.begin(115200);
  pinMode(JSx, INPUT);
  pinMode(JSy, INPUT);

  while(!mpu.begin()){
    delay(10);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);


}

void loop() {
  x = analogRead(JSx);  //1V = 205   4V = 820
  y = analogRead(JSy);

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  


//JOYSTICK

  //Down
  if(x<205){
    Serial.println("Down");
    while(x<450){
      x = analogRead(JSx);
      checkBeep();
    }
    //Serial.println("None");
  }
  //Up
  if(x>820){
    Serial.println("Up");
    while(x>820){
      x = analogRead(JSx);
      checkBeep();
    }
    //Serial.println("None");
  }
  //Left
  if(y<205){
    Serial.println("Left");
    while(y<450){
      y = analogRead(JSy);
      checkBeep();
    }
    //Serial.println("None");
  }
  //Right
  if(y>820){
    Serial.println("Right");
    while(y>820){
      y = analogRead(JSy);
      checkBeep();
    }
    //Serial.println("None");
  }

  checkBeep();
//GYRO

  //Left
  if(g.gyro.x < -1.5){
    Serial.println("Left");
    while(1){
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);
      checkBeep();
      if(g.gyro.x > 0){
        break;
      }
    }
    //Serial.println("None");
  }

  //Right
  if(g.gyro.x > 1.5){
    Serial.println("Right");
    while(1){
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);
      checkBeep();
      if(g.gyro.x < 1){
        break;
      }
    }
    //Serial.println("None");
  }

  //Up
  if(g.gyro.y > 1.5){
    Serial.println("Up");
    while(1){
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);
      checkBeep();
      if(g.gyro.y < 0.5){
        break;
      }
    }
    //Serial.println("None");
  }

  //Down
  if(g.gyro.y < -1.5){
    Serial.println("Down");
    while(1){
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);
      checkBeep();
      if(g.gyro.y > -0.5){
        break;
      }
    }
    //Serial.println("None");
  }
  
}

void checkBeep(){
  if (Serial.available() > 0){
    incoming = Serial.read();
    if (incoming == 'B'){
      tone(Buzzer, 3520, 100);
      incoming = 0;
    }
  }
  return;
}
