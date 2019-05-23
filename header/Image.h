/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.05.22
 * @brief Image-Class header file
 */
/* 
 * File:   Image.h
 * Author: Florian Leuze
 *
 * Created on 22. Mai 2019, 19:57
 */

#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <fstream>
#include <iostream>

/**
 *@brief Image Class is implemented to store the bitstream of the image file as well as the filepath and to offer easy to use methods to extract information from the image file
 */
class Image {
public:
    //CONSTRUCTORS/DECONSTRUCTORS/************************************************************/
    /**
    * @brief Standard constructor.
    */
    Image();
    /**
    * @brief Non-Standard constructor. Initializes the object with a path.
    * @param std::string p - path that is to be stored in the object.
    */
    Image(std::string p);
    /**
     * @brief Copy Constructor. 
     * @param orig - Reference to original Image-type object
     */
    Image(const Image& orig);
    /**
     * Standard deconstructor.
     */
    virtual ~Image();
    /**
     * @brief Returns the path of the image.
     * @return std::string including stored path.
     */
    std::string getPath();
    /**
     * @brief Stores path in this.
     * @param std::string p - Path to the image file.
     */
    void setPath(std::string p);
    
    void printTextFile(std::string p);
private:
    std::string path; /**< Imagepath*/

};

#endif /* IMAGE_H */

