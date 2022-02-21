int buzzer = 9;
unsigned long previousMillis4 = 0;
unsigned long previousMillis5 = 0;
const long delayTime4 = 200;
const long delayTime5 = 500;

void setup() {
  pinMode (buzzer, OUTPUT);                                               //3번 핀에 피에조 부저 연결
}

void loop() {
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis4 >= delayTime4){
    previousMillis4 = currentMillis;
    tone (buzzer, 262);         //도 음계
  }
  if(currentMillis - previousMillis5 >= delayTime5){
    previousMillis5 = currentMillis;
    noTone (buzzer);
  }
}
