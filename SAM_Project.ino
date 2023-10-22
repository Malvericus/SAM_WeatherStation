// #include <ESP8266WiFi.h>
// #include <ESP8266WebServer.h>
// #include <DHT.h>
// #include <WiFiClient.h>
// #include <Adafruit_Sensor.h>


// #define DHTPIN 5
// #define DHTTYPE DHT11
// const int gasPin = A0;
// const int raindropPin = D7;
// int gasVal = 0;
// DHT dht(DHTPIN, DHTTYPE);

// const char * ssid = "Malvika's Galaxy";
// const char * password = "malvika.";

// ESP8266WebServer server(80);

// void handleRoot() {
//   String html = "<html><body><h1>Sensor Data</h1>";

//   float humidity = dht.readHumidity();
//   float temperature = dht.readTemperature();
//   int raindropVal = digitalRead(raindropPin);
//   gasVal = analogRead(gasPin);

//   html += "<p>Humidity: " + String(humidity) + "%</p>";
//   html += "<p>Temperature: " + String(temperature) + "°C</p>";
//   html += "<p>Gas Concentration: " + String(gasVal) + "ppm</p>";
//   html += "<p>Raindrop Sensor: " + String(raindropVal == LOW ? "Raining" : "Not Raining") + "</p>";
//   html += "</body></html>";

//   server.send(200, "text/html", html);
// }

// void setup() {
//   Serial.begin(115200);
//   dht.begin();
//   pinMode(gasPin, INPUT);
//   pinMode(raindropPin, INPUT);
//   WiFi.begin(ssid, password);

//   while (WiFi.status() != WL_CONNECTED) {
//     delay(1000);
//     Serial.println("Connecting to WiFi...");
//   }

//   Serial.println("Connected to WiFi");
//   Serial.print("IP address: ");
//   Serial.println(WiFi.localIP());

//   delay(6000);

//   server.on("/", handleRoot);
//   server.begin();
// }

// void loop() {
//   server.handleClient();
// }


#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>
#include <WiFiClient.h>
#include <Adafruit_Sensor.h>

#define DHTPIN 5       
#define DHTTYPE DHT11  // Define the type of DHT sensor

const int gasPin = A0;
const int raindropPin = D7;
int gasVal = 0;
DHT dht(DHTPIN, DHTTYPE);

const char * ssid = "Malvika's Galaxy";        // Replace with your network SSID
const char * password = "malvika."; // Replace with your network password

ESP8266WebServer server(80);

void handleRoot() {

    gasVal = analogRead(gasPin);
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    int raindropVal = digitalRead(raindropPin);

  String html = "<html><body><h1>Sensor Data</h1>";

  html += "<p>Humidity: " + String(dht.readHumidity()) + "%</p>";
  html += "<p>Temperature: " + String(dht.readTemperature()) + " C</p>";
  html += "<p>Gas Concentration: " + String(gasVal) + "ppm</p>";
  html += "<p>Raindrop Sensor: " + String(digitalRead(raindropPin) == LOW ? "Raining" : "Not Raining") + "</p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}



void setup() {
  Serial.begin(115200);     
  
  dht.begin();            
  
  pinMode(gasPin, INPUT);

  pinMode(raindropPin, INPUT);

  WiFi.begin(ssid, password);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
}

void loop() {

  server.handleClient();
}

