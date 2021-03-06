#include <OneWire.h>            // OneWire-Bibliothek einbinden
#include <DallasTemperature.h>  // DS18B20-Bibliothek einbinden
#define DS18B20_PIN 8   // Pin für DS18B20 definieren Arduino D2
OneWire oneWire(DS18B20_PIN);          // OneWire Referenz setzen
DallasTemperature sensors(&oneWire);   // DS18B20 initialisieren
int modul_id;
float* s_temp = 0;
void setup() {
pinMode(3, OUTPUT); 
  // Serielle Ausgabe starten 
  Serial.begin(9600);
  pinMode(12, INPUT);           // set pin to input
digitalWrite(12, HIGH);       // turn on pullup resistors
pinMode(11, INPUT);           // set pin to input
digitalWrite(11, HIGH);       // turn on pullup resistors
pinMode(10, INPUT);           // set pin to input
digitalWrite(10, HIGH);       // turn on pullup resistors
pinMode(9, INPUT);           // set pin to input
digitalWrite(9, HIGH);       // turn on pullup resistors

 modul_id = -1;
if(digitalRead(9) == 1){modul_id +=1;}
if(digitalRead(10) == 1){modul_id +=2;}
if(digitalRead(11) == 1){modul_id +=4;}
if(digitalRead(12) == 1){modul_id +=8;}
digitalWrite(11, HIGH); 

digitalWrite(3, HIGH); 
Serial.println("register_eowt_" + String(modul_id));
Serial.flush();
digitalWrite(3, LOW); 
delay(20);


  sensors.begin();  // DS18B20 starten


  s_temp = new float[sensors.getDeviceCount()];
   sensors.requestTemperatures();

    for(byte i=0;i<sensors.getDeviceCount();i++){ // Temperatur ausgeben
       show_temperature(i,sensors.getTempCByIndex(i)); 

  }
  
 }

float stmp = 0.0f;
void loop(){
if(modul_id > 0){
  
  sensors.requestTemperatures(); // Temperatursensor(en) auslesen
  for(byte i=0;i<sensors.getDeviceCount();i++){ // Temperatur ausgeben
    stmp =  sensors.getTempCByIndex(i);
    if(stmp > (s_temp[i]+0.1) || stmp < (s_temp[i]-0.1)){
    show_temperature(i,sensors.getTempCByIndex(i)); 
      }
     
  }
  
  delay(1000);  // 5s Pause bis zur nächsten Messung
}
}

// Temperatur ausgeben
void show_temperature(byte num,float temp){
  s_temp[num] = temp;
  digitalWrite(3, HIGH);
  Serial.println(String(modul_id) + "_eowt_" + String(num) + "_" + String(temp));
Serial.flush();
digitalWrite(3, LOW); 

}
