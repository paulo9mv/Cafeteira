
The MIT License (MIT)

Copyright (c) 2017 PAULO VIANA

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

        
          

#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);					// Syntax is LiquidCrystal lcd(rs, enable, d4, d5, d6, d7)
int ping_pin = A2;    									
int temperature = A3;
int motorPin = 11;

int limite = 15;

int buttonP = 8;
int buttonM = 9;
int buttonG = 10;

void setup() {
  lcd.begin(16, 2);
  analogReference(INTERNAL);   
  Serial.begin(9600);
  
  pinMode(buttonP, INPUT);
  pinMode(buttonM, INPUT);
  pinMode(buttonG, INPUT);
  pinMode(temperature, INPUT);
  pinMode(motorPin, OUTPUT);
  
checar_nivel_agua();
  aquecer();
}
void aquecer(){
 	 float temp = temperatura();
  	
  while(temp <= 448){
    Serial.print(temp);
  	Serial.print("\n");
   		temp = temperatura();
    	lcd.setCursor(0,0);
   		lcd.print("Aquecendo");
  }
  lcd.clear();
}
float temperatura(){
 	int tempReading = analogRead(temperature);  
  return (((tempReading * 0.0048828125) - 0.5)*100.0);
  
}
void perguntar(){
  	lcd.setCursor(0, 0);
  	lcd.print("P M ou G");
	Serial.print("P M ou G\n");
}
int selecionar(){
  int selecionado = 0;
  while(selecionado == 0){
  	int val = digitalRead(buttonP);
    if(val == LOW){
      Serial.print("Apertou P\n");
      
      selecionado = 1;
      return selecionado;
    }
  	val = digitalRead(buttonM);
    if(val == LOW){
      Serial.print("Apertou M\n");
      selecionado = 2;
      return selecionado;
    }
  val = digitalRead(buttonG);
    if(val == LOW){
      	Serial.print("Apertou G\n");
      selecionado = 3;
      return selecionado;
    }
  }
  return selecionado;
}
void sucesso(){
  	lcd.clear();
  	lcd.setCursor(0,0);
  	lcd.print("Pronto!");
  	lcd.setCursor(0,1);
  	lcd.print("Retire o copo");
	Serial.print("Pronto! Retire o copo!\n");
	digitalWrite(motorPin, LOW);
  	delay(1000);
  	lcd.clear();
}
void despejar(int opcao){
  	checar_nivel_agua();
  	lcd.clear();
	switch(opcao){
		case 1:
      		lcd.setCursor(0, 0);
      		lcd.print("Opcao P");
      		lcd.setCursor(0,1);
      		lcd.print("Aguarde...");
			digitalWrite(motorPin, HIGH);
			delay(500);
			sucesso();
			break;
		case 2:
      		lcd.setCursor(0, 0);
      		lcd.print("Opcao M");
      		lcd.setCursor(0,1);
      		lcd.print("Aguarde...");
			digitalWrite(motorPin, HIGH);
			delay(500);
			sucesso();
			break;
		case 3:
      		lcd.setCursor(0, 0);
      		lcd.print("Opcao G");
      		lcd.setCursor(0,1);
      		lcd.print("Aguarde...");
			digitalWrite(motorPin, HIGH);
			delay(500);
			sucesso();
			break;
	}	
}
void checar_nivel_agua(){
	while(PingDistance() > limite){
      	lcd.setCursor(0, 0);
      	lcd.print("Add water");
      	lcd.setCursor(0,1);
      	lcd.print(" ");
		Serial.print("Colocar mais agua!\n");
	}
  	lcd.clear();
}
void loop() { 
  	perguntar();
	despejar(selecionar());
	checar_nivel_agua();
  }
float PingDistance() {
  long duration=0, cm=0;
  int inhoud=0;

  pinMode(ping_pin, OUTPUT);
  digitalWrite(ping_pin, LOW);     
  delayMicroseconds(5);
  digitalWrite(ping_pin, HIGH);
  delayMicroseconds(10);           
  digitalWrite(ping_pin, LOW);

  pinMode(ping_pin, INPUT);
  duration = pulseIn(ping_pin, HIGH);
  
  return msTocm(duration); 
}


float msTocm(long microseconds)  {
 
  return microseconds / 29.0 / 2.0;
}

