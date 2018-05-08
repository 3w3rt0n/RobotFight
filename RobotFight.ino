#include <ESP8266WiFi.h>//Biblioteca do WiFi.
#include <WiFiUdp.h>//Biblioteca do UDP.

IPAddress local_IP(10,0,0,1);
IPAddress gateway(10,0,0,1);
IPAddress subnet(255,255,255,0);
 
WiFiUDP udp;//Cria um objeto da classe UDP.

#define PORTA 8000

String req;

//D3 = GPIO00
//D4 = GPIO02 
//D5 = GPIO14 ~
//D6 = GPIO12 ~
//D7 = GPIO13 ERROR
//D8 = GPIO15 ~

#define motorDireito   4    //D5 = GPIO14
#define motorEsquerdo  3    //D6 = GPIO12
#define motorArmar     5    //D8 = GPIO15

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  
  pinMode(motorDireito, OUTPUT);
  pinMode(motorEsquerdo, OUTPUT);
  pinMode(motorArmar, OUTPUT);

  analogWrite(motorDireito, 0); //ok
  analogWrite(motorEsquerdo, 0);//ok
  digitalWrite(motorArmar, 0);  //ok

  WiFi.mode(WIFI_AP);
  Serial.print("Setting soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");
  
  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP("RobotFight", "12345678") ? "Ready" : "Failed!");

  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());

  udp.begin(PORTA);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(udp.parsePacket() > 0){
    req = "";
    while(udp.available() > 0){
      char c = udp.read();
      req += c;
    }

    Serial.print("Requisicao: ");
    Serial.println(req);

    delay(5);
  }

}
