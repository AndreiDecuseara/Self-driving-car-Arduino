#include <Servo.h>
#include <IRremote.h>

const int RECV_PIN = 13;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

int motorpin1 = 2;                 
int motorpin2 = 3; 
int controlMotorPin = A0;
int servoPin = 9;

int motorSpeed = 0;
int motorVoltage = 0;
int motorSpeedValue = 0 ;

Servo myservo; 

int servo_position = 0; 
int servoDrept = 90;
int servo_stanga=50;
int servo_dreapta=130;

int trigPin1 = 6;
int echoPin1 = 7;
long duration1;
int distance1;

int controlCar=0;//masina e oprita

int calculareDistanta1()
{
   digitalWrite(trigPin1, LOW); //clear trig
   delayMicroseconds(10);
   digitalWrite(trigPin1, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin1, LOW);
   duration1 = pulseIn(echoPin1, HIGH);
  int distanta1 = duration1*0.034/2; //calcularea distantei în cm

  return distanta1;  
}

int trigPin2 = 11;
int echoPin2 = 12;
long duration2;
int distance2;
int calculareDistanta2()
{
   digitalWrite(trigPin2, LOW); //clear trig
   delayMicroseconds(10);

   digitalWrite(trigPin2, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPin2, LOW);
   duration2 = pulseIn(echoPin2, HIGH);
  int distanta2 = duration2*0.034/2; //calcularea distantei în cm

  return distanta2;

    
}
int trigPinStanga = 10;
int echoPinStanga = 5;
long durationStanga;
int distanceStanga;
int calculareDistantaStanga()
{
   digitalWrite(trigPinStanga, LOW); //clear trig
   delayMicroseconds(10);

   digitalWrite(trigPinStanga, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPinStanga, LOW);
   durationStanga = pulseIn(echoPinStanga, HIGH);
  int distantaStanga = durationStanga*0.034/2; //calcularea distantei în cm

  return distantaStanga;

    
}

int trigPinDreapta = 8;
int echoPinDreapta = 4;
long durationDreapta;
int distanceDreapta;

int calculareDistantaDreapta()
{
   digitalWrite(trigPinDreapta, LOW); //clear trig
   delayMicroseconds(10);

   digitalWrite(trigPinDreapta, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPinDreapta, LOW);
   durationDreapta = pulseIn(echoPinDreapta, HIGH);
  int distantaDreapta = durationDreapta*0.034/2; //calcularea distantei în cm

  return distantaDreapta;

    
}

int con=1;

void control(int &con)
{
  if (irrecv.decode(&results)){
 
        if (results.value == 0XFFFFFFFF)
          results.value = key_value;

        switch(results.value){
                               
         case 0xFF6897:
          {Serial.println("0");con=0;}
          break ;  
          case 0xFF9867:
          {Serial.println("100+");con=1;}
          break ;
          case 0xFFB04F:
         { Serial.println("200+");con=2;}
          break ;
         
        }
        key_value = results.value;
        irrecv.resume(); 
  }
}


 void blocareControl(int &controlCar)
 {
  control(con);
  if(con == 0)
  {
    while(con == 0)
    {
      analogWrite(controlMotorPin, 0);
      control(con);
    }
  }
  if(con == 2)
  analogWrite(controlMotorPin, 255);
 }


void setup() {
    Serial.begin(9600);
    pinMode(motorpin1,OUTPUT);         
    pinMode(motorpin2,OUTPUT); 
    digitalWrite(motorpin1,LOW);
    digitalWrite(motorpin2,HIGH);
    myservo.attach(servoPin);
    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
    pinMode(trigPinStanga, OUTPUT);
    pinMode(echoPinStanga, INPUT);
    pinMode(trigPinDreapta, OUTPUT);
    pinMode(echoPinDreapta, INPUT);
    myservo.write(servoDrept);
    irrecv.enableIRIn();
    
}

void loop() 
{ 
 
  
   blocareControl(controlCar);//astept comanda de deblocare a masinii
   distance1 = calculareDistanta1();
   distance2 = calculareDistanta2();
   distanceStanga = calculareDistantaStanga();
   distanceDreapta = calculareDistantaDreapta();

  
  if(distance1 >= 25)
  { 
    
     digitalWrite(motorpin1,LOW);
     digitalWrite(motorpin2,HIGH); 
     analogWrite(controlMotorPin, 255);
     myservo.write(servoDrept);
     distance1 = calculareDistanta1();
     int sec1=0;
     if(distanceStanga < 25)
     while(sec1 < 8 && distance1 >= 25)
    {
      blocareControl(controlCar);
      digitalWrite(motorpin1,LOW);
      digitalWrite(motorpin2,HIGH);
      myservo.write(servo_dreapta-10);
      delay(50);
      sec1++;
      distanceStanga = calculareDistantaStanga();
      distance1 = calculareDistanta1();
     
      
    }
    
    blocareControl(controlCar);
    int sec2=0;
     if(distanceDreapta<25)
     while(sec2 < 8 && distance1 >= 25)
    {
      blocareControl(controlCar);
      digitalWrite(motorpin1,LOW);
      digitalWrite(motorpin2,HIGH);
      myservo.write(servo_stanga+10);
      delay(50);
      sec2++;
      distanceStanga = calculareDistantaStanga();
      distance1 = calculareDistanta1();
     
      
    }
    
    
  }
  // aici face intoarcerea daca vede ceva cu senzorul frontal
  if(distance1 < 25)
  {
    
    digitalWrite(motorpin1,HIGH);
    digitalWrite(motorpin2,LOW);
    analogWrite(controlMotorPin, 255);
    int sec1=0;
    int sec2=0;
    // da cu spatele aici pana trec 30 sec1 sau vede un obstacol senzorul din spate cu viraj stanga
    while(sec1 < 30 && distance2 > 10)
    {
      blocareControl(controlCar);
      distance2 = calculareDistanta2();
     
      myservo.write(servo_stanga);
      delay(50);
      sec1++;
    } 
    distance1 = calculareDistanta1();
   
    // merge cu fata cu viraj dreapta de un nr de sec2 ori sau pana vede un obstacol cu senzotul frontal
    while(sec2<15 && distance1>25)
    {
      blocareControl(controlCar);
      digitalWrite(motorpin1,LOW);
      digitalWrite(motorpin2,HIGH);
      myservo.write(servo_dreapta);
      delay(50);
      sec2++;
      distance1 = calculareDistanta1();
     
      
    }
    distance1 = calculareDistanta1();
    distance2 = calculareDistanta2();
 
   
    // se opreste daca are obsatol in fata si spate
    while(distance1<10 && distance2<10)
    {
      blocareControl(controlCar);
      distance1 = calculareDistanta1();
      distance2 = calculareDistanta2();
      analogWrite(controlMotorPin, 0);
    } 
 
  }
   
}
