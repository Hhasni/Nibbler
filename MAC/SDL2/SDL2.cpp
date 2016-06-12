#include "SDL2.hpp"

SDL2::SDL2(int Y, int X):_Y(Y-1),_X(X){
	_Key = -1;
	_Flag = true;
	_Height = 550;
	_Width = 500;
	_GUIHeigh = 50;
	_Vol = 50;
	_Key = 0;
	_Speed = 150;
	_ListRot.push_front(270);
	_ListRot.push_front(270);
	_ListRot.push_front(270);
	_Dir = 0;
	_myError = new NibblerException("");
	if (SDL_Init (SDL_INIT_VIDEO)){// | SDL_INIT_AUDIO) < 0){
		Error("SDL_Init Error: ", SDL_GetError());
	}
	if (!(_Win = SDL_CreateWindow("Nibbler SDL", 100, 100, _Width, _Height, SDL_WINDOW_SHOWN)))
		Error("SDL_CreateWindow Error: ", SDL_GetError());
	// if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		// Error("SDL_Mix_OpenAudio Error: ", Mix_GetError());
	// if (TTF_Init() == -1)
		// Error("SDL_TTF_Init Error: ", TTF_GetError());
	// if (!(_Font = TTF_OpenFont("SDL2/Assets/Open.tff", 35)))
	// 	Error("SDL_TTF_OpenFont Error: ", TTF_GetError());
	_textColor.r = 255;
	_textColor.g = 255;
	_textColor.b = 255;
	_textColor.a = 255;
	_GuiBox.x = 0;
	_GuiBox.y = _Height-_GUIHeigh;
	_GuiBox.w = _Width;
	_GuiBox.h = _GUIHeigh;
	if (!(_Render = SDL_CreateRenderer(_Win, -1, SDL_RENDERER_ACCELERATED )))
		Error("SDL_CreateRenderer Error: ", SDL_GetError());
	// std::cerr << "X = " << _X << std::endl;
	// std::cerr << "Y = " << _Y << std::endl;
	_Case_W = static_cast<double>(_Width)/_X;
	_Height -= _GUIHeigh;
	_Case_H = static_cast<double>(_Height)/_Y;
	// std::cerr << "_Case_W = " << _Case_W << std::endl;
	// std::cerr << "_Case_H = " << _Case_H << std::endl;
	// if (!(_MainMusic = Mix_LoadMUS("SDL2/Assets/Theme.wav")))
	// 	Error("SDL_Mix_LoadMUS Error: ", Mix_GetError());
	// if (!(_EatEffect = Mix_LoadWAV("SDL2/Assets/Eat.wav")))
	// 	Error("SDL_Mix_LoadWAV Error: ", Mix_GetError());
	// if (!(_DeathEffect = Mix_LoadWAV("SDL2/Assets/Death.wav")))
	// 	Error("SDL_Mix_LoadWAV Error: ", Mix_GetError());
	SDL_Surface* loadedSurface = IMG_Load("SDL2/Assets/HEAD.png");
	if (!loadedSurface)
		Error("SDL_ING_Load Error: ", IMG_GetError());
	if (!(_HeadTexture = SDL_CreateTextureFromSurface(_Render, loadedSurface)))
		Error("SDL_CreateTextureFromSurface Error: ", SDL_GetError());
	if (!(loadedSurface = IMG_Load("SDL2/Assets/TURN.png")))
		Error("SDL_ING_Load Error: ", IMG_GetError());
	if (!(_TurnTexture = SDL_CreateTextureFromSurface(_Render, loadedSurface)))
		Error("SDL_CreateTextureFromSurface Error: ", SDL_GetError());
	if (!(loadedSurface = IMG_Load("SDL2/Assets/BODY.png")))
		Error("SDL_ING_Load Error: ", IMG_GetError());
	if (!(_BodyTexture = SDL_CreateTextureFromSurface(_Render, loadedSurface)))
		Error("SDL_CreateTextureFromSurface Error: ", SDL_GetError());	
	if (!(loadedSurface = IMG_Load("SDL2/Assets/FRUIT.png")))
		Error("SDL_ING_Load Error: ", IMG_GetError());
	if (!(_FruitTexture = SDL_CreateTextureFromSurface(_Render, loadedSurface)))
		Error("SDL_CreateTextureFromSurface Error: ", SDL_GetError());	
	if (!(loadedSurface = IMG_Load("SDL2/Assets/Wall.png")))
		Error("SDL_ING_Load Error: ", IMG_GetError());
	if (!(_WallTexture = SDL_CreateTextureFromSurface(_Render, loadedSurface)))
		Error("SDL_CreateTextureFromSurface Error: ", SDL_GetError());	
	if (!(loadedSurface = IMG_Load("SDL2/Assets/Wall.png")))
		Error("SDL_ING_Load Error: ", IMG_GetError());
	if (!(_RockTexture = SDL_CreateTextureFromSurface(_Render, loadedSurface)))
		Error("SDL_CreateTextureFromSurface Error: ", SDL_GetError());	

	_GameOver = NULL;
	// Mix_VolumeMusic(_Vol);
	// Mix_PlayMusic(_MainMusic, -1);
	SDL_SetRenderDrawColor(_Render, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(_Render);
	DrawBorder();
	// DrawRock();
}

void			SDL2::DrawRock(int x, int y){
		DrawASquare(x,y,_WallTexture,0);
}

void			SDL2::DrawBorder(){
	for (int i = 0; i < (_X-1); ++i)//Top
		DrawASquare(i,0,_WallTexture,0);
	for (int i = 0; i < (_X-1); ++i)//Bot
		DrawASquare(i,(_Y-1),_WallTexture,0);
	for (int i = 0; i < _Y; ++i)//Left
		DrawASquare(0,i,_WallTexture,0);
	for (int i = 0; i < _Y; ++i)//Right
		DrawASquare((_X-1),i,_WallTexture,0);

	// SDL_SetRenderDrawColor(_Render, 0xFF, 0x00, 0x00, 0xFF);
	// SDL_Rect Left = {0, 0, _Case_W, _Height};
	// SDL_RenderFillRect(_Render, &Left);
	// SDL_Rect Right = {_Width-_Case_W, 0, _Case_W, _Height};
	// SDL_RenderFillRect(_Render, &Right);
	// SDL_Rect Up = {0, 0, _Width, _Case_H};
	// SDL_RenderFillRect(_Render, &Up);
	// SDL_Rect Down = {0, _Height-_Case_H, _Width, _Case_H};
	// SDL_RenderFillRect(_Render, &Down);

}

void			SDL2::DrawASquare(int X, int Y){
	SDL_SetRenderDrawColor(_Render, 0x00, 0x00, 0xFF, 0xFF);
	SDL_Rect Square = {X*_Case_W, Y*_Case_W, _Case_W, _Case_W};
	SDL_RenderFillRect(_Render, &Square);
}

void			SDL2::DrawASquare(int X, int Y, SDL_Texture* texture, double rot){
	SDL_SetRenderDrawColor(_Render, 0x00, 0x00, 0xFF, 0xFF);        
	SDL_Rect Square = {X*_Case_W, Y*_Case_H, _Case_W, _Case_H};
	SDL_Point center = {_Case_W/2, _Case_H/2};
	SDL_RenderCopyEx(_Render, texture, NULL, &Square, rot , &center, SDL_FLIP_NONE);	
}

void			SDL2::DrawMove(std::list<int> Lx, std::list<int> Ly){
	DrawBorder();
	// DrawRock();
	std::list<int>::iterator it1 = Lx.begin();
	std::list<int>::iterator it2 = Ly.begin();
	if (_Dir == 0)
		_ListRot.push_front(270);
	if (_Dir == 3)
		_ListRot.push_front(180);
	if (_Dir == 2)
		_ListRot.push_front(90);
	if (_Dir == 1)
		_ListRot.push_front(0);
	std::list<double>::iterator it3 = _ListRot.begin();
	DrawASquare(*it1, *it2, _HeadTexture, *it3);
	int bkp1 = *it1;
	int bkp2 = *it2;
	int bkp3 = *it3;
	int i = 1;
	it1++;
	it2++;
	it3++;
	if (it1 != Lx.end()){
		for (it1 = it1; it1 != Lx.end(); it1++){
			i++;
			if (bkp3 != *it3){
				if (bkp3 == 0 && *it3 == 270)
					DrawASquare(*it1, *it2, _TurnTexture, *it3);
				else if (bkp3 == 90 && *it3 == 180)
					DrawASquare(*it1, *it2, _TurnTexture, 270);
				if (bkp3 == 0 && *it3 == 90)
					DrawASquare(*it1, *it2, _TurnTexture, 180);
				else if (bkp3 == 270 && *it3 == 180)
					DrawASquare(*it1, *it2, _TurnTexture, 180);
				if (bkp3 == 270 && *it3 == 0)
					DrawASquare(*it1, *it2, _TurnTexture, 90);
				else if (bkp3 == 180 && *it3 == 90)
					DrawASquare(*it1, *it2, _TurnTexture, 90);
				if (bkp3 == 180 && *it3 == 270)
					DrawASquare(*it1, *it2, _TurnTexture, 0);
				else if (bkp3 == 90 && *it3 == 0)
					DrawASquare(*it1, *it2, _TurnTexture, 0);
			}
			else
				DrawASquare(*it1, *it2, _BodyTexture, *it3);
			bkp1 = *it1;
			bkp2 = *it2;
			bkp3 = *it3;
			it2++;
			it3++;
		}
	}
	if (static_cast<int>(_ListRot.size()) >= i)
		_ListRot.pop_back();
}

void			SDL2::Eated(){
	// Mix_PlayChannel(-1, _EatEffect, 0);	
}

#include <unistd.h>

void			SDL2::DrawFruit(int Y, int X){
	SDL_SetRenderDrawColor( _Render, 0x00, 0x00, 0xFF, 0xFF );        
	SDL_Rect Square = {X*_Case_W, Y*_Case_H, _Case_W, _Case_H};
	SDL_Point center = {_Case_W/2, _Case_H/2};
	SDL_RenderCopyEx(_Render, _FruitTexture, NULL, &Square, 0 ,&center , SDL_FLIP_NONE);	
}

bool			SDL2::RecoverKeyPressed(bool myflag){
	SDL_Event 	event;

	SDL_PollEvent(&event);
	if (myflag == false)
		return (false);
	if (event.type == SDL_KEYDOWN){
		if (event.key.keysym.sym == SDLK_EQUALS){
			if (_Vol < 100)
				_Vol += 10;
		    // Mix_VolumeMusic(_Vol);
		}
		else if (event.key.keysym.sym == SDLK_MINUS){
			if (_Vol > 0)
				_Vol -= 10;
		    // Mix_VolumeMusic(_Vol);
		}
		else if (event.key.keysym.sym == SDLK_p)
			Pause();
		else if (event.key.keysym.sym == SDLK_UP && _Dir != 1){
			_Key = 3;
			_Dir = 3;
		}
		else if (event.key.keysym.sym == SDLK_RIGHT && _Dir != 2){
			_Key = 0;
			_Dir = 0;
		}
		else if (event.key.keysym.sym == SDLK_LEFT && _Dir != 0){
			_Key = 2;
			_Dir = 2;
		}
		else if (event.key.keysym.sym == SDLK_DOWN && _Dir != 3){
			_Key = 1;
			_Dir = 1;
		}
		else if (event.key.keysym.sym == SDLK_ESCAPE)
			_Key = ESC;
		else if (event.key.keysym.sym == SDLK_RETURN)
			_Key = 10;
		else if (event.key.keysym.sym == SDLK_1)
			_Key = SDLK_1;
		else if (event.key.keysym.sym == SDLK_2)
			_Key = SDLK_2;
		else if (event.key.keysym.sym == SDLK_3)
			_Key = SDLK_3;
		return (true);
	}
	if (event.type == SDL_QUIT){
		_Key = ESC;
	}
	return (false);
}

void			SDL2::GenerateText(std::string str, SDL_Renderer * ren, SDL_Rect pos){
	(void)str;
	// if (!(_Text = TTF_RenderText_Solid( _Font, str.c_str(), _textColor)))
	// 	Error("TTF_RenderText_Solid Error: ", TTF_GetError());
	if (!(_myTexture = SDL_CreateTextureFromSurface(ren, _Text)))
		Error("SDL_CreateTextureFromSurface Error: ", SDL_GetError());
	SDL_FreeSurface(_Text);
	SDL_RenderCopy(ren, _myTexture, NULL, &pos);
    SDL_DestroyTexture(_myTexture);
}

void			SDL2::DisplayUI(int mytime, int pts){
	(void)mytime;
	(void)pts;
	// std::stringstream 		str;
	// str << "Time = " << mytime << " points = " << pts;
	// GenerateText(str.str(), _Render, _GuiBox);
}

void			SDL2::Pause(){
	bool 		end = true;
	SDL_Event 	event;
	// Mix_PauseMusic();

	while (end){
		SDL_PollEvent(&event);
		if (event.type == SDL_KEYDOWN){
			if (event.key.keysym.sym == SDLK_p){
				end = false;
				// Mix_ResumeMusic();
			}
			if (event.key.keysym.sym == SDLK_ESCAPE){
				_Key = ESC;
				end = false;
			}
		}
	}	
}

bool			SDL2::GameOver(){
	// Mix_HaltMusic();
	// Mix_PlayChannel(-1, _DeathEffect, 0);
	int i = clock();
	_Dir = -1;
	while(_Key != ESC){
		if (clock() - i > CLOCKS_PER_SEC * 3)
			break;
		RecoverKeyPressed(false);
	}
	if (_Key != ESC){
		_Key = -1;
		Refresh();
		SDL_DestroyRenderer(_Render);
		_Render = NULL;
		if (!(_GameOver = SDL_CreateRenderer(_Win, -1, SDL_RENDERER_ACCELERATED )))
			Error("SDL_CreateRenderer Error: ", SDL_GetError());
		Refresh(_GameOver);
		SDL_Rect Overline = {_Width/3, _Height/4, _Width/3, 50};
	    SDL_SetRenderDrawColor( _GameOver, 0x00, 0xFF, 0x00, 0xFF );        
	    SDL_RenderFillRect( _GameOver, &Overline );
		bool myMenuFlag = true;
	    Overline.y -= 100;
		// GenerateText("GameOver", _GameOver, Overline);	
		Overline.y = _Height/4;
		// GenerateText("Retry", _GameOver, Overline);	
		Overline.y = _Height/4 + 100;
		// GenerateText("Exit", _GameOver, Overline);	
		Refresh(_GameOver);
		while(_Key != 10 && _Key != ESC){
			if (RecoverKeyPressed(true)){
				if (_Key == 1 || _Key == 3)
					myMenuFlag = !myMenuFlag;
				if (myMenuFlag){
				    SDL_SetRenderDrawColor( _GameOver, 0x00, 0xFF, 0x00, 0xFF );
					Overline.y = _Height/4;
				}
				else{
				    SDL_SetRenderDrawColor( _GameOver, 0xFF, 0x00, 0x00, 0xFF );
					Overline.y = _Height/4+100;
			    }
			    SDL_RenderFillRect( _GameOver, &Overline );
				Overline.y = _Height/4 - 100;
				// GenerateText("GameOver", _GameOver, Overline);	
				Overline.y = _Height/4;
				// GenerateText("Retry", _GameOver, Overline);	
				Overline.y = _Height/4 + 100;
				// GenerateText("Exit", _GameOver, Overline);	
				Refresh(_GameOver);
			}
		}
		if (_Key == ESC)
			return(false);
		return (myMenuFlag);
	}
	return (false);
}

void			SDL2::Refresh(){
	SDL_RenderPresent(_Render);
    SDL_SetRenderDrawColor( _Render, 0x00, 0x00, 0x00, 0xFF );        
    SDL_RenderClear(_Render);
}

void			SDL2::Refresh(SDL_Renderer*	ren){
	SDL_RenderPresent(ren);
    SDL_SetRenderDrawColor( ren, 0x00, 0x00, 0x00, 0xFF );        
    SDL_RenderClear(ren);
}

void			SDL2::Stop(){
	// Mix_CloseAudio();
	// std::cerr << "1" << std::endl;
	// if (_Font)
	// 	TTF_CloseFont(_Font);
	// std::cerr << "2" << std::endl;
	// if (_DeathEffect)
	// 	Mix_FreeChunk(_DeathEffect);
	// // std::cerr << "3" << std::endl;
	// if (_EatEffect)
	// 	Mix_FreeChunk(_EatEffect);
	// // std::cerr << "4" << std::endl;
	// if (_MainMusic)
	// 	Mix_FreeMusic(_MainMusic);
	// std::cerr << "5" << std::endl;
	if (_BodyTexture)
		SDL_DestroyTexture(_BodyTexture);
	// std::cerr << "6" << std::endl;
	if (_HeadTexture)
		SDL_DestroyTexture(_HeadTexture);
	// std::cerr << "7" << std::endl;
	if (_TurnTexture)
		SDL_DestroyTexture(_TurnTexture);
	// std::cerr << "8" << std::endl;
	if (_Render)
		SDL_DestroyRenderer(_Render);
	// std::cerr << "9" << std::endl;
	if (_GameOver)
		SDL_DestroyRenderer(_GameOver);
	// std::cerr << "10" << std::endl;
	if (_Win)
		SDL_DestroyWindow(_Win);
	// std::cerr << "11" << std::endl;
	IMG_Quit();
	// std::cerr << "12" << std::endl;
	// Mix_Quit();
	// // std::cerr << "13" << std::endl;
	// TTF_Quit();
	// std::cerr << "14" << std::endl;
	SDL_Quit();
}

//GETTER

int				SDL2::getWidth() const{
	return _Width;
}

int				SDL2::getHeight() const{
	return _Height;
}

int				SDL2::getKey() const{
	return _Key;
}

bool			SDL2::getFlag() const{
	return _Flag;
}

int 			SDL2::getSpeed() const{
	return _Speed;
}

//SETTER

void			SDL2::setFlag(bool val){
	_Flag = val;
}

//C

SDL2			*createPlayer(int Y, int X){
	return new SDL2(Y, X);
}

void 			deletePlayer(SDL2 *obj){
	delete obj;
}

void			SDL2::Error(std::string str, const char * s1){
	throw NibblerException(_myError->CreatMe(str.c_str(), s1));
	Stop();
}

SDL2::~SDL2(){}

//NibblerException

std::string 	SDL2::NibblerException::CreatMe(char *s1, char *s2){
	std::stringstream	tmp;

	tmp << s1 << s2;
	return (tmp.str());
}

std::string 	SDL2::NibblerException::CreatMe(char *s1, const char *s2){
	std::stringstream	tmp;

	tmp << s1 << s2;
	return (tmp.str());
}

std::string 	SDL2::NibblerException::CreatMe(const char *s1, const char *s2){
	std::stringstream	tmp;

	tmp << s1 << s2;
	return (tmp.str());
}

SDL2::NibblerException::NibblerException(std::string str) throw() : std::runtime_error(str){
	return ;
}

SDL2::NibblerException::~NibblerException() throw() {
	return ;	
}

const char* 	SDL2::NibblerException::NibblerException::what() const throw() {
	std::string ret = "Nibbler Exception : " + std::string(std::runtime_error::what());
	return ret.c_str();
}
