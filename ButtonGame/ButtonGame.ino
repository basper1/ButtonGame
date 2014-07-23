#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
  String blah = "3..2..1..GO!";
  const int button1Pin = 8;
  const int button2Pin = 9;
  boolean lastButton1 = HIGH;
  boolean lastButton2 = HIGH;
  int location = 6, lastLocation;
  boolean button1State;
  boolean button2State;
  long startTime;
  int place;
  boolean running, starting = true;
  int interval = 1000, score = 0, highScore[] = {0,0,0,0,0}, change = 10, difficulty = 0;
  
  
void setup(){
  pinMode(button1Pin,INPUT);
  pinMode(button2Pin,INPUT);
  lcd.begin(16,2);
  lcd.clear();
  Serial.begin(9600);
  location = 5;
  randomSeed(analogRead(2));
}
 
void loop(){
  if(starting == true){
   startUp();
   
  }
  readButton();
  lcd.setCursor(location-17,1);
  lcd.print("                [_]                        ");
  if(running == false){
   place = randomNum();
   running = true;
   startTime = millis();
  }
  lcd.setCursor(place,0);
  if(millis() - startTime < interval){
    lcd.print("3");
  }else if((millis() - startTime) < (2 * interval)){
    lcd.print("2");
  }else if((millis() - startTime) < (3 * interval)){
    lcd.print("1");
  }else if((millis() - startTime) < (4 * interval)){
    if(location == place){
      score++;
      running = false;
      lcd.print(" ");
      interval -= change;
      /*Serial.print(startTime);
  Serial.print(" ");
  Serial.print(score);
  Serial.print(" ");
  Serial.println(interval);*/
    }else{
     lose(); 
    }
  }
  

}
//print the startup lines
void printSlow(String message,int time,int x,int y){
 lcd.setCursor(x,y);
 int length = message.length();
 for(int i = 0;i < length;i++){
  lcd.print(message[i]);
  x++;
  if(x == 16){
   y++; 
  }
  lcd.setCursor(x,y);
  delay(time);
 }
}

void readButton(){
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  if(button1State != lastButton1){
    lastButton1 = button1State;
    if(button1State == 0 && difficulty != 4){
     
      if(location >= 1){
      location--;
      }else if(difficulty != 3){
        location = 15;
      }
    }
  }
  if(button2State != lastButton2){
    lastButton2 = button2State;
    if(button2State == 0){
      if(location <= 14){
      location = location + 1;
      }else if(difficulty != 3){
       location = 0; 
      }
    }
  }
}

void lose(){
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("You Lose");
 delay(1000);
 lcd.setCursor(0,0);
 lcd.print("Score: ");
 lcd.setCursor(7,0);
 lcd.print(score);
 if(score > highScore[difficulty]){
  highScore[difficulty] = score; 
 }
 lcd.setCursor(0,1);
 lcd.print("High Score: ");
 lcd.setCursor(11,1);
 lcd.print(highScore[difficulty]);
 running = false;
 starting = true;
 delay(1000);
 while(1 > 0){
   if(digitalRead(button1Pin) == 0||digitalRead(button2Pin) == 0){
     break;
   }
 }
 lcd.clear();
}

int randomNum(){
  int n = random(16);
  if(n == lastLocation){
   return randomNum(); 
  }else{
   lastLocation = n;
   return n; 
  }
  
}

void startUp(){
   starting = false;
   score = 0;
   lcd.clear();
   lcd.print("Pick difficuly");
   delay(1000);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("<1><2><3><4><5> ");
   long difficultyStart = millis();
   location = 0;
   difficulty = 0;
   while(millis() <= difficultyStart + 5000){
     readButton();
     lcd.setCursor(location-17,1);
     lcd.print("                 ^                        ");
     Serial.print(difficultyStart);
     Serial.print(" ");
     Serial.println(millis());
   }
   lcd.clear();
   lcd.setCursor(0,0);
   if(location >= 0 && location < 3){
    change = 5;
    difficulty = 0;
    lcd.print("Easy");
    interval = 1000;
   }else if(location >= 3 && location < 6){
    change = 10;
    difficulty = 1;
    lcd.print("Medium");
    interval = 900;
   }else if(location >= 6 && location < 9){
     lcd.print("Hard");
     difficulty = 2;
    change = 15;
    interval = 800;
   }else if(location >= 9 && location < 12){
    change = 25;
    difficulty = 3;
    lcd.print("Expert");
    interval = 800;
   }else if(location >= 12 && location < 16){
    change = 30; 
    difficulty = 4;
    lcd.print("EXTREME!!");
    interval = 800;
   }
   delay(500);
   lcd.clear();
   if(difficulty >= 3){
   printSlow(blah,50,0,0);
   }else{
    printSlow(blah,200,0,0); 
   }
   delay(200);
   lcd.clear();
   location = 7;
}
