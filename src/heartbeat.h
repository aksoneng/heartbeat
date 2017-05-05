#ifndef __HEARTBEAT_H
#define __HEARTBEAT_H

// This particular Timer library, because it supports nesting timers inside a class: https://github.com/thomo/Timer
#include "Timer.h" //https://github.com/thomo/Timer
#include "Arduino.h"

#define _HEARTBEAT_SLOW       0
#define _HEARTBEAT_FAST       1

#define _HEARTBEAT_WEAK       1
#define _HEARTBEAT_STRONG     50

class Heartbeat{
public:
	Heartbeat(unsigned char led, bool invert);
  Heartbeat(unsigned char led);
	void update();
	void set_pace(unsigned char pace);
  void set_strength(unsigned char strength);
	void start();
	void stop();

private:
	static void _beat_cb(void *context);
	void beat();
	void set_led(unsigned char led);
	void led_on();
	void led_off();

	Timer _beat_t;
	unsigned char _beat_job;
  unsigned char _led;
  unsigned char _led_state;
  unsigned char _pace;
  unsigned char _strength         =_HEARTBEAT_STRONG;
  unsigned short int _pattern[2]  = {200, 800};
  unsigned char _patternLength    = sizeof(_pattern)/sizeof(_pattern[0]);
  unsigned char _index;
  unsigned char _on     =1;
  unsigned char _off    =0;
};

#endif
