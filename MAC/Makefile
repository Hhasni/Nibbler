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

SRCS =		Main.cpp \
			Fruit.cpp \
			Snake.cpp \
			Timer.cpp \
			Area.cpp

OBJS =		$(SRCS:.cpp=.o)

CC =		clang++

CFLAGS =	-Wall -Wextra -Werror 

DLFLAG =	-shared -fPIC

OPENGL_FLAG = -L ./lib/GLFW -lglfw3 -framework Cocoa -framework OpenGL -framework GLUT -framework IOKit -framework CoreVideo

SDL_FLAG =  -L ./lib/SDL2 -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image -lbz2 -lz -lfreetype -framework CoreMIDI -framework Carbon -framework AudioToolbox -framework AudioUnit -framework OpenGL -framework AppKit -framework IOKit -framework CoreServices -framework OpenAL -framework ForceFeedback

INC_SDL = 	-I ./lib/SDL2/include

INC_OPENGL = -I ./lib/GLFW/include

RM =		rm -rf

all:		 $(LIB_SDL) $(LIB_NCURSES) $(LIB_OPENGL) $(NAME)

$(NAME):	$(OBJS)
			@echo "\n\r\033[38;5;11m⌛  MAKE $(NAME) plz wait...\033[0m\033[K"
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIB_SDL)
			@echo -en "\r\033[38;5;22m✅  MAKE $(NAME)\033[0m\033[K"
			@echo "💟"

$(LIB_NCURSES):
			@$(CC) $(CFLAGS) $(DLFLAG) -lncurses $(NCURSES_SRC) -o $(LIB_NCURSES) -I ./

$(LIB_OPENGL):
			@$(CC) $(CFLAGS) -Wno-deprecated $(DLFLAG) $(OPENGL_SRC) -o $(LIB_OPENGL) $(OPENGL_FLAG) -I ./ $(INC_OPENGL) 

$(LIB_SDL):
			@$(CC) $(CFLAGS) $(DLFLAG) $(SDL_SRC) -o $(LIB_SDL) $(SDL_FLAG) -I ./ $(INC_SDL)

%.o:		$(CPATH)%.cpp
			@$(CC) $(CFLAGS) -c $<

clean:
			@$(RM) $(LIB_NCURSES) $(LIB_OPENGL) $(LIB_SDL) $(OBJS)
			@echo -en "\r\033[38;5;124m❌  CLEAN $(NAME) \033[0m\033[K"

fclean:		clean
			@$(RM) $(NAME)
			@echo -en "\r\033[38;5;124m❌  FCLEAN $(NAME) \033[0m\033[K"

re:			fclean all
