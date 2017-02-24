#ifndef __HEARTBEAT_H
#define __HEARTBEAT_H

// This particular Timer library, because it supports nesting timers inside a class: https://github.com/thomo/Timer
#include "Timer.h"
#include "Arduino.h"

#define _SLOW       0
#define _FAST       1

class Heartbeat{
public:
	Heartbeat(unsigned short int led);
	void update();
	void set_pace(unsigned short int pace);
	void start();
	void stop();

private:
	static void _callbackBeat(void *context);
	void beat();
	void set_led(unsigned short int led);
	void led_on();
	void led_off();

	Timer _beat_t;
	int _beat_job;
  unsigned short int _led;
  unsigned short int _pace;
  unsigned short int _pattern[4] = {50, 200, 50, 750};
  unsigned short int _patternLength = sizeof(_pattern)/sizeof(_pattern[0]);
  unsigned short int _index =0;
};

#endif
