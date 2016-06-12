#include "Ncurses.hpp"

Ncurses::Ncurses(int Y, int X):
	_Flag(true),
	_Speed(150),
	_Height(Y),
	_Width(X),
	_Key(-1){
	initscr();
	noecho();
	curs_set(0);
	use_default_colors();
	clear();
	srand(time(NULL));
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	resize();
   	if (!(_Win = newwin(_Height-1, _Width, 1, 0))){
		Stop();
		throw NibblerException("Newwin error");
	}
	DrawBorder();
}

void			Ncurses::resize(){
   	int tmpY = 0;
   	int tmpX = 0;
	getmaxyx(stdscr, tmpY, tmpX);	
	if (tmpY <= _Height-1 || tmpX <= _Width){
		Stop();
		throw NibblerException("Windows too small.");
	}
}

void			Ncurses::DrawASquare(int X, int Y){
	mvwaddch(_Win, Y, X, ' '| A_REVERSE);
}

void			Ncurses::DrawRock(int x, int y){
	(void)x;
	(void)y;
		// DrawASquare(x,y,_WallTexture,0);
}

void			Ncurses::DrawBorder(){
	wborder(_Win, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
}

void			Ncurses::DrawBorder(WINDOW *win){
	wborder(win, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
}

void			Ncurses::DrawMove(std::list<int> Ly, std::list<int> Lx){
	DrawBorder();
	std::list<int>::iterator it1 = Ly.begin();
	std::list<int>::iterator it2 = Lx.begin();

	if (it1 != Lx.end())
		DrawASquare(*it1, *it2);
	it1 = Lx.end();
	it2 = Ly.end();
	it1--;
	it2--;
	mvwaddch(_Win, *it1, *it2, ' ');
}

void			Ncurses::Eated(){
}

void			Ncurses::DrawFruit(int Y, int X){
	mvwaddch(_Win, Y, X, ACS_DIAMOND);
}

bool			Ncurses::RecoverKeyPressed(bool val){
	if (val){
		_Key = getch();
		if (_Key == KEY_RESIZE)
			resize();
		if (_Key == KEY_P)
			Pause();
	}
	return (true);
}

void			Ncurses::DisplayUI(int mytime, int pts){
	std::stringstream 	tmp;

    tmp << "time = " <<  mytime;
    if (pts != 0)
    	tmp << "\tpts = " << pts;
    mvprintw(0,3, tmp.str().c_str());
}

void			Ncurses::Pause(){
	bool 		end = true;
	_Key = -1;
	nodelay(stdscr, FALSE);
	while (end){
		_Key = getch();
		if (_Key == KEY_P){
			_Key = -1;
			end = false;
		}
		if (_Key == ESC){
			_Key = ESC;
			end = false;
		}
	}	
	nodelay(stdscr, TRUE);
}

bool			Ncurses::GameOver(){
	bool			ret = true;
	std::string 	gmStr = "GAME OVER";
	std::string 	rtStr = "Retry";
	std::string 	exStr = "Exit";
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_WHITE);
 	if(!(_GameOver = newwin(_Height/2, _Width/2, _Height/4, _Width/4))){
		Stop();
		throw NibblerException("Newwin error");
 	}
	wattron(_GameOver, COLOR_PAIR(1));
	DrawBorder(_GameOver);
	mvwprintw(_GameOver, 1, (_Width/2)/2 - (gmStr.length()/2), gmStr.c_str());
	nodelay(stdscr, FALSE);
	while(1){
		if (ret == true){
			wattron(_GameOver, COLOR_PAIR(2));
			mvwprintw(_GameOver, ((_Height/2)/2)-((_Height/2)/2/5), (_Width/2)/2 - (rtStr.length() / 2), rtStr.c_str());
			wattron(_GameOver, COLOR_PAIR(1));
			mvwprintw(_GameOver, ((_Height/2)/2)+((_Height/2)/2/5), (_Width/2)/2 - (exStr.length() / 2), exStr.c_str());
		}
		else{
			mvwprintw(_GameOver, ((_Height/2)/2)-((_Height/2)/2/5), (_Width/2)/2 - (rtStr.length() / 2), rtStr.c_str());
			wattron(_GameOver, COLOR_PAIR(2));
			mvwprintw(_GameOver, ((_Height/2)/2)+((_Height/2)/2/5), (_Width/2)/2 - (exStr.length() / 2), exStr.c_str());
			wattron(_GameOver, COLOR_PAIR(1));
		}
		Refresh(_GameOver);
		RecoverKeyPressed(true);
		switch(_Key){
		case (ESC):
			return (false);
			break;
		case (KEY_UP):
			ret = true;
			break;
		case (KEY_DOWN):
			ret = false;
			break;
		case (10):
			return (ret);
			break;
		}
	}
	return (false);
}

void			Ncurses::Refresh(){
	wrefresh(_Win);
}

void			Ncurses::Refresh(WINDOW * win){
	wrefresh(win);
}

void			Ncurses::Stop(){
	endwin();
}

//GETTER

int				Ncurses::getWidth() const{
	return _Width;
}

int				Ncurses::getHeight() const{
	return _Height;
}

int				Ncurses::getKey() const{
	switch(_Key){
		case (ESC):
			return (ESC);
			break;
		case (NUM1):
			return (NUM1);
			break;
		case (NUM2):
			return (NUM2);
			break;
		case (NUM3):
			return (NUM3);
			break;
		case (KEY_UP):
			return (3);
			break;
		case (KEY_DOWN):	
			return (1);
			break;
		case (KEY_LEFT):
			return (2);
			break;
		case (KEY_RIGHT):
			return (0);
			break;
	}
	return (-1);
}

bool			Ncurses::getFlag() const{
	return _Flag;
}

int 			Ncurses::getSpeed() const{
	return _Speed;
}

//SETTER

void			Ncurses::setFlag(bool val){
	_Flag = val;
}

//C

Ncurses			*createPlayer(int Y, int X){
	return new Ncurses(Y, X);
}

void 			deletePlayer(Ncurses *obj){
	delete obj;
}

Ncurses::~Ncurses(){}

Ncurses::NibblerException::NibblerException(std::string str) throw() : std::runtime_error(str){
	return ;
}

Ncurses::NibblerException::~NibblerException() throw() {
	return ;	
}

const char* 	Ncurses::NibblerException::NibblerException::what() const throw() {
	std::string ret = "Nibbler Exception : Ncurses Error : " + std::string(std::runtime_error::what());
	return ret.c_str();
}

