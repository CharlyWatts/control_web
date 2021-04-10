#include <VarSpeedServo.h>
VarSpeedServo servoblau;
VarSpeedServo portonGarage;
#include <SPI.h>
#include <Ethernet.h>
#include <OneWire.h> 
#include "DHT.h"
#define DHTPIN 2 
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#define epot         A0
#define ldr          A1 

int quarto          = 7;
int sala            = 3;
int cozinha         = 4;
int garagem         = 5;
int bano            = 6;
int Area            = 8;
int Pasillo         = 9;
int Entrada         = 12;
int Tualet          = 13;
int servo           = 25;
int jardin          = 24;
int servopuerta     = 22;
int servogarage     = 23;

String readString;

int Vldr = 0;
int pot = 0;
int pos = 0 ;

int puertai = 80;        // indicador de puerta abierto
int garageindicador = 80;  // indicador de garage abierto

int PuertaAnguloAbi = 10;  // Angulo de puerta Abierta
int PuertaAnguloCer  = 180;  // Agulo de puerta cerrada
int GarageAnguloAbi = 10;  // Angulo de Garage Abierta
int GarageAnguloCer =  180;  // Agulo de Garage cerrada
 
int velocidadServos = 30;



byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x7D, 0x54 };
byte ip[] = { 192, 168, 0, 115 }; 
byte subnet[] = { 255, 255, 255, 0 };
byte gateway[] = { 192, 168, 0, 1 };
EthernetServer server(80);




 
void setup() {

    Serial.begin(9600);
    Serial.println("Arrancando Setup");
    dht.begin();

    pinMode(servopuerta,  OUTPUT);
    pinMode(servogarage,  OUTPUT);
    pinMode(quarto,  OUTPUT);
    pinMode(sala,    OUTPUT);
    pinMode(cozinha, OUTPUT);
    pinMode(garagem, OUTPUT);
    pinMode(bano,    OUTPUT);
    pinMode(Area,  OUTPUT);
    pinMode(Pasillo,    OUTPUT);
    pinMode(Entrada, OUTPUT);
    pinMode(Tualet , OUTPUT);
    pinMode(jardin , OUTPUT);     
    pinMode(servo , OUTPUT);

    digitalWrite(quarto,     LOW);
    digitalWrite(sala,       LOW);
    digitalWrite(cozinha,    LOW); 
    digitalWrite(garagem,    LOW);
    digitalWrite(bano,       LOW);
    digitalWrite(Area,       LOW);
    digitalWrite(Pasillo,    LOW); 
    digitalWrite(Entrada,    LOW);
    digitalWrite(Tualet,     LOW);
    digitalWrite(jardin,     LOW);
    digitalWrite(servo,     HIGH);
    Ethernet.begin(mac, ip, gateway, subnet);

   servoblau.attach(servopuerta);
   portonGarage.attach(servogarage); 
   servoblau.slowmove(PuertaAnguloCer, velocidadServos); 
   servoblau.slowmove(GarageAnguloCer, velocidadServos);  
              
}



 
void loop() {
     
      EthernetClient client = server.available();
      
      pot = analogRead(epot);
      pot = map (pot, 0, 1023, 0, 100);
      Vldr = analogRead(ldr);
      Vldr = map (Vldr, 50, 1023, 0, 100);
      float h = dht.readHumidity();
      float t = dht.readTemperature();
 
      if (client) {
          boolean currentLineIsBlank = true;
          while (client.connected()) {
          if (client.available()) {
           char c = client.read();

      if (readString.length() < 100) {
          readString += c;
         }
         
      Serial.write(c);

      if (c == '\n' && currentLineIsBlank) {

      if (readString.indexOf("?charly") > 0){ 
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Server: Arduino");
          client.println("Connnection: close");
          client.println();      
          client.print("myCB({'temperature':");
          client.print(t);
          client.print(",'humidity':");
          client.print(h);
          client.print(",'humidity2':");
          client.print(Vldr);  
          client.print(",'temperature2':");  
          client.print(pot);
          client.print(",'humidity3':");
          client.print(puertai);  
          client.print(",'temperature3':");  
          client.print(garageindicador);

                                              //  puertaindicador
          client.print("})");
          client.println();
          delay(1);
          client.stop();
          readString = "";  
           }

     if (readString.indexOf("?quarto") > 0){
            
        if(digitalRead(quarto)){
          digitalWrite(quarto, LOW);
        }else{
             digitalWrite(quarto, HIGH);
            }
          }
          
          if (readString.indexOf("?sala") > 0)
          {
            if(digitalRead(sala)){
              digitalWrite(sala, LOW);
            }else{
              digitalWrite(sala,HIGH);
            }
          }

          if (readString.indexOf("?cozinha") > 0)
          {
            if(digitalRead(cozinha)){
              digitalWrite(cozinha, LOW);
            }else{
              digitalWrite(cozinha,HIGH);
            }
          }

if (readString.indexOf("?garagem") > 0)
          {
            if(digitalRead(garagem)){
              digitalWrite(garagem, LOW);
            }else{
              digitalWrite(garagem,HIGH);
            }
          }

      if (readString.indexOf("?bano") > 0)
          {
            if(digitalRead(bano)){
              digitalWrite(bano, LOW);
            }else{
              digitalWrite(bano,HIGH);
            }
          }

     if (readString.indexOf("?area") > 0)
          {
            if(digitalRead(Area)){
              digitalWrite(Area, LOW);
            }else{
              digitalWrite(Area, HIGH);
            }
          }


    if (readString.indexOf("?pasillo") > 0)
          {
            if(digitalRead(Pasillo)){
              digitalWrite(Pasillo, LOW);
            }else{
              digitalWrite(Pasillo, HIGH);
            }
          }

    if (readString.indexOf("?entrada") > 0)
          {
            if(digitalRead(Entrada)){
              digitalWrite(Entrada, LOW);
            }else{
              digitalWrite(Entrada, HIGH);
            }
          }

    if (readString.indexOf("?tualet") > 0)
          {
            if(digitalRead(Tualet)){
              digitalWrite(Tualet, LOW);
            }else{
              digitalWrite(Tualet, HIGH);
            }
          }

              if (readString.indexOf("?jardin") > 0)
          {
            if(digitalRead(jardin)){
              digitalWrite(jardin, LOW);
            }else{
              digitalWrite(jardin, HIGH);
            }
          }



     if (readString.indexOf("?puerta") > 0)
          {
         puertai = 20;
         servoblau.slowmove(PuertaAnguloAbi, velocidadServos); 
          
          }

     
     if (readString.indexOf("?puertaa") > 0) 
          {


          puertai = 80;
           
           servoblau.slowmove(PuertaAnguloCer, velocidadServos);

            
              
         
          }
         
          
          
          
     if (readString.indexOf("?coche") > 0)
          {
           garageindicador = 20;
           servoblau.slowmove(GarageAnguloAbi, velocidadServos);
           
           
          }
          
     if (readString.indexOf("?cochee") > 0)
          {
           
          garageindicador = 80;
          servoblau.slowmove(GarageAnguloCer, velocidadServos); 

          }


           

          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("</body>");
          client.println("69");
          client.println("</body>");
          client.println("</html>");          
          readString = "";        
          break;
        }

       
        if (c == '\n') {
          
          currentLineIsBlank = true;
        } else if (c != '\r') {
        
          currentLineIsBlank = false;
        }
          }

        }

     delay(1);
 
        client.stop();
        Serial.println("client disconnected");
       
  }
}













