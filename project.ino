#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myServo;
SoftwareSerial gsm(2, 3);   // Arduino RX, TX

int gasSensor = A0;
int buzzer = 8;
int redLed = 7;
int greenLed = 6;
int servoPin = 9;

int thresholdPercent = 30;
bool alertSent = false;
unsigned long lastAlertTime = 0;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  digitalWrite(buzzer, LOW);
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, HIGH);  // SAFE at start

  myServo.attach(servoPin);
  myServo.write(0);  // OPEN

  lcd.init();
  lcd.backlight();
  lcd.print("Gas Detector");
  delay(2000);
  lcd.clear();

  gsm.begin(9600);
  delay(3000);

  gsm.println("AT");
  delay(1000);
  gsm.println("AT+CMGF=1");
  delay(1000);
  gsm.println("AT+CNMI=2,2,0,0,0");
}

void loop() {
  int gasValue = analogRead(gasSensor);
  int gasPercent = map(gasValue, 0, 1023, 0, 100);

  lcd.setCursor(0, 0);
  lcd.print("Gas: ");
  lcd.print(gasPercent);
  lcd.print("%   ");

  if (gasPercent > thresholdPercent) {
    digitalWrite(buzzer, HIGH);
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    myServo.write(90);   // CLOSE

    lcd.setCursor(0, 1);
    lcd.print("!! GAS ALERT !!");

    if (!alertSent && millis() - lastAlertTime > 60000) {
      sendSMS(gasPercent);
      makeCall();
      alertSent = true;
      lastAlertTime = millis();
    }

  } else {
    digitalWrite(buzzer, LOW);
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    myServo.write(0);   // OPEN

    lcd.setCursor(0, 1);
    lcd.print("Status: SAFE   ");
    alertSent = false;
  }

  receiveSMS();
  delay(300);
}

// ---------- SMS ----------
void sendSMS(int percent) {
  gsm.println("AT+CMGS=\"+91XXXXXXXXXX\"");
  delay(1000);
  gsm.print("Gas Alert! Level: ");
  gsm.print(percent);
  gsm.println("%");
  gsm.write(26);
  delay(3000);
}

// ---------- CALL ----------
void makeCall() {
  gsm.println("ATD+91XXXXXXXXXX;");
  delay(12000);
  gsm.println("ATH");
}

// ---------- RECEIVE ----------
void receiveSMS() {
  if (gsm.available()) {
    String sms = gsm.readString();
    sms.toUpperCase();

    if (sms.indexOf("OFF") != -1) {
      myServo.write(90);
      lcd.clear();
      lcd.print("Regulator OFF");
    }

    if (sms.indexOf("ON") != -1) {
      myServo.write(0);
      lcd.clear();
      lcd.print("Regulator ON");
    }
  }
}