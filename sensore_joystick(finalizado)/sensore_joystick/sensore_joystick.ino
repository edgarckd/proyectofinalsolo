//inicio variable para ultrasonido
//no se puso valor de los pines

int trig1=6, eco1=7, trig2=8, eco2=9, inteco=12, intjoystick=13 ;
double medida1, medida2=500;
unsigned long previousMillis =0;
long duration, distanceCm;
boolean js, sn,  sn1, sn2;
//fin variables para ultrasonido

//variables para la funcion calibración
float valorMenorX = 3, valorMayorX = -3, valorMenorY = 3, valorMayorY = -3;
// fin de variables de calibración

//inicio variables para joystick

const int Pinx = A1; 
const int Piny = A0; 
float sensorValuex; 
float sensorValuey;

//fin variables para joystick


void setup() {
  //Serial.begin(115200);
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(inteco, OUTPUT);
  pinMode(intjoystick, OUTPUT);
  pinMode(eco1, INPUT);
  pinMode(eco2, INPUT);
  digitalWrite(inteco, LOW);
  digitalWrite(intjoystick, HIGH);
  calibracion();
}

void loop() {
  sonic(trig2, eco2, 2);
  
  sonic(trig1, eco1, 1);
  
  if(sn1 == true || sn2 == true){ sn = true;}else{sn = false;}
  joystick();
  if(js == false && sn == false){digitalWrite(intjoystick, HIGH);  digitalWrite(inteco, LOW);}
  if(js == false && sn == true){digitalWrite(intjoystick, LOW);  digitalWrite(inteco, HIGH);}
  if(js == true && sn == false){digitalWrite(intjoystick, LOW);  digitalWrite(inteco, LOW);}
  if(js == true && sn == true){digitalWrite(intjoystick, LOW);  digitalWrite(inteco, LOW);}
  
  
}

long sonic(int TRIG, int ECO, int son){
  
  digitalWrite(TRIG, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
  digitalWrite(TRIG, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  delayMicroseconds(1);
  duration = pulseIn(ECO, HIGH,23400);  //medimos el tiempo entre pulsos, en microsegundos
  distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
  if(distanceCm == 0){distanceCm = 400;}
  /*Serial.print(son);
  Serial.print(" :  ");
  Serial.println(distanceCm);*/
  if(distanceCm <= 150){
    if(son == 1){
      sn1= true;
      }
    if(son == 2){
      sn2 = true;
      }
    }else{
      if(son == 1){
      sn1= false;
      }
    if(son == 2){
      sn2 = false;
      }
      }
}


boolean joystick(){
   sensorValuex = analogRead(Pinx);
   sensorValuey = analogRead(Piny);
   sensorValuex = (sensorValuex)*(5)/1024 -2.5;
   sensorValuey = (sensorValuey)*(5)/1024 -2.5;
   if( valorMenorX < sensorValuex && sensorValuex < valorMayorX && valorMenorY < sensorValuey && sensorValuey < valorMayorY ){
    js = false ;
    }else{js = true ;}
  }

void calibracion(){
  long inicio = millis();
  do{
    sensorValuex = analogRead(Pinx);
    sensorValuey = analogRead(Piny);
    sensorValuex = (sensorValuex)*(5)/1024 -2.5;
    sensorValuey = (sensorValuey)*(5)/1024 -2.5;

    if(sensorValuex > valorMayorX){
      valorMayorX = sensorValuex;
      }
    if(sensorValuex < valorMenorX){
      valorMenorX = sensorValuex;
      }
  
    if(sensorValuey > valorMayorY){
      valorMayorY = sensorValuey;
      }
    if(sensorValuey < valorMenorY){
      valorMenorY = sensorValuey;
      }
    
    }while(millis() - inicio >=30000);

    valorMayorX = valorMayorX + 0.1;
    valorMayorY = valorMayorY + 0.1;
    valorMenorX = valorMenorX - 0.1;
    valorMenorY = valorMenorY - 0.1;
  }
