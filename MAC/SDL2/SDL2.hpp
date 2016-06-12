#ifndef SDL2_HPP
# define SDL2_HPP

# include <IGui.hpp>

# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_mixer.h>
# include <SDL2/SDL_image.h>
# include <list>
# include <stdexcept>
# include <iostream>
# include <sstream>
# define ESC 27


class SDL2 : public IGui
{
	public:
		SDL2(int, int);
		virtual ~SDL2();
		int				getKey() const;
		int				getSpeed() const;
		void			DrawASquare(int, int);
		void			DrawMove(std::list<int>, std::list<int>);
		void			DrawFruit(int, int);
		void			DisplayUI(int, int);
		bool			RecoverKeyPressed(bool);
		void			Refresh();
		void			Stop();
		bool			GameOver();
		void			Eated();

	private:
		SDL2();
		int				getWidth() const;
		int				getHeight() const;
		bool			getFlag() const;
		void			setFlag(bool);
		void			Error(std::string , const char *);
		void			Pause();
		void			DrawBorder();
		void			DrawRock(int, int);
		void			DrawASquare(int, int, SDL_Texture*, double);
		void			Refresh(SDL_Renderer*);
		void			GenerateText(std::string, SDL_Renderer * ,SDL_Rect);
		bool 			_Flag;
		int 			_Height;
		int				_Width;
		int 			_Y;
		int				_X;
		int				_Key;
		int				_Vol;
		int				_Dir;
		int				_Speed;
		double			_Rot;
		int 			_GUIHeigh;
		double			_Case_H;
		double			_Case_W;
		SDL_Window*		_Win;
		SDL_Renderer* 	_Render;
		SDL_Renderer*	_GameOver;
		SDL_Rect 		_GuiBox;
		SDL_Color		_textColor;
		SDL_Surface*	_Text;
		TTF_Font*		_Font;
		SDL_Texture*	_myTexture;
		SDL_Texture*	_HeadTexture;
		SDL_Texture*	_BodyTexture;
		SDL_Texture*	_TurnTexture;
		SDL_Texture*	_FruitTexture;
		SDL_Texture*	_WallTexture;
		SDL_Texture*	_RockTexture;
		Mix_Music*		_MainMusic;
		Mix_Chunk*		_DeathEffect;
		Mix_Chunk*		_EatEffect;

		std::list<double> _ListRot;

		class NibblerException : public std::runtime_error
		{
			public:
				NibblerException(std::string str) throw();
				std::string CreatMe(const char *, const char *);
				std::string CreatMe(char *, const char *);
				std::string CreatMe(char *, char *);
				~NibblerException() throw();
				virtual const char * what() const throw();

			private:
				NibblerException & 	operator=(NibblerException const & src);
		};
		NibblerException* _myError;

};

extern "C"{
	SDL2 				*createPlayer(int, int);
	void				deletePlayer(SDL2 *obj);
}


#endif