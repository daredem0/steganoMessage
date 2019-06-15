/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.06.15
 * @brief
 */
/* 
 * File:   OpenGLWrapper.cpp
 * Author: Florian Leuze
 * 
 * Created on 15. Juni 2019, 13:08
 */

#include "../header/OpenGLWrapper.h"

//shader sources
const GLchar* vertexSource = R"glsl(
#version 150 core
in vec2 position;
in vec3 color;
in vec2 texcoord;

out vec3 Color;
out vec2 Texcoord;
void main()
{
    Color = color;
    Texcoord = texcoord;
    gl_Position = vec4(position, 0.0, 1.0);
}
)glsl";

//uniform vec3 triangleColor
const GLchar* fragmentSource = R"glsl(
#version 150 core
in vec3 Color;
in vec2 Texcoord;
out vec4 outColor;
uniform sampler2D tex;
void main()
{
    outColor = texture(tex, Texcoord);
}
)glsl";

OpenGLWrapper::OpenGLWrapper() {
    err = NULL;
    title = "";
}

OpenGLWrapper::OpenGLWrapper(ErrorHandler *errHandle, std::string t, unsigned char* d, std::string ft, int width, int height, int (*f)(int)) : err(errHandle), 
        title(t), data(d), type(ft), image(width, height){
    if(this->init() != ErrorHandler::errNoError ||  this->setupShaders() != ErrorHandler::errNoError || this->setupTexture() != ErrorHandler::errNoError){
        f(ErrorHandler::errOgl);
    }
}

OpenGLWrapper::OpenGLWrapper(const OpenGLWrapper& orig) {
}

OpenGLWrapper::~OpenGLWrapper() {
}

int OpenGLWrapper::run(){
    return this->openGLRT();
}

int OpenGLWrapper::close(){
    return this->cleanup();
}
    
int OpenGLWrapper::init(){
    std::stringstream ss;
    err->printLog("Init started\n");
    //Setup the open gl window
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.majorVersion = 3;
    settings.minorVersion = 2;
    
    //init glfw (we need it to get screen dimensions
    if(!glfwInit())
        return (error = ErrorHandler::errOglGlfw); //might be a problem

    //get resoultion of mains creen and store it
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    screen.setX(mode->width);
    screen.setY(mode->height);
    
    //generate the opengl window size we want
    if(image.getX() <= screen.getX()-300 && image.getX() <= screen.getX()-300){
        window.setX(image.getX() + 100);
        window.setY(image.getY() + 100);
    }
    else{
        window.setX(screen.getX() - 200);
        window.setY(screen.getY() - 200);
    }
    
    //get scaling factor for the vertices and store them
    facX = Size::getFactor(image.getX(), window.getX());
    facY = Size::getFactor(image.getY(), window.getY());
    
    err->printLog(ss.str());
    //finally build the opengl window with an epic title
    win = new sf::Window(sf::VideoMode(window.getX(), window.getY(), 32), title, sf::Style::Titlebar | sf::Style::Close, settings);
    Size pos(win->getPosition().x, win->getPosition().y);
    ss << "Genearte Position: " << win->getPosition().x << "/" << win->getPosition().y << std::endl;
    err->printLog(ss.str());
    win->setPosition(sf::Vector2i(pos.getX()+screen.getX()/2 - window.getX()/2, pos.getY()-screen.getY()/2+window.getY()/2));
    // Initialize GLEW    
    glewExperimental = GL_TRUE;
    glewInit();
    
    ss << "Init finished" << std::endl;
    err->printLog(ss.str());
    
    return ErrorHandler::errNoError;
}

int OpenGLWrapper::setupShaders(){
    std::stringstream ss;
    ss << "Setting up shaders" << std::endl;
    err->printLog(ss.str());
    // Create Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &vbo); 
    
    GLfloat vertices[] = {
        //Position                //Color          //Texcoords
        facX*(-1.0f), facY*( 1.0f), 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, //top-left
        facX*( 1.0f), facY*( 1.0f), 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, //top-right
        facX*( 1.0f), facY*(-1.0f), 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, //bottom-right
        facX*(-1.0f), facY*(-1.0f), 1.0f, 1.0f, 1.0f, 0.0f, 1.0f //bottom-left
    };
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //create an element array
    glGenBuffers(1, &ebo);
    
    GLuint elements[] = {
        0, 1, 2, 
        2, 3, 0
    };
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
    
    //Create vertex shaders
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    //error handling vertexShader
    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
        
    //retrieve log vertex shader
    char buffer[512];
    glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
        ss << "Vertex buffer: " << buffer << std::endl;
    if(ss.str() != "Vertex buffer: "){
        err->printLog(ss.str());
    }

    //Create fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    //error handling fragment shader
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    char bufferFrag[512];
    glGetShaderInfoLog(fragmentShader, 512, NULL, bufferFrag);
    ss << "Fragment buffer: " << bufferFrag << std::endl;
    if(ss.str() != "Fragment buffer: "){
        err->printLog(ss.str());
    }

    if(status != GL_TRUE){
        return ErrorHandler::errOglShader;
    }
    
    // Link the vertex and fragment shader into a shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    /*now we need to tell open gl how the attributes are formatted and ordered*/
    //get a reference to the position input in the vertex shader
    posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), 0);
    
    colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(2*sizeof(float)));
    
    texAttrib  = glGetAttribLocation(shaderProgram, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7*sizeof(float), (void*)(5*sizeof(float)));
    ss << "Shaders done" << std::endl;
    err->printLog(ss.str());
    return ErrorHandler::errNoError;
}

int OpenGLWrapper::setupTexture(){
    std::stringstream ss;
    ss << "Seting up texture" << std::endl;
    err->printLog(ss.str());
    
    //Generate Texture object
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getX(), image.getY(), 0, GL_BGRA, GL_UNSIGNED_BYTE, (const GLvoid*)data);
    //Defining how to proceed if the texture is smaller than the space
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    //Specify Border Color
    float color[] = {1.0f, 0.0f, 0.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
    //Set up filter for up and downscaling of the texture (linear smooth, nearest would give pixelised result)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /*TRY MINIMAPS*/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return ErrorHandler::errNoError;
}

int OpenGLWrapper::openGLRT(){
    std::stringstream ss;
    ss << "Starting runtime loop" << std::endl;
    err->printLog(ss.str());
    //add event loop 
    bool running = true;
        
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    win->display();
    
    while (running){
        sf::Event windowEvent;
        while(win->pollEvent(windowEvent)){
            switch(windowEvent.type){
                case sf::Event::Closed:
                    running = false;
                    break;
                case sf::Event::KeyPressed:
                    if(windowEvent.key.code == sf::Keyboard::Escape){    
                        running = false;
                    }
                    break;
            }
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            win->display();
        }
    }    
    return ErrorHandler::errNoError;
}

int OpenGLWrapper::cleanup(){    
    err->printLog("Cleaning up\n");

    //cleanup
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    
    glfwTerminate();

    win->close();
    delete win;    

    return ErrorHandler::errNoError;
}

Size::Size() {
    
}
Size::Size(int X, int Y) : x(X), y(Y){
}
Size::Size(const Size& orig){
    
}
Size::~Size(){
    
}
int Size::getX(){return x;}
int Size::getY(){return y;}
void Size::setX(int X){x = X;}
void Size::setY(int Y){y = Y;}

double Size::getFactor(int x, int y){return (double)x / y;}