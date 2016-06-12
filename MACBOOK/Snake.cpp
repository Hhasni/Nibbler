#include "Snake.hpp"

Snake::Snake():
	_Len(3),
	_Pts(0),
	_Ori(0),
	_PosX(0),
	_PosY(0),
	_Life(true),
	_Available(true){
	return;
}

Snake::Snake(int y, int x):
	_Len(3),
	_Pts(0),
	_Ori(0),
	_PosX(x),
	_PosY(y),
	_Life(true),
	_Available(true){
	_Tab.insert(_Tab.begin(), std::make_pair(x-2, y));
	_Tab.insert(_Tab.begin(), std::make_pair(x-1, y));
	_Tab.insert(_Tab.begin(), std::make_pair(x, y));
	return;
}

Snake & Snake::operator=(Snake const & src){
	if (this != &src){
		_PosX = src.getPosX();
		_PosY = src.getPosY();
		_Ori = src.getOri();
		_Life = src.getLife();
		_Len = src.getLen();
		_Pts = src.getPts();
		// _Tab = src._Tab;
	}
	return *this;
}

Snake::Snake(Snake const & src){
	*this = src;
	return;
}

void		Snake::testCollision(int x, int y){
	std::list<int>	listTmpX = getListX();
	std::list<int>	listTmpY = getListY();

	std::list<int>::iterator it = listTmpY.begin();
	std::list<int>::iterator it2 = listTmpX.begin();
	it++;
	it2++;
	if (it != listTmpY.end()){
		for (it = it; it != listTmpY.end(); it++){
			if (*it == y and *it2 == x)
				_Life = false;
			it2++;
		}
	}
}

bool		Snake::tryEat(Fruit & src){
	if (src.getPosX() == _PosX && src.getPosY() == _PosY){
		src.setLife(false);
		_Len += 1;
		_Pts += 1;
		return true;
	}
	return false;
}

//SETTER

void		Snake::setLife(bool val){
	_Life = val;
	return;
}

void		Snake::setAvailable(bool val){
	_Available = val;
	return;
}

void		Snake::setLen(int val){
	_Len = val;
	return;
}

void		Snake::setOri(int val){
	_Ori = val;
	return;
}

void		Snake::setPosX(int val){
	_PosX = val;
	return;
}

void		Snake::setPosY(int val){
	_PosY = val;
	return;
}

void		Snake::setTab(int X, int Y){
	if (_Len < static_cast<int>(_Tab.size()))
		_Tab.pop_back();
	_Tab.insert(_Tab.begin(), std::make_pair(X, Y));
	return;
}

//GETTER

bool		Snake::getLife() const{
	return _Life;
}

bool		Snake::getAvailable() const{
	return _Available;
}

int			Snake::getLen() const{
	return _Len;
}

int			Snake::getPts() const{
	return _Pts;
}

int			Snake::getOri() const{
	return _Ori;
}

int			Snake::getPosX() const{
	return _PosX;
}

int			Snake::getPosY() const{
	return _PosY;
}

std::pair<int, int>		Snake::getPair(int val) const{
	int x = 0;
	std::vector<std::pair<int, int> >::const_iterator it;

	for (it = _Tab.begin(); it != _Tab.end(); it++)
	{
		if (x == val)
			return *it;
		x++;
	}
	return std::make_pair(-2,0);
}

std::list<int>			Snake::getListX() const{
	std::list<int> 		listTmp;
	std::vector<std::pair<int, int> >::const_iterator it;

	for (it = _Tab.begin(); it != _Tab.end(); it++){
		listTmp.push_back(it->first);
	}
	return listTmp;
}

std::list<int>			Snake::getListY() const{
	std::list<int> 		listTmp;
	std::vector<std::pair<int, int> >::const_iterator it;

	for (it = _Tab.begin(); it != _Tab.end(); it++){
		listTmp.push_back(it->second);
	}
	return listTmp;
}

Snake::~Snake(){
	return;
}
