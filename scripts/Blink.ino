#include <ESP8266WiFi.h>

const char* ssid = "My ASUS";
const char* password = "brasil222";

int lamp = 4;
int zero = 5;

/*
float steps = 128;
float waveTime = (float) 1000 / 120;
float stepSize = (float) (waveTime * 1000) / steps;
*/

float stepSize = ((1000.0 / 120.0) * 1000.0) / 128.0;
float value = 127;

int zc_lock = 0;
void zeroCross() {
  if (!zc_lock) {
    zc_lock = 1;
    float dimtime = stepSize * value;
    digitalWrite(lamp, LOW);
    delayMicroseconds(dimtime);
    digitalWrite(lamp, HIGH);
    zc_lock = 0;
  }
}

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.print("begin");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }
  
  server.begin();
  Serial.println(WiFi.localIP());
  
  pinMode(lamp, OUTPUT);
  digitalWrite(lamp, LOW);
  pinMode(zero, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(zero), zeroCross, RISING);
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  while(!client.available()){
    delay(100);
  }
  
  String req = client.readStringUntil('\r');
  //Serial.println(req);
  client.flush();
  
  //if (req.indexOf("GET") != -1) {
    req.replace(" HTTP/1.1", "");
    int input = req.substring(5).toInt();
    //Serial.println(input);
    //if (input > 0)
      value = input % 128;
  //}
  
  client.flush();
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<input type=\"range\" value=\"127\" min=\"0\" max=\"127\" oninput=\"fetch(`http://192.168.43.241/${event.target.value}`)\">\n";
  client.print(s);
  
  delay(100);
}




