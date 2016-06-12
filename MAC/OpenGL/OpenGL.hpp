#ifndef OPENGL_HPP
# define OPENGL_HPP

# include <stdexcept>
# include <IGui.hpp>
# include <GLFW/glfw3.h>

# define ESC 27

class OpenGL : public IGui
{
	public:
		OpenGL(int, int);
		virtual ~OpenGL();
		int				getKey() const;
		int				getSpeed() const;
		void			DrawRock(int, int);
		void			DrawASquare(int, int);
		void 			DrawASquare(int, int, int, bool);
		void 			ft_print_GameOver();
		void			DrawMove(std::list<int>, std::list<int>);
		void			DrawFruit(int, int);
		void			DisplayUI(int, int);
		bool			RecoverKeyPressed(bool);
		void			Refresh();
		void			Stop();
		bool			GameOver();
		void			Eated();


	private:
		OpenGL();
		void			DrawBorder();
		int				getWidth() const;
		int				getHeight() const;
		bool			getFlag() const;
		void			setFlag(bool);
		void			Pause();
		bool 			_Flag;
		int				_Speed;
		int 			_Height;
		int				_Width;
		int				_Key;
		double			_Case_H;
		double			_Case_W;
		GLFWwindow*		_Win;

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
	OpenGL 				*createPlayer(int, int);
	void				deletePlayer(OpenGL *obj);
}


#endif