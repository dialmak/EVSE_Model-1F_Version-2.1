// Тест для EVSE RIFORCE Model:1F Version:2.1

#define LED_WIFI_PIN 39
#define LED_ERR_PIN 40
#define LED_CHR_PIN 41
#define LED_FUNC_PIN 42

int timer = 100;
int ledPins[] = {
 LED_WIFI_PIN, LED_ERR_PIN, LED_CHR_PIN, LED_FUNC_PIN
};
int pinCount = 4;

int brightness = 0;
int fadeAmount = 5;
int fade = 30;


uint32_t chipId = 0;


void setup() {
  Serial.begin(115200);
  delay(3000);
	for(int i=0; i<17; i=i+8) {
	  chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
	}

	Serial.printf("ESP32 Chip model = %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
	Serial.printf("This chip has %d cores\n", ESP.getChipCores());
  Serial.print("Chip ID: "); Serial.println(chipId);
  Serial.print("SDK    :");
  Serial.println(ESP.getSdkVersion());
  Serial.print("SDK IDF:");
  Serial.println(esp_get_idf_version());

  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    pinMode(ledPins[thisPin], OUTPUT);
  }
  Serial.println("Тест світлодіодів 1");
  blink_led();
  Serial.println("Тест світлодіодів 2");
  on_led();
  delay(3000);
  off_led();
  Serial.println("Тест світлодіодів 3");
}

void loop() {

  fade_led();
}


void blink_led() {
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    digitalWrite(ledPins[thisPin], HIGH);
    delay(timer);
    digitalWrite(ledPins[thisPin], LOW);
  }

  for (int thisPin = pinCount - 1; thisPin >= 0; thisPin--) {
    digitalWrite(ledPins[thisPin], HIGH);
    delay(timer);
    digitalWrite(ledPins[thisPin], LOW);
  }
}

void on_led() {
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    digitalWrite(ledPins[thisPin], HIGH);
  }
}

void off_led() {
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    digitalWrite(ledPins[thisPin], LOW);
  }
}

void fade_led() {
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    analogWrite(ledPins[thisPin], brightness);
  }
  brightness = brightness + fadeAmount;
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  delay(fade);
}
