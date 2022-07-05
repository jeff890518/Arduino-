# Arduino-
發報器系統的方塊程式檔案位址在block/door.abp
# Arduino 利修版工作任務

發報器系統的方塊程式檔案位址在block/door.abp

arduino版本：1.6.5
https://downloads.arduino.cc/arduino-1.6.5-r5-windows.zip?_gl=1*1dgh12j*_ga*MTg5MDk5NDU3OS4xNjU0Njc5MjE5*_ga_NEXN8H46L5*MTY1NTg4OTE0OC45LjAuMTY1NTg4OTE1NC41NA..
ardublock版本：ardublock-beta-20140702.jar
https://sourceforge.net/projects/ardublock/files/ardublock-beta-20140702.jar/download

1.具有3I3O的繼電器功能
2.繼電器in的部分可以設定延遲時間
3.使用Ardublock完成基礎框架

把 以relay控制led 和 偵測relay是否按下按鈕
兩個東西 一個input 一個output合併 以code控制
這樣為一組  (控制燈1S，偵測0.5S)


### 以relay控制led
![](https://i.imgur.com/qwUgg7T.png)
![](https://i.imgur.com/zJ17Di6.jpg)
![](https://i.imgur.com/jjauGwM.jpg)


以程式控制LED開關
```cpp=
#define RelayPin_in 13

void setup() {
  pinMode(RelayPin_in,OUTPUT);
  Serial.begin(115200);
}

void loop() {
  if(Serial.available()){
    char c = Serial.read();
    if(c == '1') digitalWrite(RelayPin_in,HIGH);
    else if(c == '0') digitalWrite(RelayPin_in,LOW);
    else Serial.println("Inalid command.");
  } 
}
```

### 偵測relay是否有點亮led
![](https://i.imgur.com/kJp5Ovz.png)
![](https://i.imgur.com/GB9oyA5.jpg)
![](https://i.imgur.com/wDnrGlo.jpg)




```cpp=
#define RelayPin_out 7

void setup() {
  Serial.begin(115200);
  pinMode(RelayPin_out,INPUT);
}

void loop() {
  if(digitalRead(RelayPin_out) == HIGH){
    Serial.println("open");
  }else if(digitalRead(RelayPin_out) == LOW){
    Serial.println("close");
  }
  delay(1000);
}
```
### 以relay控制led 與 relay偵測是否按下按鈕 合併
![](https://i.imgur.com/VzzQbwr.png)

以ardublock拼出程式碼


![](https://i.imgur.com/ve7xZc4.png)
![](https://i.imgur.com/QCAz2QM.png)
```cpp=
int _ABVAR_1_period_LED = 0 ;
int _ABVAR_2_period_button = 0 ;
unsigned long _ABVAR_3_startTime_LED = 0UL ;
unsigned long _ABVAR_4_startTime_button = 0UL ;

void detect_ButtonA();
void detect_ButtonB();

void setup()
{
  pinMode( 11, INPUT);
  pinMode( 5, INPUT);
  pinMode( 7, INPUT);
  pinMode( 11 , OUTPUT);
  pinMode( 13 , OUTPUT);
  Serial.begin(9600);
  _ABVAR_1_period_LED = 1000 ;

  _ABVAR_2_period_button = 500 ;

  _ABVAR_3_startTime_LED = 0UL ;

  _ABVAR_4_startTime_button = 0UL ;

}

void loop()
{
  if (( ( ( millis() - _ABVAR_3_startTime_LED ) ) >= ( _ABVAR_1_period_LED ) ))
  {
    if (digitalRead(11))
    {
      digitalWrite( 11 , LOW );
      digitalWrite( 13 , HIGH );
    }
    else
    {
      digitalWrite( 11 , HIGH );
      digitalWrite( 13 , LOW );
    }
    _ABVAR_3_startTime_LED = millis() ;
  }
  if (( ( millis() ) < ( _ABVAR_3_startTime_LED ) ))
  {
    _ABVAR_3_startTime_LED = millis() ;
  }
  if (( ( ( millis() - _ABVAR_4_startTime_button ) ) >= ( _ABVAR_2_period_button ) ))
  {
    detect_ButtonA();
    detect_ButtonB();
    _ABVAR_4_startTime_button = millis() ;
  }
  if (( ( millis() ) < ( _ABVAR_4_startTime_button ) ))
  {
    _ABVAR_4_startTime_button = millis() ;
  }
}

void detect_ButtonB()
{
  if (digitalRead(7))
  {
    Serial.print("buttonB press");
    Serial.println();
  }
  else
  {
    Serial.print("buttonB NOT press");
    Serial.println();
  }
}

void detect_ButtonA()
{
  if (digitalRead(5))
  {
    Serial.print("buttonA press");
    Serial.println();
  }
  else
  {
    Serial.print("buttonA NOT press");
    Serial.println();
  }
}


```
[{%youtube V7vD6vChBwM %}](https://youtu.be/V7vD6vChBwM)

# 機構設計
### 介面(interface)
![](https://i.imgur.com/QqXwOWe.jpg)
![](https://i.imgur.com/C1D8Icw.jpg)
![](https://i.imgur.com/Gfuw48j.jpg)

## 發報器架構圖
![](https://i.imgur.com/Z2pcOa3.png)
![](https://i.imgur.com/M6sk1V9.png)

```cpp=
int _ABVAR_1_reset = 0 ;
int _ABVAR_2_In1 = 0 ;
int _ABVAR_3_In2 = 0 ;
int _ABVAR_4_In3 = 0 ;
int _ABVAR_5_Out1 = 0 ;
int _ABVAR_6_Out2 = 0 ;
int _ABVAR_7_Out3 = 0 ;
bool _ABVAR_8_alarm= false ;
bool _ABVAR_9_door= false ;
bool _ABVAR_10_alarm_overed= false ;
bool _ABVAR_11_other_alarm= false ;
bool _ABVAR_12_alarming= false ;
unsigned long _ABVAR_13_alarm_detect = 0UL ;
unsigned long _ABVAR_14_alarm_time = 0UL ;
unsigned long _ABVAR_15_alarm_over = 0UL ;
unsigned long _ABVAR_16_start_prealarm = 0UL ;
unsigned long _ABVAR_17_start_alarm = 0UL ;
unsigned long _ABVAR_18_start_alarming_close = 0UL ;
boolean __ardublockDigitalRead(int pinNumber)
{
  pinMode(pinNumber, INPUT);
  return digitalRead(pinNumber);
}


void __ardublockDigitalWrite(int pinNumber, boolean status)
{
  pinMode(pinNumber, OUTPUT);
  digitalWrite(pinNumber, status);
}

unsigned long _ABVAR_19_start_alarming = 0UL ;
bool _ABVAR_20_alarm_overd= false ;

void setup()
{
  Serial.begin(9600);
  _ABVAR_1_reset = 7 ;

  _ABVAR_2_In1 = 13 ;

  _ABVAR_3_In2 = 12 ;

  _ABVAR_4_In3 = 11 ;

  _ABVAR_5_Out1 = 8 ;

  _ABVAR_6_Out2 = 9 ;

  _ABVAR_7_Out3 = 10 ;

  _ABVAR_8_alarm = LOW ;

  _ABVAR_9_door = LOW ;

  _ABVAR_10_alarm_overed = LOW ;

  _ABVAR_11_other_alarm = LOW ;

  _ABVAR_12_alarming = LOW ;

  _ABVAR_13_alarm_detect = 8000UL ;

  _ABVAR_14_alarm_time = 15000UL ;

  _ABVAR_15_alarm_over = 600000UL ;

  _ABVAR_16_start_prealarm = 0UL ;

  _ABVAR_17_start_alarm = 0UL ;

  _ABVAR_18_start_alarming_close = 0UL ;

}

void loop()
{
  Serial.println(millis());
  if (__ardublockDigitalRead(_ABVAR_2_In1))
  {
    __ardublockDigitalWrite(_ABVAR_1_reset, LOW);
  }
  if (( ( millis() ) < ( _ABVAR_16_start_prealarm ) ))
  {
    _ABVAR_16_start_prealarm = millis() ;
  }
  if (( ( millis() ) < ( _ABVAR_17_start_alarm ) ))
  {
    _ABVAR_17_start_alarm = millis() ;
  }
  if (( ( millis() ) < ( _ABVAR_19_start_alarming ) ))
  {
    _ABVAR_19_start_alarming = millis() ;
  }
  if (!( __ardublockDigitalRead(_ABVAR_4_In3) ))
  {
    if (!( _ABVAR_9_door ))
    {
      _ABVAR_16_start_prealarm = millis() ;
      _ABVAR_9_door = HIGH ;
    }
    if (( ( ( millis() - _ABVAR_16_start_prealarm ) ) >= ( _ABVAR_13_alarm_detect ) ))
    {
      if (( !( _ABVAR_8_alarm ) && !( _ABVAR_10_alarm_overed ) ))
      {
        _ABVAR_17_start_alarm = millis() ;
        _ABVAR_8_alarm = HIGH ;
      }
    }
  }
  else
  {
    if (_ABVAR_8_alarm)
    {
      if (!( _ABVAR_12_alarming ))
      {
        _ABVAR_19_start_alarming = millis() ;
        _ABVAR_12_alarming = HIGH ;
      }
      if (( ( ( millis() - _ABVAR_19_start_alarming ) ) >= ( _ABVAR_14_alarm_time ) ))
      {
        _ABVAR_8_alarm = LOW ;
        _ABVAR_12_alarming = LOW ;
      }
    }
    else
    {
      if (_ABVAR_9_door)
      {
        _ABVAR_9_door = LOW ;
        _ABVAR_10_alarm_overed = LOW ;
      }
    }
  }
  if (_ABVAR_8_alarm)
  {
    if (( ( ( millis() - _ABVAR_17_start_alarm ) ) >= ( _ABVAR_15_alarm_over ) ))
    {
      _ABVAR_8_alarm = LOW ;
      _ABVAR_20_alarm_overd = HIGH ;
    }
  }
  if (__ardublockDigitalRead(_ABVAR_3_In2))
  {
    _ABVAR_11_other_alarm = HIGH ;
  }
  else
  {
    _ABVAR_11_other_alarm = LOW ;
  }
  if (( _ABVAR_8_alarm || _ABVAR_11_other_alarm ))
  {
    __ardublockDigitalWrite(_ABVAR_5_Out1, HIGH);
  }
  else
  {
    __ardublockDigitalWrite(_ABVAR_5_Out1, LOW);
  }
}


```
### ardublock
![](https://i.imgur.com/zKZwPGZ.png)
![](https://i.imgur.com/IxxoBJK.png)
![](https://i.imgur.com/UxCVhYU.png)
![](https://i.imgur.com/UfYFcG4.png)
