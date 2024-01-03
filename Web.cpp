#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "Motores.h"

const char* ssid = "**********";
const char* password = "**********";
const char* apiURL = "https://app.saulgomezc.site/excavadora/getStatusExcavadora.php"; 

void Web_setup(){
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado a WiFi");
}

String getAPIResponse(const String& url) {
  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();
  String payload = "";
  if (httpCode == HTTP_CODE_OK) {
    payload = http.getString();
  } else {
    Serial.print("Error en la solicitud HTTP: ");
    Serial.println(httpCode);
  }
  http.end();
  return payload;
}

void interpretarJSON(const String& jsonPayload) {
  DynamicJsonDocument jsonDoc(1024);
  deserializeJson(jsonDoc, jsonPayload);
  String statusWeb = jsonDoc[0]["status"];
  char statusChar = statusWeb.charAt(0);
  
  Serial.print(statusChar);
  switch (statusChar) {
    case 'u':
      MoverMotores(velocidad,CW,CW);
      EncenderLED(ledUR);
      EncenderLED(ledUL);
      break;
    case 'd':
      MoverMotores(velocidad,CCW,CCW);
      EncenderLED(ledDR);
      EncenderLED(ledDL);
      break;
    case 'r':
      MoverMotores(velocidad,CW,CCW);
      EncenderLED(ledUR);
      EncenderLED(ledDR);
      break;
    case 'l':
      MoverMotores(velocidad,CCW,CW);
      EncenderLED(ledUL);
      EncenderLED(ledDL);
      break;
    case 'k':
      Servoplus();
      Serial.println(servoPositionTarget);
      break;
    case 'm':
      Servominus();
      Serial.println(servoPositionTarget);
      break;
    case 's':
      Stop(); // Detenerse por defecto si se recibe un comando desconocido
      break;
    case '0':
      GradosServo(0);
      Serial.println(servoPositionTarget);
      break;
    case '1':
      GradosServo(45);
      Serial.println(servoPositionTarget);
      break;
    case '2':
      GradosServo(90);
      Serial.println(servoPositionTarget);
      break;
    case '3':
      GradosServo(135);
      Serial.println(servoPositionTarget);
      break;
    case '4':
      GradosServo(180);
      Serial.println(servoPositionTarget);
      break;
    case 'a':
      ApagarLEDVel();
      velocidad = 37;
      EncenderLED(ledLOW);
      break;
    case 'b':
      ApagarLEDVel();
      velocidad = 44;
      EncenderLED(ledMID);
      break;
    case 'c':
      ApagarLEDVel();
      velocidad = 99;
      EncenderLED(ledHIGH);
      break;
    case 'z':
      Bailar();
      break;
    default:
      Stop(); 
      break;
  }
}

void Web(){
  String jsonPayload = getAPIResponse(apiURL);
  interpretarJSON(jsonPayload);
  delay(100); 
}
