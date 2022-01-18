//Declaració dels pins on es connectaran els contactes del mòdul
int pinA = 8;
int pinB = 12;
int pinK = 13;
int pinC = 7;
int pinSout = 2;
int pinCout = 4;


void setup() {
  //S'indica el mode dels pins
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinK, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinSout, INPUT);
  pinMode(pinCout, INPUT);
  //S'inicialitza el contacte amb l'ordenador a 9600 baudis
  Serial.begin(9600);
}

//Declarem, per mitjà de cadenes de varibales booleanes, les combinacions que li aplicarem al mòdul avaluat.
const bool outputA[16] =      {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1};
const bool outputB[16] =      {0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1};
const bool outputK[16] =      {0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1};
const bool outputC[16] =      {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1}; 
//Declarem els resultats que haurien de ser rebuts segons les combinacions que li apliquem.
const bool expectedSout[16] = {0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0};
const bool expectedCout[16] = {0,0,0,1,0,1,0,0,0,1,1,1,1,1,0,1};

const int testRepetitions = 1000; //Repeticions de l'avaluació.
const int pauseTime = 100; //Temps de pausa abans de llegir els resultats.

bool hasExecuted = false; //Bandera que serà verdadera quan l'avaluació s'hagi completat

void loop() {

  if (hasExecuted == false){ //Només executarà el codi si la bandera és falsa
    for(int r=0; r<testRepetitions; r++)//Executarà el codi les vegades que hem indicat
    {
  
      bool testResult[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //Declarem una cadena de variables booleanes i les inicialitzem amb un valor fals.
      //0 ens indica que s'ha trobat una anomalia; 1 ens indicarà un resultat correcte.
      
      for(int i=0; i<16; i++)//Executarà el codi el nombre total de combinacions d'un sumador-restador
      {
        bool SoutRead = false;
        bool CoutRead = false;
        
        //Apliquem les combinacions pertinents a la placa avaluada.
        digitalWrite(pinA, outputA[i]);
        digitalWrite(pinB, outputB[i]);
        digitalWrite(pinK, outputK[i]);
        digitalWrite(pinC, outputC[i]);
        delay(pauseTime); //S'efectua una pausa.
        
        //Es llegeix quins valors estem rebent de la placa avaluada
        SoutRead = digitalRead(pinSout);
        CoutRead = digitalRead(pinCout);
        
        //En el cas que el resultat rebut no sigui l'esperat, s'indicarà l'anomalia a la cadena testResult.
        if (SoutRead != expectedSout[i] || CoutRead != expectedCout[i]) {testResult[i] = 0;} else {testResult[i] = 1;}
      }
  
      bool didSuccess = true; //Declarem la variable que ens indicara si l'avaluació ha sigut exitosa
      
      for(int i=0; i<16; i++)//Analitzem la cadena testResult per observar si hi ha hagut cap anomalia.
      {
        if (testResult[i] == 0) {didSuccess=false; Serial.println("Test failed!\n"); break;} //Si se'n detecta una, s'indica, es trenca el bucle i es finalitza l'avaluació.
      }
  
      if (didSuccess == true) {Serial.print("Test "); Serial.print(r); Serial.print(" has succeeded!\n");} else {break;} //Si l'avaluació ha sigut exitosa, s'indica i es trenca el bucle.
    }
    
    Serial.print("Test has finalized!\n");
    digitalWrite(pinA, 0);
    digitalWrite(pinB, 0);
    digitalWrite(pinK, 0);
    digitalWrite(pinC, 0);
    hasExecuted = true; //S'activa la bandera d'execució de la prova
  }

}
