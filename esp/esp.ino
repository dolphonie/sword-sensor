#include "wifi_functions.h"
#include "filters.h"
#include "config.h"
#include <CapacitiveSensor.h>

long c1Time = 0;
long c2Time=0;
CapacitiveSensor c1 = CapacitiveSensor(16, 14); // 10 megohm resistor between pins 4 & 2, pin 2 is sensor pin, add wire, foil
CapacitiveSensor c2 = CapacitiveSensor(13, 12);
LowPass lp1(LP_SPEED);
LowPass lp2(LP_SPEED);

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
  c1.set_CS_AutocaL_Millis(0xFFFFFFFF); // turn off autocalibrate on channel 1 - just as an example Serial.begin(9600);
  c2.set_CS_AutocaL_Millis(0xFFFFFFFF);
}
void loop() {
  //put your main code here, to run repeatedly:
  HitType event1 = detectEvent(&lp1, &c1);
  if (event1 != NONE && millis()>c1Time+MESSAGE_COOLDOWN) {
    sprintf(body, "data=p1,%s", HitString[event1]);
    http_post(body, requestBuffer, responseBuffer);
    c1Time = millis();
    //    Serial.println(responseBuffer);
  }

  HitType event2 = detectEvent(&lp2, &c2);
  if (event2 != NONE && millis()>c2Time+MESSAGE_COOLDOWN) {
    sprintf(body, "data=p2,%s", HitString[event2]);
    http_post(body, requestBuffer, responseBuffer);
    c2Time=millis();
    //    Serial.println(responseBuffer);
  }

  Serial.print(senseCurrent(&c1));
  Serial.print("\t");
  Serial.println(senseCurrent(&c2));
}

long senseCurrent(CapacitiveSensor* sensor) {
  long total1 = sensor->capacitiveSensorRaw(30);
  return total1;
}

HitType detectEvent(LowPass* lp, CapacitiveSensor* sensor) {
  long currentReading = senseCurrent(sensor);
  long low = lp->step(currentReading);

  if (sensor == &c1) {
    if (currentReading > SWORD_THRESH1) {
      return SWORD;
    } else if (low > OPP_THRESH1) {
      return OPPONENT;
    } else {
      return NONE;
    }
  } else if(sensor==&c2) {
        if (currentReading > SWORD_THRESH2) {
      return SWORD;
    } else if (low > OPP_THRESH2) {
      return OPPONENT;
    } else {
      return NONE;
    }
  } else{
    Serial.println("Something very wrong");
    return NONE;
  }

}
