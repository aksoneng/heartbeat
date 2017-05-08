#include "heartbeat.h"

// PUBLIC
Heartbeat::Heartbeat(unsigned char led, bool invert){
  if(invert){
    _on =0;
    _off =1;
  }
  set_led(led);
  set_pace(_HEARTBEAT_SLOW);
}

Heartbeat::Heartbeat(unsigned char led){
  set_led(led);
  set_pace(_HEARTBEAT_SLOW);
}

void Heartbeat::set_pace(unsigned char pace){
  switch(pace){
    case _HEARTBEAT_FAST:
      _pace =_HEARTBEAT_FAST;
      break;
    case _HEARTBEAT_SLOW:
      _pace =_HEARTBEAT_SLOW;
      break;
    default:
      Serial.print(F("Unknown heartbeat pace: "));
      Serial.println(pace);
      break;
  }
}

void Heartbeat::set_strength(unsigned char strength){
  switch(strength){
    case _HEARTBEAT_STRONG:
      _strength =_HEARTBEAT_STRONG;
      break;
    case _HEARTBEAT_WEAK:
      _strength =_HEARTBEAT_WEAK;
      break;
    default:
      Serial.print(F("Unknown heartbeat strength: "));
      Serial.println(strength);
      break;
  }
}

void Heartbeat::set_beat(unsigned char beats){
  if(beats >0 && beats <=255){
    _beats =beats;
  }
  else{
    Serial.print(F("Beats must be >1 && <=255 !"));
  }
}

void Heartbeat::add_beat(){
  if(_beats <255){
    _beats++;
  }
  else{
    Serial.print(F("Cannot have more than 255 beats !"));
  }
}

void Heartbeat::remove_beat(){
  if(_beats >=2){
    _beats--;
  }
  else{
    Serial.print(F("Cannot remove last beat !"));
  }
}

// PRIVATE
void Heartbeat::start(){
  _index =1;
  beat();
}

void Heartbeat::stop(){
  _beat_t.stop(_beat_job);
  led_off();
}

void Heartbeat::update(){
  _beat_t.update();
}

// PRIVATE
void Heartbeat::_beat_cb(void *context)
{
  ((Heartbeat *)context)->beat();
}

void Heartbeat::beat(){
  if(_index %2){
    led_on();
    _beat_job =_beat_t.after(_strength, _beat_cb, this);
  }
  else {
    led_off();
    if((_index>>1) >=_beats){
      _beat_job =_beat_t.after(_HEARTBEAT_SYSTOLE>>_pace, _beat_cb, this);
    }
    else{
      _beat_job =_beat_t.after(_HEARTBEAT_DIASTOLE>>_pace, _beat_cb, this);
    }
  }
  (_index>>1) >=_beats ? _index =1 : _index++;
}

void Heartbeat::set_led(unsigned char led){
  _led =led;
  pinMode(_led, OUTPUT);
}

void Heartbeat::led_on(){
  digitalWrite(_led, _on);
}

void Heartbeat::led_off(){
  digitalWrite(_led, _off);
}
