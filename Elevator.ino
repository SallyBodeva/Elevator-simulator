
#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

byte ARROWUP[8] = {
  B00000,
  B00100,
  B01110,
  B11111,
  B01110,
  B01110,
  B00000,
};

byte ARROWDOWN[8] = {
  B00000,
  B01110,
  B01110,
  B11111,
  B01110,
  B00100,
  B00000,
};

byte OPENL[8] = {
  B00011,
  B00111,
  B01110,
  B11100,
  B01110,
  B00111,
  B00011,
};

byte OPENR[8] = {
  B11000,
  B11100,
  B01110,
  B001111,
  B01110,
  B11100,
  B11000,
};


Servo Servo1;       

int call1 = A0;   
int call2 = A1;    
int call3 = A2;    
int call4 = A3;     
int call5 = A4;   
	 
int doorPin = 12;  	  
int motor1 = 9;   		
int motor2 = 11;    	

int cFloor = 1;    		
int dFloor = 1;    		
int mFloor = 0;    		

int travelTime = 2000; 
int doorTime = 3000;    

const int tempPin = A5; 
const int buzzer = 10;  

void setup() {

  for (int o = 1; o < 8; o++)
  {
    pinMode(o, OUTPUT);
    pinMode(buzzer, OUTPUT);  
    pinMode(tempPin, INPUT);  
  }

  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  

  lcd.begin(16, 2);

  
  lcd.setCursor(0, 0);
   lcd.print("--- Welcome ---");
    lcd.setCursor(0, 1);
     lcd.print("  Select Floor ");


  Servo1.attach(doorPin);   
  Servo1.write(0);       	

}


void loop() {
  
  if (digitalRead(call1) == LOW) {	 
    lcd.clear();
     lcd.setCursor(0, 0);            
      lcd.print("  First Floor ");   
    dFloor = 1;						 
    if (cFloor != 1) {				 
      mFloor = dFloor - cFloor;		 
      move();						 
    }								 
    door();							 
    cFloor = 1;						 
  }
  

  if (digitalRead(call2) == LOW)      
  {	
    lcd.clear();
     lcd.setCursor(0, 0);
      lcd.print("  Second Floor ");
    dFloor = 2;
    if (cFloor != 2) {
      mFloor = dFloor - cFloor;
      move();
    }
    door();
    cFloor = 2;
  }
  

  if (digitalRead(call3) == LOW)      
  {	
    lcd.clear();
     lcd.setCursor(0, 0);
      lcd.print("  Third Floor ");
    dFloor = 3;
    if (cFloor != 3) {
      mFloor = dFloor - cFloor;
      move();
    }
    door();
    cFloor = 3;
  }
  
  
   if (digitalRead(call4) == LOW)    
   {	
    lcd.clear();
     lcd.setCursor(0, 0);
      lcd.print("  Fourth Floor ");
    dFloor = 4;
    if (cFloor != 4) {
      mFloor = dFloor - cFloor;
      move();
    }
    door();
    cFloor = 4;
  }
 
  
  
   if (digitalRead(call5) == LOW)    
   {	
    lcd.clear();
     lcd.setCursor(0, 0);
      lcd.print(" - PENTHOUSE -  ");
    dFloor = 5;
    if (cFloor != 5) {
      mFloor = dFloor - cFloor;
      tempP();
      move();
    }
     door();
    cFloor = 5;
  }

}

void move() 
{
  if (cFloor < dFloor) {		 
    up();					 	 
  }								 
  if (cFloor > dFloor) {		 
    down();					 	 
  }
}

void up() 
{
  analogWrite(motor1, 50);			
  analogWrite(motor2, 0);			
  lcd.setCursor(0, 1);
   lcd.print("   GOING  UP   ");	
    lcd.createChar(0, ARROWUP);     
     lcd.setCursor(15, 0);  
      lcd.write(byte(0));
  delay(travelTime*(abs(mFloor)));	
  analogWrite(motor1, 0);			
}


void down() 
{
  analogWrite(motor1, 0);
  analogWrite(motor2, 50);
  lcd.setCursor(0, 1);
   lcd.print("  GOING  DOWN  ");
    lcd.createChar(0, ARROWDOWN);   
     lcd.setCursor(15, 1);  
      lcd.write(byte(0));
  delay(travelTime*(abs(mFloor)));
  analogWrite(motor2, 0);
}

void door() 
{
  delay(1500);			         
   lcd.clear();
    lcd.setCursor(0,1);
     lcd.print("   DOOR OPENS ");
  lcd.createChar(0, OPENR);      
   lcd.setCursor(10, 0);
    lcd.write(byte(0));
     lcd.createChar(1, OPENL);   
      lcd.setCursor(5, 0);
       lcd.write(byte(1));
  dingO();                   
   delay(500);
  Servo1.write(90);		   
   delay(doorTime);			
  lcd.setCursor(0,1);
   lcd.print("   DOOR CLOSES ");
  lcd.createChar(2, OPENR);
   lcd.setCursor(5, 0);
    lcd.write(byte(2));
     lcd.createChar(3, OPENL);
      lcd.setCursor(10, 0);
       lcd.write(byte(3));
  dingC();                  
   delay(1000);
  Servo1.write(0);		
   delay(1500);
  lcd.setCursor(0, 0);
   lcd.print("--- Welcome ---");
    lcd.setCursor(0,1);
     lcd.print("  Select Floor ");
}

  
  void dingO() 
  {
    tone(buzzer,200);		
     delay(350);			
    noTone(buzzer);
     delay(110);
    tone(buzzer,300);
     delay(350);
    tone(buzzer,400);
     delay(450);
    noTone(buzzer);			
  } 
   

   void dingC()
   {
     tone(buzzer,400);
      delay(450);
     noTone(buzzer);
      delay(110);
     tone(buzzer,200);
      delay(350);
     noTone(buzzer);
   }
   void tempP()
   {  
     float temp = ((analogRead(A5) * (5.0/1023))-0.5)*100;		// les analogverdi, konverter til volt og deretter til temp i celsius
     lcd.setCursor(0,1);
      lcd.write("Temp is");
	   lcd.setCursor(9,1);
	    lcd.print(temp);
	  delay(2500);
   }