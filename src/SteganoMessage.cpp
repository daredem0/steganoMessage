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
    #ifdef FULL
    ogl = NULL;    
    #endif
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
    #ifdef FULL
    if(ogl != NULL)
        delete ogl;
    #endif
}

//INIT/************************************************************/
int SteganoMessage::initialize(int argc, char *argv[]){
    int errTemp;
    try{
        //initialization stuff, especially read the header info, else everything will go horribly wrong in all possible ways
        err->printLog("Trying to get path\n");
        std::string tempPath;
            argv[2] == NULL ? tempPath = NOPATH : tempPath = (std::string)argv[2]; //if there was a path given store it in tempPath
            if(tempPath == NOPATH)
                throw errPath; //throw error if we didnt get a path
            err->printLog("Found Path: " + tempPath + "\n");
            errTemp = this->buildImage(tempPath); //Call constructor for image type object and set path
            if(errTemp != 0) throw errTemp;
            err->printLog("Built path: " + this->getImage()->getPath() + "\n");
            //set filters if activated
            if(argc > 3){
                if(argv[3] == FILTER){
                    this->setFilterMode(argv[4]);
                    crazy = false;
                    argc > 5 ? this->setLog(true) : this->setLog(false);
                }
                else if(argv[3] == CRFILTER){
                    this->setFilterMode(argv[4]);
                    crazy = true;
                    argc > 5 ? this->setLog(true) : this->setLog(false);
                }
                else if(argv[3] == LOG){
                    this->setFilterMode("");
                    this->setLog(true);
                }
            }
            else{
                this->setFilterMode("");
                this->setLog(false);
            }
            err->printLog("Filter mode: " + std::to_string(stegFilter) + "\n");
            if(img->identifyFileFormat(this->getImage()->getPath()) == BITMAP)
                errTemp = this->getImage()->readImage(); //extract the image information
            else if(img->identifyFileFormat(this->getImage()->getPath()) == JPEG)
                errTemp = this->getImage()->readImage(); //extract the image information
            else if(img->identifyFileFormat(this->getImage()->getPath()) == PNG){
                //errTemp = ((Png*)this->getImage())->read_png_file(this->getImage()->getPath()); //extract the image information
                errTemp = this->getImage()->readImage();
            }
            if(errTemp != 0) throw errTemp;
    }
    catch(int i){
        return i;
    }
    catch(const std::exception& e){
        err->printErrorStdEx(e);
        return errStdExcept;
    }
    catch(...){
        return errUnknown;
    }
    return ErrorHandler::errNoError;
}

//BUILDERS/************************************************************/
int SteganoMessage::buildMessage(std::string m){
    if(mess == NULL && m != ""){
        mess = new Message(m, err);
        return ErrorHandler::errNoError;
    }
    else if(m == "")
        return ErrorHandler::errMessEmpty;
    return ErrorHandler::errMessExist;
}

int SteganoMessage::buildImage(std::string path){
    if(img != NULL)
        return errImgExist;
    if(Image::identifyFileFormat(path) == BITMAP){
        err->printLog("Building bitmap\n");
        img = new Image(path, err);
        return errNoError;
    }    
    else if(Image::identifyFileFormat(path) == JPEG){
        err->printLog("Building jpeg\n");
        img = new Jpeg(path, err);
        return errNoError;
    }        
    else if(Image::identifyFileFormat(path) == PNG){
        err->printLog("Building png\n");
        img = new Png(path, err);
        return errNoError;
    }       
    else{
        return ErrorHandler::errFiletype;
    }
}

#ifdef FULL
int SteganoMessage::buildOpenGL(std::string t, unsigned char* d, std::string ft, int width, int height){
    ogl = new OpenGLWrapper(this->getErrHandle(), t, d, ft, width, height, SteganoMessage::naughtyEmergencyExit);
    return SteganoMessage::naughtyEmergencyExit(0);
}
#endif

//GETTERS/************************************************************/
ErrorHandler* SteganoMessage::getErrHandle(){return err;}
Message* SteganoMessage::getMessage(){return mess;}
Image* SteganoMessage::getImage(){return img;}
std::string SteganoMessage::getMode(){
    if(modeSet == false)
        return "";
    return mode;
}
#ifdef FULL
OpenGLWrapper* SteganoMessage::getOpenGL(){return ogl;}
#endif

bool SteganoMessage::getPathVerified(){return path;}

std::string SteganoMessage::getTimeString(){
    using namespace std::chrono;
    std::time_t t = system_clock::to_time_t(system_clock::now());
    return getTimeDate('Y', t) + "-" + getTimeDate('M', t) + "-" + getTimeDate('D', t) + "_" + getTimeDate('h', t) + "-" + getTimeDate('m', t) + "-" + getTimeDate('s', t);
}

