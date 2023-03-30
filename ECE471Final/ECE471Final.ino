#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsServer.h>
#include <ESP8266WebServer.h>
#include <Hash.h>


SoftwareSerial lora_node(D5, D2); //rx, tx
String system_status = " ";

//websockets
String old_value, value;

ESP8266WiFiMulti    WiFiMulti;
ESP8266WebServer    server(80);
WebSocketsServer    webSocket = WebSocketsServer(81);

//HTML and JS page to serve
char html_template[] PROGMEM = R"=====(
<html lang="en">
   <head>
      <meta charset="utf-8">
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <title>Automated Plant Water Management System</title>
      <script>
        socket = new WebSocket("ws:/" + "/" + location.host + ":81");
        socket.onopen = function(e) {  console.log("[socket] socket.onopen "); };
        socket.onerror = function(e) {  console.log("[socket] socket.onerror "); };
        socket.onmessage = function(e) {  
            console.log("[socket] " + e.data);  
            document.getElementById("sys_status").innerHTML = e.data;    
        };
      </script>
   </head>
   <body style="max-width:400px;margin: auto;font-family:Arial, Helvetica, sans-serif;text-align:center">
      <div><h1><br />Automated Plant Water Management System</h1></div>
      <div><p id="sys_status" style="font-size:100px;margin:0"></p></div>
      <br><br>
      <div><p id="moist_stat" style="font-size:100px;margin:0"></p></div>
   </body>
</html>
)=====";

//websocket event handler
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;

    case WStype_CONNECTED: {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        // send message to client
        webSocket.sendTXT(num, "0");
      }
      break;

    case WStype_TEXT:
      Serial.printf("[%u] get Text: %s\n", num, payload);
      // send message to client
      // webSocket.sendTXT(num, "message here");
      // send data to all connected clients
      // webSocket.broadcastTXT("message here");
      break;
      
    case WStype_BIN:
      Serial.printf("[%u] get binary length: %u\n", num, length);
      hexdump(payload, length);
      // send message to client
      // webSocket.sendBIN(num, payload, length);
      break;
  }

}//websocket event

void handleMain() {
  server.send_P(200, "text/html", html_template ); 
}
void handleNotFound() {
  server.send(404,   "text/html", "<html><body><p>404 Error</p></body></html>" );
}

void setup() {

  lora_node.begin(9600);
  Serial.begin(9600);
  while (!Serial);

  pinMode(D5, INPUT);
  pinMode(D2, OUTPUT);

  WiFiMulti.addAP("SM-G935P798", "rafay786");

  while (WiFiMulti.run() != WL_CONNECTED) {
    delay(100);
  }

  Serial.println(WiFi.localIP());

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  server.on("/", handleMain);
  server.onNotFound(handleNotFound);
  server.begin();


  Serial.flush();
  Serial.println("Start\n");
}




void loop() {

  webSocket.loop();
  server.handleClient();

  if(lora_node.available() > 0)
  {
    //Serial.println(lora_node.readString());  
    int status = lora_node.read();
    //Serial.println(status);
    if(status == 87)
    {
      Serial.println("Watering");
      system_status = "Watering";
      webSocket.broadcastTXT(system_status);
    }
    else if(status == 83)
    {
      Serial.println("Idle");
      system_status = "Idle";
      webSocket.broadcastTXT(system_status);      
    }
    else if(status == 77)
    {
      Serial.println("Checking Moisture");
      system_status = "Checking Moisture";
      webSocket.broadcastTXT(system_status);
    }
    else
    {
      //moisture value
      String moistureVal = "Moisture: ";
      String val = String(status);
      moistureVal = moistureVal+val;
      Serial.println(moistureVal);
    }
    delay(40);
  }

  //Serial.println(system_status);



}