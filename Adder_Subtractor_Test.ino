int pinA = 8;
int pinB = 12;
int pinK = 13;
int pinC = 7;
int pinSout = 2;
int pinCout = 4;

double operationFrequency = 1000; //in kHz
double microSeconds = 0;
void setup() {
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinK, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinSout, INPUT);
  pinMode(pinCout, INPUT);

  microSeconds = ((1/operationFrequency)*1000);

  Serial.begin(9600);

}

bool outputA[16] =      {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1};
bool outputB[16] =      {0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1};
bool outputK[16] =      {0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1};
bool outputC[16] =      {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1}; 

bool expectedSout[16] = {0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0};
bool expectedCout[16] = {0,0,0,1,0,1,0,0,0,1,1,1,1,1,0,1};

int testRepetitions = 1000;
bool hasExecuted = false;

void loop() {

  if (hasExecuted == false){
    for(int r=0; r<testRepetitions; r++)
    {
  
      bool testResult[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
      
      for(int i=0; i<16; i++)
      {
        bool SoutRead = false;
        bool CoutRead = false;
        
        digitalWrite(pinA, outputA[i]);
        digitalWrite(pinB, outputB[i]);
        digitalWrite(pinK, outputK[i]);
        digitalWrite(pinC, outputC[i]);
        delay(microSeconds);
        
        SoutRead = digitalRead(pinSout);
        CoutRead = digitalRead(pinCout);
  
        if (SoutRead != expectedSout[i] || CoutRead != expectedCout[i]) {testResult[i] = 0;} else {testResult[i] = 1;}
      }
  
      bool didSuccess = true;
      
      for(int i=0; i<16; i++)
      {
        if (testResult[i] == 0) {didSuccess=false; Serial.println("Test failed!\n"); break;}
      }
  
      if (didSuccess == true) {Serial.print("Test "); Serial.print(r); Serial.print(" has succeeded!\n");} else {break;}
    }
    Serial.print("Test has finalized!\n");
    digitalWrite(pinA, 0);
    digitalWrite(pinB, 0);
    digitalWrite(pinK, 0);
    digitalWrite(pinC, 0);
    hasExecuted = true;
  }

}
