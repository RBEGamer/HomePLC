
int modul_id;
int A0_ls = 0;
int A1_ls = 0;
int A2_ls = 0;
int A3_ls = 0;
int A4_ls = 0;
int A5_ls = 0;
int A6_ls = 0;
int A7_ls = 0;
// the setup function runs once when you press reset or power the board
void setup() {
Serial.begin(9600);

pinMode(A0, INPUT);           // set pin to input
digitalWrite(A0, HIGH);       // turn on pullup resistors
pinMode(A1, INPUT);           // set pin to input
digitalWrite(A1, HIGH);       // turn on pullup resistors
pinMode(A2, INPUT);           // set pin to input
digitalWrite(A2, HIGH);       // turn on pullup resistors
pinMode(A3, INPUT);           // set pin to input
digitalWrite(A3, HIGH);       // turn on pullup resistors

pinMode(A4, INPUT);           // set pin to input
digitalWrite(A4, HIGH);       // turn on pullup resistors
pinMode(A5, INPUT);           // set pin to input
digitalWrite(A5, HIGH);       // turn on pullup resistors
pinMode(A6, INPUT);           // set pin to input
digitalWrite(A6, HIGH);       // turn on pullup resistors
pinMode(A7, INPUT);           // set pin to input
digitalWrite(A7, HIGH);       // turn on pullup resistors

pinMode(12, INPUT);           // set pin to input
digitalWrite(12, HIGH);       // turn on pullup resistors
pinMode(11, INPUT);           // set pin to input
digitalWrite(11, HIGH);       // turn on pullup resistors
pinMode(10, INPUT);           // set pin to input
digitalWrite(10, HIGH);       // turn on pullup resistors
pinMode(9, INPUT);           // set pin to input
digitalWrite(9, HIGH);       // turn on pullup resistors

pinMode(7, OUTPUT); 
digitalWrite(7, LOW); 
  modul_id = -1;
if(digitalRead(9) == 1){modul_id +=1;}
if(digitalRead(10) == 1){modul_id +=2;}
if(digitalRead(11) == 1){modul_id +=4;}
if(digitalRead(12) == 1){modul_id +=8;}
if(modul_id > 0){
delay(modul_id*10);
  }

Serial.println("register_eqri_"+ String(modul_id));


A0_ls = digitalRead(A0);
A1_ls = digitalRead(A1);
A2_ls = digitalRead(A2);
A3_ls = digitalRead(A3);
A4_ls = digitalRead(A4);
A5_ls = digitalRead(A5);
A6_ls = digitalRead(A6);
A7_ls = digitalRead(A7);
digitalWrite(7, HIGH);
}

// the loop function runs over and over again forever
void loop() {
if(modul_id > 0){
  
delay(100);



if(digitalRead(A0) !=  A0_ls){digitalWrite(7, LOW); A0_ls = digitalRead(A0);Serial.println(String(modul_id) + "_eqri_0_" + String(A0_ls));delay(10);digitalWrite(7, HIGH);}
else if(digitalRead(A1) !=  A1_ls){digitalWrite(7, LOW); A1_ls = digitalRead(A1);Serial.println(String(modul_id) + "_eqri_1_" + String(A1_ls));delay(10);digitalWrite(7, HIGH);}
else if(digitalRead(A2) !=  A2_ls){digitalWrite(7, LOW); A2_ls = digitalRead(A2);Serial.println(String(modul_id) + "_eqri_2_" + String(A2_ls));delay(10);digitalWrite(7, HIGH);}
else if(digitalRead(A3) !=  A3_ls){digitalWrite(7, LOW); A3_ls = digitalRead(A3);Serial.println(String(modul_id) + "_eqri_3_" + String(A3_ls));delay(10);digitalWrite(7, HIGH);}
else if(digitalRead(A4) !=  A4_ls){digitalWrite(7, LOW); A4_ls = digitalRead(A4);Serial.println(String(modul_id) + "_eqri_4_" + String(A4_ls));delay(10);digitalWrite(7, HIGH);}
else if(digitalRead(A5) !=  A5_ls){digitalWrite(7, LOW); A5_ls = digitalRead(A5);Serial.println(String(modul_id) + "_eqri_5_" + String(A5_ls));delay(10);digitalWrite(7, HIGH);}
else if(digitalRead(A6) !=  A6_ls){digitalWrite(7, LOW); A6_ls = digitalRead(A6);Serial.println(String(modul_id) + "_eqri_6_" + String(A6_ls));delay(10);digitalWrite(7, HIGH);}
else if(digitalRead(A7) !=  A7_ls){digitalWrite(7, LOW); A7_ls = digitalRead(A7);Serial.println(String(modul_id) + "_eqri_7_" + String(A7_ls));delay(10);digitalWrite(7, HIGH);}






   
}
}



