#include "wifi_functions.h"
#include <CapacitiveSensor.h>

CapacitiveSensor cs_4_2 = CapacitiveSensor(16, 14); // 10 megohm resistor between pins 4 & 2, pin 2 is sensor pin, add wire, foil

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  setup_wifi();
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off autocalibrate on channel 1 - just as an example Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
//  senseCurrent();
  sprintf(body, "------WebKitFormBoundary7MA4YWxkTrZu0gW\r\nContent-Disposition: form-data; name=\"data\"\r\n\r\nfoobar\r\n------WebKitFormBoundary7MA4YWxkTrZu0gW--");
  http_post(body, requestBuffer, responseBuffer);
  Serial.println(responseBuffer);
  
  delay(1000); // arbitrary delay to limit data to serial port
}

long senseCurrent(){
  long total1 = cs_4_2.capacitiveSensorRaw(30);
  Serial.print(total1); // print sensor output 1

  Serial.print("\t"); // tab character for debug window spacing
  
  Serial.print(40);
  Serial.print("\t"); // tab character for debug window spacing
  
  Serial.println(100);
}

long uploadValue(char* id) {
  
}
