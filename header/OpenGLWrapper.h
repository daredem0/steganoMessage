/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.06.15
 * @brief
 */
/* 
 * File:   OpenGLWrapper.h
 * Author: Florian Leuze
 *
 * Created on 15. Juni 2019, 13:08
 */

#ifndef OPENGLWRAPPER_H
#define OPENGLWRAPPER_H
#define GLEW_STATIC
#include <GL/glew.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <sstream>
#include "ErrorHandler.h"
//#include <thread>


using namespace std;

class Size{
public:
    Size();
    Size(int X, int Y);
    Size(const Size& orig);
    virtual ~Size();
    int getX();
    int getY();
    void setX(int X);
    void setY(int Y);
    static double getFactor(int x, int y);
private:
    int x;
    int y;
};

class OpenGLWrapper {
public:
    OpenGLWrapper();
    OpenGLWrapper(ErrorHandler *errHandle, std::string t, unsigned char* d, std::string ft, int width, int height, int (*f)(int));
    OpenGLWrapper(const OpenGLWrapper& orig);
    virtual ~OpenGLWrapper();
    int run();
    int close();
private:
    int init();
    int setupShaders();
    int setupTexture();
    int openGLRT();
    int cleanup();
    ErrorHandler *err;
    sf::ContextSettings settings;
    int error;
    Size window;
    Size screen;
    Size image;
    GLfloat facX;
    GLfloat facY;
    std::string title;
    unsigned char* data;
    std::string type;
    sf::Window *win;
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLuint shaderProgram;
    GLint posAttrib;
    GLint colAttrib;
    GLint texAttrib;
    GLuint vertexShader;
    GLuint fragmentShader;
};

#endif /* OPENGLWRAPPER_H */

