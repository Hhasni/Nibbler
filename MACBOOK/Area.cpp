#include "Area.hpp"

Area::Area():
	_MaxX(0),
	_MaxY(0){
	return;
}

Area::Area(int y, int x):
	_MaxX(x+2),
	_MaxY(y+3){
  	srand (time(NULL));
	rx = rand() % (x-1)+1;
	ry = rand() % (y-1)+1;
	return;
}

Area & Area::operator=(Area const & src){
	if (this != &src){
		_MaxX = src._MaxX;
		_MaxY = src._MaxY;
	}
	return *this;
}

Area::Area(Area const & src){
	*this = src;
	return;
}

void		Area::moveUp(Snake & src){
	int		tmp;

	tmp = src.getPosY(); 
	src.setPosY(tmp-1);
	src.setTab(src.getPosX(),src.getPosY());
	if (tmp-1 > 0){
		src.testCollision(src.getPosX(), tmp - 1);
		src.testCollision(rx,ry);
		// src.setAvailable(true);
	}
	else
		src.setLife(false);
	return;
}

void		Area::moveDown(Snake & src){
	int		tmp;

	tmp = src.getPosY(); 
	src.setPosY(tmp+1);
	src.setTab(src.getPosX(),src.getPosY());
	if (tmp+1 < _MaxY - 2){
		src.testCollision(src.getPosX(), tmp + 1);
		src.testCollision(rx,ry);
		// src.setAvailable(true);
	}
	else
		src.setLife(false);
	return;
}

void		Area::moveLeft(Snake & src){
	int		tmp;

	tmp = src.getPosX(); 
	src.setPosX(tmp-1);
	src.setTab(src.getPosX(),src.getPosY());
	if (tmp-1 > 0){
		src.testCollision(tmp - 1, src.getPosY());
		src.testCollision(rx,ry);
		// src.setAvailable(true);
	}
	else
		src.setLife(false);
	return;
}

void		Area::moveRight(Snake & src){
	int		tmp;

	tmp = src.getPosX(); 
	src.setPosX(tmp+1);
	src.setTab(src.getPosX(),src.getPosY());
	if (tmp+1 < _MaxX - 1){
		src.testCollision(tmp + 1, src.getPosY());
		src.testCollision(rx,ry);
		// src.setAvailable(true);		
	}
	else
		src.setLife(false);
	return;
}

void		Area::Spawner(Snake & src, Fruit & obj){
	int		x;
	int		y;

	x = rand() % (_MaxX-2)+1;
	y = rand() % (_MaxY-3)+1;
	std::list<int>	_listTmpX = src.getListX();
	std::list<int>	_listTmpY = src.getListY();
	while(std::find(_listTmpX.begin(), _listTmpX.end(), x) != _listTmpX.end() &&
		std::find(_listTmpY.begin(), _listTmpY.end(), y) != _listTmpY.end()){
		x = rand() % (_MaxX-2) +1;
		y = rand() % (_MaxY-3) +1;
	}
	obj.Spawner(x,y);
}

//SETTER

void		Area::setMaxX(int val){
	_MaxX = val;
}

void		Area::setMaxY(int val){
	_MaxY = val;
}

//GETTER

int			Area::getMaxX() const{
	return _MaxX;
}

int			Area::getMaxY() const{
	return _MaxY;
}

Area::~Area(){
	return;
}
