
# pin connections:


Buzzer_1 → pin 2 
green_Led_1→ pin 31 
red_Led_1 → pin 30 
buzzer2 →  pin 42 
green_Led_2 → pin 44 
red_Led_2 → pin 39
lcd→pins (22,23,24,25,26,27) 
lcd2→pins (32,33,34,35,36,37)rf1 →pins (5,28,51,50,53) 
rf2→pins (6,38,51,50,53) 
servo_1 → pin (8)
servo_2 →  pin(11)
seven_segment →pins(16,17,18,19,20,21) 


# System program:
#include <Servo.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <RFID.h>
#define buzzer1 2
#define green_Led_1 31
#define red_Led_1 30 
#define buzzer2 42
#define green_Led_2 44
#define red_Led_2 39

LiquidCrystal lcd(22,23,24,25,26,27); 
LiquidCrystal lcd2(32,33,34,35,36,37); 
RFID rf1(28,5);
RFID rf2(38,6);

Servo servo_1; 
Servo servo_2;

int sernum0[5] = {128,142,175,34,131};
int sernum1[5] = {96,20,112,26,30};
int sernum2[5] = {147,221,110,11,43};
int sernum3[5] = {179,65,106,4,156};
int sernum4_master[5] = {97,123,204,39,241};
int sernum5_master[5] = {128,37,197,34,66};

int serNum0_1=0;
int serNum1_1=0;
int serNum2_1=0;
int serNum3_1=0;
int serNum4_1=0;
int serNum0_2=0;
int serNum1_2=0;

int serNum2_2=0;
int serNum3_2=0;
int serNum4_2=0;
int count=0;

byte arrow_up[8] = {
B00000,
B11110,
B11000,
B10100,
B10010,
B00001,
B00000,
B00000
};

byte arrow_down[8] = {
B00000, 
B00000, 
B10000,30
B01001, 
B00101, 
B00011, 
B01111, 
B00000 
};

//seven segment pins 
const int A=20;
const int B=19;
const int C=18;
const int D=17;
const int EN2 = 16;
const int EN1 = 21;

void setup()
{   pinMode(53 , OUTPUT); 
Serial.begin(9600);
SPI.begin(); 
rf1.init();31
rf2.init();
lcd.begin(16 , 2);   
lcd2.begin(16 , 2);      
lcd.createChar(5,arrow_up);
lcd2.createChar(6,arrow_down);       
lcd.setCursor(4, 0);
lcd2.setCursor(6, 0);            
lcd.print("Entrance");
lcd2.print("Exit");   
lcd.setCursor(3, 1);
lcd2.setCursor(3, 1); 
for(int i =0 ; i<10 ; i++) { 
lcd.write(5); }
for(int i =0 ; i<10 ; i++) {
lcd2.write(6); }
pinMode(buzzer1, OUTPUT);
pinMode(green_Led_1, OUTPUT);
pinMode(red_Led_1, OUTPUT);32
pinMode(buzzer2, OUTPUT); 
pinMode(green_Led_2, OUTPUT);  
pinMode(red_Led_2, OUTPUT);   
servo_1.attach(8);
servo_2.attach(11); 
servo_1.write(90);
servo_2.write(90);
//seven segment
pinMode(A, OUTPUT); //LSB
pinMode(B, OUTPUT);
pinMode(C, OUTPUT);
pinMode(D, OUTPUT); //MSB  
}

