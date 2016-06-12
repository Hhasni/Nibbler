#ifndef IGUI_HPP
# define IGUI_HPP

# include <list>

class IGui
{
	public:
		virtual void			DrawRock(int, int) = 0;
		virtual void			DrawASquare(int, int) = 0;
		virtual void			DrawMove(std::list<int>, std::list<int>) = 0;
		virtual void			DrawFruit(int, int) = 0;
		virtual void			DisplayUI(int, int) = 0;
		virtual bool			RecoverKeyPressed(bool) = 0;
		virtual void			Refresh() = 0;
		virtual void			Stop() = 0;
		virtual	bool			GameOver() = 0;
		virtual void			Eated() = 0;
		virtual int				getKey() const = 0;
		virtual	int				getHeight() const = 0;
		virtual	int				getWidth() const = 0;
		virtual int				getSpeed() const = 0;

};

#endif