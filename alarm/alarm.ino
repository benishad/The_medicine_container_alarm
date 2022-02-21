

﻿//#include <LiquidCrystal.h>
//#include <core_build_options.h>
//#include <swRTC.h>

LiquidCrystal lcd(4, 6, 10, 11, 12, 13); //RS 핀, E핀, 데이터 핀 4개
String lcdString = ""; //객체 선언 : 출력 할 글자 저장
swRTC rtc;
int piezo = 5;
int temp=1038; // 알람이 울릴 시간을 지정해주는 변수...   2030 => PM. 20:30분을 의미

//AM PM을 구분해 주는 함수
void Set_AMPM(int hour) {
if(hour >=12)
lcd.print("PM");
else
lcd.print("AM");
lcd.print(hour%12, DEC); //시간 출력
}

//10보다 작은수를 출력할때 앞에 0을 출력하게 하는 함수
void Set_lowThanTen(int time) {
if(time < 10) {
lcd.print("0");
lcd.print(time%10);
}
else
lcd.print(time);
}
//유효한 알람시간인지 체크하는 함수
int checkTheAlarmClock(int time) {
if(time/100 < 24 && time %100 < 60) {
Serial.println("Success");
return time;
}
else {
Serial.println("Failed");
return 0;
}
}
//알람이 울릴시간인지 체크하는 함수
void checkTheAlarmTime(int alarmHour, int alarmMinute) {
if(alarmHour == rtc.getHours() && alarmMinute == rtc.getMinutes()) {
analogWrite(piezo, 128);
}
}

void setup() {
lcd.begin(16,2); //LCD 크기 지정, 2줄 16칸
lcd.clear(); //화면 초기화
rtc.stopRTC(); //정지
rtc.setTime(10,37,00); //시간, 분, 초 초기화 현재 시간 입력하는 코드
rtc.setDate(13, 8, 2019); //일, 월, 년 초기화
rtc.startRTC(); //시작
pinMode(piezo, OUTPUT);
Serial.begin(9600); //시리얼 포트 초기화
Serial.begin(9600); //시리얼 통신 초기화
}

void loop() {
int day;
lcd.setCursor(0,0); //커서를 0,0에 지정

//1초 단위로 갱신하며 현재시간을 LCD에 출력
Set_AMPM(rtc.getHours());
lcd.print(":");
Set_lowThanTen(rtc.getMinutes());
lcd.print(":");
Set_lowThanTen(rtc.getSeconds());

//날짜를 LCD에 출력
lcd.print("[");
Set_lowThanTen(rtc.getMonth());
lcd.print("/");
Set_lowThanTen(rtc.getDay());
lcd.print("]");

//세팅된 알람시간을 LCD에 출력
lcd.setCursor(0,1);
lcd.print("Alarm ");
Set_AMPM(temp/100);
lcd.print(":");
Set_lowThanTen(temp%100);

//1초마다 LCD갱신
lcdString = ""; //문자열 초기화
lcd.print(" "); //전 글씨 삭제
delay(1000);

//알람이 울릴 시간인지 체크
checkTheAlarmTime(temp/100, temp%100);

//시리얼 통신을 통해 알람시간을 입력받고 시리얼 모니터에 출력
char theDay[4];
int i = 0;
if(Serial.available()) {
while(Serial.available()) {
theDay[i] = Serial.read();
i++;
}
day = atoi(theDay);
if(day/100 >= 12) {
Serial.print("PM");
Serial.print((day/100)-12);
}
else {
Serial.print("AM");
Serial.print(day/100);
}
Serial.print(":");
if(day%100 < 10)
Serial.print("0");
Serial.println(day%100);
temp = checkTheAlarmClock(day);
}
}
