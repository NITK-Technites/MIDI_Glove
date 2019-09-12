#include <Wire.h>
#define ON 0x90
#define OFF 0x80
#define v 100
int k=0;

int gyro_x, gyro_y, gyro_z;
long gyro_x_cal, gyro_y_cal, gyro_z_cal;
boolean set_gyro_angles;

long acc_x, acc_y, acc_z, acc_total_vector;
float angle_roll_acc, angle_pitch_acc;

float angle_pitch, angle_roll;
int angle_pitch_buffer, angle_roll_buffer;
float angle_pitch_output, angle_roll_output;

long loop_timer;
int temp;


void setup() {
  // put your setup code here, to run once:
  Wire.begin();                                                        
  setup_mpu_6050_registers();                                          
  for (int cal_int = 0; cal_int < 1000 ; cal_int ++){                 
    read_mpu_6050_data();                                            
    gyro_x_cal += gyro_x;                                              
    gyro_y_cal += gyro_y;                                              
    gyro_z_cal += gyro_z;                                              
    delay(3);                                                          
  }
  
  gyro_x_cal /= 1000;                                                 
  gyro_y_cal /= 1000;                                                 
  gyro_z_cal /= 1000;                                                 
  loop_timer = micros(); 
  Serial.begin(9600);
  
}


void loop() {
  // put your main code here, to run repeatedly:
  read_mpu_6050_data();   
  gyro_x -= gyro_x_cal;                                                
  gyro_y -= gyro_y_cal;                                                
  gyro_z -= gyro_z_cal;                                                
         
 
  angle_pitch += gyro_x * 0.0000611;                                  
  angle_roll += gyro_y * 0.0000611;                                    
  angle_pitch += angle_roll * sin(gyro_z * 0.000001066);               
  angle_roll -= angle_pitch * sin(gyro_z * 0.000001066);               
  
  acc_total_vector = sqrt((acc_x*acc_x)+(acc_y*acc_y)+(acc_z*acc_z)); 
  angle_pitch_acc = asin((float)acc_y/acc_total_vector)* 57.296;      
  angle_roll_acc = asin((float)acc_x/acc_total_vector)* -57.296;       
  
  angle_pitch_acc -= 0.0;                                              
  angle_roll_acc -= 0.0;                                              

  if(set_gyro_angles){                                                 
    angle_pitch = angle_pitch * 0.9996 + angle_pitch_acc * 0.0004;     
    angle_roll = angle_roll * 0.9996 + angle_roll_acc * 0.0004;       
  }
  else{                                                                
    angle_pitch = angle_pitch_acc;                                    
    angle_roll = angle_roll_acc;                                      
    set_gyro_angles = true;                                            
  }
  
  angle_pitch_output = angle_pitch_output * 0.9 + angle_pitch * 0.1;   
  angle_roll_output = angle_roll_output * 0.9 + angle_roll * 0.1;     



 while(micros() - loop_timer < 4000);                                
 loop_timer = micros();
   
 
 play_tune();
  
}

