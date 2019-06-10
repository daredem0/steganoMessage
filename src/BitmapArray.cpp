/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.05.24
 * @brief BitmapArray header file
 */
/* 
 * File:   BitmapArray.cpp
 * Author: Florian Leuze
 * 
 * Created on 24. Mai 2019, 22:46
 */

#include "../header/BitmapArray.h"

/********PUBLIC**************PUBLIC*****************PUBLIC**************PUBLIC************/
//CONSTRUCTORS/DECONSTRUCTORS/************************************************************/
BitmapArray::BitmapArray() {
    for(auto itOuter = bData.begin(); itOuter != bData.end(); ++itOuter){
        itOuter->clear();
    }
    bData.clear();
}

BitmapArray::BitmapArray(std::string p, uint32_t b, uint32_t w, uint32_t h, uint32_t bit, ErrorHandler *errH, std::string fm) : path(p), bitOffset(b), width(w), 
        height(h), bitCount(bit), errHandle(errH), filterMode(fm){
    for(auto itOuter = bData.begin(); itOuter != bData.end(); ++itOuter){ //clear all inner std::vectors
        itOuter->clear();
    }
    bData.clear(); //clear outer std::vector
    errHandle->printLog("All went well in the constructor\n");
    readArray();
}

BitmapArray::BitmapArray(std::string p, uint32_t b, uint32_t w, uint32_t h, uint32_t bit, ErrorHandler *errH, std::string fm, std::vector<std::vector<uint32_t>> d) : path(p), bitOffset(b), width(w), 
        height(h), bitCount(bit), errHandle(errH), filterMode(fm), bData(d){
    errHandle->printLog("All went well in the constructor\n");
}

BitmapArray::BitmapArray(const BitmapArray& orig) {
}

BitmapArray::~BitmapArray() {
}

//GETTERS/************************************************************/
std::vector<std::vector<uint32_t>> BitmapArray::getBData(){return bData;}
std::vector<std::vector<uint32_t>> *BitmapArray::getBDataPointer(){return &bData;}

//lets go the C lifestyle and use a bit of memcpy... *_*
char* BitmapArray::getBDataStream(){
    dataStream = new char[height*width*bitCount/8];
    int k = 0;
    for(auto itOuter = bData.begin(); itOuter != bData.end(); ++itOuter){
            int padding = (4-(width%4)==4) ? 0 : 4-(width%4);
            for(auto itInner = itOuter->begin(); itInner != itOuter->end(); ++itInner){
                switch(bitCount){
                    case 8:
                    case 16:
                        std::memcpy((dataStream+k), (void*)(&(*itInner)), (size_t)(bitCount/8));
                        break;
                    case 24:{
                        if(padding == 0){
                            std::memcpy(dataStream+k, (void*)(&(*itInner)), (size_t)(bitCount/8));
                            break;
                        }
                        std::memcpy(dataStream+k, (void*)(&(*itInner)), (size_t)padding);
                    }
                    break;
                    case 32:{
                        std::memcpy(dataStream+k, (void*)(&(*itInner)), (size_t)(bitCount/8));
                        break;
                    }
                    default:{
                        *(dataStream + k) = '\0';
                    }
                }
                k += bitCount/8;
            }
       }
    
    return dataStream;
}


//SETTERS/************************************************************/
int BitmapArray::setFilter(std::string fm){
    filterMode = fm;
    return 0;
}

//OTHER METHODS/************************************************************/
int BitmapArray::readArray(){
    try{
        errHandle->printLog("Opening stream\n");
        std::ifstream file(path);
        if(!file.good())
            return 3;
        int returnValue = read(file);
        errHandle->printLog("Finished reading\n");
        file.close();
        return returnValue;
    }
    catch(const std::exception& e){
        errHandle->printErrorStdEx(e);
        errHandle->printError(errBmDataRead);
        return errBmDataRead;
    }
    catch(...){
        errHandle->printError(errUnknown);
        errHandle->printError(errBmDataRead);
        return errBmDataRead;
    }
    return errBmDataRead;
}

void BitmapArray::printArray(){
    int i = 0;
    for(auto itOuter = bData.begin(); itOuter != bData.end(); ++itOuter){
        int j = 0;
        errHandle->printLog("Outer: " + std::to_string(i) + "\n");
        for(auto itInner = itOuter->begin(); itInner != itOuter->end(); ++itInner){
            errHandle->printLog("Inner: " + std::to_string(j) + "\n");
            errHandle->printLog(std::to_string((uint32_t)*itInner) + "\n");
            ++j;
        }
        ++i;
        std::cout << std::endl;
    }
}

