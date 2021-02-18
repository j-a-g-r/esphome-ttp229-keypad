#include "esphome.h"
#include "ErriezTTP229.h"

class ttpkeypad : public Component, public Sensor {
 public:

#define TTP229_SDO_PIN    D1  // Interrupt pin
#define TTP229_SCL_PIN    D2  // Any pin

ErriezTTP229 ttp229;
#if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINO_ARCH_ESP32)
ICACHE_RAM_ATTR
#endif

void keyChange()
{
    // A key press changed
    ttp229.keyChange = true;
}

  void setup() override {
    // This will be called by App.setup()
    ttp229.begin(TTP229_SCL_PIN, TTP229_SDO_PIN);
    attachInterrupt(         (TTP229_SDO_PIN), keyChange, FALLING);

  }
  void loop() override {
    // This will be called by App.loop()
    if (ttp229.keyChange) {
      publish_state(ttp229.GetKey16());
      ttp229.keyChange = false;
    }

  }
};
