/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.06.09
 * @brief
 */
/* 
 * File:   Filter.cpp
 * Author: Florian Leuze
 * 
 * Created on 9. Juni 2019, 21:19
 */

#include "../header/Filter.h"

Filter::Filter() {
}

Filter::Filter(const Filter& orig) {
}

Filter::~Filter() {
}

//FILTERS/*******************************************************************************/
uint32_t Filter::revertUint(uint32_t d, size_t s){
    uint32_t out = 0;
    for(int i = 0; i < s; ++i){
        out |= invert(d >> i*8)<<i*8;
    }
    return out;
}

uint32_t Filter::invert(uint8_t w){
   w = (w & 0xF0) >> 4 | (w & 0x0F) << 4;
   w = (w & 0xCC) >> 2 | (w & 0x33) << 2;
   w = (w & 0xAA) >> 1 | (w & 0x55) << 1;
   return w;
}

uint32_t Filter::swapBytes(uint32_t d, size_t s){
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
    return 0;
}

uint32_t Filter::swapOctets(uint32_t d, size_t s){
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
    return 0;
}

uint32_t Filter::swapBytesOctets(uint32_t d, size_t s){return swapBytes(swapOctets(d, s), s);}

uint32_t Filter::swapBytesBits(uint32_t d, size_t s){return revertUint(swapBytes(d,s),s);}

uint32_t Filter::swapBytesOctetsBits(uint32_t d, size_t s){return revertUint(swapBytes(swapOctets(d, s), s),s);}



uint32_t Filter::swapBR(uint32_t d, size_t s){
    switch(s){
        case 1:
            return d;
        case 2:
            return (d & 0xFF00) >> 8 | (d & 0x00FF) << 8;
        case 3:
            return (d & 0xFF0000) >> 16 | (d & 0x0000FF) << 16;
        case 4:
            return (d & 0x00FF00FF) | ((d & 0xFF000000) >> 16 | (d & 0x0000FF00) << 16);
    }
    return 0;
}

uint32_t Filter::swapBG(uint32_t d, size_t s){
    switch(s){
        case 1:
            return d;
        case 2:
            return (d & 0xFF00) >> 8 | (d & 0x00FF) << 8;
        case 3:
            return (d & 0xFF0000) >> 16 | (d & 0x0000FF) << 16;
        case 4:
            return (d & 0x0000FFFF) | ((d & 0xFF000000) >> 8 | (d & 0x00FF0000) << 8);
    }
    return 0;
}

uint32_t Filter::swapGR(uint32_t d, size_t s){
    switch(s){
        case 1:
            return d;
        case 2:
            return (d & 0xFF00) >> 8 | (d & 0x00FF) << 8;
        case 3:
            return (d & 0xFF0000) >> 16 | (d & 0x0000FF) << 16;
        case 4:
            return (d & 0xFF0000FF) | ((d & 0x00FF0000) >> 8 | (d & 0x0000FF00) << 8);
    }
    return 0;
}

uint32_t Filter::substB(uint32_t d, size_t s){
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
    return 0;
}

uint32_t Filter::substR(uint32_t d, size_t s){
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
    return 0;
}

uint32_t Filter::substG(uint32_t d, size_t s){
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
    return 0;
}

/*uint32_t Filter::swap(uint32_t d, uint8_t posA, uint8_t posB){
    if(posA == posB)
        return d;
    else if(posA == )
}*/