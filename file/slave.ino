// slave_receiver.ino
// Refer to the "master_sender" example for use with this
#include <Wire.h>
#include <Servo.h>
Servo jawservo; // 夾爪馬達
Servo openservo;  // 閘門置物盒馬達
//設定I2Cx
const int SLAVE_ADDRESS = 1;
//設定接收指令
char c = 0;
// 置物盒伸縮
int box1=9;
int box2=10;
int boxa=11;
// 手臂
int arm1=8;
int arm2=7;
int arma=6;
// servo(步進)
int jaws=3;
int opens=3;
// 設定起始條件
int jojo=0;
//RESET
int reset=A2;

void setup() {  
  //I2C 設定
  Wire.begin(SLAVE_ADDRESS);    // join I2C bus as a slave with address 1
  Wire.onReceive(receiveEvent); // register event
  
  Serial.begin(9600);
  Serial.println("Received data:");
  //伺服馬達
  jawservo.attach(3);
  
  openservo.attach(5);
  //伺服馬達
  pinMode  ( box1 ,  OUTPUT );
  pinMode  ( box2 ,  OUTPUT );
  pinMode  ( boxa ,  OUTPUT );
  pinMode  ( arm1 ,  OUTPUT );
  pinMode  ( arm2 ,  OUTPUT );
  pinMode  ( arma ,  OUTPUT );
}
void receiveEvent(int howMany)
{
  while (Wire.available()) 
  {
    // receive one byte from Master
    c = Wire.read();
    Serial.print(c);
  }
}

void loop() {
//置物盒reset
          if (jojo==0 || c=='j'){
            jawservo.write(0);
            openservo.write(180);
            opens=180;
            jaws=0;
            jojo=jojo+87;
          }
          
//置物盒前伸
         if(c == '1'){  
          digitalWrite(box1,HIGH);
          digitalWrite(box2,LOW);
          analogWrite(boxa,150);
          }
          if(c == '2'){
          digitalWrite(box1,LOW);
          }
//置物盒後縮
         if(c == '3'){
          digitalWrite(box1,LOW);
          digitalWrite(box2,HIGH);
          analogWrite(boxa,150);
          }
          if(c == '4'){
          digitalWrite(box2,LOW);
          }
//開啟置物箱
         if (c == '5' ){        
          if (opens<=170){
            opens+=10;
            openservo.write(opens);
          }
         }
         if(c== '6' ){      
            openservo.write(opens);
         }
//關閉置物箱
        if(c=='7'){       
         if (opens>=10){
            opens-=10;
            openservo.write(opens);
          }
         }
         if(c=='8'){       
            openservo.write(opens);
         }
//置物盒起始
        if(c=='j'){
          openservo.write(180);
        }
//閉爪
         if(c=='9') {           
          if(jaws<177){
            jaws+=2;
            jawservo.write(jaws);
          }
         }
         
        if(c=='a') {           
            jawservo.write(jaws);
         }
         
//開爪
         if(c=='b') {        
         if(jaws>3){
            jaws-=2;
            jawservo.write(jaws);
          }
         }
         
         if(c=='c') {    
            jawservo.write(jaws);
         }
         
//手臂前伸 
         if(c=='d'){    
         digitalWrite(arm1,HIGH);
         digitalWrite(arm2,LOW);
         analogWrite(arma,110);
        }
//手臂後縮
        if(c=='e'){    
         digitalWrite(arm1,LOW);
         digitalWrite(arm2,HIGH);
         analogWrite(arma,110);
        }
        if(c=='f'){    
         digitalWrite(arm1,LOW);
         digitalWrite(arm2,LOW);
         analogWrite(arma,0);
        }
//RESET
        if(c=='r'){
           analogWrite(reset,0);       
        }
      

}
