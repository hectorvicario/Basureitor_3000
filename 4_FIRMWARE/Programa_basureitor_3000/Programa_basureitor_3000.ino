#include <Servo.h>
#include <NewPing.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;


int segundo,minuto,hora,dia,mes;
long anio; //variable año
DateTime HoraFecha;
LiquidCrystal lcd(7, 8, 9, 10, 11 , 12);
NewPing pollo(3, 4); // Triger=12, Echo=13.
Servo servo;
int distancia;
int lectura;
float volt,temp;
volatile int a=0;
long tinicio=millis(); 
void setup() {
  pinMode(5,OUTPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  servo.attach(6);
  servo.write(13);
  rtc.begin(); //Inicializamos el RTC
  attachInterrupt(0,pulsador,RISING);
} 
void loop() {
  distancia=pollo.ping_cm();
  if((distancia<15)&&(distancia!=0)){
    servo.write(80);
    digitalWrite(5,1);
    delay(2000);
    digitalWrite(5,0);
    servo.write(13);
    delay(500);
  }
  switch(a){
    case 0:
      HoraFecha = rtc.now(); //obtenemos la hora y fecha actual
      dia=HoraFecha.day();
      mes=HoraFecha.month();
      anio=HoraFecha.year();
      lcd.setCursor(0,0);
      lcd.print("   FECHA ACTUAL   ");
      lcd.setCursor(3,1);
      lcd.print(dia);
      lcd.print("/");
      lcd.print(mes);
      lcd.print("/");
      lcd.print(anio);
      lcd.print("          ");
      delay(100);
      break;
    case 1:
      HoraFecha = rtc.now(); //obtenemos la hora y fecha actual
      segundo=HoraFecha.second();
      minuto=HoraFecha.minute();
      hora=HoraFecha.hour();
      lcd.setCursor(0,0);
      lcd.print("   HORA ACTUAL   ");
      lcd.setCursor(3,1);
      lcd.print(hora);
      lcd.print(":");
      lcd.print(minuto);
      lcd.print(":");
      lcd.print(segundo);
      lcd.print("          ");
      delay(100);
      break;
    case 2:
      lectura=analogRead(A1);
      volt=(lectura/1024.0)*5.0;
      temp=volt*100*0.96;
      lcd.setCursor(0,0);
      lcd.print("  TEMPERATURA    ");
      lcd.setCursor(3,1);
      lcd.print(int(temp));
      lcd.setCursor(5,1);
      lcd.print("C        ");
      delay(150);
      break;
  }
}
void pulsador(){
  if(millis()>tinicio+250){
    a++;
    tinicio=millis();
  }
  if(a==3)a=0;  
} 


