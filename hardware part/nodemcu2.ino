#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <WiFiClient.h>
IPAddress server_addr(10,144,93,67);
SoftwareSerial nodemcu(D3,D2);

char user[] = "root2";              // MySQL user login username
char password[] = "1";        // MySQL user login password
char INSERT_SENSOR[] = "INSERT INTO android_api.parking (slotID, parkingCondition , userID) VALUES (%d, %d, %d)";
char UPDATE_SENSOR[] = "UPDATE android_api.parking SET parkingCondition =%d  WHERE slotID = 2 AND userID=%d";

char mainSelectQuery[600] = "SELECT a.parkingCondition FROM android_api.parking userID, WHERE a.slotID = 2 ";
char queryInsert[128];
char queryUpdate[128];
String SensorValue= "0";
WiFiClient client1;
WiFiClient client;
MySQL_Connection conn(&client);
MySQL_Cursor* cursor;


char rdata; // Received characters
String myString;
int sensorValues[99]={}; // Sensors
int counter = 0;

const char *ssid =  "RZ";     
const char *pass =  "qwer1234";

//partingcn = 0;
void setup() {
  Serial.begin(115200);
  nodemcu.begin(115200);
  //***************** Wifi Connection*********************//
 Serial.println("Connecting to ");
 Serial.println(ssid);
 WiFi.mode(WIFI_STA);
 WiFi.begin(ssid, pass); 
 while (WiFi.status() != WL_CONNECTED) 
   {
   delay(500);
   Serial.print(".");}
 Serial.println("");
 Serial.println("WiFi connected"); 
 Serial.println(WiFi.localIP());
      
//****************************************************//
//*********************Database Connection************//
 Serial.print("Connecting to SQL...  ");
 
 if (conn.connect(server_addr, 3306, user, password)){
      delay(1000);
      Serial.println("OK.");}
 else
      Serial.println("FAILED.");
  
  // create MySQL cursor object
  cursor = new MySQL_Cursor(&conn);


}
void loop() {
  
  while (Serial.available() > 0 ){
    rdata = Serial.read();
    myString = myString+ rdata;
    if( rdata == '\n'){
      String tempData = getValue(myString, ',', 0);
      sensorValues[0] = tempData.toInt();
      Serial.println(sensorValues[0]);
      myString = "";
      if(counter!=0 ){
        sprintf(queryUpdate, UPDATE_SENSOR,sensorValues[0],8);
        cursor->execute(queryUpdate); 
        Serial.println("Parking Condition updated.");
      }
      else{
        sprintf(queryInsert, INSERT_SENSOR, 2,sensorValues[0],8);
        cursor->execute(queryInsert); 
        Serial.println("Parking Condition recorded.");
        counter++;
      }
  }
  continue;
 }
}

String getValue(String data, char separator, int index){
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
      if (data.charAt(i) == separator || i == maxIndex) {
          found++;
          strIndex[0] = strIndex[1] + 1;
          strIndex[1] = (i == maxIndex) ? i+1 : i;}
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
