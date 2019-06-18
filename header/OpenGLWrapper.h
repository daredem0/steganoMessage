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
#include <SFML/OpenGL.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <sstream>
#include "ErrorHandler.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
//#include <thread>


using namespace std;

/**
 *@brief Size is a simple class that can either be used to store a 2D coordinate or the size of a plane.
 */
class Size{
public:
    //CONSTRUCTORS/DECONSTRUCTORS/************************************************************/
    /**
    * @brief Standard constructor. 
    */
    Size();
    /**
    * @brief Non-Standard constructor. Stores the values automatically
     * @param int X - x value of the coordinate/width of the plane
     * @param int Y - y value of the coordinate/height of the plane 
    */
    Size(int X, int Y);
    /**
     * @brief Copy Constructor. 
     * @param orig - Reference to original Size-type object
     */
    Size(const Size& orig);
    /**
     * Standard deconstructor.
     */
    virtual ~Size();
    
    ///////////////////////////////////************************************************************/
    /**GETTERS**///////////////////////
    ///////////////////////////////////
    /**
     * @brief Getter for x value of the coordinate/width of the plane
     * @return integer value containing the x coordiante/width
     */
    int getX();
    /**
     * @brief Getter for y value of the coordinate/height of the plane
     * @return integer value containing the y coordiante/height
     */
    int getY();
    /**
     * @brief Setter for x value of the coordinate/width of the plane
     * @param int X -  value containing the x coordiante/width
     */
    void setX(int X);
    /**
     * @brief Setter for y value of the coordinate/height of the plane
     * @param int Y -  value containing the y coordiante/height
     */
    void setY(int Y);
    /**
     * @brief Static function that gives a resizing factor for the vertices. Basically just builds the quotient
     * @param int X -  value of the divisor
     * @param int Y - value of the dividend
     */
    static double getFactor(int x, int y);
private:
    int x; /**< x coordinate/width*/
    int y; /**< y coordinate/height*/
};

/**
 *@brief OpenGLWrapper gives a C++ like interface to easily build an OpenGL Window. It takes a lot of freedom away but it offers a very easy to use interface. 
 * It depends on OpenGL, SFML, GLFW and GLEW (as u can see in the includes).
 */
class OpenGLWrapper {
public:
    //CONSTRUCTORS/DECONSTRUCTORS/************************************************************/
    /**
    * @brief Standard constructor. 
    */
    OpenGLWrapper();
    /**
    * @brief Non-Standard constructor. Initializes the OpenGLWrapper object automatically. After calling this constructor you only have to OpenGLWrapper::run()
     * @param ErrorHandler *errHandle - Pointer to errorHandler or other objet that offers ->printLog(std::string log) functionality. 
     * @param std::string t - Title of the window
     * @param unsigned char* d - Pointer to the image data
     * @param std:.string ft - Type of Image data. For possible values check SFML documentation
     * @param int width - width of the image file
     * @param int height - height of the image file
     * @param int (*f)(int) - Callback function of type int f(int); constructor will call this function if something goes horribly wrong. Provide a callback that will deal with it.
    */
    OpenGLWrapper(ErrorHandler *errHandle, std::string t, unsigned char* d, std::string ft, int width, int height, int (*f)(int));
    /**
     * @brief Copy Constructor. 
     * @param orig - Reference to original OpenGLWrapper-type object
     */
    OpenGLWrapper(const OpenGLWrapper& orig);
    /**
     * Standard deconstructor.
     */
    virtual ~OpenGLWrapper();
    /**
     * @brief Calls the OpenGL Runtime. This will open the OpenGL window (call of overloaded Constructor is absolutely necassary before running!) and open it endlessly. 
     * Here is a endless loop that will only end when the window is closed or the user hits escape. No multithreading supported as of now (steganoMessage 0.3)
     * @return Returns integer containing error code
     */
    int run();
    /**
     * @brief Cleans up. Calling before init with constructor can do many many bad things. Dont do it.
     * @return Returns integer containing error code
     */
    int close();
private:
    Size window; /**< Stores the values of the OpenGL Window*/
    Size screen;/**< Stores the values of the current screen*/
    Size image;/**< Stores the values of the image*/
    GLfloat facX;/**< Stretch factor for vertice*/
    GLfloat facY;/**< Stretch factor for vertice*/
    std::string title;/**< Title of the OpenGL Window*/
    unsigned char* data;/**< Pointer to image data*/
    std::string type;/**< Type of image data*/
    sf::Window *win; /**< SFML Window object*/
    GLuint vao; /**< Pointer to Vertex Array. Needed for the vertex shader*/
    GLuint vbo; /**< Pointer to Vertex Buffer. Buffers data for the vertex shader*/
    GLuint ebo; /**< Pointer to element Array. This is needed to Organize the structure of the vertice*/
    GLuint shaderProgram; /**< linked shader Program*/
    GLint posAttrib; /**< Location of the position attribute in the vertice*/
    GLint colAttrib; /**< Location of the color attribute in the vertice*/
    GLint texAttrib; /**< Location of the Texture attribute in the vertice*/
    GLuint vertexShader; /**< Created Vertex Shader*/
    GLuint fragmentShader; /**< Created Fragment Shader*/
    
    glm::mat4 model; /**< Transformation matrix*/
    GLint uniTrans; /** Address of transformation uniform*/
    GLint uniModel;
    glm::mat4 view; /**< View matrix - not implemented as of now (0.43)*/
    GLint uniView; /**< Address of view uniform*/
    glm::mat4 proj; /**< Projection matrix*/
    GLint uniProj; /**< Address of projection uniform*/
    float degree; /**< Degree value for rotation*/
    float aspect; /**< Aspect value needed to keep the proportions right*/
     
    ErrorHandler *err; /**< Pointer to ErrorHandler*/
    sf::ContextSettings settings; /**< SFML Settings object*/
    
    /**
     * @brief Initializes the SFML Window and GLEW (which does the ugly job of finding out what OpenGL functions the local GPU offers for us)
     * @return Returns integer containing error code
     */
    int init();
    /**
     * @brief Sets up the shader configuration. Usage of a color shader is prepared but turned off for the moment (0.3)
     * @return Returns integer containing error code
     */
    int setupShaders();
    /**
     * @brief Sets up the texture Configuration.
     * @return Returns integer containing error code
     */
    int setupTexture();
    /**
     * @brief Contains the OpenGL Runtime loop and the event handling for the open Window
     * @return Returns integer containing error code
     */
    int openGLRT();
    /**
     * @brief Deletes the shaderProgram, fragmentShader, vertexShader, ebo and vbo buffers as well as vao Array. It terminates glfw, closes the sfml window object and finally delets the window pointer.
     * @return Returns integer containing error code
     */
    int cleanup();
};

#endif /* OPENGLWRAPPER_H */

