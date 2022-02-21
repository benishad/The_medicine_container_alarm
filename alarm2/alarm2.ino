#include <ThreeWire.h>  
#include <RtcDS1302.h>

ThreeWire myWire(4,5,2); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);
int Side_trig = 6;
int Side_echo = 7;
int led = 8;
int buzzer = 9;

//------------------------------------------------------------------------
//                     예약 설정
int H = 00;                             // 시 설정 00시
int M = 13;                             // 분 설정 13분
int S = 50;                             // 초 설정 50초
//------------------------------------------------------------------------

unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
unsigned long previousMillis4 = 0;
unsigned long previousMillis5 = 0;
const long delayTime = 1000;
const long delayTime2 = 10;
const long delayTime3 = 100;
const long delayTime4 = 200;
const long delayTime5 = 500;

float duration;
float distance;

boolean state = false;

void setup () {
    Serial.begin(57600);
    Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);

    Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();

    if (!Rtc.IsDateTimeValid()) {
        Serial.println("RTC lost confidence in the DateTime!");
        Rtc.SetDateTime(compiled);
    }

    if (Rtc.GetIsWriteProtected()){
        Serial.println("RTC was write protected, enabling writing now");
        Rtc.SetIsWriteProtected(false);
    }

    if (!Rtc.GetIsRunning()){
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }

    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled) {
        Serial.println("RTC is older than compile time!  (Updating DateTime)");
        Rtc.SetDateTime(compiled);
    }
    else if (now > compiled) {
        Serial.println("RTC is newer than compile time. (this is expected)");
    }
    else if (now == compiled) {
        Serial.println("RTC is the same as compile time! (not expected but all is fine)");
    }

    pinMode(led, OUTPUT);
    pinMode(Side_trig, OUTPUT);
    pinMode(Side_echo, INPUT);
    pinMode(buzzer, OUTPUT);
}

void loop () {
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= delayTime){        //delay 함수를 사용하지 않고 효과를 나타내는 코드 1초 딜레이와 같은 효과가 나타남
    previousMillis = currentMillis;                       //--------------------------
    RtcDateTime now = Rtc.GetDateTime();                  //여기서부터 delay(1000)로 나타내려는 코드줄

    printDateTime(now);
    Serial.println();

    if (!now.IsValid()){
        Serial.println("RTC lost confidence in the DateTime!");
    }
  }

  if(state == true){
    if(currentMillis - previousMillis4 >= delayTime4){
      previousMillis4 = currentMillis;
      tone (buzzer, 262);         //도 음계
    }
    if(currentMillis - previousMillis5 >= delayTime5){
      previousMillis5 = currentMillis;
      noTone (buzzer);
    }
  }
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt){
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis2 >= delayTime2){
    previousMillis2 = currentMillis;
    digitalWrite(Side_trig, HIGH);
   }
  if(currentMillis - previousMillis3 >= delayTime3){
    previousMillis3 = currentMillis;
    digitalWrite(Side_trig, LOW);
    duration = pulseIn(Side_echo, HIGH);        //pulseIn함수는 (핀, 상태) 이고 핀상태가 바뀌면 그때까지 경과된 시간을 ms단위로 바꿔줌.
    distance = ((float)(340*duration)/10000)/2;    //계산한 거리를 다시 cm로 바꾸는 코드
   }
   
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);
    Serial.print("  dis = ");
    Serial.print(distance);

    if (dt. Hour() == H && dt.Minute() == M && dt.Second() == S){
      digitalWrite(led, HIGH);
      state = true;
      
    }
    else if(distance < 10){
      digitalWrite(led, LOW);
      noTone (buzzer);
      state = false;
    }
}