void to_BCD(int count)
{  if (count == 0) //write 0000
{   digitalWrite(A, LOW); 
digitalWrite(B, LOW);
digitalWrite(C, LOW);33
digitalWrite(D, LOW); 
}

if (count == 1) //write 0001
{  digitalWrite(A, HIGH);
digitalWrite(B, LOW);
digitalWrite(C, LOW);
digitalWrite(D, LOW);  }
if (count == 2) //write 0010
{digitalWrite(A, LOW);
digitalWrite(B, HIGH);
digitalWrite(C, LOW);
digitalWrite(D, LOW);
}

if (count == 3) //write 0011
{  digitalWrite(A, HIGH);
digitalWrite(B, HIGH);
digitalWrite(C, LOW);
digitalWrite(D, LOW);34
}

if (count == 4) //write 0100
{ digitalWrite(A, LOW);
digitalWrite(B, LOW);
digitalWrite(C, HIGH);
digitalWrite(D, LOW); }

if (count == 5) //write 0101 
{  digitalWrite(A, HIGH);
digitalWrite(B, LOW);
digitalWrite(C, HIGH);
digitalWrite(D, LOW);}
if (count == 6) //write 0110
{  digitalWrite(A, LOW);
digitalWrite(B, HIGH);
digitalWrite(C, HIGH);
digitalWrite(D, LOW);   }

if (count == 7) //write 0111
{ digitalWrite(A, HIGH);35
digitalWrite(B, HIGH);
digitalWrite(C, HIGH);
digitalWrite(D, LOW); }

if (count == 8) //write 1000
{ digitalWrite(A, LOW);
digitalWrite(B, LOW);
digitalWrite(C, LOW);
digitalWrite(D, HIGH) }

if (count == 9) //write 1001
{ digitalWrite(A, HIGH);
digitalWrite(B, LOW);
digitalWrite(C, LOW);
digitalWrite(D, HIGH); }
}


