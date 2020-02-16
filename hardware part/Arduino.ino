#include <SoftwareSerial.h>

SoftwareSerial nodemcu(2,3);
int trigPin = 12;    
int echoPin = 13;  
int trigPin2= 10;
int echoPin2= 11;  
long duration ,distance,sonic1,sonic2;
long cm=0, cm2=0;
int change=0;
int tempData=0;
int counter=0,counter2=0;
String cdata;




void setup() {
  Serial.begin(115200);
  nodemcu.begin(115200);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
}

void loop() {
 /* digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = (duration/2) / 29.1;
  */
SonarSensor(trigPin, echoPin);
cm = distance;
SonarSensor(trigPin2, echoPin2);
cm2 = distance;
  if((cm<40&&cm2>40)||(cm2<40&&cm>40)){
   Serial.print("Sensor1: ");
   Serial.println(cm);
   Serial.print("Sensor2: ");
   Serial.println(cm2);
  }
  if(((cm<40&&cm2>40)||(cm2<40&&cm>40))&&counter2==0&&counter==0){
    Serial.println("something entered in spot");
    counter=1;            //detect something
    counter2=0;           // car
    delay(1000);
  }

  else if((cm>40 && cm2>40)&&counter==1&&counter2==0){
     Serial.println("Entered thing has left");
     counter=0;            //detect something
     counter2=0;           // car
     delay(1000);
    }

  else if((cm<40 && cm2<40)&&counter==1&&counter2==0){
   // if(change>500){
     Serial.println("Car entered in spot");
     counter=1;            //detect something
     counter2=1;           // car
     cdata=counter2;
    // Serial.println(cdata);
     send_data();
     change=0;//}
    // change++;
     
  }
  else if((cm>40 && cm2>40)&&counter==1&&counter2==1){
   // if(change>500){
     Serial.println("Entered car has left");
     counter=0;            //detect something
     counter2=0;           // car
     cdata=counter;
    // Serial.println(cdata);
      
     send_data();
     change=0;//}
    //change++;
    }
    
   

}

void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;

}
void send_data()
{
  cdata = cdata ;
  //Serial.println(cdata);
  nodemcu.println(cdata);
  Serial.println(cdata);
  cdata = "";
}
