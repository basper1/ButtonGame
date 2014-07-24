#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
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
  int interval = 1000, score = 0, highScore[] = {0,0,0,0,0,0}, change = 10, difficulty = 0, unlock = 0;
  
  
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
 if(unlock == 0&& highScore[2] >= 25){
   unlock = 1;
 }else if(unlock == 1 && highScore[3] >= 20){
   unlock = 2;
 }else if(unlock == 2 && highScore[4] >= 10){
   unlock = 3;
 }
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
   if(unlock==0){
    lcd.print("<-1-><-2-><-3-> ");
   }else if(unlock == 1){
    lcd.print("< 1>< 2>< 3>< 4>");  
   }else if(unlock >= 2){
    lcd.print("<1><2><3><4><5> ");
   }
   
   long difficultyStart = millis();
   location = 0;
   difficulty = 0;
   while(millis() <= difficultyStart + 5000){
     readButton();
     lcd.setCursor(location-17,1);
     lcd.print("                 ^                        ");
   }
   Serial.println(location);
   lcd.clear();
   difficultySel();
   delay(500);
   lcd.clear();
   lcd.setCursor(0,0);
   
   delay(500);
   lcd.clear();
   if(difficulty >=5){
   lcd.println("GO");
   }else if(difficulty >= 3){
   printSlow("3..2..1..GO!",75,0,0);
   }else{
    printSlow("3..2..1..GO!",200,0,0); 
   }
   delay(200);
   lcd.clear();
   location = 7;
}

void difficultySel(){
  if(unlock == 0){
    if(location >= 0 && location < 5){
      difficultyChoice(0);
    }else if(location >= 5 && location < 10){
      difficultyChoice(1);
      Serial.println("BLAH");
    }else if(location >= 10 && location < 16){
      difficultyChoice(2);
    }
  }else if(unlock == 1){
    if(location >= 0 && location < 4){
      difficultyChoice(0);
    }else if(location >= 4 && location < 8){
      difficultyChoice(1);
    }else if(location >= 8 && location < 12){
      difficultyChoice(2);
    }else if(location >= 12 && location < 16){
      difficultyChoice(3);
    }
  }else if(unlock >= 2){
    if(location >= 0 && location < 3){
      difficultyChoice(0);
    }else if(location >= 3 && location < 6){
      difficultyChoice(1);
    }else if(location >= 6 && location < 9){
      difficultyChoice(2);
    }else if(location >= 9 && location < 12){
      difficultyChoice(3);
    }else if(location >= 12 && location < 15){
      difficultyChoice(4);
    }else if(location >= 15 && location < 16){
      if(unlock == 3){
        difficultyChoice(5);
      }else{
        difficultyChoice(4);
      }
    }
  }
}

void difficultyChoice(int diff){
  Serial.println(diff);
  lcd.clear();
  lcd.setCursor(0,0);
  if(diff == 0){
    change = 5;
    difficulty = 0;
    lcd.print("Easy");
    interval = 1000;
   }else if(diff == 1){
    change = 10;
    difficulty = 1;
    lcd.print("Medium");
    interval = 900;
   }else if(diff == 2){
     lcd.print("Hard");
     difficulty = 2;
    change = 15;
    interval = 800;
   }else if(diff == 3){
    change = 25;
    difficulty = 3;
    lcd.print("Expert");
    interval = 800;
   }else if(diff == 4){
    change = 30; 
    difficulty = 4;
    lcd.print("EXTREME!!");
    interval = 800;
   }else if(diff == 5){
    change = 10; 
    difficulty = 5;
    lcd.print("death");
    interval = 400;
   }
}

