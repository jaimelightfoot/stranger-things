#ifndef ALPHABET_H
#define ALPHABET_H

struct colorCode {
  char letter;
  unsigned int red;
  unsigned int green;
  unsigned int blue;
};

struct colorCode alphabet[26] = {
    {'a', 255, 255, 225},   // A 0 white
    {'b', 0, 0, 225},       // B 1 dark blue
    {'c', 210, 30, 210},    // C 2 magenta
    {'d', 103, 228, 255},   // D 3 light blue
    {'e', 0, 0, 225},       // E 4 dark blue
    {'f', 255, 255, 0},     // F 5 yellow  
    {'g', 255, 0, 0},       // G 6 red
    {'h', 0, 255, 100},     // H 7 green
    
    /* second row, reverse order */
    {'q', 210, 30, 210},    // Q 8 magenta
    {'p', 103, 228, 255},   // P 9 icy blue 
    {'o', 210, 30, 210},    // O 10 magenta
    {'n', 255, 0, 0},       // N 11 red
    {'m', 255, 255, 0},     // M 12 yellow
    {'l', 103, 228, 255},   // L 13 light blue
    {'k', 0, 0, 225},       // K 14 dark blue
    {'j', 255, 0, 0},       // J 15 red
    {'i', 0, 255, 100},     // I 16 green

    /* new row, normal order */
    {'r', 103, 228, 255},   // R 17 light blue
    {'s', 255, 255, 225},   // S 18 white
    {'t', 255, 255, 0},     // T 19 yellow
    {'u', 0, 0, 225},       // U 20 dark blue
    {'v', 255, 0, 0},       // V 21 red
    {'w', 0, 255, 100},     // W 22 green
    {'x', 255, 255, 0},     // X 23 yellow
    {'y', 210, 30, 210},    // Y 24 magenta
    {'z', 255, 0, 0},        // Z 25 red
  };

#endif
