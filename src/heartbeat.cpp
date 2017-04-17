#include "heartbeat.h"

// PUBLIC
Heartbeat::Heartbeat(unsigned short int led, bool invert){
  if(invert){
    _on =0;
    _off =1;
  }
  set_led(led);
  set_pace(_SLOW);
}

void Heartbeat::set_pace(unsigned short int pace){
  _pace =pace;
}

void Heartbeat::start(){
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
void Heartbeat::_callbackBeat(void *context)
{
  ((Heartbeat *)context)->beat();
}

void Heartbeat::beat(){
  _index%2 ==0 ? led_on() : led_off();
  _beat_job =_beat_t.after(_pattern[_index]>>_pace, _callbackBeat, this);
  _index >=(_patternLength-1) ? _index =0 : _index++;
}

void Heartbeat::set_led(unsigned short int led){
  _led =led;
  pinMode(led, OUTPUT);
}

void Heartbeat::led_on(){
  digitalWrite(_led, _on);
}

void Heartbeat::led_off(){
  digitalWrite(_led, _off);
}
