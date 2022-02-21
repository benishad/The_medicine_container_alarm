  #define C 262
  #define D 294
  #define DS 311
  #define E 330
  #define F 349
  #define FS 370
  #define G 392
  #define GS 415
  #define A 440
  #define AS 466
  #define B 494
  #define HC 523
  #define HD 587
  #define HDS 622
  #define HF 698
  #define HG 784
  #define HA 880
  #define HAS 932                                                    //여기까지는 모두 음정 선언일 뿐입니다.
  int L[10]={D, G, A, AS, HC, HD, HDS, HF, HG, HA};                  //사용할 음들을 배열에 정리
  int buzzer = 9;
void setup() {
  // put your setup code here, to run once:
  pinMode (buzzer, OUTPUT);                                               //3번 핀에 피에조 부저 연결
}

void loop() {
 // put your main code here, to run repeatedly:
  int i;
  tone (buzzer, D);
  delay (500);
  tone (buzzer, G);
  delay (500);
  tone (buzzer, AS);
  delay (500);
  tone (buzzer, HD);
  delay (1000);
  tone (buzzer, HD);
  delay (500);
  tone (buzzer, HC);
  delay (500);
  tone (buzzer, AS);
  delay (500);
  tone (buzzer, A);
  delay (500);
  tone (buzzer,AS);
  delay (1000);
  noTone (buzzer);
  delay (500);
  tone (buzzer,G);
  delay (500);
  tone (buzzer,AS);
  delay (500);
  tone (buzzer, HD);
  delay (500);
  tone (buzzer, HG);
  delay (500);
  noTone (buzzer);                   //no 200
  tone (buzzer, HG);
  delay (300);
  noTone (buzzer);                  //no 200
  tone (buzzer, HG);
  delay (500);
  tone (buzzer, HA);
  delay (700);
  tone (buzzer, HF);
  delay (300);
  tone (buzzer, HDS);
  delay (300);
  tone (buzzer, HF);
  delay (500);
  tone (buzzer, A);
  delay (500);
  tone (buzzer, HD);
  delay (500);
  tone (buzzer, HF);
  delay (500);
  tone (buzzer, HA);
  delay (1000);
  tone (buzzer, HG);
  delay (300);
  tone (buzzer, HF);
  delay (300);
  tone (buzzer, HDS);
  delay (300);
  tone (buzzer, HF);
  delay (300);
  tone (buzzer, HG);
  delay (700);
  tone (buzzer, HF);
  delay (300);
  tone (buzzer, HDS);
  delay (700);
  tone (buzzer, HD);
  delay (300);
  tone (buzzer, HC);
  delay (500);
  tone (buzzer, AS);
  delay (500);
  tone (buzzer, HC);
  delay (500);
  tone (buzzer, HD);
  delay (500);
  tone (buzzer, HC);
  delay (500);
  tone (buzzer, G);
  delay (500);
  tone (buzzer, A);
  delay (1000);
  noTone (buzzer);
  delay (500);                                                    //여기까지가 연주 ^^;
}
