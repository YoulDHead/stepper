int inA1 = 6; // input 1 of the stepper
int inA2 = 8; // input 2 of the stepper
int inB1 = 7; // input 3 of the stepper
int inB2 = 9; // input 4 of the stepper

int stepDelay = 5; // Delay between steps in milliseconds

String IncomeString;
bool Direction;
bool CommandComplete;
int Steps;

void setup() {                
  pinMode(inA1, OUTPUT);     
  pinMode(inA2, OUTPUT);     
  pinMode(inB1, OUTPUT);     
  pinMode(inB2, OUTPUT);  

  Direction=false;
  CommandComplete=false;
  Steps=0;

  Serial.begin(9600);
}

void step1() {
  digitalWrite(inA1, LOW);   
  digitalWrite(inA2, HIGH);   
  digitalWrite(inB1, HIGH);   
  digitalWrite(inB2, LOW);   
  delay(stepDelay);
  
}
void step2() {
  digitalWrite(inA1, LOW);   
  digitalWrite(inA2, HIGH);   
  digitalWrite(inB1, LOW);   
  digitalWrite(inB2, HIGH);   
  delay(stepDelay);
}
void step3() {
  digitalWrite(inA1, HIGH);   
  digitalWrite(inA2, LOW);   
  digitalWrite(inB1, LOW);   
  digitalWrite(inB2, HIGH);   
  delay(stepDelay);
}
void step4() {
  digitalWrite(inA1, HIGH);   
  digitalWrite(inA2, LOW);   
  digitalWrite(inB1, HIGH);   
  digitalWrite(inB2, LOW);   
  delay(stepDelay);
}
void stopMotor() {
  digitalWrite(inA1, LOW);   
  digitalWrite(inA2, LOW);   
  digitalWrite(inB1, LOW);   
  digitalWrite(inB2, LOW);   
}

// the loop routine runs over and over again forever:
void loop() {
  bool flag=false;

  IncomeString="";

  while(!flag){
    if (Serial.available() > 0) {  //если есть доступные данные
        // считываем байт
      
        char incomingByte = Serial.read();

        if(incomingByte==0x0d || IncomeString.length()>20){
          flag=true;            
        }

        IncomeString=IncomeString+incomingByte;
        // отсылаем то, что получили
        Serial.print("I received: ");
        Serial.println(IncomeString);
    }


  }

  if(IncomeString.substring(0,4)=="left"){
      Serial.println("left catched");
      Direction=false;
      Steps=IncomeString.substring(4,IncomeString.length()-1).toInt();
      Serial.println(IncomeString.substring(4,IncomeString.length()-1));
      CommandComplete=true;
  }
  if(IncomeString.substring(0,5)=="right"){
      Serial.println("right catched");
      Direction=true;
      Steps=IncomeString.substring(5,IncomeString.length()-1).toInt();
      Serial.println(IncomeString.substring(5,IncomeString.length()-1));
      CommandComplete=true;
  }


  if(CommandComplete && !Direction){
    
    for (int i=0; i<=Steps; i++){ 
      step1(); 
      step2();
      step3();
      step4();
    }
    stopMotor();
  }

  if(CommandComplete && Direction){
    
    for (int i=0; i<=Steps; i++){ 
      step4(); 
      step3();
      step2();
      step1();
    }
    stopMotor();
  }
    Steps=0;
    CommandComplete=0;


  if(IncomeString.substring(0,4)=="setd"){
      Serial.println("setdelay catched");
      stepDelay=IncomeString.substring(4,IncomeString.length()-1).toInt();
      Serial.println(IncomeString.substring(4,IncomeString.length()-1));
      CommandComplete=true;
  }
  
 /* for (int i=0; i<=100; i++){ 
    step1(); 
    step2();
    step3();
    step4();
  }
  stopMotor();
  //delay(1000);
  
  for (int i=0; i<=100; i++){
    step3();
    step2();
    step1();
    step4(); 
  }
  
  stopMotor();
  //delay(1000);*/
}//
