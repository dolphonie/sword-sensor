#ifndef CONFIG_H
#define CONFIG_H

// Server URL
char URL[] = "http://65ac765d.ngrok.io/post";
char HOST[] = "http://65ac765d.ngrok.io";

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
float OPP_THRESH = 70;
float SWORD_THRESH = 85;


#endif
