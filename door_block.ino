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


