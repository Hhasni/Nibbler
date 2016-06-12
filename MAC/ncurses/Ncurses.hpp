#ifndef NCURSES_HPP
# define NCURSES_HPP

# include "IGui.hpp"
# include <stdexcept>
# include <cstdlib>
# include <curses.h>
# include <sstream>
# include <iostream>
# include <unistd.h>

# define NUM1 49
# define NUM2 50
# define NUM3 51
# define ESC 27
# define KEY_P 112

class Ncurses : public IGui
{
	public:
		Ncurses(int, int);
		virtual	~Ncurses();
		int				getKey() const;
		int				getSpeed() const;
		void			DrawRock(int, int);
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
		Ncurses();
		void			Pause();
		int				getHeight() const;
		int				getWidth() const;
		bool			getFlag() const;
		void			setFlag(bool);
		void			resize();
		void			Refresh(WINDOW *);
		void			DrawBorder(WINDOW *);
		void			DrawBorder();
		bool 			_Flag;
		int				_Speed;		
		int 			_Height;
		int				_Width;
		int				_Key;
		WINDOW *		_Win;	
		WINDOW *		_GameOver;

		class NibblerException : public std::runtime_error
		{
			public:
				NibblerException(std::string str) throw();
				~NibblerException() throw();
				virtual const char * what() const throw();

			private:
				NibblerException & 	operator=(NibblerException const & src);
		};
};

extern "C"{
	Ncurses 			*createPlayer(int, int);
	void				deletePlayer(Ncurses *obj);
}


#endif