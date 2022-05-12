const byte segment_pins[8] = {9, 8, 7, 6, 5, 4, 3, 1};
const byte power_pins[4] = {10, 11, 12, 13};
const byte digit[10][8] = {
  {0, 0, 0, 0, 0, 0, 1, 1},
  {1, 0, 0, 1, 1, 1, 1, 1},
  {0, 0, 1, 0, 0, 1, 0, 1},
  {0, 0, 0, 0, 1, 1, 0, 1},
  {1, 0, 0, 1, 1, 0, 0, 1},
  {0, 1, 0, 0, 1, 0, 0, 1},
  {1, 1, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 1, 1, 0, 0, 1},
};
const byte scan[4][4] = {
  {1, 0, 0, 0},
  {0, 1, 0, 0},
  {0, 0, 1, 0},
  {0, 0, 0, 1}
};
int a, x;
byte d[4];
unsigned long startTime, count, step;
int btn = 0;

void setup()
{
  for (byte i = 0; i < 8; i++) {
    pinMode(segment_pins[i], OUTPUT); 
  }
  for (byte i = 0; i < 4; i++) {
    pinMode(power_pins[i], OUTPUT);
  }
  startTime = millis() /500;
  pinMode(2, INPUT);
  pinMode(0, OUTPUT);
}

void loop()
{
  btn = digitalRead(2);
  step = millis() /1000 - startTime;
  if(btn == HIGH){
    if(step == 6040){
      startTime = millis() / 1000;
    }
    step = 3599 - step;
    count = 3599 - step;
  }
  else{
    step = 3599 - step;
    if(step == 0){
      startTime = millis() / 500;
    }
    count = step;
  }
  set_decimal(count);
  for(byte i =0; i < 4; i++){
    
    for(byte j = 0; j < 4; j++){
      digitalWrite(power_pins[j], LOW);
    }
    for(byte j = 0; j < 8; j++){
      digitalWrite(segment_pins[j], digit[d[i]][j]);
      if(scan[i][2] == 1 && j == 7){
        digitalWrite(segment_pins[j], LOW);
      }
    }
    for(byte j = 0; j < 4; j++){
      digitalWrite(power_pins[j], scan[i][j]);
    }
    delay(2);
  }
}

void set_decimal(int a){
  a = count%60;
  d[0] = a%10;
  d[1] = (a/10)%10;
  a = count/60;
  d[2] = a%10;
  d[3] = (a/10)%10;
}
