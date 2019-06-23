// master_sender.ino
// Refer to the "slave_receiver" example for use with this
#include <Wire.h>
#include <PS2X_lib.h>
#include <Servo.h>
PS2X ps2x; // Create PS2 Controller Class


const int SLAVE_ADDRESS = 1;
char incomingByte = 0;
int error = 0; 
byte type = 0;
byte vibrate = 0;
// Start!!!!
// 車子有兩個馬達
// We choose car1 and car2 are the left motor, car3 and car4 are the right motor
int car1=7;
int car2=8;
int cara=9;
int car3=4;
int car4=5;
int carb=6;
// 升降
int rise1=A1;
int rise2=2;
int risea=3;
// 底盤馬達類比
int motor1=0;
int motor2=0;
int motor3=0;
int motor4=0;
// 車子底盤極限速度
int maxx=255;
int maxy=255;
// 車子旋轉極限速度
int maxxx=255;
int maxyy=255;
// 車子左右模式
int cor=0;
// reset
int reset=A2;
//JOJO!!!!
int jojo=0;


void setup() {  
  Wire.begin();         // join I2C bus as a Master
  Serial.begin(9600);
  Serial.println("Type something to send:");
//  底盤左馬達
  pinMode  ( car1 ,  OUTPUT );
  pinMode  ( car2 ,  OUTPUT );
  pinMode  ( cara ,  OUTPUT );
//  底盤右馬達
  pinMode  ( car3 ,  OUTPUT );
  pinMode  ( car4 ,  OUTPUT );
  pinMode  ( carb ,  OUTPUT );
//  升降
  pinMode  ( rise1 ,  OUTPUT );
  pinMode  ( rise2 ,  OUTPUT );
  pinMode  ( risea ,  OUTPUT );

//步進馬達
   
  error = ps2x.config_gamepad(13,11,10,12,true,true);
  if(error == 0){
    Serial.println("Found Controller, configured successful");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Go to www.billporter.info for updates and to report bugs.");
    }
  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
  else if(error == 1)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
   //Serial.print(ps2x.Analog(1), HEX);   
   type = ps2x.readType(); 
     switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");
       break;
     }
}

