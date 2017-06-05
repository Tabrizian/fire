#ifndef CONSTANT_H
#define CONSTANT_H

#define F_CPU 1000000UL
#define SAMPLE_RATE 200
#define FIRE_THRESHOLD 480
#define ASCII_NUMBER_BASE 48

enum machinState{ACTIVE_NORMAL,ACTIVE_QUIET,DEACTIVE};
extern int state ;
#endif
