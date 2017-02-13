#define DEBUG 1

double servoPos[16];
double servoMin[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
double servoMax[16] = {120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120};
double servoHome[16] = {60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60};

void setup() {  
}

void loop()
{
  
}

for(int i= 0; i <3;i=1+i)
{
  if(DEBUG)
  {
    Serial.print("walkingIndex");Serial.println(walkingIndex[i]);
  }

}
}

