git s#include <Wire.h>
#include <LiquidCrystal_I2C.h> // includes the LiquidCrystal Library 

const int switchPin = 2; // Slide Switcc

#define trigPin 13
#define echoPin 12
//sonar define

#define GREEN 4
#define RED 6
//LED define

#define buzzerPin 8
//Buzzer define


LiquidCrystal_I2C lcd(0x3f,16,2); 
String message1 = "Projekat";
String message2 = "Parking senzor";
String message3 = "Ubacite u rikverc";
String message4 = "za aktivaciju!";
String message5 = "Parking senzor";
String message6 = "Aktiviran!";
int switchState = 0;

void setup() { 
  
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(switchState, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.display();
  for(int i = 0; i < message1.length(); i++){
    lcd.print(message1.charAt(i));
    delay(200); 
  }

lcd.blink();
  lcd.setCursor(0,1);
  
  for(int i = 0; i < message2.length(); i++){
    lcd.print(message2.charAt(i));
    delay(200);
  }


lcd.noBlink();
delay(3000);
lcd.clear();
}

int call_distance() {
 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = (duration / 2) / 29.1; // Calculate distance in centimeters
  return distance;

}

void blink(int pin) {    // Blink speed
  digitalWrite(pin, HIGH); 
  delay(pin);
  digitalWrite(pin, LOW);
  delay(pin);
}

void buzz(int duration) {
  digitalWrite(buzzerPin, HIGH); // Turn on buzzer
  delay(duration); // Wait for the specified duration
  digitalWrite(buzzerPin, LOW); // Turn off buzzer
  delay(duration);
}

void loop() {  
  switchState = digitalRead(switchPin);
  
  if (switchState == LOW) {
    lcd.setCursor(0, 0);
    lcd.print(message3);
    lcd.setCursor(0, 1);
    lcd.print(message4);
    
  }else{
    
    int distance = call_distance();
    Serial.print("Distance (cm): ");
    Serial.println(distance); // Print distance for debugging
    
    lcd.setCursor(0, 0);
    lcd.print(message5);
    lcd.setCursor(0, 1);
    lcd.print(message6);
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Udaljenost: ");
    lcd.setCursor(0,1);
    lcd.print(distance);

    if (distance <= 3) {
    digitalWrite(GREEN, LOW);
    analogWrite(RED, HIGH);
    digitalWrite(buzzerPin, HIGH);
    
    }else if (distance > 3 && distance <=8) {
    digitalWrite(GREEN, LOW);
    analogWrite(RED, HIGH); 
    blink(40);
    buzz(50);
    
    } else if (distance > 8 && distance <= 15) {
    digitalWrite(GREEN, LOW);
    analogWrite(RED, HIGH); // Fully turn on the green LED
    blink(100);
    buzz(100);
    
       
    } else if (distance >15 && distance <= 30){
    digitalWrite(RED, LOW);
    analogWrite(GREEN, HIGH); // Fully turn on the yellow LED
    blink(130);
    buzz(200);
   
    
    } else if (distance >30 && distance <= 50){
    digitalWrite(RED, LOW);
    analogWrite(GREEN, 255); // Fully turn on the yellow LED
    blink(200);
    buzz(300);
   
    
    }else {
    digitalWrite(RED, LOW);
    analogWrite(GREEN, LOW); // Fully turn on the yellow LED
    digitalWrite(buzzerPin, LOW);
     
    }

  }
  delay(100);
  
}