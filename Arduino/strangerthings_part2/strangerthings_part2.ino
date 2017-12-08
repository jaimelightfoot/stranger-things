/***************************************************
  Adafruit MQTT Library ESP8266 Example

  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution

  This also uses the NeoPixel library.  
  
 ****************************************************/
 
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "alphabet.h"

/************* WiFi and AdafruitIO Setup **************/

#define WLAN_SSID       "WIFI_NAME_HERE"
#define WLAN_PASS       "WIFI_PASSWORD_HERE"

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "AIO_USERNAME_HERE"
#define AIO_KEY         "AIO_KEY_HERE"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

Adafruit_MQTT_Subscribe STmessages = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/alph");

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            2 
#define NUMPIXELS      26

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

byte byteRead;

void setup() {
  Serial.begin(115200);
  delay(10);

  WifiConnectionDebugPrintout();

  // Connect our callback function to the ST messages subscription
  STmessages.setCallback(STmessagesCallback);

  // Setup MQTT subscription for ST messages.
  mqtt.subscribe(&STmessages);

  pixels.begin(); // This initializes the NeoPixel library.
}

void WifiConnectionDebugPrintout() {
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());
}

void STmessagesCallback(char *data, uint16_t len) {
  int i;
  
  for (i = 0; i<len; i++) {
     byteRead = data[i];
     if (isLowerCase(byteRead)) {
        int j = getIndexOfLetter(byteRead);
        if (0 <= j && j < NUMPIXELS) {
          int red = alphabet[j].red;
          int blue = alphabet[j].blue;
          int green = alphabet[j].green;
    
          pixels.setPixelColor(j, pixels.Color(red, green, blue)); 
          pixels.show();

          // wait 1.5 seconds, clear it, 
          // then wait 0.25 seconds before the next char
          delay(1500);
          clearAllPixels();
          delay(250);
        }
      } 
  }
}

void loop() {

   // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  // note:  waiting for 10 seconds means that we'll miss some messages
  mqtt.processPackets(10000);

  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}

int getIndexOfLetter(char letter) {
  for (int i=0; i<NUMPIXELS; i++) {
    if(alphabet[i].letter == letter) {
      return i;
    }
  }
  return 0;
}

void clearAllPixels() {
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));  
  }
  pixels.show();
}

