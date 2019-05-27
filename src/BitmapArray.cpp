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

BitmapArray::BitmapArray(std::string p, uint32_t b, uint32_t w, uint32_t h, uint32_t bit) : path(p), bitOffset(b), width(w), height(h), bitCount(bit){
    for(auto itOuter = bData.begin(); itOuter != bData.end(); ++itOuter){
        itOuter->clear();
    }
    bData.clear();
    std::cout << "All went well in the constructor" << std::endl;
    readArray();
}

BitmapArray::BitmapArray(const BitmapArray& orig) {
}

BitmapArray::~BitmapArray() {
}

int BitmapArray::readArray(){
    std::cout << "Opening the stream" << std::endl;
    std::ifstream file(path);
    if(!file.good())
        return 3;
    read(file);
    std::cout << "Finished reading" << std::endl;
    file.close();
}

int BitmapArray::read(std::ifstream& f){
    std::cout << "And now reading the data" << std::endl;
    f.seekg(bitOffset);
    for(int i = 0; i < height; ++i){
        std::vector<uint32_t> temp;
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
                    return -1;
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
    return 0;
}

void BitmapArray::printArray(char* c, size_t s){
    std::cout << "Found this :" ;
    for(int i = 0; i<s; ++i){ 
        std::cout << +((uint8_t)(*(c+s-1-i))) << " / ";
    }
    std::cout << std::endl;
}


uint32_t BitmapArray::genInt(char* c, size_t s){
    uint32_t returnValue = 0;
    for(int i = 0; i<s; ++i){
        returnValue |= (uint32_t)((uint8_t)*(c+i)<<(i*8)); //this will make blueish output file
        //returnValue |= (uint32_t)((uint8_t)*(c+s-1-i)<<(i*8)); //this will make orange output file
    }
    return returnValue;
}

void BitmapArray::printArray(){
    int i = 0;
    for(auto itOuter = bData.begin(); itOuter != bData.end(); ++itOuter){
        int j = 0;
        std::cout << "Outer: " << i << std::endl;
        for(auto itInner = itOuter->begin(); itInner != itOuter->end(); ++itInner){
            std::cout << "Inner: " << j << " / "; 
            std::cout << (uint32_t)*itInner << std::endl;
            ++j;
        }
        ++i;
        std::cout << std::endl;
    }
}

std::vector<std::vector<uint32_t>> BitmapArray::getBData(){
    return bData;
}

std::string BitmapArray::infuse(std::string message){
    
    for(auto itOuter = bData.begin(); itOuter != bData.end(); ++itOuter){
        for(auto itInner = itOuter->begin(); itInner != itOuter->end(); ++itInner){
            *itInner |= 0x3;
        }
    }
    
    
    
    return "Successfully infused bitmap with message";
}


