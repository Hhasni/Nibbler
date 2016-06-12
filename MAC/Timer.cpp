#include "Timer.hpp"

Timer::Timer(){
	_StartTime = clock();
	_ElapsedTime = _StartTime;
}

unsigned long 		Timer::getTime() const{
	return _StartTime;
}

unsigned long 		Timer::getElapsedTime() const{
	return _ElapsedTime;
}

int					Timer::getTimeSecond() const{
	return ((clock() - _StartTime) / CLOCKS_PER_SEC);
}

unsigned long		Timer::getTimeInter() const{
	return ((clock() - getElapsedTime()) / 1000);
}

void				Timer::Reset(){
	_ElapsedTime = clock();	
}

void 				Timer::setTime(unsigned long val){
	_StartTime = val;
}
Timer::~Timer(){}