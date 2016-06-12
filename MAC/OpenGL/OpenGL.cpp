#include "OpenGL.hpp"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <GLUT/glut.h>

OpenGL::OpenGL(int Y, int X):_Height(Y),_Width(X){
	double	ratio;
	int		width;
	int		height;
	_Speed = 150;
	_Key = 0;
	_Flag = true;
	if (!glfwInit()){
		Stop();
		throw NibblerException("glfwInit error");
	}
	_Win = glfwCreateWindow(500, 500, "Nibbler GLFW2D", NULL, NULL);
	if (!_Win){
		Stop();
		throw NibblerException("glfwInit error");
	}
	glfwGetFramebufferSize(_Win, &width, &height);
	ratio = static_cast<double>(width) / height;
	_Case_W = static_cast<double>(width) / _Width;
	_Case_W /= width/2;
	_Case_H = static_cast<double>(height) / _Height;
	_Case_H /= height/2;
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1.02, 1, 1, -1);
	glfwSwapBuffers(_Win);
	glfwPollEvents();
}

void			OpenGL::DrawRock(int X, int Y){
	glBegin(GL_QUADS);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3d(-1.f+(_Case_W * X),1.f-(_Case_H * Y), 0.f);
		glVertex3d(-1.f+(_Case_W * (X+1)), 1.f-(_Case_H * Y), 0.f);
		glVertex3d(-1.f+(_Case_W * (X+1)), 1.f-(_Case_H * (Y+1)), 0.f);
		glVertex3d(-1.f+(_Case_W * X), 1.f-(_Case_H * (Y+1)), 0.f);
	glEnd();
}

void			OpenGL::DrawBorder(){
	glBegin(GL_QUADS);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3d(-1.f, 1.f, 0.f);
		glVertex3d(-1.f, -1.f+(_Case_H), 0.f);
		glVertex3d(-1.f+_Case_W, -1.f+(_Case_H), 0.f);
		glVertex3d(-1.f+_Case_W, 1.f, 0.f);
	glEnd();
	glBegin(GL_QUADS);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3d(1.f, 1.f, 0.f);
		glVertex3d(1.f, -1.f+(_Case_H), 0.f);
		glVertex3d(1.f-_Case_W, -1.f+(_Case_H), 0.f);
		glVertex3d(1.f-_Case_W, 1.f, 0.f);
	glEnd();
	glBegin(GL_QUADS);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3d(1.f, 1.f-_Case_H, 0.f);
		glVertex3d(-1.f, 1.f-_Case_H, 0.f);
		glVertex3d(-1.f, 1.f, 0.f);
		glVertex3d(1.f, 1.f, 0.f);
	glEnd();
	glBegin(GL_QUADS);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3d(1.f, -1.f+(_Case_H * 2), 0.f);
		glVertex3d(-1.f, -1.f+(_Case_H * 2), 0.f);
		glVertex3d(-1.f, -1.f+_Case_H, 0.f);
		glVertex3d(1.f, -1.f+_Case_H, 0.f);
	glEnd();
}

void			OpenGL::DrawASquare(int X, int Y){
	glBegin(GL_QUADS);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3d(-1.f+(_Case_W * X),1.f-(_Case_H * Y), 0.f);
		glVertex3d(-1.f+(_Case_W * (X+1)), 1.f-(_Case_H * Y), 0.f);
		glVertex3d(-1.f+(_Case_W * (X+1)), 1.f-(_Case_H * (Y+1)), 0.f);
		glVertex3d(-1.f+(_Case_W * X), 1.f-(_Case_H * (Y+1)), 0.f);
	glEnd();
}

void			OpenGL::DrawASquare(int X, int Y, int W, bool flag){
	glBegin(GL_QUADS);
	if (flag)
		glColor3f(0.f, 1.f, 0.f);
	else
		glColor3f(1.f, 0.f, 0.f);
		glVertex3d(-1.f+(_Case_W * X),1.f-(_Case_H * Y), 1.f);
		glVertex3d(-1.f+(_Case_W * (X+W)), 1.f-(_Case_H * Y), 0.f);
		glVertex3d(-1.f+(_Case_W * (X+W)), 1.f-(_Case_H * (Y+(X/3))), 0.f);
		glVertex3d(-1.f+(_Case_W * X), 1.f-(_Case_H * (Y+(X/3))), 0.f);
	glEnd();
}

