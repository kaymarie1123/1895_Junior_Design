
//DEFINE NOTES
#define NOTE_A3  220
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330

//DECLARE GLOBAL VARIABLES
 int state;
 int score;
 int command;
 double InitialValue;
 int timer;
 int tensBinaryNum[4];
 int onesBinaryNum[4];
 unsigned long delayStart;
 unsigned long delayEnd;
// notes to play, corresponding to the 3 commands:
int notes[] = {
  NOTE_A3, NOTE_B3, NOTE_C4, NOTE_D4, NOTE_E4
};
 
void setup() {
  // configure pins (reset,button,flex,IR, 7 segments,speaker,LED)
  pinMode(3,INPUT); //reset button
  pinMode(9,INPUT); //IR sensor
  pinMode(10,OUTPUT); //B1 BopIt
  pinMode(3,OUTPUT); //B2 
  pinMode(A0,INPUT); //flex sensor
  pinMode(5,OUTPUT); //speaker
  pinMode(4,OUTPUT); //green led
  pinMode(2,OUTPUT); //red led
  pinMode(8,OUTPUT); 
  pinMode(13, OUTPUT);
  //Decoder pins left
  //pinMode(,OUTPUT); //D
  pinMode(1,OUTPUT); //C
  pinMode(0,OUTPUT); //B
  pinMode(A5,OUTPUT); //A
  //Decoder pins right
  pinMode(A4,OUTPUT); //D
  pinMode(A3,OUTPUT); //C
  pinMode(A2,OUTPUT); //B
  pinMode(A1,OUTPUT); //A
  Serial.begin(9600);
  state=0;
  score=0;
  command=0;
  InitialValue=0;
  timer=5000;
  delayStart=0;
  delayEnd=0;
}

// the loop function runs over and over again forever
void loop() {
  //check if reset button is pressed else check for states
  if(digitalRead(3)==HIGH){
    Reset();
  }
  
  if(state==0){
    
    Blink();
  }
  if(state==1){
    Blink2();
  }

  
}
void Reset(){
  //set 8 segment display to 0 
  //set score to 0
  score=0;
  timer=5000;
  //next state is choosecommand
  //delay(half second)
  delay(500);
  ChooseCommand();
}
void ChooseCommand(){
  //pick a random number between 1-3 and set command
  //set next state to prompt command
  //delay(half second)
  command=random(3);
  delay(500);
  PromptCommand();
}
void PromptCommand(){
  //look at command and play apporopriate sound
  if(command==0){
    //play sound for bopit
    tone(5, notes[2], 20);
    tone(5, notes[2], 20);
    tone(5, notes[2], 20);
  }
  if(command==1){
    //play sound for bend it
    tone(5, notes[0], 20);
    tone(5, notes[1], 20);
    tone(5, notes[2], 20);
  }
  if(command==2){
    //play sound for hide it
    tone(5, notes[4], 20);
    tone(5, notes[3], 20);
    tone(5, notes[2], 20);
  }
  //next state is wait for input
  //delay(half second)
  delay(500);
  WaitForInput();
}
void WaitForInput(){
  //look at command and set initialValue to the value of the appropriate sensor
  //look at score and start a timer and poll the value of the sensor make sure it changes
  delayStart=millis();
  delayEnd=millis();
  while((delayEnd-delayStart)<=timer){
    //if sensor value changes go to correct
    if(command==0){
      //bop it
      if(digitalRead(10)==HIGH){
        Correct();
      }
    }
    if(command==1){
      //bend it
      int val= analogRead(A0);
      if(val>200){
        Correct();
      }
    }
    if(command==2){
      //hide it
      if(digitalRead(9)==HIGH){
        Correct();
      }
    }
    delayEnd=millis();
  }
  //timer runs out then go to Lose()
  Lose();
}
void Correct(){
  //set green light on
  digitalWrite(4,HIGH);
  //increase score
  score+=1;
  //decrease timer
  timer-=50;
  //delay for .5 seconds 
  delay(500);
  //next state is win if score is 99 else choosecommand
  if(score==99) Win();
  else ChooseCommand();

}
void Lose(){
  //set red light on 
  digitalWrite(2,HIGH);
  //set the score to the 7 segment 
  decToBinary(score);
  //if(tensBinaryNum[3]==1)digitalWrite(,HIGH);
  //else digitalWrite(,LOW);
  if(tensBinaryNum[2]==1)digitalWrite(1,HIGH);
  else digitalWrite(1,LOW);
  if(tensBinaryNum[1]==1)digitalWrite(0,HIGH);
  else digitalWrite(0,LOW);
  if(tensBinaryNum[0]==1)analogWrite(A5,255);
  else digitalWrite(A5,0);

  if(onesBinaryNum[3]==1)analogWrite(A4,255);
  else digitalWrite(A4,0);
  if(tensBinaryNum[2]==1)analogWrite(A3,255);
  else digitalWrite(A3,0);
  if(tensBinaryNum[1]==1)analogWrite(A2,255);
  else digitalWrite(A2,0);
  if(tensBinaryNum[0]==1)analogWrite(A1,255);
  else digitalWrite(A1,0);
  
  //check for reset?
  if(digitalRead(3)==HIGH){
    Reset();
   }
  //next state is Lose();
  Lose();
}
void Win(){
  //set green light on
  digitalWrite(4,HIGH);
  //set score to 7 segment
  decToBinary(score);
  //if(tensBinaryNum[3]==1)digitalWrite(,HIGH);
  //else digitalWrite(,LOW);
  if(tensBinaryNum[2]==1)digitalWrite(1,HIGH);
  else digitalWrite(1,LOW);
  if(tensBinaryNum[1]==1)digitalWrite(0,HIGH);
  else digitalWrite(0,LOW);
  if(tensBinaryNum[0]==1)analogWrite(A5,255);
  else digitalWrite(A5,0);

  if(onesBinaryNum[3]==1)analogWrite(A4,255);
  else digitalWrite(A4,0);
  if(tensBinaryNum[2]==1)analogWrite(A3,255);
  else digitalWrite(A3,0);
  if(tensBinaryNum[1]==1)analogWrite(A2,255);
  else digitalWrite(A2,0);
  if(tensBinaryNum[0]==1)analogWrite(A1,255);
  else digitalWrite(A1,0);
  //check for reset?
  if(digitalRead(3)==HIGH){
    Reset();
   }
  //next state is win
  Win();
}

void decToBinary(int n)
{
    //split score into tens and ones
    int ones=n%10;
    int tens=(n-(n%10))/10;
    
    // counter for tens binary array
    int i = 0;
    while (tens > 0) {
 
        // storing remainder in binary array
        tensBinaryNum[i] = tens % 2;
        tens = tens / 2;
        i++;
    }

    // counter for ones binary array
    i = 0;
    while (ones > 0) {
 
        // storing remainder in binary array
        onesBinaryNum[i] = ones % 2;
        ones = ones / 2;
        i++;
    }
}

void Blink(){
 digitalWrite(8,HIGH);
 delay(1000);
 digitalWrite(8,LOW);
 delay(1000);
 state=1;
}
void Blink2(){
 digitalWrite(8,HIGH);
 delay(3000);
 digitalWrite(8,LOW);
 delay(3000);
 state=0;
}
