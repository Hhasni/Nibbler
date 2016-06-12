#ifndef TIMER_HPP
# define TIMER_HPP

# include <ctime>

class Timer{
	public:
		Timer();
		~Timer();
		unsigned long		getTime() const;
		unsigned long		getElapsedTime() const;
		unsigned long		getTimeInter() const;
		int					getTimeSecond() const;
		void				Reset();
		void				setTime(unsigned long val);

	private:
		unsigned long 		_StartTime;
		unsigned long 		_ElapsedTime;

	protected:

};

#endif