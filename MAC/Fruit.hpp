#ifndef FRUIT_HPP
# define FRUIT_HPP

class Fruit{
	public:
		Fruit();
		~Fruit();
		int		getPosX() const;
		int		getPosY() const;
		int		getTime() const;
		bool	getLife() const;
		
		void	setPosX(int);
		void	setPosY(int);
		void	setTime(int);
		void	setLife(bool);

		void	Spawner(int, int);

	protected:

	private:
		int		_Life;
		int		_Time;
		int		_PosX;
		int		_PosY;

};

#endif