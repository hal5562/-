void setup() {
  // put your setup code here, to run once:
  pinMode(8, INPUT);
  Serial.begin(9600);
}
#define number 500
uint16_t data[number];
int count = 0;
unsigned long startTime = 0;  // 開始時刻を保存する変数
unsigned long duration;       // 経過時間を保存する変数
unsigned long lasttime;
bool value = 1;
bool onece = 1;
void loop() {
  duration = micros() - startTime;
  if ((digitalRead(8) != value) && (onece == 0)) {
    lasttime = duration;
    //Serial.println("OUT");
    if (count <= number-1) {
      //Serial.println("IN");
      data[count] = duration;
      count++;
    }

    value = digitalRead(8);
  }
  if ((digitalRead(8) != value) && (onece == 1)) {
    startTime = micros();  // ★ここが「スタートボタン」を押した瞬間
    duration = micros() - startTime;
    lasttime=duration;
    value = digitalRead(8);
    onece = 0;
  }

  if ((duration - lasttime >= 100000) && (onece == 0)) {
    Serial.print(0);
    Serial.print(":");
    Serial.println(data[0]);
    for (int i = 0; i < count-1; i++) {
      Serial.print(i+1);
      Serial.print(":");
      Serial.println(data[i + 1] - data[i]);
    }
    onece = 1;
    count = 0;
    value = 1;
    delay(2000);
  }
}
