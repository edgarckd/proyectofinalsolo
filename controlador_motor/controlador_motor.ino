
// configuracion para el magnetometro

#include <Arduino.h>
#include <Wire.h>
// libraries



// Fin configuracion Magnetometro



static void smartdelay(unsigned long ms);
//const char* sol_pc_sen = "add";

const int I_sonic = 2, I_joystick = 3;

const int EN1 = 7, RPWM1 = 6, LPWM1 = 5;

const int EN2 = 8, RPWM2 = 10, LPWM2 = 9;
int pwm=130 , pwm1, pwm2 ;


const int Piny = A0, Pinx = A1; 
float Valuex, valorMayorX = -2, valorMenorX = 2; 
float Valuey, valorMayorY = -2, valorMenorY = 2;
char buffer = "M";
                /* **************************************** */



                  /* **************************************** */





void setup() {
  Serial.begin(115200);
  //pines de interrupciones
  Wire.begin(0x10);
  Wire.onReceive(automo);
  pinMode(13, OUTPUT);
 
  //pines de canal A
  pinMode(RPWM1, OUTPUT);
  pinMode(LPWM1, OUTPUT);
  pinMode(EN1, OUTPUT);
  //pines de canal B
  pinMode(RPWM2, OUTPUT);
  pinMode(LPWM2, OUTPUT);
  pinMode(EN2, OUTPUT);
  //apaga los motores, mas no frena la silla
  PayFr(EN1, RPWM1,LPWM1);
  PayFr(EN2, RPWM2,LPWM2);
  digitalWrite(13, HIGH);
  calibracion();
  digitalWrite(13, LOW);
  attachInterrupt(digitalPinToInterrupt(I_joystick), joystick , LOW);
}

void loop() {
delay(10);

  
  if(buffer == 'A'){
    int wm = 90;
    RoAde(wm,EN1,RPWM1,LPWM1);
    RoAde(wm,EN2,RPWM2,LPWM2);
    }
  if(buffer == 'S'){
    PayFr(EN1,RPWM1,LPWM1);
    PayFr(EN2,RPWM2,LPWM2);
    }
  if(buffer == 'B'){
      pwm = 90;
      RoRev(pwm, EN1, RPWM1,LPWM1);
      RoAde(pwm, EN2, RPWM2,LPWM2);
            
      }
  if(buffer == 'P'){         //Este comando hace que la silla Gire hacia la izquierda
      pwm = 90;
      RoRev(pwm, EN2, RPWM2,LPWM2);
      RoAde(pwm, EN1, RPWM1,LPWM1);
    }else{
      PasFr(EN1,RPWM1,LPWM1);
      PasFr(EN2,RPWM2,LPWM2);
    }
}

void RoAde(int pwm, int EN,int RPWM, int LPWM) {
  digitalWrite(EN,HIGH);
  analogWrite(RPWM,pwm);
  digitalWrite(LPWM,HIGH);
}

void RoRev(int pwm, int EN,int RPWM, int LPWM) {
  digitalWrite(EN,HIGH);
  analogWrite(LPWM,pwm);
  digitalWrite(RPWM,HIGH);
  }

void PasFr(int EN,int RPWM, int LPWM) {
  digitalWrite(EN,LOW);
  digitalWrite(RPWM,HIGH);
  digitalWrite(LPWM,HIGH);
  }

 void PayFr(int EN,int RPWM, int LPWM) {
  digitalWrite(EN,HIGH);
  digitalWrite(RPWM,HIGH);
  digitalWrite(LPWM,HIGH);
  }

void freno_ultrasonic(){
  PayFr(EN1, RPWM1,LPWM1);
  PayFr(EN2, RPWM2,LPWM2);
  }
