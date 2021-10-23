  
static void smartdelay(unsigned long ms);
//const char* sol_pc_sen = "add";

const int I_sonic = 2, I_joystick = 3, pinNoMagnetometro = null;

const int EN1 = 7, RPWM1 = 6, LPWM1 = 5;

const int EN2 = 9, RPWM2 = 10, LPWM2 = 9;
int pwm = 130, pwm1, pwm2;

// pines del joystick
const int Pinx = A1; 
const int Piny = A0; 
float Valuex, valorMayorX = -2, valorMenorX = 2; 
float Valuey, valorMayorY = -2, valorMenorY = 2;

                /* **************************************** */

// configuracion para el magnetometro

#include <Arduino.h>
#include <Wire.h>
// libraries
#include "bmm150.h"
#include "bmm150_defs.h"

BMM150 bmm = BMM150();
bmm150_mag_data value_offset;

float angulo; // la variable angulo contiene el sentido de la silla 

// Fin configuracion Magnetometro

                  /* **************************************** */

//configuracion del modo autonomo

char dato; // Esta es la variable que lee el puerto I2C una vez el maestro envia un dato
float consigna;
//fin del modo autonomo



void setup() {
  //Serial.begin(115200);
  //pines de interrupciones
  Wire.begin(0x10);
  Wire.onReceive(autonomo);
  pinMode(13, OUTPUT);
  pinMode(pinNoMagnetometro, OUTPUT);
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
  PayFr(EN1, RPWM1,LPWM1);
  PayFr(EN2, RPWM2,LPWM2);
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
  /*Se esperan 500 milisegundos antes de leer si el ultrasonido detectó un objeto. 
  Esto se hace con el objetivo de que el controlador de interrupciones pueda activar el pin de ultrasonido
  y este pueda ser leido por el controlador del moto
  */
  delay(10);
  //smartdelay(500);
    
  if(digitalRead(I_sonic) == HIGH){
    //frenar silla sin parar
    freno_ultrasonic();
    }
    
  if(digitalRead(I_sonic) == LOW){
    // activar joystick
    leer();
    if(Valuey < valorMenorY && (Valuex<=valorMayorX || Valuex >= valorMenorX)){
      //silla adelante
      pwm = (255 * Valuey)/(valorMenorY + 2.5) + (255*2.5)/(valorMenorY + 2.5);
      RoAde(pwm,EN1,RPWM1,LPWM1);
      RoAde(pwm,EN2,RPWM2,LPWM2);
      }
    if(Valuey > valorMayorY && (Valuex<=valorMayorX || Valuex >= valorMenorX)){
      //silla atras
      pwm = (255 * Valuey)/(valorMayorY - 2.5) - (255*2.5)/(valorMayorY - 2.5);
      RoRev(pwm,EN1,RPWM1,LPWM1);
      RoRev(pwm,EN2,RPWM2,LPWM2);
      }
    if(Valuex > valorMayorX && (Valuey >= valorMenorY || Valuey <= valorMayorY)){
      //giro derecha
      pwm = (255/(valorMayorX - 2.5))*(Valuex) - (255*2.5)/(valorMayorX - 2.5);
      RoRev(pwm, EN1,RPWM1,LPWM1);
      RoAde(pwm, EN1, RPWM1,LPWM1);
      }
    if(Valuex < valorMenorX && (Valuey >= valorMenorY || Valuey <= valorMayorY)){
      //giro izquierda
      pwm = (255/(valorMenorX + 2.5))*(Valuex) + (255*2.5)/(valorMenorX + 2.5);
      RoRev(pwm, EN2,RPWM2,LPWM2);
      RoAde(pwm, EN2, RPWM2,LPWM2);
      }else{
        PayFr(EN1,RPWM1,LPWM1);
        PayFr(EN2,RPWM2,LPWM2);
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

float medirMagnetometro(){
  if(bmm.initialize() == BMM150_E_ID_NOT_CONFORM){
    Serial.println("Chip ID can not read!");
    digitalWrite(pinNoMagnetometro,HIGH);
    smartdelay(1);
    digitalWrite(pinNoMagnetometro, LOW);
    //return ; aquí retorno el angulo que me pidan para que la silla no se mueva y no se me genere error
  } 
  else {
    bmm150_mag_data value;
    bmm.read_mag_data();
  
    value.x = bmm.raw_mag_data.raw_datax - value_offset.x;
    value.y = bmm.raw_mag_data.raw_datay - value_offset.y;
    value.z = bmm.raw_mag_data.raw_dataz - value_offset.z;
  
    float xyHeading = atan2(value.x, value.y);
    float zxHeading = atan2(value.z, value.x);
    float heading = xyHeading;
  
    if(heading < 0)
      heading += 2*PI;
    if(heading > 2*PI)
      heading -= 2*PI;
    angulo = heading * 180/M_PI; 
    float xyHeadingDegrees = xyHeading * 180 / M_PI;
    float zxHeadingDegrees = zxHeading * 180 / M_PI;
    return angulo;
  }
}

void autonomo(){
  while(1 < Wire.available()){ dato = Wire.read(); /* receive byte as a character */ /*Serial.print(c);  print the character*/}
  char comando = getValue(dato, ' ', 0);
  if( comando == S){
    // posicionar la silla en angulo
    consigna = getValue(dato, ' ', 1);
    //se debe de ingresar dentro de una ciclo while o do-while
    
    float error = error();
    if(error < dir()){
      // giro por derecha
      
      }
    if(error >= dir()){
      //giro por Izquierda
      }

    
    }
  if (comando == A){
    //pone en movimiento la silla haci adelante
    }

  if(comando == D){
    // detiene la silla
    }
}

float error(){
  float erro = consigna - medirMagnetometro();
  return abs(erro);
  
  }

float dir(){
  float anReal = medirMagnetometro;
  if (anReal >= 180){
    anReal -= PI;
    }else{
    anReal += PI;  
      }
    return anReal;
  }

String getValue(String data, char separator, int index)//Esta funcion es un .split()
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}