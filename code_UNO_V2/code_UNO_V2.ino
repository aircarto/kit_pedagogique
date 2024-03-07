/*
Code pour Arduino UNO - Kit pédagogique qualité de l'air proposé par AirCarto et AtmoSud
Plus d'infos sur le site d'aircarto: aircarto.fr
Harware:
1.Arduino UNO
2.Capteur de particules fines SDS011 connecté sur la pin 10 (TX)
3.Ecran LCD 1602 avec module I2C connecté sur les pins A4 et A5
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>  //bibliothèque pour l'écran LCD
#include <SDS011.h>             //bibliothèque pour le capteur SDS011

LiquidCrystal_I2C lcd(0x27,16,2);

float p10,p25;
int error;
bool led_on = true;

SDS011 my_sds;


void setup()
{
Serial.begin(9600);
my_sds.begin(10,11);
pinMode(LED_BUILTIN, OUTPUT);
lcd.init();                      
lcd.init();
lcd.backlight();
lcd.setCursor(0,0);
lcd.print("Atelier capteur"); //message d'intro ligne 2

for (int i = 0; i <= 16; i++) {
  lcd.setCursor(i,1);
  lcd.print("-");
  // on fait clignoter la LED
  if(led_on){
    digitalWrite(LED_BUILTIN, LOW);
    led_on = false;
  }else{
    digitalWrite(LED_BUILTIN, HIGH);
    led_on = true;
  }
  delay(200);
}
lcd.clear(); 

delay(1000);
}

void loop()
{
error = my_sds.read(&p25,&p10);
if (! error) {
  //Uncomment next two line for serial debugging output
  //Serial.println("P2.5: "+String(p25));
  //Serial.println("P10:  "+String(p10));
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PM10: "+ String(p10,1));
  lcd.setCursor(11,0);
  lcd.print("ug/m3");

  // On affiche ici les seuils en fonction de l'indice atmo: https://www.atmosud.org/article/comprendre-les-indices-pour-qualifier-lair
  if(p10<=20){ 
      lcd.setCursor(6,1);
      lcd.print("BON"); 
  }
   if(p10>20 && p10<=40){
      lcd.setCursor(5,1);
      lcd.print("MOYEN"); 
  }
   if(p10>40 && p10<=50){
      lcd.setCursor(4,1);
      lcd.print("DEGRADE"); 
  }
   if(p10>50 && p10<=100){
      lcd.setCursor(4,1);
      lcd.print("MAUVAIS"); 
  }
   if(p10>100 && p10<=150){
      lcd.setCursor(4,1);
      lcd.print("TRES MAUVAIS"); 
  }
  if(p10>150 ){
      lcd.setCursor(4,1);
      lcd.print("EXTRM. MAUVAIS"); 
  }
  
if(led_on){
    digitalWrite(LED_BUILTIN, LOW);
    led_on = false;
  }else{
    digitalWrite(LED_BUILTIN, HIGH);
    led_on = true;
  }
  }
delay(200);
}