void joystick(){
  /*Se esperan 500 milisegundos antes de leer si el ultrasonido detect?? un objeto. 
  Esto se hace con el objetivo de que el controlador de interrupciones pueda activar el pin de ultrasonido
  y este pueda ser leido por el controlador del moto
  */
  delay(10);
  if(digitalRead(I_sonic) == HIGH){
    //frenar silla sin parar
    freno_ultrasonic();
    }
    
  if(digitalRead(I_sonic) == LOW){
    // activar joystick
    leer();
    

    if(Valuey < valorMenorY && (Valuex<=valorMayorX && Valuex >= valorMenorX)){
      //silla adelante
      pwm = ((255 * Valuey)/(valorMenorY + 2.5)) + ((255*2.5)/(valorMenorY + 2.5));
      Serial.println(pwm);
      RoAde(pwm,EN1,RPWM1,LPWM1);
      RoAde(pwm,EN2,RPWM2,LPWM2);
      }else{
    if(Valuey > valorMayorY && (Valuex<=valorMayorX && Valuex >= valorMenorX)){
      //silla atras
      pwm = (255 * Valuey)/(valorMayorY - 2.5) - (255*2.5)/(valorMayorY - 2.5);
      Serial.println(pwm);
      RoRev(pwm,EN1,RPWM1,LPWM1);
      RoRev(pwm,EN2,RPWM2,LPWM2);
      }else{
        if(Valuex > valorMayorX && (Valuey >= valorMenorY && Valuey <= valorMayorY)){
      //giro derecha
      pwm = (255/(valorMayorX - 2.5))*(Valuex) - (255*2.5)/(valorMayorX - 2.5);
      Serial.println(pwm);
      PayFr(/*pwm,*/ EN2,RPWM2,LPWM2);
      RoAde(pwm, EN1, RPWM1,LPWM1);
      }else{
        if(Valuex < valorMenorX && (Valuey >= valorMenorY && Valuey <= valorMayorY)){
      //giro izquierda
      pwm = (255/(valorMenorX + 2.5))*(Valuex) + (255*2.5)/(valorMenorX + 2.5);
      Serial.println(pwm);
      PayFr(/*pwm,*/ EN1, RPWM1,LPWM1);
      RoAde(pwm, EN2, RPWM2,LPWM2);
      }else{
        PasFr(EN1,RPWM1,LPWM1);
        PasFr(EN2,RPWM2,LPWM2);
        }}
        }
    
    
      
    }
  }
    

  }
  

void leer(){
  Valuex = analogRead(Pinx);
  Valuey = analogRead(Piny);
   
  Valuex = (Valuex)*(5)/1024 -2.5;
  Valuey = (Valuey)*(5)/1024 -2.5;
  //return Valuex, Valuey;
  }

static void smartdelay(unsigned long ms){
  unsigned long start = millis();
  do{

  } while (millis() - start < ms);
}


void calibracion(){
  //for(int i; i<=150; i++){
    leer();

    if(Valuex > valorMayorX){
      valorMayorX = Valuex;
      }
    if(Valuex < valorMenorX){
      valorMenorX = Valuex;
      }
  
    if(Valuey > valorMayorY){
      valorMayorY = Valuey;
      }
    if(Valuey < valorMenorY){
      valorMenorY = Valuey;
      }
//}

    valorMayorX = valorMayorX + 0.1;
    valorMayorY = valorMayorY + 0.1;
    valorMenorX = valorMenorX - 0.1;
    valorMenorY = valorMenorY - 0.1;
    
  }

void automo(int howMany){
  /*String dato = "";           // como la variable dato se inicializa con un caracter nulo es importante verificar que este 
  while(Wire.available()){    // caracter no me genere inconvenientes mas adelante. si  genera el inconveniente, inicializa
    char c = Wire.read();
    dato.concat(c);           // siguiente forma if( dato.substring(1,2) == '#'){  pass  }, tambien tienes que incrementar el
    }                         // substring() de los if que se usan para los angulos
    dato.concat('\0');*/
    buffer = Wire.read();
  }



/*
void aut(int howMany){
  String dato = "";           // como la variable dato se inicializa con un caracter nulo es importante verificar que este 
  while(Wire.available()){    // caracter no me genere inconvenientes mas adelante. si  genera el inconveniente, inicializa
    char c = Wire.read();     // la variable con cualquier valor, y en los " dato.substring() " de los if, quedarian de la
    dato.concat(c);           // siguiente forma if( dato.substring(1,2) == '#'){  pass  }, tambien tienes que incrementar el
    }                         // substring() de los if que se usan para los angulos
    dato.concat('\0');

  if(dato.substring(0,1) == "B"){         //Este comando hace que la silla Gire hacia la derecha
    pwm = 90;
    RoRev(pwm, EN1, RPWM1,LPWM1);
    RoAde(pwm, EN2, RPWM2,LPWM2);
    }

  if(dato.substring(0,1) == "P"){         //Este comando hace que la silla Gire hacia la izquierda
    pwm = 90;
    RoRev(pwm, EN2, RPWM2,LPWM2);
    RoAde(pwm, EN1, RPWM1,LPWM1);
    }
    
  if(dato.substring(0,1) == "A"){         //Este comando hace que la silla vaya hacia delante
    pwm = 130;
    RoAde(pwm,EN1,RPWM1,LPWM1);
    RoAde(pwm,EN2,RPWM2,LPWM2);
    }
  if(dato.substring(0,1) == "S"){         // Este comando hace que la silla se detenga
    PayFr(EN1, RPWM1,LPWM1);
    PayFr(EN2, RPWM2,LPWM2);
    }
}*/
