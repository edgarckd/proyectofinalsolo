
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <Arduino.h>
#include <Wire.h>
#include "bmm150.h"
#include "bmm150_defs.h"
BMM150 bmm = BMM150();
bmm150_mag_data value_offset;

TinyGPS gps;
SoftwareSerial ss (13, 12);

static void smartdelay(unsigned long ms);
static void print_float(float val, float invalid, int len, int prec);

char dato;

void calgps(){
  float flat, flon;
  unsigned long age;
  static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;

  gps.f_get_position(&flat, &flon, &age);
  print_float(flat, TinyGPS::GPS_INVALID_F_ANGLE, 10, 6);
  print_float(flon, TinyGPS::GPS_INVALID_F_ANGLE, 11, 6);
  
}

static void smartdelay(unsigned long ms){
  unsigned long start = millis();
  do{
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

static void print_float(float val, float invalid, int len, int prec){
  if (val == invalid){
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else{
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
}
float magnetometro(){
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
  float headingDegrees = heading * 180/M_PI; 
  float xyHeadingDegrees = xyHeading * 180 / M_PI;
  float zxHeadingDegrees = zxHeading * 180 / M_PI;
    
  return headingDegrees; 
}

void setup() {
  Serial.begin(115200);
  ss.begin(9600);
  Wire.begin();
  if(bmm.initialize() == BMM150_E_ID_NOT_CONFORM){
    while(1);
  } 
}

void loop() {
  smartdelay(600);
}

void serialEvent(){
  String dato = "";
  while(Serial.available()){
    char da = Serial.read();
    dato.concat(da);
    }
    dato.concat('\0');

    //_--------------------------------------------------------------------------------------------------------------

    
    if(dato.substring(0,1) == "M"){          //Este comando hace que la silla envie los datos de GPS y Magnetometro   
      calgps();
      Serial.print(magnetometro());
    }
    
    // ---------------------------------------------------------------------------------------------------

    
    if(dato.substring(0,1) == "B"){         //Este comando hace que la silla Gire hacia la derecha
      float anguloError = dato.substring(1).toFloat();
      float posicion = magnetometro();
      float consigna = posicion + anguloError;
      Wire.beginTransmission(0x10);
      Wire.write("B");
      Wire.endTransmission();
      while(posicion < (consigna - 10)){
        posicion = magnetometro();
        }
      Wire.beginTransmission(0x10);
        Wire.write("S");
      Wire.endTransmission();

      Serial.print("ok");
      
     }

    // ---------------------------------------------------------------------------------------------------

    if(dato.substring(0,1) == "P"){         //Este comando hace que la silla Gire hacia la izquierda
      float anguloError = dato.substring(1).toFloat();
      float posicion = magnetometro();
      float consigna = posicion - anguloError;
      Wire.beginTransmission(0x10);
      Wire.write("P");
      Wire.endTransmission();
      while(posicion > (consigna - 10)){
        posicion = magnetometro();
        }
      Wire.beginTransmission(0x10);
        Wire.write("S");
      Wire.endTransmission();

      Serial.print("ok");
      
     }

    // ---------------------------------------------------------------------------------------------------
      
    if(dato.substring(0,1) == "A"){         //Este comando hace que la silla vaya hacia delante
      Wire.beginTransmission(0x10);
      Wire.write("A");
      Wire.endTransmission();
      Serial.print("ok");
    }
   
    // ---------------------------------------------------------------------------------------------------

    if(dato.substring(0,1) == "S"){         // Este comando hace que la silla se detenga
      Wire.beginTransmission(0x10);
      Wire.write("S");
      Wire.endTransmission();
      Serial.print("ok");
    }

    // ---------------------------------------------------------------------------------------------------

  }
