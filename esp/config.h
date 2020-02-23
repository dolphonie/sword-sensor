#ifndef CONFIG_H
#define CONFIG_H

// Server URL
char URL[] = "http://a8880110.ngrok.io/post";
char HOST[] = "http://a8880110.ngrok.io";

// Wifi constants
char NETWORK[] = "stratus";  // SSID for Wifi Network
char PASSWORD[] = "jeremysux"; // Password for Wifi Networkbvg

// Song playing constants
char USER[] = "dolphonie";

// buffers
char requestBuffer[900];
char responseBuffer[900];
char body[600];


// filters
float LP_SPEED = 0.95;  

// thresholds
float OPP_THRESH1 = 70;
float SWORD_THRESH1 = 85;
float OPP_THRESH2 = 110;
float SWORD_THRESH2 = 135;

long MESSAGE_COOLDOWN = 1000;

#endif
