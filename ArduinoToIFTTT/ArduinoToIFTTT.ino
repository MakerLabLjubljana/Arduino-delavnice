
/*
POTEK PROGRAMA ARDUINO -> IFTTT
-Razloži, da bomo z arduinom pushali notoifikejšne na mobi 
-Naredimo IFTTT account - primer pošlji email, dobi notification (pokaži primer z NASO)
-Najprej koncept blink without delay (nardiš primer z LED 13)
-Na roke napišeš incializacijo ethernet+IFTTT (vse kar je pred in v setupu)
-Copy/Paste GETrequest funkcijo (razloži server, JSON, in kje vidimo kakšen format mormo narest - IFTTT)
-Sestavimo funkcijo ki bo sestavila JSON
-Pushamo notification ko pritisnemo tipko, senzor

*/


#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFF, 0xED };

char server[] = "maker.ifttt.com"; 
IPAddress ip(10, 0, 0, 99);
EthernetClient client;

long Time = 0;
String IFTTTKey = "csB_0GMzOkFL2Fn7xvS7D3";
String TriggerWord = "delavnice";

void setup() {

  Serial.begin(9600);

  while (!Serial) {
    ; 
  }

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }

  Time = millis()+20000;
}

void loop() {
  if(millis()-Time>20000){
    Time = millis();
    GETrequest();
  }

  while(true){;}


}

String getJSON() {
  String json = "{\"value1\":\"";
  json += 0;
  json += "\",\"value2\":\"";
  json += 0;
  json += "\",\"value3\":\"";
  json += 0;
  json += "\"}";

  return json;
}

int GETrequest(){
  delay(1000);
  Serial.println("connecting...");

  
  if (client.connect(server, 80)) {
    Serial.println("connected");

    String json = getJSON();
  
    client.println("POST http://maker.ifttt.com/trigger/"+TriggerWord+"/with/key/"+IFTTTKey+" HTTP/1.1");
    client.println("Host: maker.ifttt.com");
    client.println("Content-Type: application/json");
    client.print("Content-Length: ");
    client.println(json.length());
    client.println("Connection: close");
    client.println();
    
    client.println(json);
    client.println();

  } else {
  
    Serial.println("connection failed");
  }
  delay(500);

  while (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  Serial.println("disconnecting.");
  client.stop();

}
