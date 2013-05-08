// parameters
const int stepsPerRev = 200; // depends on stepper
const int microstepsPerStep = 8; // depends on EasyDriver
const float degreesPerRev = 360; // 360 deg per revolution
float microstepsPerDeg = (stepsPerRev * microstepsPerStep) /degreesPerRev; // 4.44 microsteps/degree
int numberVials = 8; // number of vials on sampler
int cmd;

// setup pins
#define DIR_PIN 2
#define STEP_PIN 3
#define RELAY_PIN 7

void setup() {
  Serial.begin(9600);
  pinMode(DIR_PIN, OUTPUT); 
  pinMode(STEP_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT); 
}

void loop()
{
  if( Serial.available())
  {
    char ch = Serial.read();
    // index of possible commands
    // 0 = switch valve off
    // 1 = switch valve on
    // 2 = advance one position

    if(isDigit(ch)) // is this an ASCII digit between 0 and 9?
    {
      // convert ASCII value to actual number
      cmd = ch - '0';

      // execute command
      switch (cmd) {
      case 0: 
        {
          // switch valve off
          digitalWrite(RELAY_PIN, LOW);
          Serial.println("valve off");
          break;
        }
      case 1: 
        {
          // switch valve on
          digitalWrite(RELAY_PIN, HIGH);
          Serial.println("valve on");
          break;
        }
      case 2: 
        {
          // advance one position
          float degreesToMove = (360/numberVials);
          rotateDeg(degreesToMove);
          Serial.println("advanced");
          break;
        }
      default: 
        {
          Serial.println("unrecognised cmd");
        }
      }
    }
  }
}

void rotateSteps(int microsteps){ 
  //rotate a specific number of microsteps (8 microsteps per step) - (negitive for reverse movement)
  //speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger
  int dir = (microsteps > 0)? HIGH:LOW;
  digitalWrite(DIR_PIN,dir); 

  microsteps = abs(microsteps);
  float usDelay = 1400; //(1/speed) * 70;

  for(int i=0; i < microsteps; i++){ 
    digitalWrite(STEP_PIN, HIGH); 
    delayMicroseconds(usDelay); 

    digitalWrite(STEP_PIN, LOW); 
    delayMicroseconds(usDelay); 
  } 
} 

void rotateDeg(float deg){
  float microstepsToMove = microstepsPerDeg * deg;

  // need to round to the nearaest integer
  int microstepsToMoveInt;

  if(microstepsToMove > 0.0) {
    microstepsToMoveInt = floor(microstepsToMove + 0.5);
  } 
  else {
    microstepsToMoveInt = ceil(microstepsToMove - 0.5);
  }

  rotateSteps(microstepsToMoveInt);
}

