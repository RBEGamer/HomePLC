
#include <elapsedMillis.h>
 #include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
elapsedMillis timeElapsed; //declare global if you don't want it reset every time loop runs
// delay in milliseconds between blinks of the LED
unsigned int interval = 10000;
 bool bgs;
String readString;
int modul_id = 0;
String msg1 = "";
String msg2 = "";
// the setup function runs once when you press reset or power the board
void setup() {
  
pinMode(3, OUTPUT); 
digitalWrite(3, HIGH); 

pinMode(4, OUTPUT); 
digitalWrite(4, HIGH); 

pinMode(5, OUTPUT); 
digitalWrite(5, HIGH); 

Serial.begin(9600);
  Wire.begin ();
  // initialize digital pin 13 as an output.
 lcd.begin(16,2);   

// NOTE: Cursor Position: CHAR, LINE) start at 0  
  lcd.setCursor(0,0); //Start at character 4 on line 0
  lcd.print("MSI : BNID");
  lcd.setCursor(0,1); //Start at character 4 on line 0
  lcd.print("MID : 0");
  delay(1000);

 
bgs = false;



Serial.println( "register_bnid_0");
  lcd.clear();
        bgs = false;
       lcd.noBacklight();

       digitalWrite(3, LOW); 
       digitalWrite(4, LOW); 
       digitalWrite(5, LOW); 
}

// the loop function runs over and over again forever
void loop() {
if(modul_id >= 0){
  }
 if (timeElapsed > interval && bgs == true) 
  {       
   
    timeElapsed = 0;       // reset the counter to 0 so the counting starts over...
    bgs = false;
       lcd.noBacklight();
        digitalWrite(5, LOW); 
  }



   while (Serial.available()) {
    delay(3);  //delay to allow buffer to fill 
    if (Serial.available() >0) {
      digitalWrite(4, HIGH);
      char c = Serial.read();  //gets one byte from serial buffer
      readString += c; //makes the string readString
    } 
  }
  digitalWrite(4, LOW);

  if (readString.length() >0) {
      //Serial.println(readString); //see what was received

if(getValue(readString, '_', 0).toInt() == modul_id){
  if(getValue(readString, '_', 1) == "bnid"){
    digitalWrite(3, HIGH);
  
       int _cursor = getValue(readString, '_', 2).toInt();
       if(_cursor < 2){

      if(_cursor == 0){
  msg1 = getValue(readString, '_', 3);
  if(msg1.length() > 0){
  msg1 = msg1.substring(0, msg1.length()-1);
  }
  }else if(_cursor == 1){
    msg2 = getValue(readString, '_', 3);
      if(msg2.length() > 0){
  msg2 = msg2.substring(0, msg2.length()-1);
  }
    }
      
        lcd.clear();
        lcd.setCursor(0,0); //Start at character 4 on line 0 //CHAR LINE
        lcd.print(msg1);
        lcd.setCursor(0,1); //Start at character 4 on line 0 //CHAR LINE
        lcd.print(msg2);
        
     
        digitalWrite(5, HIGH); 
        lcd.backlight();
        bgs = true;
         timeElapsed = 0; 

         
        }
       }else{
          lcd.clear();
        }
        digitalWrite(3, LOW);
    
  }
    readString="";
  } 
 
}





String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {
    0, -1  };
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
