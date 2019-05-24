/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.05.24
 * @brief BitmapArray-Class cpp file
 */
/* 
 * File:   BitmapArray.h
 * Author: Florian Leuze
 *
 * Created on 24. Mai 2019, 22:46
 */

#ifndef BITMAPARRAY_H
#define BITMAPARRAY_H

/**
 *@brief BitmapArray Class is supposed to contain image data of the bitmap file
 */
class BitmapArray {
public:
    //CONSTRUCTORS/DECONSTRUCTORS/************************************************************/
    /**
    * @brief Standard constructor.
    */
    BitmapArray();
    /**
     * @brief Copy Constructor. 
     * @param orig - Reference to original BitmapArray-type object
     */
    BitmapArray(const BitmapArray& orig);
    /**
     * Standard deconstructor.
     */
    virtual ~BitmapArray();
    
private:
};

#endif /* BITMAPARRAY_H */

