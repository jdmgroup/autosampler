// parameters
const int stepsPerRev = 200; // depends on stepper
const int microstepsPerStep = 8; // depends on EasyDriver
const float degreesPerRev = 360; // 360 deg per revolution
float microstepsPerDeg = (stepsPerRev * microstepsPerStep) /degreesPerRev; // 4.44 microsteps/degree
int numberVials = 8; // number of vials on sampler

// setup pins
#define DIR_PIN 2
#define STEP_PIN 3
#define RELAY_PIN 7
byte cmd;

void setup()
{
  Serial.begin(9600);
  pinMode(DIR_PIN, OUTPUT); 
  pinMode(STEP_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
}

void loop()
{
  if (Serial.available()) {
      cmd = Serial.read();
      parsecommand(cmd);
  } 
}

void parsecommand(int cmd) {
    switch (cmd) 
    {
    case 48: // 0: switch valve off
      {
        digitalWrite(RELAY_PIN, LOW); 
        Serial.println("off");
        Serial.flush();
        break;
      }
    case 49: // 1: switch valve on
      {
        digitalWrite(RELAY_PIN, HIGH);
        Serial.println("on");
        Serial.flush();
        break;
      }
    case 50: // 2: advance one position
      {
        float degreesToMove = (360/numberVials);
        rotateDeg(degreesToMove);
        Serial.println("moved");
        Serial.flush();
        break;
      }
    case 63: // ?: check arduino status 
      {
        Serial.println("ready");
        Serial.flush();
        break;
      }
    default:
      {
        Serial.println("error");
        Serial.flush();
      }
    }
}

void rotateSteps(int microsteps){ 
  //rotate a specific number of microsteps (8 microsteps per step)
  // (negitive for reverse movement)
  int dir = (microsteps > 0)? HIGH:LOW;
  digitalWrite(DIR_PIN,dir); 

  microsteps = abs(microsteps);
  float usDelay = 1400;

  for (int i=0; i < microsteps; i++)
  { 
    digitalWrite(STEP_PIN, HIGH); 
    delayMicroseconds(usDelay); 

    digitalWrite(STEP_PIN, LOW); 
    delayMicroseconds(usDelay); 
  }
} 

void rotateDeg(float deg) {
  float microstepsToMove = microstepsPerDeg * deg;
  int microstepsToMoveInt; // need to round to the nearaest integer

  if (microstepsToMove > 0.0) {
    microstepsToMoveInt = floor(microstepsToMove + 0.5);
  } 
  else {
    microstepsToMoveInt = ceil(microstepsToMove - 0.5);
  }

  rotateSteps(microstepsToMoveInt);
}
