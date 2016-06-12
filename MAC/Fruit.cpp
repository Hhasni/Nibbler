#include "Fruit.hpp"

Fruit::Fruit():
	_Life(true),
	_Time(0),
	_PosX(5),
	_PosY(5){
	return;
}

Fruit::~Fruit(){
	return;
}

int			Fruit::getPosX() const{
	return _PosX;
}

int			Fruit::getPosY() const{
	return _PosY;
}

int			Fruit::getTime() const{
	return _Time;
}

bool		Fruit::getLife() const{
	return _Life;
}

void		Fruit::setPosX(int val){
	_PosX = val;
	return;
}
void		Fruit::setPosY(int val){
	_PosY = val;
	return;
}
void		Fruit::setTime(int val){
	_Time = val;
	return;
}
void		Fruit::setLife(bool val){
	_Life = val;
	return;
}

void		Fruit::Spawner(int x , int y){
	_PosX = x;
	_PosY = y;
	_Life = true;
}

