#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DFRobotDFPlayerMini.h>

#define RX_PIN 0   
#define TX_PIN 1  
#define PLAY_BUTTON 4
#define STATUS_LED 5
#define BATT_SENSE A0

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

SoftwareSerial mp3Serial(RX_PIN, TX_PIN); 
DFRobotDFPlayerMini mp3;

bool isPlaying = false;
unsigned long lastDebounce = 0;
int lastButtonState = HIGH;


int batteryPercentage() {
  int adc = analogRead(BATT_SENSE);
  float voltage = (adc / 1023.0) * 5.0; 

  voltage *= 2.0; 
  int percent = map(voltage * 100, 330, 420, 0, 100); 
  percent = constrain(percent, 0, 100);
  return percent;
}

void setup() {
  pinMode(PLAY_BUTTON, INPUT_PULLUP);
  pinMode(STATUS_LED, OUTPUT);

  mp3Serial.begin(9600);
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (1);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);

  display.setCursor(0, 10);
  display.println("Initializing DFPlayer...");
  display.display();

  if (!mp3.begin(mp3Serial)) {
    display.clearDisplay();
    display.setCursor(0, 10);
    display.println("DFPlayer not found!");
    display.display();
    while (true);
  }

  mp3.volume(20);
  mp3.play(1);    
  isPlaying = true;
  digitalWrite(STATUS_LED, HIGH);
}

void loop() {
  int buttonState = digitalRead(PLAY_BUTTON);
  if (buttonState == LOW && lastButtonState == HIGH && millis() - lastDebounce > 300) {
    lastDebounce = millis();
    if (isPlaying) {
      mp3.pause();
      isPlaying = false;
      digitalWrite(STATUS_LED, LOW);
    } else {
      mp3.start();
      isPlaying = true;
      digitalWrite(STATUS_LED, HIGH);
    }
  }
  lastButtonState = buttonState;

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("MP3 Player");
  display.setTextSize(2);
  display.setCursor(0, 20);
  display.println(isPlaying ? "Playing" : "Paused");

  display.setTextSize(1);
  display.setCursor(0, 48);
  display.print("Battery: ");
  display.print(batteryPercentage());
  display.println("%");

  display.display();
  delay(300);
}