void			OpenGL::DrawMove(std::list<int> Lx, std::list<int> Ly){
	DrawBorder();

	std::list<int>::iterator it1 = Lx.begin();
	std::list<int>::iterator it2 = Ly.begin();
	if (it1 != Lx.end()){
		for (it1 = it1; it1 != Lx.end(); it1++){
			DrawASquare(*it1, *it2);
			it2++;
		}
	}
}

void			OpenGL::Eated(){
}

void			OpenGL::DrawFruit(int Y, int X){
	glBegin(GL_QUADS);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3d(-1.f+(_Case_W * X),1.f-(_Case_H * Y), 0.f);
		glVertex3d(-1.f+(_Case_W * (X+1)), 1.f-(_Case_H * Y), 0.f);
		glVertex3d(-1.f+(_Case_W * (X+1)), 1.f-(_Case_H * (Y+1)), 0.f);
		glVertex3d(-1.f+(_Case_W * X), 1.f-(_Case_H * (Y+1)), 0.f);
	glEnd();
}

bool			OpenGL::RecoverKeyPressed(bool myflag){
	if (!myflag)
		return (false);
	else if (glfwGetKey(_Win, GLFW_KEY_UP) == GLFW_PRESS)
		_Key = GLFW_KEY_UP;
	else if (glfwGetKey(_Win, GLFW_KEY_DOWN) == GLFW_PRESS)
		_Key = GLFW_KEY_DOWN;
	else if (glfwGetKey(_Win, GLFW_KEY_LEFT) == GLFW_PRESS)
		_Key = GLFW_KEY_LEFT;
	else if (glfwGetKey(_Win, GLFW_KEY_1) == GLFW_PRESS)
		_Key = GLFW_KEY_1;
	else if (glfwGetKey(_Win, GLFW_KEY_2) == GLFW_PRESS)
		_Key = GLFW_KEY_2;
	else if (glfwGetKey(_Win, GLFW_KEY_3) == GLFW_PRESS)
		_Key = GLFW_KEY_3;
	else if (glfwGetKey(_Win, GLFW_KEY_RIGHT) == GLFW_PRESS)
		_Key = GLFW_KEY_RIGHT;
	else if (_Key != -1 && glfwGetKey(_Win, GLFW_KEY_P) == GLFW_PRESS)
		Pause();
	else if (glfwGetKey(_Win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		_Key = GLFW_KEY_ESCAPE;
	return (true);
}

void			OpenGL::DisplayUI(int mytime, int pts){
	std::stringstream str;
	str << "Time = " << mytime << " points = " << pts;

	glRasterPos2f(-1,-1.02);
	for (int i = 0; i < static_cast<int>(str.str().length()); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, str.str()[i]);
	}
	mytime = mytime + pts - pts;
}

void			OpenGL::Pause(){
	bool 	end = true;
	bool 	plop = true;
	while (plop)
	{
		glfwPollEvents();
		if (glfwGetKey(_Win, GLFW_KEY_P) == GLFW_RELEASE)
			plop = false;
	}
	while (end){
		glfwPollEvents();
		if (glfwGetKey(_Win, GLFW_KEY_P) == GLFW_PRESS){
			_Key = -1;
			end = false;
		}
		if (glfwGetKey(_Win, GLFW_KEY_ESCAPE) == GLFW_PRESS){
			_Key = GLFW_KEY_ESCAPE;			
			end = false;
		}
	}	
}

void 			OpenGL::ft_print_GameOver(){
	std::stringstream str_exit;
	std::stringstream str_retry;
	str_retry << "RETRY";
	str_exit << "EXIT";

	glColor3f(1.f, 1.f, 1.f);
	glRasterPos2f(-0.1,+0.3);
	for (int i = 0; i < static_cast<int>(str_retry.str().length()); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str_retry.str()[i]);
	}
	glColor3f(1.f, 1.f, 1.f);
	glRasterPos2f(-0.1,-0.1);
	for (int i = 0; i < static_cast<int>(str_exit.str().length()); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str_exit.str()[i]);
	}	
}

