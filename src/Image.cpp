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
}
