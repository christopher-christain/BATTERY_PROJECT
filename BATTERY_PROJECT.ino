const int trigPin = 9; 
const int EchoPin = 10;
const int relayPin = 7;
bool relayState = LOW;
bool previousCondition = false;
// int inverter_on_led = 7;
int Buzzer_pin = 2;
// const int distanceThreshold = 1000; //10 meters
long duration;
int distance;

unsigned long printInterval = 1 * 60 * 1000; // 5 minutes in milliseconds
unsigned long previousPrintTime = 0;
// bool buzzerOn = false;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode (Buzzer_pin, OUTPUT);
 //  pinMode (inverter_on_led, OUTPUT);
  pinMode (trigPin, OUTPUT); // NOTE: THE TRIGPIN SENDS OUT OING SOUNDS 
  pinMode (EchoPin, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  // Interfacing ultrasonic sensor pinout with Arduino
  // Vcc is the supply pin of the HC-SR04 module
  // GND is the ground pin of the modules
  // TRIG is the trigger pin of the modules (pin 4)
  // ECHO is the echo pin of the modules (pin 5)

  // SETTING TRIGERPIN TO LOW AND HIGH TO TRIGGER ULTRA-SONIC SENSORS TO SEND OUT ULTRA-SONIC PULSE.
  digitalWrite(trigPin, LOW); //SETTING THE INITIAL TRIGPIN TO LOW.
  delayMicroseconds(10); //WAIT FOR 2MICROSECONDS
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);

  // CODE TO CALCULATE THE DISTANCE BASE ON DURATION OF THE ECHO
  duration = pulseIn(EchoPin, HIGH); //THE PULSEIN READS THE LENGTH OF A PULSE ON A PIN EITHER HIGH OR LOW
  //CALCULATE THE DISTANCE
  // DISTANCE IN (CM) = (TIME * SPEED OF SOUND)/2
  // NOTE: SPEED OF SOUND IN AIR IS 343.2M/S
  // DISTANCE IS DIVIDED BY 2, SINCE WE ARE SENDING AND RECIEVING AND WE NEED THE JUST DISTANCE BTW THE SENSOR AND THE OBJECT
  distance = duration /2.0 * 0.034; // THE O.O34CM/US IS THE SPEED OF SOUND IN AIR


  if(distance < 10){
    if(!previousCondition){
      relayState = !relayState;
      digitalWrite(Buzzer_pin, HIGH);
      digitalWrite(relayPin, relayState);
      previousCondition = true;
    }
  }

  
  else {
      digitalWrite(Buzzer_pin, LOW);
      previousCondition = false;
    
  }

  unsigned long currentTime = millis();
  if(currentTime - previousPrintTime >= printInterval){
    previousPrintTime = currentTime;

  }
   
  Serial.print("distance ");
  Serial.print(distance);
  Serial.print(" cm | inverter: ");
  Serial.println(relayState);


  delay(1000);
// print side working
}