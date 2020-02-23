#include "wifi_functions.h"
#include "filters.h"
#include "config.h"

void setup() {
  Serial.begin(115200);
  setup_wifi();
}

void loop() {
  String paramsString = "data=test";
  char params[paramsString.length()];
  paramsString.toCharArray(params, paramsString.length());
  http_get(params, requestBuffer, responseBuffer);
  String response = String(responseBuffer);
  Serial.println(response);
  if (response.equals("up")) {
    
  } else if (response.equals("left")) {
    
  }
  delay(10000);
}
