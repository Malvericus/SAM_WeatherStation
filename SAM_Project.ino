// Final code for the NodeMCU
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>
#include <WiFiClient.h>
#include <Adafruit_Sensor.h>

#define DHTPIN 5
#define DHTTYPE DHT11

const int gasPin = A0;
const int raindropPin = D7;
int gasVal = 0;
DHT dht(DHTPIN, DHTTYPE);

const char *ssid = "Malvika's Galaxy";
const char *password = "malvika.";

ESP8266WebServer server(80);

void handleRoot() {
  // Read sensor data
  gasVal = analogRead(gasPin);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int raindropVal = digitalRead(raindropPin);

  String html = "<!DOCTYPE html><html lang=\"en\"><head>\n";
  html += "<meta charset=\"UTF-8\">\n";
  html += "<title>Weather Station</title>\n";
  html += "<style>\n";
  html += "* { padding: 0; margin: 0; -webkit-box-sizing: border-box; box-sizing: border-box; }\n";
  html += "body { background-image: url('https://c4.wallpaperflare.com/wallpaper/535/254/360/trees-digital-art-geometry-forest-wallpaper-preview.jpg'); background-size: cover; }\n";
  html += ".card__weather { margin-left: 40%; margin-top: 5%; display: flex; align-items: center; gap: 10px; }\n";
  html += ".card__weather__temp { font-size: 30px; }\n";
  html += ".card__weather__icon { animation: move 1s infinite alternate ease-in-out; }\n";
  html += ".temp-text { color: #d5d5d5; font-size: 30px; font-weight: 600; text-transform: uppercase; letter-spacing: 5px; margin: 5px 0; }\n";
  html += "@keyframes move { to { transform: translateY(-10px); } }\n";
  html += ".card { height: 500px; width: 80%; background-color: rgba(255, 255, 255, 0.06); -webkit-backdrop-filter: blur(20px); backdrop-filter: blur(20px); position: absolute; margin: auto; left: 0; right: 0; top: 0; bottom: 0; border-radius: 8px; -webkit-box-shadow: 20px 20px 22px rgba(0, 0, 0, 0.2); box-shadow: 20px 20px 22px rgba(0, 0, 0, 0.2); font-family: 'Poppins', sans-serif; }\n";
  html += ".card-img { height: 120px; width: 120px; background-color: rgba(255, 255, 255, 0.06); -webkit-backdrop-filter: blur(20px); backdrop-filter: blur(20px); border-radius: 50%; position: absolute; margin: 30px auto 20px auto; left: 0; right: 0; }\n";
  html += ".card-img img { height: 86%; border-radius: 50%; margin-left: 7%; margin-top: 7%; }\n";
  html += "h6 { margin: 0; }\n";
  html += ".desc { width: 100%; text-align: center; position: absolute; top: 160px; }";
  html += ".primary-text { color: #d5d5d5; font-size: 16px; font-weight: 600; letter-spacing: 0.7px; margin: 5px 0; }\n";
  html += ".primary-text2 { color: #d5d5d5; font-size: 20px; font-weight: 600; text-transform: uppercase; letter-spacing: 10px; margin: 5px 0; }\n";
  html += ".secondary-text { color: #c0c0c0; font-weight: 400; font-size: 14px; letter-spacing: 1px; margin: 5px 0; }\n";
  html += "button { background-color: rgba(255, 255, 255, 0.06); -webkit-backdrop-filter: blur(20px); backdrop-filter: blur(20px); border: none; }\n";
  html += ".details { display: grid; grid-template-columns: repeat(3, 1fr); width: 100%; height: 120px; padding: 5px 0; background-color: rgba(255, 255, 255, 0.06); -webkit-backdrop-filter: blur(20px); backdrop-filter: blur(20px); position: absolute; bottom: 0; border-radius: 0 0 8px 8px; }\n";
  html += ".rating, .activity, .third-box { text-align: center; display: flex; flex-direction: column; align-items: center; width: 100%; border-right: 2px solid rgba(255, 255, 255, 0.08); }\n";
  html += ".third-box { border-right: none; }\n";
  html += ".rating .primary-text { color: #d5d5d5; font-size: 50px; font-weight: 600; letter-spacing: 0.7px; margin: 5px 0; }\n";
  html += ".activity .primary-text { color: #d5d5d5; font-size: 50px; font-weight: 600; letter-spacing: 0.7px; margin: 5px 0; }\n";
  html += ".third-box h6 { color: #d5d5d5; font-size: 50px; font-weight: 600; letter-spacing: 0.7px; margin: 5px 0; }\n";
  html += ".third-box .secondary-text { color: #c0c0c0; font-weight: 400; font-size: 14px; letter-spacing: 1px; margin: 5px 0; }\n";
  html += ".details > div { text-align: center; }\n";
  html += ".details > div:first-child { border-right: 2px solid rgba(255, 255, 255, 0.08); }\n";
  html += "button { width: 80%; padding: 15px 0; position: absolute; left: 10%; top: 240px; border-radius: 5px; outline: none; }\n";
  html += "a { color: #ffffff; font-family: 'Poppins', sans-serif; font-weight: 400; letter-spacing: 0.5px; position: absolute; right: 20px; top: 20px; border: 3px solid #ffffff; border-radius: 5px; text-decoration: none; }\n";
  html += "a > .fa { color: #FF0000; }\n";
  html += "@media screen and (min-width: 451px) { a { font-size: 18px; padding: 8px 12px 8px 12px; } }\n";
  html += "@media screen and (max-width: 450px) { a { font-size: 12px; padding: 5px 8px 5px 8px; } }\n";
  html += "</style></head><body>\n";
  html += "<div class=\"card\"><div class=\"card__weather\">\n";
  html += "<svg width=\"100\" class=\"card__weather__icon\" height=\"70\" viewBox=\"0 0 34 24\" fill=\"none\" xmlns=\"http://www.w3.org/2000/svg\">\n";
  html += "<path d=\"M31.7764 13.3718C30.8073 12.1841 29.5779 11.4201 28.0897 11.0793C28.5632 10.3633 28.7992 9.57921 28.7992 8.72709C28.7992 7.52249 28.3664 6.49418 27.5014 5.64182C26.6361 4.78976 25.592 4.36354 24.3688 4.36354C23.2612 4.36354 22.3034 4.71584 21.496 5.42044C20.8155 3.80682 19.7334 2.50001 18.251 1.50001C16.7682 0.500241 15.1152 0 13.2921 0C10.8461 0 8.75757 0.852482 7.02679 2.55703C5.29589 4.26116 4.43071 6.31818 4.43071 8.72727C4.43071 8.89777 4.44229 9.1419 4.46532 9.46011C3.12694 10.0738 2.04801 11.0027 1.22884 12.2473C0.409735 13.4913 0 14.8637 0 16.3637C0 18.4659 0.758789 20.2642 2.27594 21.7583C3.79316 23.2528 5.61918 24 7.75375 24H26.5847C28.4191 24 29.9853 23.3603 31.2836 22.0823C32.5816 20.804 33.2308 19.2615 33.2308 17.4545C33.2306 15.9206 32.7457 14.5591 31.7764 13.3718Z\" fill=\"#f9f7ef\"/>\n";
  html += "</svg>\n";
  html += "<h6 class=\"temp-text\">" + String(temperature) + "° C <br> Pune</h6>\n";
  html += "</div>\n";
  html += "<button class=\"primary-text2\">Weather Station</button>\n";
  html += "<div class=\"details\">\n";
  html += "<div class=\"rating\">\n";
  html += "<h6 class=\"primary-text\">" + String(gasVal) + "ppm</h6>\n";
  html += "<h6 class=\"secondary-text\">Gas Concentration</h6>\n";
  html += "</div>\n";
  html += "<div class=\"activity\">\n";
  html += "<h6 class=\"primary-text\">" + String(humidity) + "%</h6>\n";
  html += "<h6 class=\"secondary-text\">Humidity</h6>\n";
  html += "</div>\n";
  html += "<div class=\"third-box\">\n";
  html += "<h6 class=\"primary-text\">" + String(raindropVal == LOW ? "Raining" : "Not Raining") + "</h6>\n";
  html += "<h6 class=\"secondary-text\">Rain Status</h6>\n";
  html += "</div>\n";
  html += "</div></div></body></html>\n";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(gasPin, INPUT);
  pinMode(raindropPin, INPUT);
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
