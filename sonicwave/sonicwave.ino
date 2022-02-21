int trig = 12;               //trig 핀 6번
int echo = 11;               //echo핀 7번


void setup() {
  Serial.begin(57600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

}

void loop() {
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);

  float duration = pulseIn(echo, HIGH);
  float distance = ((float)(340 * duration) / 10000) / 2;

  Serial.print("듀레이션 ");
  Serial.println(duration);
  Serial.print("디스턴스 ");
  Serial.println(distance);

  delay(500);

}
