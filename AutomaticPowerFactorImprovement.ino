#include <EmonLib.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

EnergyMonitor emon1;
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Relay pins
#define R1 4
#define R2 5
#define R3 6
#define R4 7

float voltage, current, pf;

// Thresholds
float PF_LOW  = 0.92;
float PF_HIGH = 0.99;

// Calibration values (will auto update)
float V_CAL = 230.0;
float I_CAL = 60.0;
float PHASE_CAL = 1.7;

// Stage
int stage = 0;

// Timing
unsigned long lastSwitch = 0;
const unsigned long delayTime = 3000;

// -------- APPLY STAGE --------
void applyStage() {
  digitalWrite(R1, (stage >= 1));
  digitalWrite(R2, (stage >= 2));
  digitalWrite(R3, (stage >= 3));
  digitalWrite(R4, (stage >= 4));
}

// -------- SAFE PF --------
float safePF(float pf){
  if(pf < 0.05) return 0.05;
  if(pf > 0.99) return 0.99;
  return pf;
}

// -------- AUTO CALIBRATION --------
void autoCalibrate() {

  Serial.println("Calibrating...");

  float vSum = 0;

  for(int i=0; i<10; i++){
    emon1.calcVI(20,2000);
    vSum += emon1.Vrms;
    delay(200);
  }

  float vMeasured = vSum / 10.0;

  // Assume real voltage = 220V
  float V_REAL = 220.0;

  float factor = V_REAL / vMeasured;

  V_CAL = V_CAL * factor;

  Serial.print("Measured V: ");
  Serial.println(vMeasured);

  Serial.print("New V_CAL: ");
  Serial.println(V_CAL);

  // Update library with new calibration
  emon1.voltage(A0, V_CAL, PHASE_CAL);
}

// -------- SETUP --------
void setup() {
  Serial.begin(9600);

  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);

  applyStage();

  lcd.init();
  lcd.backlight();

  // Initial setup
  emon1.voltage(A0, V_CAL, PHASE_CAL);
  emon1.current(A1, I_CAL);

  lcd.print("CALIBRATING...");
  delay(1000);

  autoCalibrate();   // 🔥 AUTO CALIBRATION

  lcd.clear();
  lcd.print("READY");
  delay(1000);
  lcd.clear();
}

// -------- LOOP --------
void loop() {

  emon1.calcVI(20, 2000);

  voltage = emon1.Vrms;
  current = emon1.Irms;
  pf = safePF(emon1.powerFactor);

  unsigned long now = millis();

  // CONTROL
  if (now - lastSwitch > delayTime) {

    if (pf < PF_LOW && stage < 4) {
      stage++;
      applyStage();
      Serial.println("ADD CAP");
      lastSwitch = now;
    }

    else if (pf > PF_HIGH && stage > 0) {
      stage--;
      applyStage();
      Serial.println("REMOVE CAP");
      lastSwitch = now;
    }
  }

  // SERIAL
  Serial.print("V="); Serial.print(voltage);
  Serial.print(" I="); Serial.print(current);
  Serial.print(" PF="); Serial.print(pf);
  Serial.print(" Stage="); Serial.println(stage);

  // LCD
  lcd.setCursor(0,0);
  lcd.print("V:"); lcd.print(voltage,0);

  lcd.setCursor(8,0);
  lcd.print("I:"); lcd.print(current,1);

  lcd.setCursor(0,1);
  lcd.print("PF:"); lcd.print(pf,2);

  lcd.setCursor(9,1);
  lcd.print("C:"); lcd.print(stage);

  delay(1000);
}