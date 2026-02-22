#include <SoftwareSerial.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>

// ===================
// KONFIGURASI THINGER
// ===================
#define USERNAME "davinonathan"
#define DEVICE_ID "node_mcu3"
#define DEVICE_CREDENTIAL "PrK$-ICrZm&yA3Me"
#define SSID "Damn"
#define SSID_PASSWORD "12345678"

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

// ===================
// GLOBAL VARIABLE
// ===================
String myString = "";
String v1, v2, v3, v4, v5, v6;
char c;

// ===================
// SETUP
// ===================
void setup() {
  Serial.begin(9600);

  thing.add_wifi(SSID, SSID_PASSWORD);

  thing["COBA"] >> [](pson& out){
    out["koil"]      = v1;
    out["kecepatan"] = v2;
    out["AFR"]       = v3;
    out["TPS"]       = v4;
    out["SUHU"]      = v5;
    out["waktu"]     = v6;
  };
}

// ===================
// LOOP
// ===================
void loop() {

  thing.handle();   // WAJIB untuk Thinger

  while (Serial.available() > 0)
  {
    char c = Serial.read();
    myString += c;

    if (myString.endsWith("#F1#"))
      prosesData("#S1#", "#F1#");

    else if (myString.endsWith("#F2#"))
      prosesData("#S2#", "#F2#");

    else if (myString.endsWith("#F3#"))
      prosesData("#S3#", "#F3#");

    else if (myString.endsWith("#F4#"))
      prosesData("#S4#", "#F4#");

    else if (myString.endsWith("#F5#"))
      prosesData("#S5#", "#F5#");

    else if (myString.endsWith("#F6#"))
      prosesData("#S6#", "#F6#");
  }

  yield(); // supaya WiFi tidak timeout
}

// ===================
// FUNCTION PARSING
// ===================
void prosesData(String startTag, String endTag)
{
  int startIndex = myString.indexOf(startTag);
  int endIndex   = myString.indexOf(endTag);

  if (startIndex != -1 && endIndex != -1)
  {
    String nilai = myString.substring(startIndex + 4, endIndex);

    if(startTag == "#S1#") v1 = nilai;
    else if(startTag == "#S2#") v2 = nilai;
    else if(startTag == "#S3#") v3 = nilai;
    else if(startTag == "#S4#") v4 = nilai;
    else if(startTag == "#S5#") v5 = nilai;
    else if(startTag == "#S6#") v6 = nilai;

    // Debug monitor
    Serial.println("========== DATA UPDATE ==========");
    Serial.print("RPM      : "); Serial.println(v1);
    Serial.print("Speed    : "); Serial.println(v2);
    Serial.print("AFR      : "); Serial.println(v3);
    Serial.print("TPS      : "); Serial.println(v4);
    Serial.print("SUHU     : "); Serial.println(v5);
    Serial.print("Waktu    : "); Serial.println(v6);
    Serial.println("=================================");
  }

  myString = "";
}