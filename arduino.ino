# Arduino code to check if moister level of the soil is under a procentage.

# Pins that are used with on the arduinop
const int analogInPin = A0;
const int relayPin = 2;

# Settings for freqensy
const int Hz = 2;

# Setting for the sensor value
const int dry = 80;

# Variables that are used in the script
const long serial = 9600*Hz;
const long sekund = 1000/Hz;
const long hour = 60;
const long restSensor = Hz*hour;
const long sensorDelay = 60;
const float dl = 2.1*sekund;
const int amount = Hz*dl;

# Defult values
bool watered = false;
int sensorValue = 0;
int outputValue = 0;
int value = 0;







void setup() {
  noInterrupts();
  CLKPR = _BV(CLKPCE);
  CLKPR = _BV(CLKPS0);
  interrupts();
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(relayPin, OUTPUT);
  Serial.begin(serial);
  led(true);
  led(false);
}

void sleep(long time, bool water){
  long i = 0;
  if(water){
    while(i < time){
      show();
      delay(sekund);
      Serial.print(i);
      Serial.print(" < ");
      Serial.println(time);
      i = i+1;
    }
    led(false);
  } else {
    while(i < time){
      show();
      led(true);
      delay(sekund/2);
      led(false);
      delay(sekund/2);
      Serial.print(i);
      Serial.print(" < ");
      Serial.println(time);
      i = i+1;
    }
  } 
}

long show(){
  sensorValue = analogRead(analogInPin);
  outputValue = map(sensorValue, 199, 499, 0, 100);
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.println(outputValue);
  return outputValue;
}

void pump(float amount){
  digitalWrite(relayPin, HIGH);
  delay(amount);
  digitalWrite(relayPin, LOW);
}

void led(bool onOff){
  if(onOff){
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void loop() {
  value = show();
  if(value > dry){
    Serial.println("watering");
    pump(amount);
    Serial.println("done :)");
    led(true);
    sleep(restSensor, true);
  } else {
    sleep(sensorDelay, false);
  }
}