int BitmapArray::infuse(std::string message){
    uint32_t charmask32bit = 0x0;                           //Masks for Character Bits
    uint32_t charmask24bit = 0x0;
    uint32_t charmask16bit = 0x0;
    const uint32_t charmask8bit  = 0x3;
    
    const uint32_t pixelmask32bit = 0xFCFCFCFC;             //Masks for Pixel Bits
    const uint32_t pixelmask24bit = 0xFCFCFC;
    const uint32_t pixelmask16bit = 0xFCFC;
    const uint32_t pixelmask8bit  = 0xFC;
    
    auto itOuter = bData.begin();                           //Outer iterator of 2D Array
    auto itInner = itOuter->begin();                        //Inner iterator of 2D Array
    std::string::iterator chariterator = message.begin();   //Characteriterator for messagestring

    bool encoded = false;                                   //Flag to terminate for-loop
    
    int messcharcounter = 1;                                //Counter for each character in messagestring
    
    //std::cout for debugging purposes
    
    switch(bitCount){
            
        case 8:
            std::cout << "8bit Bitmap to infuse with message" << std::endl;
            for(itOuter; itOuter != bData.end() && encoded != true; ++itOuter){
                for(itInner; itInner != itOuter->end() && encoded != true; ++itInner){
                    //std::cout << "Pixel value: " << std::hex << *itInner << std::endl;
                    *itInner &= pixelmask8bit;
                    //std::cout << "Pixel value after mask: " << *itInner << std::endl;
                    
                    if(messcharcounter<=4 && chariterator != message.end()){
                        //std::cout << "This is the charmask: " << (*chariterator >> (2*(4-messcharcounter))) & charmask8bit << std::endl; 
                        *itInner |= (*chariterator >> (2*(4-messcharcounter))) & charmask8bit;
                        ++messcharcounter;
                        //std::cout << "New pixel value: " << *itInner << std::endl;
                        //std::cout << "Ended in infuse <=4" << std::endl;
                        
                        if (messcharcounter>4) {
                            messcharcounter = 1;
                            //std::cout << "Infused character: " << *chariterator << std::endl;
                            //std::cout << "------------------------------------" << std::endl;
                            ++chariterator;
                        }
                    }
                
                    else if (messcharcounter<=4 && chariterator == message.end()){
                        *itInner |= (*chariterator >> (2*(4-messcharcounter))) & charmask8bit;
                        messcharcounter++;
                        //std::cout << "New pixel value: " << *itInner << std::endl;
                        //std::cout << "Ended in infuse <=4 & end" << std::endl;
                    }
                    
                    else{
                        //std::cout << "Infused character " << *chariterator << std::endl;
                        //std::cout << "Ended in infuse encoded = true" << std::endl;
                        encoded = true;   
                    }
                }
            }
            break;
            
        case 16:
            std::cout << "16bit Bitmap to infuse with message" << std::endl;
            for(itOuter; itOuter != bData.end() && encoded != true; ++itOuter){
                for(itInner; itInner != itOuter->end() && encoded != true; ++itInner){
                    std::cout << "Pixel value: " << std::hex << *itInner << std::endl;
                    *itInner &= pixelmask16bit;
                    std::cout << "Pixel value after mask: " << *itInner << std::endl;

                    if(chariterator != message.end()){
                        for(messcharcounter; messcharcounter<=4; ++messcharcounter){
                            charmask16bit |= ((uint32_t)*chariterator >> (2*(4-messcharcounter))) & charmask8bit;
                            if(messcharcounter == 1 || messcharcounter == 3){
                                charmask16bit <<= 8;
                            }
                            if (messcharcounter == 2) {
                                ++messcharcounter;          //After break will it still increment messcharcounter?
                                break;
                            }
                            if (messcharcounter == 4) {
                                messcharcounter = 1;
                                ++chariterator;
                            }
                        }
                        std::cout << "This is the charmask: " << charmask32bit << std::endl;
                        *itInner |= charmask16bit;
                        charmask16bit = 0x0;
                        std::cout << "New pixel value: " << *itInner << std::endl;
                        std::cout << "Infused character: " << *chariterator << std::endl;
                        std::cout << "------------------------------------" << std::endl;
                    }
                    
                    else{
                        for(messcharcounter; messcharcounter<=4; ++messcharcounter){
                            charmask16bit |= ((uint32_t)*chariterator >> (2*(4-messcharcounter))) & charmask8bit;
                            if(messcharcounter == 1 || messcharcounter == 3){
                                charmask16bit <<= 8;
                            }
                            if (messcharcounter == 2) {
                                ++messcharcounter;          //After break will it still increment messcharcounter?
                                break;
                            }
                            if (messcharcounter == 4) {
                                messcharcounter = 1;
                                encoded = true;
                            }
                        }
                        std::cout << "This is the charmask: " << charmask32bit << std::endl;
                        *itInner |= charmask16bit;
                        charmask16bit = 0x0;
                        std::cout << "New pixel value: " << *itInner << std::endl;
                        std::cout << "Infused character: " << *chariterator << std::endl;
                        std::cout << "------------------------------------" << std::endl;
                    }
                }
            }
            break;
        
        case 24:
            break;
        
        case 32:
            std::cout << "32bit Bitmap to infuse with message" << std::endl;
            for(itOuter; itOuter != bData.end() && encoded != true; ++itOuter){
                for(itInner; itInner != itOuter->end() && encoded != true; ++itInner){
                    //std::cout << "Pixel value: " << std::hex << *itInner << std::endl;
                    *itInner &= pixelmask32bit;
                    //std::cout << "Pixel value after mask: " << *itInner << std::endl;
                    
                    if(chariterator != message.end()){
                        for(messcharcounter = 1; messcharcounter<=4; messcharcounter++){
                            charmask32bit |= ((uint32_t)*chariterator >> (2*(4-messcharcounter))) & charmask8bit;
                            if(messcharcounter != 4){
                                charmask32bit <<= 8;   
                            }
                            //std::cout << "This is the charmask: " << charmask32bit << std::endl; 
                        }
                        *itInner |= charmask32bit;
                        charmask32bit = 0x0; 
                        //std::cout << "New pixel value: " << *itInner << std::endl;
                        //std::cout << "Infused character: " << *chariterator << std::endl;
                        //std::cout << "------------------------------------" << std::endl;
                        chariterator++;
                    }
                    
                    else{
                        for(messcharcounter = 1; messcharcounter<=4; messcharcounter++){
                            charmask32bit |= ((uint32_t)*chariterator >> (2*(4-messcharcounter))) & charmask8bit;
                            if(messcharcounter != 4){
                                charmask32bit <<= 8;   
                            }
                        }
                        //std::cout << "This is the charmask: " << charmask32bit << std::endl;
                        *itInner |= charmask32bit;
                        //std::cout << "New pixel value: " << *itInner << std::endl;
                        //std::cout << "Infused character: " << *chariterator << std::endl;
                        //std::cout << "Ended in infuse encoded = true" << std::endl;
                        encoded = true; 
                    }
                }
            }
            break;
    }
    errHandle->printLog("Bitmap successfully infused with Message");
    //return errInfused; /*is this intentional? This way infuse will always return an error message. Fixed it for you
    return ErrorHandler::errNoError;
}

