/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.05.22
 * @brief Image-Class cpp file
 */
/* 
 * File:   Image.cpp
 * Author: Florian Leuze
 * 
 * Created on 22. Mai 2019, 19:57
 */

#include "../header/Image.h"

Image::Image() {
    path == "";
}

Image::Image(std::string p):path(p){
}

Image::Image(const Image& orig) {
}

Image::~Image() {
}

std::string Image::getPath(){
    if(path == "")
        return NULL;
    else
        return path;
}

void Image::setPath(std::string p){
    path = p;
}

void Image::printTextFile(std::string p){
    std::ifstream file(p.c_str());
    std::string out;
    while (getline(file,out)) {
        std::cout << out << std::endl ;
    }
    file.close();
}

void Image::writeTextFile(std::string t, std::string n){
    std::string path = "./"+n;
    std::ofstream file(path.c_str());
    file << t << std::endl;
    file.close();
}

int Image::readImage(){
    if(path == "")
        return 3;
    header = new BitmapHeader(path);
    array = new BitmapArray(path, header->getOffBits(), header->getWidth(), header->getHeight(), header->getBitCount());
    return 0;
}

BitmapHeader *Image::getBitmapHeader(){return header;}

int Image::generateBitmap(){
    std::cout << "opening ofstream" << std::endl;
    std::ofstream file("test.bmp", std::ios::binary | std::ios::trunc);
    std::cout << "writing header" << std::endl;
    file.write(header->getHeader(), header->getOffBits());
    std::cout << "header written and closing stream" << std::endl;
    file.close();
    std::cout << "opening ofstream" << std::endl;
    file.open("test.bmp", std::ios::binary | std::ios::app);
    std::cout << "reopened ofstream" << std::endl;
    //std::cout << "How its supposed to look: " << std::endl;
    //array->printArray();
   // std::cout << "How it really is: " << std::endl;
    long i = 0;
    std::vector<std::vector<uint32_t>> temp = array->getBData();
   // std::cout << "Height: " << temp.size() << std::endl;
    //std::cout << "Width: " << temp[0].size() << std::endl;
    for(auto itOuter = temp.begin(); itOuter != temp.end(); ++itOuter){
        for(auto itInner = itOuter->begin(); itInner != itOuter->end(); ++itInner){
            //std::cout << (uint16_t)*itInner << std::endl;
            switch(header->getBitCount()){
                case 8:
            file  << (uint8_t) *itInner;
                    break;
                case 16:
                    file  << (uint16_t) *itInner;
                    break;
                case 24:
                    file  << (uint32_t) *itInner;
                    break;
                case 32:
                    file  << (uint32_t) *itInner;
                    break;
                default:
                    exit(-1);
            }
        }
    }
    file.close();
    std::cout << "Finished writing" << std::endl;
    /*for(auto itOuter = array->getBData().begin(); itOuter != array->getBData().end(); ++itOuter){
        for(auto itInner = itOuter->begin(); itInner != itOuter->end(); ++itInner){
            std::cout << std::dec << i << ": " << (uint32_t)*itInner << std::endl;
                    file << (uint32_t)*itInner;
            ++i;
        }
    }*/
}