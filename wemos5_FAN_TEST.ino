#include <SocketIoClient.h>
#include <ESP8266WiFi.h>


char ssid[] = "YOUR_SSID";
char pass[] = "YOUR_PASS";
SocketIoClient socket;
const int PIN_RELAY1 = 0;
const int PIN_RELAY2 = 16;
const int PIN_RELAY3 = 4;


void connectEvent(const char* a , size_t b){
   Serial.println("connectEvent called...");
   socket.emit("join_arduino");
}

void disconnectEvent(const char* a , size_t b){
   Serial.println("disonnectEvent called...");
   socket.emit("leave_arduino");
}


void turnOffEvent(const char* a , size_t b){
  Serial.println("turnOffEvent called...");
  digitalWrite(PIN_RELAY1,HIGH);
  digitalWrite(PIN_RELAY2,HIGH);
  digitalWrite(PIN_RELAY3,HIGH); 
}

void onSpeedEvent(const char* a , size_t b){
  Serial.println("onSpeedEvent called...");
  int speedData = atoi(a);
  Serial.println(speedData);
  
  if(speedData == 1){
      digitalWrite(PIN_RELAY1,LOW);
      digitalWrite(PIN_RELAY2,HIGH);
      digitalWrite(PIN_RELAY3,HIGH); 
  }else if(speedData == 2){
      digitalWrite(PIN_RELAY1,HIGH);
      digitalWrite(PIN_RELAY3,HIGH); 
      digitalWrite(PIN_RELAY2,LOW);
  }else{
      digitalWrite(PIN_RELAY1,HIGH);
      digitalWrite(PIN_RELAY2,HIGH);
      digitalWrite(PIN_RELAY3,LOW); 
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid , pass);
  while(WiFi.status() != WL_CONNECTED){
    Serial.println("Wifi not connected");
    delay(1000);   
  }
  pinMode(PIN_RELAY1,OUTPUT);
  pinMode(PIN_RELAY2,OUTPUT);
  pinMode(PIN_RELAY3,OUTPUT);
  
  digitalWrite(PIN_RELAY1,HIGH);
  digitalWrite(PIN_RELAY2,HIGH);
  digitalWrite(PIN_RELAY3,HIGH);

  socket.on("connect",connectEvent);
  socket.on("disconnect",disconnectEvent);
  socket.on("on_speed",onSpeedEvent);
  socket.on("turn_off",turnOffEvent);
  socket.begin("192.168.1.8",9600);
}

void loop() {
  socket.loop();
}
