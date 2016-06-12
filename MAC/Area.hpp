#ifndef AREA_HPP
# define AREA_HPP

# include "Snake.hpp"
# include <iostream>

class Area{
	public:
		int			rx;
		int			ry;

		Area();
		Area(int, int);
		Area(Area const & src);
		Area & operator=(Area const & src);
		virtual ~Area();

		void		moveUp(Snake &);
		void		moveDown(Snake &);
		void		moveLeft(Snake &);
		void		moveRight(Snake &);
		void		Spawner(Snake&, Fruit &);


		void		setMaxX(int);
		void		setMaxY(int);

		int			getMaxX() const;
		int			getMaxY() const;
	protected:

	private:
		int			_MaxX;
		int			_MaxY;

};

#endif