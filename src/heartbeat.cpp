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

// PRIVATE
void Heartbeat::start(){
  _index =0;
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
    _beat_job =_beat_t.after(_pattern[_index>>1]>>_pace, _beat_cb, this);
    Serial.println(_pattern[_index>>1]>>_pace);
  }
  _index >=(2*_patternLength-1) ? _index =0 : _index++;
}

void Heartbeat::set_led(unsigned char led){
  _led =led;
  pinMode(led, OUTPUT);
}

void Heartbeat::led_on(){
  digitalWrite(_led, _on);
}

void Heartbeat::led_off(){
  digitalWrite(_led, _off);
}
