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
            
            //set filters if activated
            if(argc > 3){
                if(argv[3] == FILTER)
                    this->setFilterMode(argv[4]);
            }
            else
                this->setFilterMode("");
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
    else if(this->getMode() == FILTER){
        this->getImage()->generateBitmap(); 
    }
}


int SteganoMessage::setFilterMode(std::string mode){
    switch(parseFilterMode(mode)){
        case noFilter:
            this->getImage()->setFilter("", "");
            break;
        case grey:
            this->getImage()->setFilter(GREY, "");
            break;
        case colorA:
            this->getImage()->setFilter("", COLORA);
            break;
        case colorB:
            this->getImage()->setFilter(GREY, COLORB);
            break;
        case color:
            filter = COLORDUMMY;
            break;
        case invertBit:
            filter = INVERTBIT;
            break;
        case swapByte:
            filter = SWAPBYTE;
            break;
        case swapOctet:
            filter = SWAPOCTET;
            break;
        case swapByteOctet:
            filter = SWAPBYOC;
            break;
        case swapByteOctetBit:
            filter = SWAPBYOCBI;
            break;
        default:
            return errUnknown;
    }
    return errNoError;
}

int SteganoMessage::parseFilterMode(std::string m){
    Filter ret;
    if (m == "")
        ret = noFilter;
    else if(m == GREY)
        ret = grey;
    else if(m == COLORA)
        ret = colorA;
    else if(m == COLORB)
        ret = colorB;
    else if(m == COLORDUMMY)
        ret = color;
    else if(m == SWAPBYTE)
        ret = swapByte;
    else if(m == SWAPOCTET)
        ret = swapOctet;
    else if(m == SWAPBYOC)
        ret = swapByteOctet;
    else if(m == SWAPBYOCBI)
        ret = swapByteOctetBit;
    else
        ret = noFilter;
    return ret;
}

std::string SteganoMessage::getFilter(){return filter;}

int SteganoMessage::applyFilter(){
    std::cout << "Successfully ended up in dummy filter" << std::endl;
    std::vector<std::vector<uint32_t>> *data = this->getImage()->getBitmapArray()->getBDataPointer();
    //filterInvertBits(data);
    filterSwapBytesOctetsBits(data);
}

int SteganoMessage::filterSwapBytesOctets(std::vector<std::vector<uint32_t>> *d){ //noisy and heave shift into yellowish
    int count = 0;
    int pixle = this->getImage()->getBitmapHeader()->getHeight() * this->getImage()->getBitmapHeader()->getWidth();
    for(auto itOuter = d->begin(); itOuter != d->end(); ++itOuter){
        for(auto itInner = itOuter->begin(); itInner != itOuter->end(); ++itInner){
            *itInner = swapBytes(swapOctets(*itInner, sizeof(*itInner)), sizeof(*itInner));
            if((uint32_t)(((double)count/pixle)*100) - (uint32_t)(((double)(++count)/pixle)*100) > 1){
                std::cout << ((double)count/pixle)*100 << "% done" << std::endl;
                std::cout << "\033[2J\033[1;1H"; //ANSI Code to clear terminal
            }
        }
    }
    std::cout << 100.000 << "% done" << std::endl;
}

int SteganoMessage::filterSwapBytesOctetsBits(std::vector<std::vector<uint32_t>> *d){
    int count = 0;
    int pixle = this->getImage()->getBitmapHeader()->getHeight() * this->getImage()->getBitmapHeader()->getWidth();
    for(auto itOuter = d->begin(); itOuter != d->end(); ++itOuter){
        for(auto itInner = itOuter->begin(); itInner != itOuter->end(); ++itInner){
            *itInner = revertUint(swapBytes(swapOctets(*itInner, sizeof(*itInner)), sizeof(*itInner)),sizeof(*itInner));
            if((uint32_t)(((double)count/pixle)*100) - (uint32_t)(((double)(++count)/pixle)*100) > 1){
                std::cout << ((double)count/pixle)*100 << "% done" << std::endl;
                std::cout << "\033[2J\033[1;1H"; //ANSI Code to clear terminal
            }
        }
    }
    std::cout << 100.000 << "% done" << std::endl;
}

