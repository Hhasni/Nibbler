#include <dlfcn.h>
#include <stdexcept>
#include "Area.hpp"
#include "Snake.hpp"
#include "Fruit.hpp"
#include "Timer.hpp"
#include "IGui.hpp"

# define NUM1 49
# define NUM2 50
# define NUM3 51
# define ESC 27

# define NCURSE	"./lib_ncurses.so"
# define OENPGL	"./lib_OpenGL.so"
# define SDL2	"./lib_SDL2.so"

void	dlerror_wrapper(void){
	std::cerr << "Error: " << dlerror() << std::endl;
	exit(EXIT_FAILURE);
}

bool	ft_check(int x, int y){
	if ((x < 10 || x > 50) || (y < 10 || y > 50))
		throw std::string("Error Size must be between 10 and 50");
	return true;
}

void	ft_score(int len){
	std::cout << "Your Score : " + std::to_string(len-3) + "pts" << std::endl;
	return;
}

int		ft_nibbler(char **av, std::string str){
	ft_check(std::stoi(av[1]), std::stoi(av[2]));
	Area		 	map = Area(std::stoi(av[1]), std::stoi(av[2]));
	Fruit			fruit = Fruit();
	Timer			timer = Timer();
	void			*dl_handle;
	IGui			*(*PlayerCreator)(int, int);
	IGui			*myGui;
 	Snake			player = Snake(map.getMaxY()/2, 4);

	dl_handle = dlopen(str.c_str(), RTLD_LAZY | RTLD_LOCAL);
	if (!dl_handle)
		dlerror_wrapper();
	//CREATION
	PlayerCreator = (IGui *(*)(int, int)) dlsym(dl_handle, "createPlayer");
	if (!PlayerCreator)
		dlerror_wrapper();
	myGui = PlayerCreator(map.getMaxY(), map.getMaxX());
	for (int i = 0; i < player.getLen(); i++){
	 	std::pair<int, int> 	ItemPair = player.getPair(i);
		myGui->DrawASquare(ItemPair.first, ItemPair.second);
	}
	myGui->Refresh();
	while (player.getLife())
	{
		myGui->DisplayUI(timer.getTimeSecond(), player.getPts());
		if (player.getAvailable()){
			if (myGui->RecoverKeyPressed(true))
				player.setAvailable(false);
		}
		else
			myGui->RecoverKeyPressed(false);
		switch(myGui->getKey()){
			case (27):
				player.setLife(false);
				goto quit;
				break;
			case (3):
				if (player.getOri() != 1)
					player.setOri(3);
				break;
			case (1):
				if (player.getOri() != 3)
					player.setOri(1);
				break;
			case (2):
				if (player.getOri() != 0)
					player.setOri(2);
				break;
			case (0):
				if (player.getOri() != 2)
					player.setOri(0);
				break;
			case (NUM1):
				myGui->Stop();
				ft_nibbler(av, NCURSE);
				break;
			case (NUM2):
				myGui->Stop();
				ft_nibbler(av, OENPGL);
				break;
			case (NUM3):
				myGui->Stop();
				ft_nibbler(av, SDL2);
				break;
		}
		if (timer.getTimeInter() > static_cast<unsigned long>(myGui->getSpeed() - player.getLen())){
			timer.Reset();
			player.setAvailable(true);
			switch(player.getOri()){
				case (1):
					map.moveDown(player);
					break;
				case (2):
					map.moveLeft(player);
					break;
				case (3):
					map.moveUp(player);
					break;
				default:
					map.moveRight(player);
			}
			if (player.tryEat(fruit))
				myGui->Eated();
			if (player.getLife()){
				myGui->DrawRock(map.rx, map.ry);
				myGui->DrawMove(player.getListX(), player.getListY());
				myGui->Refresh();
			}
			if (!fruit.getLife())
				map.Spawner(player, fruit);
			if (fruit.getLife())
				myGui->DrawFruit(fruit.getPosY(), fruit.getPosX());
		}
		if (!player.getLife()){
			if (myGui->GameOver()){
				myGui->Stop();
				ft_nibbler(av, str);
				return (EXIT_SUCCESS);
			}
		}
	}
	myGui->Refresh();
	quit:
	myGui->Stop();
	ft_score(player.getLen());
	//DESTRUCTION
	IGui			*(*PlayerDestructor)(IGui *);

	PlayerDestructor = (IGui *(*)(IGui*)) dlsym(dl_handle, "deletePlayer");
	if (!PlayerDestructor)
		dlerror_wrapper();
	dlclose(dl_handle);
   	return (EXIT_SUCCESS);
}


void ft_usage(){
	std::cerr << "Usage : ./nibbler [LINES] [COLUMNS] [LIB]" << std::endl;
	std::cerr << "LIB =\t1 --> Ncurse" << std::endl;
	std::cerr << "\t2 --> OpenGL" << std::endl;
	std::cerr << "\t3 --> SDL2" << std::endl;
	std::cerr << "\tdefault --> SDL2" << std::endl;

}

std::string ft_selectLib(char**av){
	if (atoi(av[3]) == 1)
		return NCURSE;
	if (atoi(av[3]) == 2)
		return OENPGL;
	else
		return SDL2;
}

int main(int ac, char **av){
	std::string str1 = NCURSE;
	std::string str2 = OENPGL;
	std::string str3 = SDL2;
	std::string lib = NCURSE;
	
	if (ac < 3){
		ft_usage();
		return (-1);
	}
	if (ac == 4)
		lib = ft_selectLib(av);
	try{
		ft_nibbler(av, lib);
	}
	catch(std::exception &e){
		std::cerr << e.what() << std::endl;
	}
	catch(std::string &e){
		
		std::cerr << "Usage : " + e << std::endl;
	}
	return (0);
}
