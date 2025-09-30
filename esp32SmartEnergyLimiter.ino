#include <WiFi.h>
#include <WebServer.h>   // Built-in lightweight web server

// Replace with your Wi-Fi credentials
const char* ssid = "Mumfety2.4";
const char* password = "kefety2.4G";
bool relayState = false;
// Create a web server object that listens on port 80
WebServer server(80);


String webpage() {
  String html = "<!DOCTYPE html><html lang='en'><head>";
  html += "<meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<title>ESP32 Smart Energy Limiter</title>";
  html += "<link href='https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css' rel='stylesheet'>";
  html += "</head><body class='bg-light'>";
  html += "<div class='container py-5 text-center'>";
  html += "<h1 class='mb-4'>ESP32 Smart Energy Limiter</h1>";
  html += "<div class='card shadow p-4'>";
  html += "<h4>Relay Status: <span class='badge bg-";
  html += relayState ? "success'>ON" : "danger'>OFF";
  html += "</span></h4><br>";
  html += "<div class='d-grid gap-2 d-sm-flex justify-content-sm-center'>";
  html += "<a href='/on' class='btn btn-success btn-lg'>Turn ON</a>";
  html += "<a href='/off' class='btn btn-danger btn-lg'>Turn OFF</a>";
  html += "</div></div></div>";
  html += "<script src='https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js'></script>";
  html += "</body></html>";
  return html;
}

void handleRoot() {
  server.send(200, "text/html", webpage());
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi!");
  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());

  // Define what happens when client visits "/"
  server.on("/", handleRoot);

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();  // Keep listening for incoming clients
}
