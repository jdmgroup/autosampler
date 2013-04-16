// send two digits:
// (currentvialposition,finalvialposition)
// (0,1) turns on relay
// (0,0) turns off relay
// After recieving Arduino sends back:
// "received"
// "firstnumber"
// "secondnumber"

// parameters
const int stepsPerRev = 200; // depends on stepper
const int microstepsPerStep = 8; // depends on EasyDriver
const float degreesPerRev = 360; // 360 deg per revolution
float microstepsPerDeg = (stepsPerRev * microstepsPerStep) /degreesPerRev; // 4.44 microsteps/degree
int numberVials = 8; // number of vials on sampler

// serial comm
const int NUMBER_OF_FIELDS = 2;
int fieldIndex = 0;
int values[NUMBER_OF_FIELDS];

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
    // is this an ascii digit between 0 and 9 or V?
    if(ch >= '0' && ch <= '9')
    {
      // yes, accumulate the value
      values[fieldIndex] = (values[fieldIndex] * 10) + (ch - '0');
    }
    else if (ch == ',')  // comma is our separator, so move on to the next field
    {
      if(fieldIndex < NUMBER_OF_FIELDS-1)
        fieldIndex++;   // increment field index
    }
    else
    {
      // any character not a digit or comma ends the acquisition of fields
      // in this example it's the newline character sent by the Serial Monitor
        if (values[0] == 0) // valve mode
        {
          if (values[1] == 1) // switch the relay on
            {
              digitalWrite(RELAY_PIN, HIGH);
            }
            else if (values[1] == 0) // switch the off
            {
              digitalWrite(RELAY_PIN, LOW);
            }
        }
        else // move vial position
        {
          float degreesToMove = (values[1]-values[0]) * (360/numberVials);
          rotateDeg(degreesToMove);
        }
      // debugging
      Serial.print("received:");
      
      //for(int i=0; i <= fieldIndex; i++)
      //{
        Serial.print(values[0]);
                Serial.print(',');
      Serial.println(values[1]);
values[0] = 0; // set the values to zero, ready for the next message
values[1] = 0;
    //}
      fieldIndex = 0;  // ready to start over
      Serial.println();
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
