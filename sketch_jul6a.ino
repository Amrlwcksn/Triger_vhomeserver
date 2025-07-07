#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

RTC_DS3231 rtc;

const int relayPin = 8;
bool triggeredToday = false;
String relayStatus = "Standby";

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // OFF di awal (aktif LOW)

  Serial.begin(9600);
  Wire.begin();

  if (!rtc.begin()) {
    Serial.println("RTC not found");
    while (1);
  }

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED init failed");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // SET RTC sekali saja, lalu comment!
  // rtc.adjust(DateTime(2025, 7, 6, 12, 57, 00));
}

void loop() {
  DateTime now = rtc.now();

  // Cek apakah perlu trigger
  if (now.hour() == 6 && now.minute() == 30 && now.second() == 0 && !triggeredToday) {
    triggerRelay();
    triggeredToday = true;
    relayStatus = "Triggered";
  }

  // Reset trigger agar bisa aktif lagi besok
  if (now.hour() == 6 && now.minute() == 31 && now.second() == 0) {
    triggeredToday = false;
    relayStatus = "Standby";
  }

  // OLED Tampilan
  display.clearDisplay();

  // Judul
  display.setCursor(20, 0);
  display.setTextSize(1);
  display.print("Wake Up Server!");

  // Waktu
  display.setTextSize(2);
  display.setCursor(15, 20);
  printFormattedTime(now.hour(), now.minute(), now.second());

  // Status Relay
  display.setTextSize(1);
  display.setCursor(10, 50);
  display.print("Relay: ");
  display.print(relayStatus);

  display.display();

  delay(1000);
}

void triggerRelay() {
  digitalWrite(relayPin, LOW);  // Aktifkan relay
  delay(1000);                  // 1 detik
  digitalWrite(relayPin, HIGH); // Matikan
}

void printFormattedTime(int h, int m, int s) {
  if (h < 10) display.print("0");
  display.print(h);
  display.print(":");
  if (m < 10) display.print("0");
  display.print(m);
  display.print(":");
  if (s < 10) display.print("0");
  display.print(s);
}
