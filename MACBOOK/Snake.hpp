#ifndef SNAKE_HPP
# define SNAKE_HPP

# include <vector>
# include <list>
# include "Fruit.hpp"

class Snake{

	public:
		Snake();
		Snake(int, int);
		Snake & operator=(Snake const & src);
		Snake(Snake const & src);
		virtual ~Snake();

		bool		tryEat(Fruit &);
		void		testCollision(int,int);

		void		setLife(bool);
		void		setAvailable(bool);
		void		setPosX(int);
		void		setPosY(int);
		void		setLen(int);
		void		setOri(int);
		void		setTab(int, int);

		bool		getLife() const;
		bool		getAvailable() const;
		int			getPosX() const;
		int			getPosY() const;
		int			getLen() const;
		int			getPts() const;
		int			getOri() const;
		std::list<int>			getListX() const;
		std::list<int>			getListY() const;
		std::pair<int, int>		getPair(int) const;


	private:
		int			_Len;
		int			_Pts;
		int			_Ori;
		int			_PosX;
		int			_PosY;
		bool		_Life;
		bool		_Available;
		std::vector<std::pair<int, int> > 	_Tab;

};

#endif