bool			OpenGL::GameOver(){
	bool myMenuFlag = true;
	glClear(GL_COLOR_BUFFER_BIT);
	DrawASquare(_Width/3, _Height/3, _Width/3, myMenuFlag);
	_Key = -1;
	ft_print_GameOver();
	glfwSwapBuffers(_Win);
	while (_Key != GLFW_KEY_ESCAPE && _Key != GLFW_KEY_ENTER)
	{
		usleep(90000);
		glfwPollEvents();
		if (glfwGetKey(_Win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			_Key = GLFW_KEY_ESCAPE;
		else if (glfwGetKey(_Win, GLFW_KEY_ENTER) == GLFW_PRESS)
			_Key = GLFW_KEY_ENTER;
		else if (glfwGetKey(_Win, GLFW_KEY_UP) == GLFW_PRESS)
			_Key = GLFW_KEY_UP;
		else if (glfwGetKey(_Win, GLFW_KEY_DOWN) == GLFW_PRESS)
			_Key = GLFW_KEY_DOWN;

		if (_Key == GLFW_KEY_DOWN || _Key == GLFW_KEY_UP){
			usleep(200000);
			glClear(GL_COLOR_BUFFER_BIT);
			myMenuFlag = !myMenuFlag;
			if (myMenuFlag)
				DrawASquare(_Width/3, _Height/3, _Width/3, myMenuFlag);
			else
				DrawASquare(_Width/3, _Height/2, _Width/3, myMenuFlag);
			ft_print_GameOver();
			glfwSwapBuffers(_Win);
			_Key = -1;
		}
	}
	if (_Key == GLFW_KEY_ESCAPE)
		return(false);
	return (myMenuFlag);
}

void			OpenGL::Refresh(){
	glfwSwapBuffers(_Win);
	glfwPollEvents();
	glClear(GL_COLOR_BUFFER_BIT);
}

void			OpenGL::Stop(){
	glfwDestroyWindow(_Win);
	glfwTerminate();
}

//GETTER

int				OpenGL::getWidth() const{
	return _Width;
}

int				OpenGL::getHeight() const{
	return _Height;
}

int				OpenGL::getKey() const{
	switch(_Key){
		case (GLFW_KEY_ESCAPE):
			return (ESC);
			break;
		case (GLFW_KEY_UP):
			return (3);
			break;
		case (GLFW_KEY_DOWN):	
			return (1);
			break;
		case (GLFW_KEY_LEFT):
			return (2);
			break;
		case (GLFW_KEY_RIGHT):
			return (0);
			break;
		case (GLFW_KEY_1):
			return (GLFW_KEY_1);
			break;
		case (GLFW_KEY_2):
			return (GLFW_KEY_2);
			break;
		case (GLFW_KEY_3):
			return (GLFW_KEY_3);
			break;
	}
	return _Key;
}

bool			OpenGL::getFlag() const{
	return _Flag;
}

int 			OpenGL::getSpeed() const{
	return _Speed;
}

//SETTER

void			OpenGL::setFlag(bool val){
	_Flag = val;
}

//C

OpenGL			*createPlayer(int Y, int X){
	return new OpenGL(Y, X);
}

void 			deletePlayer(OpenGL *obj){
	delete obj;
}

OpenGL::~OpenGL(){}

OpenGL::NibblerException::NibblerException(std::string str) throw() : std::runtime_error(str){
	return ;
}

OpenGL::NibblerException::~NibblerException() throw() {
	return ;	
}

const char* 	OpenGL::NibblerException::NibblerException::what() const throw() {
	std::string ret = "Nibbler Exception : OpenGL Error : " + std::string(std::runtime_error::what());
	return ret.c_str();
}