std::string SteganoMessage::getTimeDate(char t, std::time_t system_clock){
    using namespace std::chrono;
    std::stringstream ss;
    switch(t){
        case 'Y':
            ss << std::put_time(std::localtime(&system_clock), "%Y");
            break;
        case 'M':
            ss << std::put_time(std::localtime(&system_clock), "%m");
            break;
        case 'D':
            ss << std::put_time(std::localtime(&system_clock), "%d");
            break;
        case 'h':
            ss << std::put_time(std::localtime(&system_clock), "%H");
            break;
        case 'm':
            ss << std::put_time(std::localtime(&system_clock), "%M");
            break;
        case 's':
            ss << std::put_time(std::localtime(&system_clock), "%S");
            break;
        default:
            return NULL;
    }
    return ss.str();
}

bool SteganoMessage::getLogMode(){return log;}

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

void SteganoMessage::setLog(bool l){
    log = l;
    std::string outpath = "./log/"+ this->getTimeString() + ".txt";
    err->setLog(l, outpath);
    if(l == true)
        img->setLogMode(outpath , std::ios::app);
    else
        img->setLogMode("./outputText.txt", std::ios::trunc);     
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
    try{
        int errTemp = 0;
        if(this->getMode() == ENCRYPT){
            err->printLog("\nPlease enter your message\n");
            std::string mess;
            std::getline(std::cin, mess);
            (errTemp = this->buildMessage(mess)) != 0 ? throw errTemp: errTemp = 0;
            //check if message was read properly:
            err->printLog("Found: " + this->getMessage()->getMessage() + "\n");

            (errTemp = this->getImage()->getBitmapArray()->infuse(mess)) != 0 ? throw errTemp : errTemp = 0;                     /*this->getMessage()->getMessage()*/
            err->printLog("\n \n"); //fix missing endl in infuse function

            (errTemp = this->getImage()->generateBitmap()) != 0 ? throw errTemp : errTemp = 0;
        }
        else if(this->getMode() == DECRYPT){
            err->printLog("\nTrying to decrypt\n");
            auto mes =  this->getImage()->getBitmapArray()->defuse();
            err->printLog("\nFound: " + mes + '\n');
            //do some decryption, print message to std::out, be nasty and destroy the image file 
        }
        else if(this->getMode() == BMPTOTXT){
            (errTemp = this->getImage()->bmpToTxt()) != 0 ? throw errTemp : errTemp = 0;
        }
        else if(this->getMode() == FILTER){
            (errTemp = this->getImage()->generateBitmap()) != 0 ? throw errTemp : errTemp = 0; 
        }
    return ErrorHandler::errNoError;
    }
    catch(int i){
        return  err->printError(i);        
    }
}

int SteganoMessage::applyFilter(){
    err->printLog("Loading up filter handler\n");
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
            genFilter(data, Filter::revertUint);
            return errNoError;
        case swapByte:
            genFilter(data, Filter::swapBytes);
            return errNoError;
        case swapOctet:
            genFilter(data, Filter::swapOctets);
            return errNoError;
        case swapByteOctet:
            genFilter(data, Filter::swapBytesOctets);
            return errNoError;
        case swapByteOctetBit:
            genFilter(data, Filter::swapBytesOctetsBits);
            return errNoError;
        case swapByteBit:
            genFilter(data, Filter::swapBytesBits);
            return errNoError;
        case swapBtG:
            genFilter(data, Filter::swapBG);
            return errNoError;
        case swapBtR:
            genFilter(data, Filter::swapBR);
            return errNoError;
        case swapGtR:
            genFilter(data, Filter::swapGR);
            return errNoError;
        case substBl:
            genFilter(data, Filter::substB);
            return errNoError;
        case substRd:
            genFilter(data, Filter::substR);
            return errNoError;
        case substGr:
            genFilter(data, Filter::substG);
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

int SteganoMessage::naughtyEmergencyExit(int err){
    static int naugthyEmergencyExitValue = 0;
    static int counter = 1;
    if ((counter == 1 || (naugthyEmergencyExitValue == 0)) && err == 0){
        counter = 1;
        return (naugthyEmergencyExitValue = 0);
    }
    else if (err != 0){
        ++counter;
        return (naugthyEmergencyExitValue = err);
    }
    return naugthyEmergencyExitValue;
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




void SteganoMessage::genFilter(std::vector<std::vector<uint32_t>> *d, uint32_t (*f)(uint32_t, size_t)){
    try{
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
    catch(const std::exception& e){
        err->printErrorStdEx(e);
        exit(1);
    }
    catch(...){
        err->printError(ErrorHandler::ERRUNKNOWN);
        exit(1);
    }
}

void SteganoMessage::dummyFilter(std::vector<std::vector<uint32_t>> *d){
    std::cout << "In dummy filter" << std::endl;
    genFilter(d, Filter::substB);
}