void play_tune(){
 
 if(angle_pitch_output >=0 && angle_pitch_output <=16.36)
 {
   if(k!=1){
    Serial.write(ON);
    Serial.write(60);
    Serial.write(v);

    delay(100);

    Serial.write(OFF);
    Serial.write(60);
    Serial.write(v);

    delay(100);
    k=1;
 }
 }

 if(angle_pitch_output >=16.37 && angle_pitch_output <=32.72)
 {
  if(k!=2){
    Serial.write(ON);
    Serial.write(58);
    Serial.write(v);

    delay(100);

    Serial.write(OFF);
    Serial.write(58);
    Serial.write(v);

    delay(100);
    k=2;
 }
 }

 if(angle_pitch_output >=32.73 && angle_pitch_output <=49.08)
 {
  if(k!=3){
    Serial.write(ON);
    Serial.write(54);
    Serial.write(v);

    delay(100);

    Serial.write(OFF);
    Serial.write(54);
    Serial.write(v);

    delay(100);
    k=3;
 }
 }

 if(angle_pitch_output >=49.09 && angle_pitch_output <=65.44)
 {
  if(k!=4){
    Serial.write(ON);
    Serial.write(52);
    Serial.write(v);

    delay(100);

    Serial.write(OFF);
    Serial.write(52);
    Serial.write(v);

    delay(100);
    k=4;
 }
 }

 if(angle_pitch_output >=65.45 && angle_pitch_output <=81.80)
  {
    if(k!=5){
    Serial.write(ON);
    Serial.write(50);
    Serial.write(v);

    delay(100);

    Serial.write(OFF);
    Serial.write(50);
    Serial.write(v);

    delay(100);
    k=5;
  }
  }

 if(angle_pitch_output >=81.81 && angle_pitch_output <=90)
 {
  if(k!=6){
    Serial.write(ON);
    Serial.write(48);
    Serial.write(v);

    delay(100);

    Serial.write(OFF);
    Serial.write(48);
    Serial.write(v);

    delay(100);
    k=6;
 }
 }

 if(angle_pitch_output >=-16.36 && angle_pitch_output <0)
 {
  if(k!=7){
    Serial.write(ON);
    Serial.write(62);
    Serial.write(v);

    delay(100);

    Serial.write(OFF);
    Serial.write(62);
    Serial.write(v);

    delay(100);
    k=7;
 }
 }
 if(angle_pitch_output >=-32.72 && angle_pitch_output <=-16.37) 
 {
  if(k!=8){
    Serial.write(ON);
    Serial.write(64);
    Serial.write(v);

    delay(100);

    Serial.write(OFF);
    Serial.write(64);
    Serial.write(v);

    delay(100);
    k=8;
 }
 }

 if(angle_pitch_output >=-49.08 && angle_pitch_output <=-32.73)
 {
  if(k!=9){
    Serial.write(ON);
    Serial.write(66);
    Serial.write(v);

    delay(100);

    Serial.write(OFF);
    Serial.write(66);
    Serial.write(v);

    delay(100);
    k=9;
 }
 }
 
 if(angle_pitch_output >=-65.44 && angle_pitch_output <=-49.09)
 {
  if(k!=10){
    Serial.write(ON);
    Serial.write(68);
    Serial.write(v);

    delay(100);

    Serial.write(OFF);
    Serial.write(68);
    Serial.write(v);

    delay(100);
    k=10;
 }}

 if(angle_pitch_output >=-81.08 && angle_pitch_output <=-65.45)
 {
  if(k!=11){
    Serial.write(ON);
    Serial.write(70);
    Serial.write(v);

    delay(100);

    Serial.write(OFF);
    Serial.write(70);
    Serial.write(v);

    delay(100);
    k=11;
 }}

 if(angle_pitch_output >=-90 && angle_pitch_output <=-81.09)
 {
  if(k!=12){
    Serial.write(ON);
    Serial.write(72);
    Serial.write(v);

    delay(100);

    Serial.write(OFF);
    Serial.write(72);
    Serial.write(v);

    delay(100);
    k=12;
 }
 }
}



void setup_mpu_6050_registers(){
 
  Wire.beginTransmission(0x68);                                      
  Wire.write(0x6B);                                                  
  Wire.write(0x00);                                                    
  Wire.endTransmission();                                             
  Wire.beginTransmission(0x68);                                      
  Wire.write(0x1C);                                                   
  Wire.write(0x10);                                                    
  Wire.endTransmission();                                             
  Wire.beginTransmission(0x68);                                        
  Wire.write(0x1B);                                                  
  Wire.write(0x08);                                                    
  Wire.endTransmission();                                             
}


void read_mpu_6050_data(){                                             
  Wire.beginTransmission(0x68);                                        
  Wire.write(0x3B);                                                   
  Wire.endTransmission();                                             
  Wire.requestFrom(0x68,14);                                           
  while(Wire.available() < 14);                                        
  acc_x = Wire.read()<<8|Wire.read();                                  
  acc_y = Wire.read()<<8|Wire.read();                                  
  acc_z = Wire.read()<<8|Wire.read();                                  
  temp = Wire.read()<<8|Wire.read();                                   
  gyro_x = Wire.read()<<8|Wire.read();                                 
  gyro_y = Wire.read()<<8|Wire.read();                                 
  gyro_z = Wire.read()<<8|Wire.read();                                 
}

