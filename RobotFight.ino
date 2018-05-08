#include <ESP8266WiFi.h>//Biblioteca do WiFi.
#include <WiFiUdp.h>//Biblioteca do UDP.

IPAddress local_IP(10,0,0,1);
IPAddress gateway(10,0,0,1);
IPAddress subnet(255,255,255,0);
 
WiFiUDP udp;//Cria um objeto da classe UDP.

#define PORTA 8000

//D3 = GPIO00
//D4 = GPIO02 
//D5 = GPIO14 ~
//D6 = GPIO12 ~
//D7 = GPIO13 ERROR
//D8 = GPIO15 ~

#define motorDireitoA   4     //D4 = GPIO02 UP
#define motorDireitoB   3     //D3 = GPIO00 UP
#define motorEsquerdoA  5     //D5 = GPIO14
#define motorEsquerdoB  2     //D2 = GPIO04
#define motorArmar      0     //D0 = GPIO16

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  
  pinMode(motorDireitoA, OUTPUT);
  pinMode(motorDireitoB, OUTPUT);
  pinMode(motorEsquerdoA, OUTPUT);
  pinMode(motorEsquerdoB, OUTPUT);
  pinMode(motorArmar, OUTPUT);

  analogWrite(motorDireitoA, 0); //ok
  analogWrite(motorDireitoB, 0); //ok
  analogWrite(motorEsquerdoA, 0);//ok
  analogWrite(motorEsquerdoB, 0);//ok
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
    while(udp.available() > 0){
      char c = udp.read();
      Serial.print("Requisicao: ");
      Serial.println(c);

      switch(c){
        //Robo andar para frente
        case '1':   analogWrite(motorDireitoA, 0);
                  analogWrite(motorDireitoB, 1024);
                  analogWrite(motorEsquerdoB, 0);
                  analogWrite(motorEsquerdoA, 1024);
                  Serial.println("Robo para frente.");
                  break;
        //Robo andar para traz
        case '2':   analogWrite(motorDireitoB, 0);
                  analogWrite(motorDireitoA, 1024);
                  analogWrite(motorEsquerdoA, 0);
                  analogWrite(motorEsquerdoB, 1024);
                  Serial.println("Robo para traz.");
                  break;
        //Robo para direita
        case '3':   analogWrite(motorDireitoB, 0);
                  analogWrite(motorDireitoA, 1024);
                  analogWrite(motorEsquerdoB, 0);
                  analogWrite(motorEsquerdoA, 1024);
                  Serial.println("Robo para direita.");
                  break;
        //Robo para esquerda
        case '4':   analogWrite(motorDireitoA, 0);
                  analogWrite(motorDireitoB, 1024);
                  analogWrite(motorEsquerdoA, 0);
                  analogWrite(motorEsquerdoB, 1024);
                  Serial.println("Robo para esquerda.");
                  break;  
        //Robo parado
        case '5':   analogWrite(motorDireitoA, 0);
                  analogWrite(motorDireitoB, 0);
                  analogWrite(motorEsquerdoA, 0);
                  analogWrite(motorEsquerdoB, 0);
                  Serial.println("Robo parado.");
                  break;        
        
      }
      
    } 

    delay(5);
  }

}
