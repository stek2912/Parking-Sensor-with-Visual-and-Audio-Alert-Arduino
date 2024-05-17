#include <Wire.h>
#include <LiquidCrystal_I2C.h> // includes the LiquidCrystal Library 

const int switchPin = 2; // Slide Switch

#define trigPin 13
#define echoPin 12
//sonar define

#define GREEN 4
#define RED 6
//LED define

#define buzzerPin 8
//Buzzer define


LiquidCrystal_I2C lcd(0x3f,16,2); 
String message1 = "Projekat:";
String message2 = "Parking senzor";
String message3 = "Rikverc";
String message4 = "za aktivaciju!";

int switchState = 0;


void blink(int pin, int duration) { // Updated blink function
  digitalWrite(pin, HIGH); 
  delay(duration);
  digitalWrite(pin, LOW);
  delay(duration);
}

void buzz(int duration) {
  digitalWrite(buzzerPin, HIGH); // Turn on buzzer
  delay(duration); // Wait for the specified duration
  digitalWrite(buzzerPin, LOW); // Turn off buzzer
  delay(duration);
}

void setup() { 
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(switchPin, INPUT);
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

void loop() {  
  int distance = call_distance();
  Serial.print("Distance (cm): ");
  Serial.println(distance);
  switchState = digitalRead(switchPin);
  
  if (switchState == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(message3);
    lcd.setCursor(0, 1);
    lcd.print(message4);
    delay(3000); 
  } else {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Udaljenost: ");
    lcd.setCursor(0,1);
    lcd.print(distance);
    lcd.print(" cm");

    if (distance <= 3) {
      digitalWrite(RED, HIGH); // Turn on RED LED
      digitalWrite(GREEN, LOW); // Turn off GREEN LED
      digitalWrite(buzzerPin, HIGH); // Turn on Buzzer
    } else if (distance > 3 && distance <= 8) {
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, LOW);
      blink(RED, 40); // Blink the RED LED
      buzz(50); // Buzz the buzzer
    } else if (distance > 8 && distance <= 15) {
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, LOW);
      blink(RED, 100);
      buzz(100);
    } else if (distance > 15 && distance <= 30) {
      digitalWrite(GREEN, HIGH); // Turn on GREEN LED
      digitalWrite(RED, LOW); // Turn off RED LED
      blink(GREEN, 130); // Blink the GREEN LED
      buzz(200);
    } else if (distance > 30 && distance <= 50) {
      digitalWrite(GREEN, HIGH);
      digitalWrite(RED, LOW);
      blink(GREEN, 150);
      buzz(300);
    } else {
      digitalWrite(GREEN, HIGH); // Turn off GREEN LED
      digitalWrite(RED, LOW); // Turn off RED LED
      digitalWrite(buzzerPin, LOW); // Turn off Buzzer
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Vise od 50cm!");
    }
  }
  delay(100);
}
