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

/********PUBLIC**************PUBLIC*****************PUBLIC**************PUBLIC************/
//CONSTRUCTORS/DECONSTRUCTORS/************************************************************/
SteganoMessage::SteganoMessage() {
    err = NULL;
    mess = NULL;
    img = NULL;
    err = new ErrorHandler();
    err->printLog("Creating new SteganoMessage object\n");
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

//INIT/************************************************************/
int SteganoMessage::initialize(int argc, char *argv[]){
    try{
        //initialization stuff, especially read the header info, else everything will go horribly wrong in all possible ways
        std::cout << "Trying to get path" << std::endl;
        std::string tempPath;
            argv[2] == NULL ? tempPath = NOPATH : tempPath = (std::string)argv[2]; //if there was a path given store it in tempPath
            if(tempPath == NOPATH)
                throw errPath; //throw error if we didnt get a path
            std::cout << "Found Path: " << tempPath << std::endl; 
            if(Image::identifyFileFormat(tempPath) != BITMAP){
                std::cout << "shit" << std::endl;
                exit(1);
            }
            int i;
            this->buildImage(tempPath); //Call constructor for image type object and set path
            std::cout << "Built path: " << this->getImage()->getPath() << std::endl;
            //set filters if activated
            if(argc > 3){
                if(argv[3] == FILTER){
                    this->setFilterMode(argv[4]);
                    crazy = false;
                }
                else if(argv[3] == CRFILTER){
                    this->setFilterMode(argv[4]);
                    crazy = true;
                }
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

//BUILDERS/************************************************************/
int SteganoMessage::buildMessage(std::string m){
    if(mess == NULL){
        mess = new Message(m, err);
        return errNoError;
    }
    return errMessExist;
}

int SteganoMessage::buildImage(std::string path){
    if(img == NULL){
        img = new Image(path, err);
        return errNoError;
    }
    return errImgExist;
}

//GETTERS/************************************************************/
ErrorHandler* SteganoMessage::getErrHandle(){return err;}
Message* SteganoMessage::getMessage(){return mess;}
Image* SteganoMessage::getImage(){return img;}
std::string SteganoMessage::getMode(){modeSet == false ? "" : mode;}
bool SteganoMessage::getPathVerified(){return path;}

//SETTERS/************************************************************/
int SteganoMessage::setMode(std::string m){
    if(modeSet == false){
        mode = m;
        modeSet = true;
        return errNoError;
    }
    else
        return errMode;
}

int SteganoMessage::setFilterMode(std::string mode){
    if (mode == ""){
        this->getImage()->setFilter("", "");
        stegFilter = noFilter;
    }
    else if(mode == GREY){
        this->getImage()->setFilter(GREY, "");
        stegFilter = grey;
    }
    else if(mode == COLORA){
        this->getImage()->setFilter("", COLORA);
        stegFilter = colorA;
    }
    else if(mode == COLORB){
        this->getImage()->setFilter(GREY, COLORB);
        stegFilter = colorB;
    }
    else if(mode == COLORDUMMY)
        stegFilter = color;
    else if(mode == INVERTBIT)
        stegFilter = invertBit;
    else if(mode == SWAPBYTE)
        stegFilter = swapByte;
    else if(mode == SWAPOCTET)
        stegFilter = swapOctet;
    else if(mode == SWAPBYOC)
        stegFilter = swapByteOctet;
    else if(mode == SWAPBYOCBI)
        stegFilter = swapByteOctetBit;
    else if(mode == SWAPBYBI)
        stegFilter = swapByteBit;
    else if(mode == SWAPBG)
        stegFilter = swapBtG;
    else if(mode == SWAPBR)
        stegFilter = swapBtR;
    else if(mode == SWAPGR)
        stegFilter = swapGtR;
    else if(mode == SUBSTB)
        stegFilter = substBl;
    else if(mode == SUBSTR)
        stegFilter = substRd;
    else if(mode == SUBSTG)
        stegFilter = substGr;
    else
        stegFilter = noFilter;
    
    return errNoError;
}

//EVALUATIONS/************************************************************/
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

//OTHER METHODS/************************************************************/
int SteganoMessage::modeHandler(){
    if(this->getMode() == ENCRYPT){
        std::cout << "Please enter your message" << std::endl;
        std::string mess;
        std::getline(std::cin, mess);
        this->buildMessage(mess);
        //check if message was read properly:
        std::cout << "I found: " << this->getMessage()->getMessage() << std::endl;
        //call infusion stuff ********************TOBI********************
        this->getImage()->getBitmapArray()->infuse("AAA");
        
        //*end Tobi************************************
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

int SteganoMessage::applyFilter(){
    std::cout << "Successfully filter application initialized" << std::endl;
    std::vector<std::vector<uint32_t>> *data = this->getImage()->getBitmapArray()->getBDataPointer();
    switch(stegFilter){
        case noFilter:
            return 0;
        case grey:
            return errNoError;
        case colorA:
            return errNoError;
        case colorB:
            return errNoError;
        case color:
            dummyFilter(data);
            return errNoError;
        case invertBit:
            genFilter(data, revertUint);
            return errNoError;
        case swapByte:
            genFilter(data, swapBytes);
            return errNoError;
        case swapOctet:
            genFilter(data, swapOctets);
            return errNoError;
        case swapByteOctet:
            genFilter(data, swapBytesOctets);
            return errNoError;
        case swapByteOctetBit:
            genFilter(data, swapBytesOctetsBits);
            return errNoError;
        case swapByteBit:
            genFilter(data, swapBytesBits);
            return errNoError;
        case swapBtG:
            genFilter(data, swapBG);
            return errNoError;
        case swapBtR:
            genFilter(data, swapBR);
            return errNoError;
        case swapGtR:
            genFilter(data, swapGR);
            return errNoError;
        case substBl:
            genFilter(data, substB);
            return errNoError;
        case substRd:
            genFilter(data, substR);
            return errNoError;
        case substGr:
            genFilter(data, substG);
            return errNoError;
        default:
            return errUnknown;
    }
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

/********PRIVATE**************PRIVATE*************PRIVATE**************PRIVATE************/
//PROGRESS/*******************************************************************************/

void SteganoMessage::displayProgress(int& c, int p){
    if((uint32_t)(((double)c/p)*100) - (uint32_t)(((double)(++c)/p)*100) > 1){
        std::cout << "                                           " << '\r' << std::flush;
        std::cout << ((double)c/p)*100 << "% done"  << '\r' << std::flush;
    }
}

void SteganoMessage::displayProgress(int p){
    if(p == 0)
        std::cout << 100.000 << "% done" << std::endl;
    else
        std::cout << (-1) << std::endl;
}

//GETTERS/*******************************************************************************/
int SteganoMessage::getPixel(){return this->getImage()->getBitmapHeader()->getHeight() * this->getImage()->getBitmapHeader()->getWidth();}


//FILTERS/*******************************************************************************/
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

uint32_t SteganoMessage::swapOctets(uint32_t d, size_t s){
    switch(s){
        case 1:
            return (d & 0xF0) >> 4 ??! (d & 0x0F) << 4;
        case 2:
            return ((d & 0xF000) >> 4 ??! (d & 0x0F00) << 4) ??! ((d & 0xF0) >> 4 ??! (d & 0x0F) << 4);
        case 3:
            return ((d & 0xF00000) >> 4 ??! (d & 0x0F0000) << 4) ??! ((d & 0xF000) >> 4 ??! (d & 0x0F00) << 4) ??! ((d & 0xF0) >> 4 ??! (d & 0x0F) << 4);
        case 4:
            return ((d & 0xFF000000) >> 4  ??! (d & 0x0F000000) << 4) ??! ((d & 0xF00000) >> 4 ??! (d & 0x0F0000) << 4) 
                    ??! ((d & 0xF000) >> 4 ??! (d & 0x0F00) << 4) ??! ((d & 0xF0) >> 4 ??! (d & 0x0F) << 4);
    }
}

uint32_t SteganoMessage::swapBytesOctets(uint32_t d, size_t s){return swapBytes(swapOctets(d, s), s);}

uint32_t SteganoMessage::swapBytesBits(uint32_t d, size_t s){return revertUint(swapBytes(d,s),s);}

uint32_t SteganoMessage::swapBytesOctetsBits(uint32_t d, size_t s){return revertUint(swapBytes(swapOctets(d, s), s),s);}



uint32_t SteganoMessage::swapBR(uint32_t d, size_t s){
    switch(s){
        case 1:
            return d;
        case 2:
            return (d & 0xFF00) >> 8 ??! (d & 0x00FF) << 8;
        case 3:
            return (d & 0xFF0000) >> 16 ??! (d & 0x0000FF) << 16;
        case 4:
            return (d & 0x00FF00FF) ??! ((d & 0xFF000000) >> 16 ??! (d & 0x0000FF00) << 16);
    }
}

uint32_t SteganoMessage::swapBG(uint32_t d, size_t s){
    switch(s){
        case 1:
            return d;
        case 2:
            return (d & 0xFF00) >> 8 ??! (d & 0x00FF) << 8;
        case 3:
            return (d & 0xFF0000) >> 16 ??! (d & 0x0000FF) << 16;
        case 4:
            return (d & 0x0000FFFF) ??! ((d & 0xFF000000) >> 8 ??! (d & 0x00FF0000) << 8);
    }
}

uint32_t SteganoMessage::swapGR(uint32_t d, size_t s){
    switch(s){
        case 1:
            return d;
        case 2:
            return (d & 0xFF00) >> 8 ??! (d & 0x00FF) << 8;
        case 3:
            return (d & 0xFF0000) >> 16 ??! (d & 0x0000FF) << 16;
        case 4:
            return (d & 0xFF0000FF) ??! ((d & 0x00FF0000) >> 8 ??! (d & 0x0000FF00) << 8);
    }
}

uint32_t SteganoMessage::substB(uint32_t d, size_t s){
    switch(s){
        case 1:
            return d;
        case 2:
            return (d & 0xFF00) >> 8 | (d & 0x00FF) << 8;
        case 3:
            return (d -(d & 0xFF0000)) | ((d & 0x00FF00) - (d & 0xFF0000 >> 8)) | ((d & 0x0000FF) - (d & 0xFF0000 >> 16)); 
        case 4:
            return (d -(d & 0xFF000000)) | ((d & 0x00FF0000) - (d & 0xFF000000 >> 8)) | ((d & 0x0000FF00) - (d & 0xFF000000 >> 16)) | (d & 0xFF); 
    }
}

uint32_t SteganoMessage::substR(uint32_t d, size_t s){
    switch(s){
        case 1:
            return d;
        case 2:
            return (d & 0xFF00) >> 8 | (d & 0x00FF) << 8;
        case 3:
            return (d -(d & 0x0000FF)) | ((d & 0x00FF00) - (d & 0x0000FF << 8)) | ((d & 0xFF0000) - (d & 0x0000FF << 16)); 
        case 4:
            return (d -(d & 0x0000FF00)) | ((d & 0x00FF0000) - (d & 0x0000FF00 << 8)) | ((d & 0xFF000000) - (d & 0x0000FF00 << 16)) | (d & 0xFF); 
    }
}

uint32_t SteganoMessage::substG(uint32_t d, size_t s){
    switch(s){
        case 1:
            return d;
        case 2:
            return (d & 0xFF00) >> 8 | (d & 0x00FF) << 8;
        case 3:
            return (d -(d & 0x00FF00)) | ((d & 0xFF0000) - (d & 0x00FF00 << 8)) | ((d & 0x0000FF) - (d & 0x00FF00 >> 8)); 
        case 4:
            return (d -(d & 0x00FF0000)) | ((d & 0xFF000000) - (d & 0x00FF0000 << 8)) | ((d & 0x0000FF00) - (d & 0x00FF0000 >> 8)) | (d & 0xFF); 
    }
}

void SteganoMessage::genFilter(std::vector<std::vector<uint32_t>> *d, uint32_t (*f)(uint32_t, size_t)){
    int count = 0;
    int pixel = getPixel();
    for(auto itOuter = d->begin(); itOuter != d->end(); ++itOuter){
        for(auto itInner = itOuter->begin(); itInner != itOuter->end(); ++itInner){
            if(crazy == true)
                *itInner = f(*itInner, sizeof(*itInner));
            else
                *itInner = f(*itInner, this->getImage()->getBitmapHeader()->getBitCount()/8);
            displayProgress(count, pixel);
        }
    }
    displayProgress(0);
}

void SteganoMessage::dummyFilter(std::vector<std::vector<uint32_t>> *d){
    std::cout << "In dummy filter" << std::endl;
    genFilter(d, substB);
}