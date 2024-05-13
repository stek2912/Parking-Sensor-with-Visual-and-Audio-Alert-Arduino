#define trigPin 13
#define echoPin 12
//sonar define

#define GREEN 4
#define RED 6
//LED define

#define buzzerPin 8
//Buzzer define


void setup() {
  
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
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
  int distance = call_distance();
  Serial.print("Distance (cm): ");
  Serial.println(distance); // Print distance for debugging
  

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

  delay(100);
}

