#include "wifi_functions.h"
#include "filters.h"
#include "config.h"
#include <CapacitiveSensor.h>


CapacitiveSensor cs_4_2 = CapacitiveSensor(16, 14); // 10 megohm resistor between pins 4 & 2, pin 2 is sensor pin, add wire, foil
LowPass lp(LP_SPEED);

enum HitType {
  SWORD,
  OPPONENT,
  NONE
};

static const char *HitString[] = {
  "sword", "opponent", "none"
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  setup_wifi();
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off autocalibrate on channel 1 - just as an example Serial.begin(9600);
}
void loop() {
  //put your main code here, to run repeatedly:
  HitType event = detectEvent();
  if (event != NONE) {
    sprintf(body, "data=p1,%s", HitString[event]);
    http_post(body, requestBuffer, responseBuffer);
    //    Serial.println(responseBuffer);
  }
}

long senseCurrent() {
  long total1 = cs_4_2.capacitiveSensorRaw(30);
  return total1;
}

HitType detectEvent() {
  long currentReading = senseCurrent();
  long low = lp.step(currentReading);

  Serial.print(currentReading); // print sensor output 1

  Serial.print("\t"); // tab character for debug window spacing

  Serial.print(40);
  Serial.print("\t"); // tab character for debug window spacing

  Serial.print(100);
  Serial.print("\t"); // tab character for debug window spacing

  Serial.println(low);


  if (currentReading > SWORD_THRESH) {
    return SWORD;
  } else if (low > OPP_THRESH) {
    return OPPONENT;
  } else{
    return NONE;
  }
}
