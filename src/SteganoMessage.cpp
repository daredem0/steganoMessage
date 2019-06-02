/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.05.21
 * @brief SteganoMessage Class cpp file
 */
/* 
 * File:   SteganoMessage.cpp
 * Author: Florian Leuze
 * 
 * Created on 21. Mai 2019, 14:42
 */

#include "../header/SteganoMessage.h"

SteganoMessage::SteganoMessage() {
    err = NULL;
    mess = NULL;
    img = NULL;
    std::cout << "Creating new SteganoMessage object" << std::endl;
    err = new ErrorHandler();
    modeSet = false;
    path = false;
}

SteganoMessage::SteganoMessage(const SteganoMessage& orig) {
    err = NULL;
}

SteganoMessage::~SteganoMessage() {
    if(err != NULL)
        delete err;
    if(mess != NULL)
        delete mess;
    if(img != NULL)
        delete img;
}

ErrorHandler* SteganoMessage::getErrHandle(){
    return err;
    
}

int SteganoMessage::buildMessage(std::string m){
    if(mess == NULL){
        mess = new Message(m, err);
        return errNoError;
    }
    return errMessExist;
}

Message* SteganoMessage::getMessage(){
    return mess;
}

int SteganoMessage::buildImage(std::string path){
    if(img == NULL){
        img = new Image(path, err);
        return errNoError;
    }
    return errImgExist;
}

Image* SteganoMessage::getImage(){
    return img;
}

int SteganoMessage::setMode(std::string m){
    if(modeSet == false){
        mode = m;
        modeSet = true;
        return errNoError;
    }
    else
        return errMode;
}

std::string SteganoMessage::getMode(){
    if(modeSet == false)
        return "";
    return mode;
}

void SteganoMessage::printValues(){
    try{
        std::cout << "Mode: " << mode << std::endl;
        std::cout << "Path: " << img->getPath() << std::endl;
    }
    catch(...){
        err->printError(errUnknown);
    }
}


int SteganoMessage::checkPath(std::string p){
    int returnValue = errNoError;
    if(p[0] != '.' && p[0] != '/')
        returnValue = 4;
    if(exists(p) == false)
        returnValue = errPathExist;
    path = true;
    return returnValue;
}

bool SteganoMessage::exists(std::string p){
    try{
        std::ifstream img(p.c_str());
        bool returnValue = img.good();
        img.close();
        return returnValue;
    }
    catch(const std::exception& e){
        err->printErrorStdEx(e);
        return false;
    }
    catch(...){
        err->printError(errUnknown);
        return false;
    }
    return false;
}

bool SteganoMessage::getPathVerified(){
    return path;
}

int SteganoMessage::initialize(int argc, char *argv[]){
    try{
        //initialization stuff, especially read the header info, else everything will go horribly wrong in all possible ways
        std::cout << "Trying to get path" << std::endl;
        std::string tempPath;
            argv[2] == NULL ? tempPath = NOPATH : tempPath = (std::string)argv[2]; //if there was a path given store it in tempPath
            if(tempPath == NOPATH)
                throw errPath; //throw error if we didnt get a path
            std::cout << "Found Path: " << tempPath << std::endl; 
            this->buildImage(tempPath); //Call constructor for image type object and set path
            std::cout << "Built path: " << this->getImage()->getPath() << std::endl;
            this->getImage()->readImage(); //extract the image information
            //steg->getImage()->getBitmapHeader()->printHeader(); //only for debugging
            return 0;
    }
    catch(int i){
        err->printError(i);
        return errPath;
    }
    catch(const std::exception& e){
        err->printErrorStdEx(e);
        return errStdExcept;
    }
    catch(...){
        err->printError(errUnknown);
        return errUnknown;
    }
}

int SteganoMessage::modeHandler(){
    if(this->getMode() == ENCRYPT){
        std::cout << "Please enter your message" << std::endl;
        std::string mess;
        std::getline(std::cin, mess);
        this->buildMessage(mess);
        //check if message was read properly:
        std::cout << "I found: " << this->getMessage()->getMessage() << std::endl;
        //call infusion stuff ********************TOBI********************
        this->getImage()->generateBitmap(); 
    }
    else if(this->getMode() == DECRYPT){
        //do some decryption, print message to std::out, be nasty and destroy the image file 
    }
    else if(this->getMode() == BMPTOTXT){
        this->getImage()->bmpToTxt();
    }
}