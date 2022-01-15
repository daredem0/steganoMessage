# steganoMessage
Tool to encrypt and decrypt a message withing a random graphic file (we support bitmap (8,16,24,32bit), JPEG and PNG).
The up to date version (currently feature-branch_opengl) relies heavily on the following external libs:
libjpeg-turbo, libpng, glew, sfml, glfw-x11
They are included as dependencies in PACKAGEBUILD. The cmake file will do the work for you and find the paths to include dirs and libs. 

Mainly as experiment to learn about steganography.

Project can be built with cmake file. Do:  
$./$ cmake .  -DCMAKE_DEBUG_TYPE=Full   <-(Full will build including OpenGL Renderer. Any other value, including empty will build without OpenGL Renderer)  
$./$ make  
Tested on Linux, not tested on OSX/Windows

***

***

Usage:
_steganoMessage_ is a command line tool to hide a message somewhere in a bitmap file.
Use either of the following as first switch to decide if you want to encrypt a message or decrypt a message. Add path of image file after the switch.
-decrypt\n
-encrypt 

***

**example**:

`./steganoMessage -encrypt <path>`  
This will start the routine to encrypt your message into example.bmp  
`./steganoMessage -decrypt <path>`  
This will start the routine to decrypt your message from example.bmp

`./steganoMessage -h`  
This will return the information contained in this help file.  

`./steganoMessage -convert_txt <path>`  
This will convert the bitmap file into a readable text file containing all information as hex values.

`./steganoMessage -filter <path> -filter <type>`  
Applies filter, possible values: `grey/color_a/color_b` <- Filters that are going to be applied while reading/writing  
`color` <- Dummy filter 
 
`inv_n/swap_by/swap_oc/swap_by_oc/swap_by_bi/swap_by_oc_bi/swap_bg/swap_br/swap_gr/subst_bl/subst_rd/subst_gr` <- Filters that will be applied after reading before writing. 
 
`./steganoMessage -filter_cr <path> -filter <type>`  
Activates crazy mode for filters. Same filter codes, automatically shifts the color.  
Sorry, no time yet to describe the filter effects. Just try.

Filters can also be applied automatically while adding a steganoMessage. This will likely mess up everything. Do:
`./steganoMessage -decrypt/-encrypt <path> -filter <type>`




Output into a textfile is possible with the switch -log. Usage is possible with and without filters:  
example a: `./steganoMessage -encrypt <path> -filter <type> -log`  
example b: `./steganoMessage -encrypt <path> -log`  
Logfile will be generated in log folder in ./ and will be named with a timestampm  

It is furthermore possible to view the processed image starting with version 0.3  
To view the image add -show at the end (this is important) of your call. Example:  
`./steganoMessage -encrypt <path> -show`  
`./steganoMessage -encrypt <path> -filter <type> -show`  
`./steganoMessage -encrypt <path> -filter <type> -log -show`  
