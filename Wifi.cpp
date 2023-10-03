#include <WiFi.h>
#include "Motores.h"

WiFiServer server(80);
const char* ssid = "INFINITUMB6AD";
const char* password = "Tp6Dd4Gc1x";

String header;
String html = "<!DOCTYPE html><html><head>"
"<title>Control WiFi</title>"
"<style>table {border-spacing: 0;border-collapse: separate;}</style>"
"</head><body><center><table>"
"<tr><td></td><td><p><a href='/up'><button style='height: 40px; width: 100px'>Up</button></a></p></td><td></td></tr>"
"<tr><td><p><a href='/left'><button style='height: 50px; width: 100px'>Left</button></a></p></td>"
    "<td><p><a href='/stop'><button style='height: 50px; width: 100px'>Stop</button></a></p></td>"
    "<td><p><a href='/right'><button style='height: 50px; width: 100px'>Right</button></a></p></td></tr>"
"<tr><td></td><td><p><a href='/down'><button style='height: 50px; width: 100px'>Down</button></a></p></td><td></td></tr>"
"<tr><td><p><a href='/0'><button style='height: 50px; width: 100px'>0</button></a></p></td><td></td>"
    "<td><p><a href='/180'><button style='height: 50px; width: 100px'>180</button></a></p></td></tr>"
"<tr><td><p><a href='/45'><button style='height: 50px; width: 100px'>45</button></a></p></td>"
    "<td><p><a href='/90'><button style='height: 50px; width: 100px'>90</button></a></p></td>"
    "<td><p><a href='/135'><button style='height: 50px; width: 100px'>135</button></a></p></td></tr>"
"<tr><td><p><a href='/minus'><button style='height: 50px; width: 100px'>-</button></a></p></td><td></td>"
    "<td><p><a href='/plus'><button style='height: 50px; width: 100px'>+</button></a></p></td></tr>"
"<tr><td><p><a href='/low'><button style='height: 50px; width: 100px'>Low</button></a></p></td>"
    "<td><p><a href='/medium'><button style='height: 50px; width: 100px'>Medium</button></a></p></td>"
    "<td><p><a href='/high'><button style='height: 50px; width: 100px'>High</button></a></p></td></tr>"
"<tr><td></td><td><p><a href='/bailar'><button style='height: 50px; width: 100px'>Dance</button></a></p></td><td></td></tr>"
"</table></center></body></html>";

void Wifi_setup(){ 
  Serial.print("Conectando a: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando...");
  }
  Serial.println("Conectado a WiFi");
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void Wifi_loop(){
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  String currentLine = "";
  while (client.connected()) {
    if (client.available()) {
      char c = client.read();
      header += c;
      if (c == '\n') {
        if (currentLine.length() == 0) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();
  
          String request = header;
          request.toUpperCase();  // Convertir a mayúsculas para hacerlo insensible a mayúsculas y minúsculas

          if (header.indexOf("GET /up") >= 0) {
            // Código para avanzar
            MoverMotores(velocidad,CW,CW);
          } else if (header.indexOf("GET /down") >= 0) {
            // Código para retroceder
            MoverMotores(velocidad,CCW,CCW);
          } else if (header.indexOf("GET /left") >= 0) {
            // Código para girar a la izquierda
            MoverMotores(velocidad,CCW,CW);
          } else if (header.indexOf("GET /right") >= 0) {
            // Código para girar a la derecha
            MoverMotores(velocidad,CW,CCW);
          } else if (header.indexOf("GET /stop") >= 0) {
            // Código para detenerse
            Stop();
          } else if (header.indexOf("GET /0") >= 0) {
            // Código para mover el servo a 0 grados
            GradosServo(0);
            Serial.println(servoPositionTarget);
          } else if (header.indexOf("GET /45") >= 0) {
            // Código para mover el servo a 45 grados
            GradosServo(45);
            Serial.println(servoPositionTarget);
          } else if (header.indexOf("GET /90") >= 0) {
            // Código para mover el servo a 90 grados
            GradosServo(90);
            Serial.println(servoPositionTarget);
          } else if (header.indexOf("GET /135") >= 0) {
            // Código para mover el servo a 135 grados
            GradosServo(135);
            Serial.println(servoPositionTarget);
          } else if (header.indexOf("GET /180") >= 0) {
            // Código para mover el servo a 180 grados
            GradosServo(180);
            Serial.println(servoPositionTarget);
          } else if (header.indexOf("GET /minus") >= 0) {
            // Código para disminuir la velocidad
            Servominus();
            Serial.println(servoPositionTarget);
            Serial.println(servoPositionTarget);
          } else if (header.indexOf("GET /plus") >= 0) {
            // Código para aumentar la velocidad
            Servoplus();
            Serial.println(servoPositionTarget);
          } else if (header.indexOf("GET /low") >= 0) {
            // Código para velocidad baja
            velocidad = 37;
          } else if (header.indexOf("GET /medium") >= 0) {
            // Código para velocidad media
            velocidad = 44;
          } else if (header.indexOf("GET /high") >= 0) {
            // Código para velocidad alta
            velocidad = 99;
          } else if (header.indexOf("GET /bailar") >= 0) {
            // Código para realizar un baile
            Bailar();
          }
          client.println(html);
          break;
        } else {
          currentLine = "";
        }
      } else if (c != '\r') {
        currentLine += c;
      }
    }
  }
  
  header = "";
  client.stop();
}
