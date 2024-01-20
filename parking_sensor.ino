#define trigPin 51 
#define echoPin 53
#define buzzerPin 8
#define redLEDPin 45
#define yellowLEDPin 47
#define greenLEDPin 49

#include <LiquidCrystal.h>
long duration, distance;
int delayTime;
int frequency=1000;
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
byte full[8]={
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte half[8]={
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100,
  B11100
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(yellowLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  lcd.createChar(0, full);
  lcd.createChar(1, half);
}
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //se regelaza senzorul HC sr04 cu ultrasunete sa porneasca masurarea distantei

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * 0.0343) / 2;
  //distanta este durata ultrasunetului sa mearga pana la obiect si inapoi,
  //0.0343 este viteza sunetului si este impartita la doi deoarece dorim distanta pana la obiect nu si inapoi

  updateLED(distance);
  displayOnLCD(distance);

  if(distance < 20) {
    delayTime = map(distance, 0, 20, 200, 20);
    tone(buzzerPin,frequency,delayTime);
    delay(delayTime);
    noTone(buzzerPin);  
  } else {
    noTone(buzzerPin);
  }

  delay(100);
}

void updateLED(long distance){
  if (distance < 10) {
    digitalWrite(redLEDPin, HIGH);
    digitalWrite(yellowLEDPin, LOW);
    digitalWrite(greenLEDPin, LOW);
  }else if (distance < 20) {
    digitalWrite(redLEDPin, LOW);
    digitalWrite(yellowLEDPin, HIGH);
    digitalWrite(greenLEDPin, LOW);
  } else {
    digitalWrite(redLEDPin, LOW);
    digitalWrite(yellowLEDPin, LOW);
    digitalWrite(greenLEDPin, HIGH);
  }
}

void displayOnLCD(long distance){
  lcd.clear();
  lcd.setCursor(8, 0);
  lcd.print("Distance");
  lcd.setCursor(8,1);
  lcd.print(distance);
  lcd.print(" cm");
  
  if (distance>35){
    lcd.setCursor(0, 0);
    lcd.write(byte(0));
    lcd.setCursor(0, 1);
    lcd.write(byte(0));
    lcd.setCursor(1, 0);
    lcd.write(byte(0));
    lcd.setCursor(1, 1);
    lcd.write(byte(0));
    lcd.setCursor(2, 0);
    lcd.write(byte(0));
    lcd.setCursor(2, 1);
    lcd.write(byte(0));
    lcd.setCursor(3, 0);
    lcd.write(byte(0));
    lcd.setCursor(3, 1);
    lcd.write(byte(0));
    delay(20);
  }else{
    if(distance>30){
      lcd.setCursor(0, 0);
      lcd.write(byte(0));
      lcd.setCursor(0, 1);
      lcd.write(byte(0));
      lcd.setCursor(1, 0);
      lcd.write(byte(0));
      lcd.setCursor(1, 1);
      lcd.write(byte(0));
      lcd.setCursor(2, 0);
      lcd.write(byte(0));
      lcd.setCursor(2, 1);
      lcd.write(byte(0));
      lcd.setCursor(3, 0);
      lcd.write(1);
      lcd.setCursor(3, 1);
      lcd.write(1);
      delay(20);
    }else{
      if(distance>25){
        lcd.setCursor(0, 0);
        lcd.write(byte(0));
        lcd.setCursor(0, 1);
        lcd.write(byte(0));
        lcd.setCursor(1, 0);
        lcd.write(byte(0));
        lcd.setCursor(1, 1);
        lcd.write(byte(0));
        lcd.setCursor(2, 0);
        lcd.write(byte(0));
        lcd.setCursor(2, 1);
        lcd.write(byte(0));
        delay(20);
      }else{
        if (distance>20){
          lcd.setCursor(0, 0);
          lcd.write(byte(0));
          lcd.setCursor(0, 1);
          lcd.write(byte(0));
          lcd.setCursor(1, 0);
          lcd.write(byte(0));
          lcd.setCursor(1, 1);
          lcd.write(byte(0));
          lcd.setCursor(2, 0);
          lcd.write(1);
          lcd.setCursor(2, 1);
          lcd.write(1);
          delay(20);
        }else{
          if(distance>15){
            lcd.setCursor(0, 0);
            lcd.write(byte(0));
            lcd.setCursor(0, 1);
            lcd.write(byte(0));
            lcd.setCursor(1, 0);
            lcd.write(byte(0));
            lcd.setCursor(1, 1);
            lcd.write(byte(0));
            delay(20);
          }else{
            if(distance>10){
              lcd.setCursor(0, 0);
              lcd.write(byte(0));
              lcd.setCursor(0, 1);
              lcd.write(byte(0));
              lcd.setCursor(1, 0);
              lcd.write(1);
              lcd.setCursor(1, 1);
              lcd.write(1);
              delay(20);
            }else{
              if(distance>5){
                lcd.setCursor(0, 0);
                lcd.write(byte(0));
                lcd.setCursor(0, 1);
                lcd.write(byte(0));
                delay(20);
              }else{
                if(distance>=3){
                  lcd.setCursor(0, 0);
                  lcd.write(1);
                  lcd.setCursor(0, 1);
                  lcd.write(1);
                  delay(20);
                }
              }
            }
          }
        }
      }
    }
  }
} 