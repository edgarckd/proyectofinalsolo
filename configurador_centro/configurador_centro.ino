
float valorMayorX = -2, valorMenorX =4 , valorMayorY = -2, valorMenorY = 4; 

void setup() {
  Serial.begin(115200);
  pinMode(A1, INPUT);
  pinMode(A0, INPUT);    
}

void loop() {
  float sensorValuex = analogRead(A1);
  float sensorValuey = analogRead(A0);
  sensorValuex = (sensorValuex)*(5)/1024 -2.5;
  sensorValuey = (sensorValuey)*(5)/1024 -2.5;
  if(sensorValuex > valorMayorX){
    valorMayorX = sensorValuex;
    Serial.print("nuevo valor mayor de x: ");
    Serial.println(valorMayorX);
    }
  if(sensorValuex < valorMenorX){
    valorMenorX = sensorValuex;
    Serial.print("nuevo valor menor de x: ");
    Serial.println(valorMenorX);
    }

  if(sensorValuey > valorMayorY){
    valorMayorY = sensorValuey;
    Serial.print("nuevo valor mayor de y: ");
    Serial.println(valorMayorY);
    }
  if(sensorValuey < valorMenorY){
    valorMenorY = sensorValuey;
    Serial.print("nuevo valor menor de y: ");
    Serial.println(valorMenorY);
    }
}
