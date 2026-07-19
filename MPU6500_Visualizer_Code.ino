
#include <Wire.h>
#define MPU_ADDR 0x68

float roll=0,pitch=0,yaw=0;
unsigned long lastIMU,lastSend;

void setup(){
 Serial.begin(115200);
 Wire.begin();

 Wire.beginTransmission(MPU_ADDR);
 Wire.write(0x6B);
 Wire.write(0x00);
 Wire.endTransmission();

 delay(500);
 lastIMU=millis();
}

void loop(){

 Wire.beginTransmission(MPU_ADDR);
 Wire.write(0x3B);
 Wire.endTransmission(false);
 Wire.requestFrom(MPU_ADDR,14);

 if(Wire.available()<14) return;

 int16_t axR=Wire.read()<<8|Wire.read();
 int16_t ayR=Wire.read()<<8|Wire.read();
 int16_t azR=Wire.read()<<8|Wire.read();

 Wire.read(); Wire.read();

 int16_t gxR=Wire.read()<<8|Wire.read();
 int16_t gyR=Wire.read()<<8|Wire.read();
 int16_t gzR=Wire.read()<<8|Wire.read();

 float ax=axR/16384.0;
 float ay=ayR/16384.0;
 float az=azR/16384.0;

 float gx=gxR/131.0;
 float gy=gyR/131.0;
 float gz=gzR/131.0;

 unsigned long now=millis();
 float dt=(now-lastIMU)/1000.0;
 lastIMU=now;

 float rollAcc=atan2(ay,az)*180.0/PI;
 float pitchAcc=atan2(-ax,sqrt(ay*ay+az*az))*180.0/PI;

 roll=0.95*(roll+gx*dt)+0.05*rollAcc;
 pitch=0.95*(pitch+gy*dt)+0.05*pitchAcc;

 if(abs(gz)>1.5) yaw+=gz*dt;

 if(millis()-lastSend>50){
  lastSend=millis();

  Serial.print("DATA,");
  Serial.print(roll,2);Serial.print(",");
  Serial.print(pitch,2);Serial.print(",");
  Serial.print(yaw,2);Serial.print(",");
  Serial.print(ax,3);Serial.print(",");
  Serial.print(ay,3);Serial.print(",");
  Serial.print(az,3);Serial.print(",");
  Serial.print(gx,2);Serial.print(",");
  Serial.print(gy,2);Serial.print(",");
  Serial.println(gz,2);
 }
}
