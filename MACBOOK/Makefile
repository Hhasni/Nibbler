NAME =		nibbler

CPATH =		./

NCURSES_PATH = 		./ncurses/
OpenGL_PATH = 		./OpenGL/
SDL_PATH = 			./SDL2/

NCURSES_SRC =		$(NCURSES_PATH)Ncurses.cpp
OPENGL_SRC =		$(OpenGL_PATH)OpenGL.cpp
SDL_SRC =			$(SDL_PATH)SDL2.cpp

#USLESSTART
NCURSES_OBJ =		$(SRCS:.cpp=.o)
OPENGL_OBJ =		OpenGL.o
SDL_OBJ =			SDL2.o
#USLESSEND

LIB_NCURSES =		lib_ncurses.so
LIB_OPENGL =		lib_OpenGL.so
LIB_SDL =			lib_SDL2.so

HPATH = 	./glfw-3.1.1/include \
			./SDL2-2.0.3/include 

SRCS =		Main.cpp \
			Fruit.cpp \
			Snake.cpp \
			Timer.cpp \
			Area.cpp

OBJS =		$(SRCS:.cpp=.o)

CC =		clang++

CFLAGS =	-Wall -Wextra -Werror 

DLFLAG =	-shared -fPIC

OPENGL_FLAG = /usr/local/lib/libglfw3.a -framework Cocoa -framework OpenGL -framework GLUT -framework IOKit -framework CoreVideo

SDL_FLAG =  -F/Library/Frameworks -framework SDL2 -I/Library/Frameworks/SDL2.framework/Headers/ -framework SDL2_ttf -I /Library/Frameworks/SDL2_ttf.framework/Headers -framework SDL2_mixer -I /Library/Frameworks/SDL2_mixer.framework/Headers/ -framework SDL2_image -I /Library/Frameworks/SDL2_image.framework/Headers/

RM =		rm -rf

all:		$(LIB_SDL) $(LIB_NCURSES) $(LIB_OPENGL) $(NAME)

$(NAME):	$(OBJS)
			@echo "\n\r\033[38;5;11m⌛  MAKE $(NAME) plz wait...\033[0m\033[K"
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIB_SDL)
			@echo -en "\r\033[38;5;22m✅  MAKE $(NAME)\033[0m\033[K"
			@echo "💟"

$(LIB_NCURSES):
			@$(CC) $(CFLAGS) $(DLFLAG) -lncurses $(NCURSES_SRC) -o $(LIB_NCURSES) -I ./

$(LIB_OPENGL):
			@$(CC) $(CFLAGS) -Wno-deprecated $(DLFLAG) $(OPENGL_SRC) -o $(LIB_OPENGL) $(OPENGL_FLAG) -I ./

$(LIB_SDL):
			@$(CC) $(CFLAGS) $(DLFLAG) $(SDL_SRC) -o $(LIB_SDL) $(SDL_FLAG) -I ./

%.o:		$(CPATH)%.cpp
			@$(CC) $(CFLAGS) -c $<

clean:
			@$(RM) $(LIB_NCURSES) $(LIB_OPENGL) $(LIB_SDL) $(OBJS)
			@echo -en "\r\033[38;5;124m❌  CLEAN $(NAME) \033[0m\033[K"

fclean:		clean
			@$(RM) $(NAME)
			@echo -en "\r\033[38;5;124m❌  FCLEAN $(NAME) \033[0m\033[K"

re:			fclean all
