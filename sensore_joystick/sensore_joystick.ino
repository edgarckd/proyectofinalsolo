//inicio variable para ultrasonido
//no se puso valor de los pines

int trig1, eco1, trig2, eco2, inteco, intjoystick ;
double medida1, medida2;
unsigned long previousMillis =0;

//fin variables para ultrasonido



//inicio variables para joystick

const int Pinx = A1; 
const int Piny = A0; 
float sensorValuex; 
float sensorValuey;

//fin variables para joystick


void setup() {
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(inteco, OUTPUT);
  pinMode(intjoystick, OUTPUT);
  pinMode(eco1, INPUT);
  pinMode(eco2, INPUT);
  digitalWrite(inteco, LOW);
  digitalWrite(intjoystick, LOW);
}

void loop() {
  medida1 = sonic(trig1, eco1);
  medida2 = sonic(trig2, eco2);
  if (joystick()){digitalWrite(intjoystick, HIGH);}else{digitalWrite(intjoystick, LOW);}
  do{
    digitalWrite(inteco, LOW);
    medida1 = sonic(trig1, eco1);
    medida2 = sonic(trig2, eco2);
    if (joystick()){digitalWrite(intjoystick, HIGH);}else{digitalWrite(intjoystick, LOW);}
    if(medida1 >= 150 && medida2 >=150 ){
      previousMillis = millis();
      }
  }while((medida1<=150 || medida2 <= 150) && (millis() - previousMillis >= 500 ));
  digitalWrite(inteco, HIGH);

}

double sonic(int TRIG, int ECO){
  double sensador = 0;
  for (int i =0; i<=50;i++){
    delayMicroseconds(2);
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    double duracion = pulseIn(ECO,HIGH);
    double distancia = (0.034*duracion)/2;
    sensador=sensador+ distancia;
  }
  sensador = sensador/50;
  return sensador; 
}


boolean joystick(){
   float sensorValuex = analogRead(Pinx);
   float sensorValuey = analogRead(Piny);
   sensorValuex = (sensorValuex)*(5)/1024 -2.5;
   sensorValuey = (sensorValuey)*(5)/1024 -2.5;
   if( -0.5 > sensorValuex ||sensorValuex > 0.5 || -0.5> sensorValuey || sensorValuey > 0.5 ){
    return true ;
    }
  }
