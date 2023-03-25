#define RCPin1 24
#define RCPin2 26
#define RCPin3 28
#define SerPin1 30
#define SerPin2 32
#define SerPin3 34
#define Message
int RCValue;
int Serpin;
void setup() {
  Serial.begin(9600);
  pinMode(RCPin1, INPUT);
  pinMode(RCPin2, INPUT);
  pinMode(RCPin3, INPUT);
  pinMode(RCPin4, INPUT);
  pinMode(SerPin1,OUTPUT);
  pinMode(SerPin2,OUTPUT);
  pinMode(SerPin3,OUTPUT);
}
void Update_Transmitter() {
  TransmitterData =  “servo1:” + String(RCPin1) + “servo2:” + String(RCPin2) + “servo3:” + String(RCPin3)
  output(RCPin1,RCPin2,RCPin3,RCPin4);
}
void output(int ch1,int ch2,int ch3,int ch4){
  digitalWrite(30, ch1);
  digitalWrite(32, ch2);
  digitalWrite(34, ch3);
  digitalWrite(30, ch4);
}
void GetTranmitterData{
  return TransmitterData
}