void loop() {
  if(error == 1)
  return;
  else{
    ps2x.read_gamepad(false,vibrate);

  motor1=ps2x.Analog(PSS_LY);
  motor2=ps2x.Analog(PSS_LX);
  
 //置物盒前伸     
           if(ps2x.ButtonPressed(PSB_PAD_UP)) {      
           Wire.beginTransmission(SLAVE_ADDRESS);
           Wire.write("1");
           Wire.endTransmission();
           }
          if(ps2x.ButtonReleased(PSB_PAD_UP)){
          Wire.beginTransmission(SLAVE_ADDRESS);
          Wire.write("2");
          Wire.endTransmission();
         }
//置物盒後縮         
         if(ps2x.ButtonPressed(PSB_PAD_DOWN)){      
           Wire.beginTransmission(SLAVE_ADDRESS);
           Wire.write("3");
           Wire.endTransmission();
           }    
         if(ps2x.ButtonReleased(PSB_PAD_DOWN)){      
           Wire.beginTransmission(SLAVE_ADDRESS);
           Wire.write("4");
           Wire.endTransmission();
           }
//開啟置物箱
         if(ps2x.ButtonPressed(PSB_R1)){     
         Wire.beginTransmission(SLAVE_ADDRESS);
          Wire.write("5");
          Wire.endTransmission();
         }
         if(ps2x.ButtonReleased(PSB_R1)){      
         Wire.beginTransmission(SLAVE_ADDRESS);
          Wire.write("6");
          Wire.endTransmission();
         }
//關閉置物箱
         if(ps2x.ButtonPressed(PSB_R2)){      
          Wire.beginTransmission(SLAVE_ADDRESS);
          Wire.write("7");
          Wire.endTransmission();
         }
         if(ps2x.ButtonReleased(PSB_R2)){     
          Wire.beginTransmission(SLAVE_ADDRESS);
          Wire.write("8");
          Wire.endTransmission();
         }     
// 置物盒歸零
          if (jojo==0){
              Wire.beginTransmission(SLAVE_ADDRESS);
              Wire.write("j");
              Wire.endTransmission();
              jojo=87;
          }
 //閉爪
         if(ps2x.Button(PSB_RED)) {           
          Wire.beginTransmission(SLAVE_ADDRESS);
          Wire.write("9");
          Wire.endTransmission();
         }
      /*  if(ps2x.ButtonReleased(PSB_RED)) {           
          Wire.beginTransmission(SLAVE_ADDRESS);
          Wire.write("a");
          Wire.endTransmission();
         }*/
         
//開爪
         if(ps2x.Button(PSB_PINK)) {         
         Wire.beginTransmission(SLAVE_ADDRESS);
          Wire.write("b");
          Wire.endTransmission();
         }
         /*
         if(ps2x.ButtonReleased(PSB_PINK)) {     
         Wire.beginTransmission(SLAVE_ADDRESS);
          Wire.write("c");
          Wire.endTransmission();
         }*/
         
//手臂前伸 
        if(ps2x.Analog(PSS_RY)==0){       
         Wire.beginTransmission(SLAVE_ADDRESS);
          Wire.write("d");
          Wire.endTransmission();
        }
//手臂後縮
        if(ps2x.Analog(PSS_RY)==255){    
         Wire.beginTransmission(SLAVE_ADDRESS);
          Wire.write("e");
          Wire.endTransmission();
        }
//手臂靜止
        if( (ps2x.Analog(PSS_RY)<=150) && (ps2x.Analog(PSS_RY)>=100)){      
         Wire.beginTransmission(SLAVE_ADDRESS);
          Wire.write("f");
          Wire.endTransmission();
        }
 
//上升
         if(ps2x.ButtonPressed(PSB_L2)) {        
         analogWrite(rise1,255);
         digitalWrite(rise2,LOW);
         analogWrite(risea,255);
         }
         if(ps2x.ButtonReleased(PSB_L2)) {    
         analogWrite(rise1,0);
         }
//下降
         if(ps2x.ButtonPressed(PSB_L1)){    
         analogWrite(rise1,0);
         digitalWrite(rise2,HIGH);
         analogWrite(risea,255);
         }
         if(ps2x.ButtonReleased(PSB_L1)){    
        digitalWrite(rise2,LOW);
         }
         
/*
//上層置物櫃智慧上升
        if(ps2x.ButtonPressed(PSB_GREEN)){
         analogWrite(rise1,0);
         digitalWrite(rise2,HIGH);
         analogWrite(risea,255);
         delay(900);
         delay(900);
         delay(900);
         delay(900);
         analogWrite(risea,0);
        }
*/          
//下層置物櫃智慧上升
        if(ps2x.ButtonPressed(PSB_BLUE)){
         analogWrite(rise1,0);
         digitalWrite(rise2,HIGH);
         analogWrite(risea,255);
         delay(900);
         analogWrite(risea,0);
        }
//MASTER RESET
  if(ps2x.ButtonPressed(PSB_R3)){ 
    analogWrite(reset,0);
  }
  
//SLAVE RESET
  if(ps2x.ButtonPressed(PSB_L3)){ 
     Wire.beginTransmission(SLAVE_ADDRESS);
          Wire.write("r");
          Wire.endTransmission();
  }

//        偵測類比鍵
// 車子往後
        if(motor2>140){
 //        Serial.println("backward");
         motor3 = map(motor2, 140, 255, 0, maxx);
         motor4 = map(motor2, 140, 255, 0, maxy);       
         digitalWrite(car1,HIGH);
         digitalWrite(car2,LOW);
         analogWrite(cara,motor4);
         digitalWrite(car3,LOW);
         digitalWrite(car4,HIGH);
         analogWrite(carb,motor3);
         }
// 車子往前
        if(motor2<115){ 
 //         Serial.println("forward");
         motor3 = map(motor2, 115, 0, 0, maxx);
         motor4 = map(motor2, 115, 0, 0, maxy);          
         digitalWrite(car1,LOW);
         digitalWrite(car2,HIGH);
         analogWrite(cara,motor4);
         digitalWrite(car3,HIGH);
         digitalWrite(car4,LOW);
         analogWrite(carb,motor3);
         } 
// 車子右轉
        if(motor1>140){  
   //       Serial.println(motor1);  
         motor4 = map(motor1, 140, 255, 0, maxxx);
         motor3 = map(motor1, 140, 255, 0, maxyy); 
         if (cor==0){
          digitalWrite(car1,HIGH);
          digitalWrite(car2,LOW);
          digitalWrite(car3,HIGH);
          digitalWrite(car4,LOW);
          }
         if (cor==1){
          digitalWrite(car1,LOW);
          digitalWrite(car2,HIGH);
          digitalWrite(car3,LOW);
          digitalWrite(car4,HIGH);
         }
         analogWrite(cara,motor4);
         analogWrite(carb,motor3);
        }
// 車子左轉  
        if(motor1<115){     
   //       Serial.println("no");   
         motor4 = map(motor1, 115, 0, 0, maxxx);
         motor3 = map(motor1, 115, 0, 0, maxyy); 
         if (cor==0){
           digitalWrite(car1,LOW);
           digitalWrite(car2,HIGH);
           digitalWrite(car3,LOW);
           digitalWrite(car4,HIGH);
         }
         if (cor==1){
           digitalWrite(car1,HIGH);
           digitalWrite(car2,LOW);
           digitalWrite(car3,HIGH);
           digitalWrite(car4,LOW);
         }
         analogWrite(cara,motor4);
         analogWrite(carb,motor3);
        }   
    }
   
//車子靜止
 if( (motor1<=140) && (motor1>=115) && (motor2<=140) &&  (motor2>=115)){    
         digitalWrite(car1,LOW);
         digitalWrite(car2,LOW);
         digitalWrite(car3,LOW);
         digitalWrite(car4,LOW);
 }  
//微調模式
if(ps2x.ButtonPressed(PSB_START)) {
  if (maxx==255){
    maxx=200;
    maxy=200;
    maxxx=225;
    maxyy=225;
  }
 else if (maxx==200){
    maxx=255;
    maxy=255;
    maxxx=255;
    maxyy=255;
  }
}

//左右模式
if(ps2x.ButtonPressed(PSB_SELECT)){
  if (cor==0){
    cor=1;
  }
  else if (cor==1){
    cor=0;
  }
}

  delay(50);
}
void serialEvent()
{
  // read one byte from serial port
  incomingByte = Serial.read();

  // send the received data to slave
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(incomingByte);
  Wire.endTransmission();
}
