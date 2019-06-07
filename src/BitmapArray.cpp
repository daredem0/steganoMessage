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

BitmapArray::BitmapArray() {
    for(auto itOuter = bData.begin(); itOuter != bData.end(); ++itOuter){
        itOuter->clear();
    }
    bData.clear();
}

BitmapArray::BitmapArray(std::string p, uint32_t b, uint32_t w, uint32_t h, uint32_t bit, ErrorHandler *errH, std::string fm) : path(p), bitOffset(b), width(w), 
        height(h), bitCount(bit), errHandle(errH), filterMode(fm){
    for(auto itOuter = bData.begin(); itOuter != bData.end(); ++itOuter){
        itOuter->clear();
    }
    bData.clear();
    errHandle->printLog("All went well in the constructor\n");
    readArray();
}

BitmapArray::BitmapArray(const BitmapArray& orig) {
}

BitmapArray::~BitmapArray() {
}

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

int BitmapArray::read(std::ifstream& f){
    errHandle->printLog("And now reading the data\n");
    std::vector<uint32_t> temp;
    try{
        f.seekg(bitOffset);
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
                    }
                    break;
                    case 32:{
                        char *tempo = new char[bitCount/8];
                        f.read(tempo, sizeof(uint32_t));
                        temp.push_back(genInt(tempo, (size_t)(bitCount/8)));
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

void BitmapArray::printArray(char* c, size_t s){
    errHandle->printLog("Found this :");
    for(int i = 0; i<s; ++i){
        errHandle->printLog(std::to_string(+((uint8_t)(*(c+s-1-i)))) + " / ");
    }
    errHandle->printLog("\n");
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

std::vector<std::vector<uint32_t>> BitmapArray::getBData(){return bData;}

std::vector<std::vector<uint32_t>> *BitmapArray::getBDataPointer(){return &bData;}

int BitmapArray::setFilter(std::string fm){filterMode = fm;}

std::string BitmapArray::infuse(std::string message){
    
    //Function to evaluate what the size of the Bitmap ist
    //Different functions for different bit depths 
    //Iterate through message string only copying 2 bits at a time
    //Iterate through Bitmap masking each pixle 
    
    const int mask32bit = 0x3030303;    //Masks for Bitmap Bits
    const int mask24bit = 0x30303;
    const int mask16bit = 0x303;
    const int mask8bit = 0x3;
    const int mask8bit_n = 0xFC;
    
    auto itOuter = bData.begin();                           //Outer iterator of 2D Array
    auto itInner = itOuter->begin();                        //Inner iterator of 2D Array
    std::string::iterator chariterator = message.begin();   //Characteriterator for messagestring
    int flag = 0;                                           //Flag when reaching message end
    bool encoded = false;
    
    int messcharcounter = 1;            //Counter for each character in messagestring
    
    
    
    switch(bitCount){
        case 8:
            for(itOuter; itOuter != bData.end() && encoded != true; ++itOuter){
                for(itInner; itInner != itOuter->end() && encoded != true; ++itInner){
                    std::cout << "Old value: " << (*itInner&0x03) << std::endl;
                    *itInner &= mask8bit_n;
                    
                    if(messcharcounter<=4 && chariterator != message.end()){
                        std::cout << "Ended in infuse <=4" << std::endl;
                        *itInner |= (*chariterator >> (2*(4-messcharcounter))) & mask8bit; 
                        messcharcounter++;
                        std::cout << "New value: " << *itInner << std::endl;
                    }
                    
                    else if (messcharcounter>4 && chariterator != message.end()){
                        std::cout << "Ended in infuse >4" << std::endl;
                        messcharcounter = 1;
                        chariterator++;
                        --itInner; //ugly as shit
                    }
                    
                    //else if (messcharcounter<=4 && chariterator = message.end()){ // = propably unintended, won't build like this. Fixed it for you:
                    else if (messcharcounter<=4 && chariterator == message.end()){
                        std::cout << "Ended in infuse <=4 & end" << std::endl;
                        *itInner |= (*chariterator >> (2*(4-messcharcounter))) & mask8bit;
                        messcharcounter++;
                    }
                    
                    else{
                        std::cout << "Ended in infuse encoded = true" << std::endl;
                        encoded = true;   
                    }
                }
            }
            break;
            
        case 16:
            for(itOuter; itOuter != bData.end(); ++itOuter){
                for(itInner; itInner != itOuter->end(); ++itInner){
                    *itInner |= mask16bit;
                }
            }
            break;
        
        case 24:
            for(itOuter; itOuter != bData.end(); ++itOuter){
                for(itInner; itInner != itOuter->end(); ++itInner){
                    *itInner |= mask24bit;
                }
            }
            break;
        
        case 32:
            for(itOuter; itOuter != bData.end(); ++itOuter){
                for(itInner; itInner != itOuter->end(); ++itInner){
                    *itInner |= mask32bit;
                }
            }
            break;
    }
    
    
    
    
 /*  
   This is SHIT... Will get deleted soon
     
    std::string::iterator chariterator = message.begin();
    auto itOuter = bData.begin();
    auto itInner = itOuter->begin();
    int charcounter = 0;
    
    for(itOuter; itOuter != bData.end(); ++itOuter){
        for(itInner; itInner != itOuter->end(); ++itInner){
            for(chariterator; chariterator != message.end(); ++chariterator){
                *itInner |= 0x3;
                char character = *chariterator;
                char infusechar = 0xFF;
                switch (charcounter) {
                    case 0:
                        charcounter += 1;
                        break;
                        
                    case 1:
                        character = << << character;
                        charcounter += 1;
                        break;
                        
                    case 2:
                        character = << << << << character;
                        charcounter += 1;
                        break;
                        
                    case 3:
                        character = << << << << << << character;
                        charcounter = 0;
                        break;
                        
                    default:
                        break;
                }
                infusechar << << character;
                *itInner &= infusechar;
            }
        }
    }
*/
    return ""
            "\nSuccessfully infused bitmap with message\n"; /*you can send this to stdout inside here already. Ideally using errHandle->printLog(std::string whatever) to easily change from
    stdout to logfile in final build. Recommended to use integer as return value to send error code. Possible create constant in constant.h like - errInfuse which you could return here*/
}

