#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---------- LCD ----------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------- PIR Sensor ----------
const int pirPin = 2;
int pirState = LOW;   // Start assuming no motion
int val = 0;

// ---------- Custom Icons ----------
// Person / motion icon 🕵️ (stick figure)
byte personIcon[8] = {
  B00100,
  B01110,
  B00100,
  B01110,
  B10101,
  B00100,
  B01010,
  B10001
};

// Skull 💀 (alert)
byte skullIcon[8] = {
  B01110,
  B10101,
  B11111,
  B11111,
  B01110,
  B01010,
  B10101,
  B00000
};

// Sleep / idle icon 😴
byte sleepIcon[8] = {
  B00000,
  B00000,
  B01000,
  B00100,
  B00010,
  B00000,
  B00000,
  B00000
};

void setup() {
  pinMode(pirPin, INPUT);

  lcd.init();
  lcd.backlight();

  // Load custom icons
  lcd.createChar(0, personIcon);
  lcd.createChar(1, skullIcon);
  lcd.createChar(2, sleepIcon);

  // Startup screen
  lcd.setCursor(0, 0);
  lcd.write(byte(0));
  lcd.print(" PIR Sensor ");
  lcd.write(byte(0));
  lcd.setCursor(0, 1);
  lcd.print(" Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  val = digitalRead(pirPin);

  // ---------- Line 1: Label + Status ----------
  lcd.setCursor(0, 0);
  lcd.write(byte(0));         // Person icon
  lcd.print(" Motion: ");

  if (val == HIGH) {
    lcd.print("DETECTED ");
    lcd.setCursor(15, 0);
    lcd.write(byte(1));       // Skull icon for alert
  } else {
    lcd.print("None     ");
    lcd.setCursor(15, 0);
    lcd.write(byte(2));       // Sleep icon
  }

  // ---------- Line 2: Digital Value + Message ----------
  lcd.setCursor(0, 1);
  lcd.print("D:");
  lcd.print(val);
  lcd.print(" ");

  lcd.setCursor(4, 1);
  if (val == HIGH) {
    lcd.print("Movement ");
    lcd.write(byte(1)); // Skull icon
    pirState = HIGH;
  } else {
    lcd.print("No Movement   ");
    pirState = LOW;
  }

  delay(100);
}
