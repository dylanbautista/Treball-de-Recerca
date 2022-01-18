int pinA = 0;
int pinB = 1;
int pinK = 2;
int pinC = 3;
int pinSout = 4;
int pinCout = 5;

void setup() {
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinK, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinSout, INPUT);
  pinMode(pinCout, INPUT);

}

bool outputA[16] =      {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1};
bool outputB[16] =      {0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1};
bool outputK[16] =      {0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1};
bool outputC[16] =      {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1}; 

bool expectedSout[16] = {0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0};
bool expectedCout[16] = {0,0,0,1,0,1,0,0,0,1,1,1,1,1,0,1};

int testRepetitions = 10;
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
        delay(10);
        
        SoutRead = digitalRead(pinSout);
        CoutRead = digitalRead(pinCout);
  
        if (SoutRead != expectedSout[i] && CoutRead != expectedCout[i]) {testResult[i] = 0;} else {testResult[i] = 1;}
      }
  
      bool didSuccess = true;
      
      for(int i=0; i<16; i++)
      {
        if (testResult[i] == 0) {didSuccess=false; Serial.println("Test failed!\n"); break;}
      }
  
      if (didSuccess == true) {Serial.println("Test has succeeded!\n");} else {break;}
    }
    hasExecuted = true;

  
  }

}
