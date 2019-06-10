/**
 * @file Expression file is undefined on line 2, column 12 in file:///home/florian/git/steganoMessage/nbproject/licenseheader.txt.
 * @author Florian Leuze (3308288) <st155013@stud.uni-stuttgart.de>
 * @date 2019.06.09
 * @brief
 */
/* 
 * File:   Filter.h
 * Author: Florian Leuze
 *
 * Created on 9. Juni 2019, 21:19
 */

#ifndef FILTER_H
#define FILTER_H

#include <cstdint>
#include <unistd.h>
/**
 *@brief Provides constant filter methods
 */
class Filter {
public:
    /**
    * @brief Standard constructor.
    */
    Filter();
    /**
     * @brief Copy Constructor. 
     * @param orig - Reference to original Filter-type object
     */
    Filter(const Filter& orig);
    /**
     * Standard deconstructor. 
     */
    virtual ~Filter();
    ///////////////////////////////////************************************************************/
    /**FILTERS**///////////////////////
    ///////////////////////////////////
    /*following functions are pretty performant. Mostly bit operations, rarely loops or anything. You can use them without too many worries even in big loops*/
    /**
     * @brief Turns the whole bit-pattern around
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern
     */
    static uint32_t revertUint(uint32_t d, size_t s);
    /**
     * @brief Turns the bit pattern of a single byte around. Slight noise and color shift into magenta in normal mode/yellow in crazy mode.
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern stored in first 2 bytes of the integer
     */
    static uint32_t invert(uint8_t w);
    /**
     * @brief Swaps the bytes as good as possible depending on value in s
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern
     */
    static uint32_t swapBytes(uint32_t d, size_t s);
    /**
     * @brief Swaps each octet pairs as good as possible depending on value in s. Strong color shift into magenta in normal mode/yellow in crazy mode.
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern
     */
    static uint32_t swapOctets(uint32_t d, size_t s);
    /**
     * @brief Swaps the bytes first and then each octets as good as possible depending on value in s. Very noisy filter. In normal mode shift into magenta, in crazy mode shift into yellow.
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern
     */
    static uint32_t swapBytesOctets(uint32_t d, size_t s);
    /**
     * @brief Swaps the bytes first and then the bits as good as possible depending on value in s. Strong noise and psychodelig color effect.
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern
     */
    static uint32_t swapBytesBits(uint32_t d, size_t s);
    /**
     * @brief Swaps the bytes first followed by the octets and bits as good as possible depending on value in s. Fluid like filter.  In normal mode shift into magenta, in crazy mode shift into yellow.
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern
     */
    static uint32_t swapBytesOctetsBits(uint32_t d, size_t s);
    /**
     * @brief Swaps Blue with Red value if size >= 24bit
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern
     */
    static uint32_t swapBR(uint32_t d, size_t s);
    /**
     * @brief Swaps Blue with Green value if size >= 24bit
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern
     */
    static uint32_t swapBG(uint32_t d, size_t s);
    /**
     * @brief Swaps Green with Red value if size >= 24bit
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern
     */
    static uint32_t swapGR(uint32_t d, size_t s);
    /**
     * @brief Substracts blue value from each channel if size >= 24bit
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern
     */
    static uint32_t substB(uint32_t d, size_t s);
    /**
     * @brief Substracts green value from each channel if size >= 24bit
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern
     */
    static uint32_t substG(uint32_t d, size_t s);
    /**
     * @brief Substracts red value from each channel if size >= 24bit. 
     * @param uint32_t d - bit pattern
     * @param size_t s - size of the part of the pattern that needs to be changed
     * @return uint32_t generated new bit pattern
     */
    static uint32_t substR(uint32_t d, size_t s);
private:

};

#endif /* FILTER_H */