int SteganoMessage::filterSwapOctets(std::vector<std::vector<uint32_t>> *d){ //super strong noice and psychodelic color effect
    int count = 0;
    int pixle = this->getImage()->getBitmapHeader()->getHeight() * this->getImage()->getBitmapHeader()->getWidth();
    for(auto itOuter = d->begin(); itOuter != d->end(); ++itOuter){
        for(auto itInner = itOuter->begin(); itInner != itOuter->end(); ++itInner){
            *itInner = swapOctets(*itInner, sizeof(*itInner));
            if((uint32_t)(((double)count/pixle)*100) - (uint32_t)(((double)(++count)/pixle)*100) > 1){
                std::cout << ((double)count/pixle)*100 << "% done" << std::endl;
                std::cout << "\033[2J\033[1;1H"; //ANSI Code to clear terminal
            }
        }
    }
    std::cout << 100.000 << "% done" << std::endl;
}

int SteganoMessage::filterSwapBytes(std::vector<std::vector<uint32_t>> *d){ //strong color shift into yellowish
    int count = 0;
    int pixle = this->getImage()->getBitmapHeader()->getHeight() * this->getImage()->getBitmapHeader()->getWidth();
    for(auto itOuter = d->begin(); itOuter != d->end(); ++itOuter){
        for(auto itInner = itOuter->begin(); itInner != itOuter->end(); ++itInner){
            *itInner = swapBytes(*itInner, sizeof(*itInner));
            if((uint32_t)(((double)count/pixle)*100) - (uint32_t)(((double)(++count)/pixle)*100) > 1){
                std::cout << ((double)count/pixle)*100 << "% done" << std::endl;
                std::cout << "\033[2J\033[1;1H"; //ANSI Code to clear terminal
            }
        }
    }
    std::cout << 100.000 << "% done" << std::endl;
}

int SteganoMessage::filterInvertBits(std::vector<std::vector<uint32_t>> *d){ //adds strong noise and shifts the color
    int count = 0;
    int pixle = this->getImage()->getBitmapHeader()->getHeight() * this->getImage()->getBitmapHeader()->getWidth();
    for(auto itOuter = d->begin(); itOuter != d->end(); ++itOuter){
        for(auto itInner = itOuter->begin(); itInner != itOuter->end(); ++itInner){
            *itInner = revertUint(*itInner, sizeof(*itInner));
            if((uint32_t)(((double)count/pixle)*100) - (uint32_t)(((double)(++count)/pixle)*100) > 1){
                std::cout << ((double)count/pixle)*100 << "% done" << std::endl;
                std::cout << "\033[2J\033[1;1H"; //ANSI Code to clear terminal
            }
        }
    }
    std::cout << 100.000 << "% done" << std::endl;
}

uint32_t SteganoMessage::swapOctets(uint32_t d, size_t s){
    switch(s){
        case 1:
            return (d & 0xF0) >> 4 | (d & 0x0F) << 4;
        case 2:
            return ((d & 0xF000) >> 4 | (d & 0x0F00) << 4) | ((d & 0xF0) >> 4 | (d & 0x0F) << 4);
        case 3:
            return ((d & 0xF00000) >> 4 | (d & 0x0F0000) << 4) | ((d & 0xF000) >> 4 | (d & 0x0F00) << 4) | ((d & 0xF0) >> 4 | (d & 0x0F) << 4);
        case 4:
            return ((d & 0xFF000000) >> 4  | (d & 0x0F000000) << 4) | ((d & 0xF00000) >> 4 | (d & 0x0F0000) << 4) 
                    | ((d & 0xF000) >> 4 | (d & 0x0F00) << 4) | ((d & 0xF0) >> 4 | (d & 0x0F) << 4);
    }
}

uint32_t SteganoMessage::swapBytes(uint32_t d, size_t s){
    switch(s){
        case 1:
            return d;
        case 2:
            return (d & 0xFF00) >> 8 | (d & 0x00FF) << 8;
        case 3:
            return (d & 0xFF0000) >> 16 | (d & 0x0000FF) << 16;
        case 4:
            return ((d & 0xFF000000) >> 24 | (d & 0x000000FF) << 24) | ((d & 0xFF0000) >> 8 | (d & 0xFF00) << 8);
    }
}

uint32_t SteganoMessage::revertUint(uint32_t d, size_t s){
    uint32_t out = 0;
    for(int i = 0; i < s; ++i){
        out |= invert(d >> i*8)<<i*8;
    }
    return out;
}

uint32_t SteganoMessage::invert(uint8_t w){
   w = (w & 0xF0) >> 4 | (w & 0x0F) << 4;
   w = (w & 0xCC) >> 2 | (w & 0x33) << 2;
   w = (w & 0xAA) >> 1 | (w & 0x55) << 1;
   return w;
}