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
    std::cout << "Now opening the stream" << std::endl;
    std::ifstream file(path);
    if(!file.good())
        return 3;
    read(file);
    std::cout << "Finished reading" << std::endl;
    file.close();
    std::cout << "Stream closed, waiting for input" << std::endl;
    //printArray();
    std::cout << "Finishhed printing" << std::endl;
}

void BitmapArray::read(std::ifstream& f){
    std::cout << "And now reading the data" << std::endl;
    f.seekg(bitOffset-1);
    for(int i = 0; i < height; ++i){
        std::vector<uint32_t> temp;
        temp.clear();
        uint32_t s;
        //std::cout << "Outer Nr.: " << i << std::endl;
        for(int j = 0; j <width; ++j){
            std::cout << "Inner Nr.: " << j << " / ";
            f.read((char*) &s, sizeof(char));
            std::cout << "Found this: " << (uint16_t)s << std::endl;
            temp.push_back(s);
        }
        bData.push_back(temp);
        std::cout << "Finished " << i << std::endl;
        temp.clear();
   }
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

std::ofstream BitmapArray::getBDataStream(){
    std::ofstream temp;
    for(auto itOuter = bData.begin(); itOuter != bData.end(); ++itOuter){
        for(auto itInner = itOuter->begin(); itInner != itOuter->end(); ++itInner){
            switch(bitCount){
                case 8:
                    temp << (uint8_t)*itInner;
                    break;
                case 16:
                    temp << (uint16_t)*itInner;
                    break;
                case 24:
                    uint16_t a;
                    uint8_t b;
                    a = (uint16_t)*itInner;
                    b = (uint8_t) (*itInner >> 16);
                    temp << a << b;
                    break;
                case 32:
                    temp << (uint32_t)*itInner;
                    break;
                default:
                    exit(-1);
                
            }
        }
    }
    return temp;
}
/*
    for(auto itOuter = bData.begin(); itOuter != bData.end(); ++itOuter){
        for(auto itInner = itOuter->begin(); itInner != itOuter->end(); ++itInner){
            
        }
    }
 */

/*
  f.seekg(0, std::ios::beg);
    //File Header
    f.read((char*) &bfType, sizeof(bfType));
    fixType();
    f.read((char*) &bfSize, sizeof(bfSize));
    f.read((char*) &bfReserved, sizeof(bfReserved));
    f.read((char*) &bfOffBits, sizeof(bfOffBits));*/