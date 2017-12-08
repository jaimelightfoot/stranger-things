
#include "alphabet.h"

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            2 
#define NUMPIXELS      26

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

byte byteRead;

void setup() {
  Serial.begin(9600); // So we can input messages
  delay(10);
  pixels.begin(); // Initialize strand of LEDs
}

void loop() {
    int i;
    byte Byteread;

    if (Serial.available()) {
        byteRead = Serial.read();

        int j = getIndexOfLetter(byteRead);
        
        if (0 <= j && j < NUMPIXELS) {
          int red = alphabet[j].red;
          int blue = alphabet[j].blue;
          int green = alphabet[j].green;
  
          // set LED and show it
          pixels.setPixelColor(j, pixels.Color(red, green, blue));
          pixels.show();
  
          // after 1.5 seconds
          delay(1500);
          // clear pixels,
          clearAllPixels();
          // then wait before moving onto the next character
          delay(250);
        }
    }
}

/* Helper function that gets the index of a given letter 
from the alphabet RGB data structure */
int getIndexOfLetter(char letter) {
    for (int i=0; i<NUMPIXELS; i++) {
        if(alphabet[i].letter == letter) {
            return i;
        }
    }
    return -1;
}

/* Helper function that clears all the pixels */
void clearAllPixels() {
    for(int i=0;i<NUMPIXELS;i++)
    { 
        pixels.setPixelColor(i, pixels.Color(0, 0, 0)); 
    } 
    pixels.show(); 
} 