/********PRIVATE**************PRIVATE*****************PRIVATE**************PRIVATE************/
int BitmapArray::read(std::ifstream& f){
    errHandle->printLog("Reading the image data\n");
    std::vector<uint32_t> temp;
    try{
        f.seekg(bitOffset);
        //dataStream = new char[height*width*bitCount/8];
        //f.read(dataStream, height*width*bitCount/8);
        //f.seekg(bitOffset);
        
        for(int i = 0; i < height; ++i){
            temp.clear();
            int padding = (4-(width%4)==4) ? 0 : 4-(width%4);
            for(int j = 0; j <width; ++j){
                switch(bitCount){
                    case 8:
                        char s;
                        f.read((char*) &s, sizeof(char));
                        temp.push_back(s);
                        break;
                    case 16:
                        break;
                    case 24:{
                        char *tempo = new char[bitCount/8];
                        f.read(tempo, (size_t)(bitCount/8));
                        temp.push_back(genInt(tempo, (size_t)(bitCount/8)));
                        delete tempo;
                    }
                    break;
                    case 32:{
                        char *tempo = new char[bitCount/8];
                        f.read(tempo, sizeof(uint32_t));
                        temp.push_back(genInt(tempo, (size_t)(bitCount/8)));
                        delete tempo;
                    }
                        break;
                    default:
                        return errBitCount;
                }

            }
            if(bitCount == 24 && padding != 0)
            {
                char *tempo = new char[padding];
                for(int i = 0; i < padding; ++i){
                    *(tempo+i) = 0;
                }
                temp.push_back(genInt(tempo, (size_t)(padding)));
                delete tempo;
            }
            bData.push_back(temp);
            temp.clear();
       }
        return errNoError;
    }
    catch(const std::exception& e){
        errHandle->printErrorStdEx(e);
        errHandle->printError(errBmDataRead);
        return errBmDataRead;
    }
    catch(...){
        errHandle->printError(errUnknown);
        errHandle->printError(errBmDataRead);
        return errBmDataRead;
    }
    return errBmDataRead;
}

uint32_t BitmapArray::genInt(char* c, size_t s){
    uint32_t returnValue = 0;
    //std::cout << filterMode << std::endl;
    for(int i = 0; i<s; ++i){
        if(filterMode == COLORA || filterMode == COLORB)
           returnValue |= (uint32_t)((uint8_t)*(c+s-1-i)<<(i*8)); //this will make orange output file
        else
            returnValue |= (uint32_t)((uint8_t)*(c+i)<<(i*8)); //this will make blueish output file
    }
    return returnValue;
}

void BitmapArray::printArray(char* c, size_t s){
    errHandle->printLog("Found this :");
    for(int i = 0; i<s; ++i){
        errHandle->printLog(std::to_string(+((uint8_t)(*(c+s-1-i)))) + " / ");
    }
    errHandle->printLog("\n");
}

/*I restructured the file. BitmapArray::infuse can be found in Private/Other Methods ~line 100*/





