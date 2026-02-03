GSM Gas Leakage Detector 🚨🔥

A smart GSM-based Gas Leakage Detection System using Arduino that detects gas leakage, alerts users via SMS and call, displays status on an I2C LCD, activates a buzzer & LEDs, and automatically controls a gas regulator using a servo motor.

📌 Features

✅ Detects gas leakage using MQ gas sensor

📟 Displays gas level (%) on 16x2 I2C LCD

🚨 Activates buzzer and red LED during leakage

📞 Automatically makes a call on gas detection

📩 Sends SMS alert with gas level

🔄 Controls gas regulator using servo motor

📬 Can receive SMS commands:

ON → Open gas regulator

OFF → Close gas regulator

🧰 Components Used
Component	Quantity
Arduino Uno	1
MQ Gas Sensor	1
GSM Module (SIM800/900)	1
Servo Motor	1
16x2 I2C LCD	1
Buzzer	1
Red LED	1
Green LED	1
Resistors	As required
Connecting Wires	As required
External Power Supply (for GSM)	1
🔌 Pin Connections
Gas Sensor

AO → A0

GSM Module

TX → Arduino Pin 2

RX → Arduino Pin 3

GND → GND

VCC → External 12V / 5V (as per module)

⚠️ Do NOT power GSM module directly from Arduino 5V

LCD (I2C)

SDA → A4

SCL → A5

Servo Motor

Signal → Pin 9

VCC → External 5V

GND → GND

LEDs & Buzzer

Red LED → Pin 7

Green LED → Pin 6

Buzzer → Pin 8

📚 Libraries Required

Install the following libraries from Arduino Library Manager:

LiquidCrystal_I2C

Servo

SoftwareSerial

Wire

⚙️ Working Principle

Gas sensor continuously monitors gas level

Gas value is converted into percentage

If gas level exceeds 30% threshold:

Buzzer turns ON

Red LED glows

Servo closes gas regulator

SMS alert is sent

Call is made to user

LCD displays GAS ALERT

User can remotely control regulator via SMS (ON / OFF)

When gas level is safe:

Green LED glows

System resets automatically

📱 SMS Commands
Command	Action
ON	Opens gas regulator
OFF	Closes gas regulator
🛠️ Configuration

Edit the phone number in the Arduino code:

AT+CMGS="+91XXXXXXXXXX"
ATD+91XXXXXXXXXX;


Adjust gas threshold if required:

int thresholdPercent = 30;

🧪 Applications

Home kitchens

Restaurants

Gas laboratories

Industries

LPG safety systems

👨‍💻 Author

Sab
B.Tech – Robotics & Artificial Intelligence
Embedded Systems | Arduino | GSM | IoT

📜 License

This project is open-source and free to use for educational purposes.