void loop()
{ 
if(rf1.isCard()){
if(rf1.readCardSerial()){ 
if(serNum0_1!=rf1.serNum[0] &&36
serNum1_1!=rf1.serNum[1] &&
serNum2_1!=rf1.serNum[2] &&
serNum3_1!=rf1.serNum[3] &&
serNum4_1!=rf1.serNum[4] )
{   Serial.println("Card ID: ");
Serial.print(rf1.serNum[0]);
Serial.print(",");
Serial.print(rf1.serNum[1]);
Serial.print(",");
Serial.print(rf1.serNum[2]);
Serial.print(",");
Serial.print(rf1.serNum[3]);
Serial.print(",");
Serial.print(rf1.serNum[4]);
Serial.println(" ");
serNum0_1=rf1.serNum[0];
serNum1_1=rf1.serNum[1];
serNum2_1=rf1.serNum[2];37
serNum3_1=rf1.serNum[3]; 
serNum4_1=rf1.serNum[4]
if((sernum0[0] == rf1.serNum[0]&&sernum0[1]==rf1.serNum[1]&&sernum0[2]== rf1.serNum[2]&&sernum0[3]== rf1.serNum[3]&&sernum0[4]== rf1.serNum[4])||
(sernum1[0] == rf1.serNum[0]&&sernum1[1]== rf1.serNum[1]&&sernum1[2]== rf1.serNum[2]&&sernum1[3]== rf1.serNum[3]&&sernum1[4]== rf1.serNum[4])||
(sernum2[0] == rf1.serNum[0]&&sernum2[1]== rf1.serNum[1]&&sernum2[2]== rf1.serNum[2]&&sernum2[3]== rf1.serNum[3]&&sernum2[4]== rf1.serNum[4])||
(sernum3[0] == rf1.serNum[0]&&sernum3[1]== rf1.serNum[1]&&sernum3[2]== rf1.serNum[2]&&sernum3[3]== rf1.serNum[3]&&sernum3[4]== rf1.serNum[4])||
(sernum4_master[0] == rf1.serNum[0]&&sernum4_master[1]== rf1.serNum[1]&&sernum4_master[2]== rf1.serNum[2]&&sernum4_master[3]== rf1.serNum[3]&&sernum4_master[4]== rf1.serNum[4])||
(sernum5_master[0] == rf1.serNum[0]&&sernum5_master[1]== rf1.serNum[1]&&sernum5_master[2]== rf1.serNum[2]&&sernum5_master[3]== rf1.serNum[3]&&sernum5_master[4]== rf1.serNum[4])){

tone(buzzer1,1000); // Send 1KHz sound signal... 
digitalWrite(green_Led_1 , HIGH);38
servo_1.write(0);
count++;
to_BCD(count);
digitalWrite(EN1 , HIGH); 
delay(2000);        // ...for 1 sec 
noTone(buzzer1);     // Stop sound... 
digitalWrite(green_Led_1 , LOW); 
servo_1.write(90); 
digitalWrite(EN1 , LOW);        
} 
else{
digitalWrite(red_Led_1,HIGH); 
delay(2000);      
digitalWrite(red_Led_1,LOW); 
}         }           }}
rf1.halt();

if(rf2.isCard()){
if(rf2.readCardSerial()){39
if(serNum0_2!=rf2.serNum[0] &&
serNum1_2!=rf2.serNum[1] &&
serNum2_2!=rf2.serNum[2] &&
serNum3_2!=rf2.serNum[3] &&
serNum4_2!=rf2.serNum[4] )
{     Serial.println("Card ID: ");
Serial.print(rf2.serNum[0]);
Serial.print(",");
Serial.print(rf2.serNum[1]);
Serial.print(",");
Serial.print(rf2.serNum[2]);
Serial.print(",");
Serial.print(rf2.serNum[3]);
Serial.print(",");
Serial.print(rf2.serNum[4]);
Serial.println(" ");    
serNum0_2=rf2.serNum[0]; 
serNum1_2=rf2.serNum[1];40
serNum2_2=rf2.serNum[2];
serNum3_2=rf2.serNum[3];
serNum4_2=rf1.serNum[4];
if((sernum0[0] == rf2.serNum[0]&&sernum0[1]== rf2.serNum[1]&&sernum0[2]== rf2.serNum[2]&&sernum0[3]== rf2.serNum[3]&&sernum0[4]== rf2.serNum[4])||
(sernum1[0] == rf2.serNum[0]&&sernum1[1]== rf2.serNum[1]&&sernum1[2]== rf2.serNum[2]&&sernum1[3]== rf2.serNum[3]&&sernum1[4]== rf2.serNum[4])||
(sernum2[0] == rf2.serNum[0]&&sernum2[1]== rf2.serNum[1]&&sernum2[2]== rf2.serNum[2]&&sernum2[3]== rf2.serNum[3]&&sernum2[4]== rf2.serNum[4])||
(sernum3[0] == rf2.serNum[0]&&sernum3[1]== rf2.serNum[1]&&sernum3[2]== rf2.serNum[2]&&sernum3[3]== rf2.serNum[3]&&sernum3[4]== rf2.serNum[4])||
(sernum4_master[0] == rf2.serNum[0]&&sernum4_master[1]== rf2.serNum[1]&&sernum4_master[2]== rf2.serNum[2]&&sernum4_master[3]== rf2.serNum[3]&&sernum4_master[4]== rf2.serNum[4])||
(sernum5_master[0] == rf2.serNum[0]&&sernum5_master[1]== rf2.serNum[1]&&sernum5_master[2]== rf2.serNum[2]&&sernum5_master[3]== rf2.serNum[3]&&sernum5_master[4]== rf2.serNum[4])){

tone(buzzer2, 1000); // Send 1KHz sound signal...41
digitalWrite(green_Led_2 , HIGH); 
servo_2.write(0);
count--;
to_BCD(count);
digitalWrite(EN1 , HIGH);          
delay(2000);        // ...for 1 sec          
noTone(buzzer2);     // Stop sound... 
digitalWrite(green_Led_2 , LOW); 
servo_2.write(90); 
digitalWrite(EN1 , HIGH);      }
else{
digitalWrite(red_Led_2,HIGH); 
delay(2000);      
digitalWrite(red_Led_2,LOW); 
}  
 } 
  } 
   }  
rf2.halt();
}
