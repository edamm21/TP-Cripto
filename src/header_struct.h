//
// Created by Eugenio Damm on 03/05/2021.
//

#ifndef HEADER_STRUCT_H
#define HEADER_STRUCT_H

/*
 *  Header 	            14 bytes 	Windows Structure: BITMAPFILEHEADER

  	Signature 	        2 bytes 	0000h 	'BM'
    FileSize 	        4 bytes 	0002h 	File size in bytes
    reserved 	        4 bytes 	0006h 	unused (=0)
    DataOffset 	        4 bytes 	000Ah 	Offset from beginning of file to the beginning of the bitmap data

    InfoHeader 	        40 bytes 	  	Windows Structure: BITMAPINFOHEADER

    Size 	            4 bytes 	000Eh 	Size of InfoHeader =40
    Width 	            4 bytes 	0012h 	Horizontal width of bitmap in pixels
    Height 	            4 bytes 	0016h 	Vertical height of bitmap in pixels
    Planes 	            2 bytes 	001Ah 	Number of Planes (=1)
    Bits Per Pixel 	    2 bytes 	001Ch 	Bits per Pixel used to store palette entry information. This also identifies in an indirect way the number of possible colors. Possible values are:
                                            1 = monochrome palette. NumColors = 1
                                            4 = 4bit palletized. NumColors = 16
                                            8 = 8bit palletized. NumColors = 256
                                            16 = 16bit RGB. NumColors = 65536
                                            24 = 24bit RGB. NumColors = 16M
    Compression 	    4 bytes 	001Eh 	Type of Compression
                                            0 = BI_RGB   no compression
                                            1 = BI_RLE8 8bit RLE encoding
                                            2 = BI_RLE4 4bit RLE encoding
    ImageSize 	        4 bytes 	0022h 	(compressed) Size of Image
                                            It is valid to set this =0 if Compression = 0
    XpixelsPerM 	    4 bytes 	0026h 	horizontal resolution: Pixels/meter
    YpixelsPerM 	    4 bytes 	002Ah 	vertical resolution: Pixels/meter
    Colors Used 	    4 bytes 	002Eh 	Number of actually used colors. For a 8-bit / pixel bitmap this will be 100h or 256.
    Important Colors 	4 bytes 	0032h 	Number of important colors
                                            0 = all
 *
 */

struct header {
    // Header 14 bytes
    unsigned char signature[2]; // 0 1
    int fileSize; // 2 3 4 5
    unsigned char reserved[4]; // 6 7 8 9
    int dataOffset; // 10 11 12 13
    // InfoHeader 40 bytes
    int size; // 14 15 16 17
    int width; // 18 19 20 21
    int height; // 22 23 24 25
    int planes; // 26 27
    int bitsPerPixel; // 28 29
    int compression; // 30 31 32 33
    int imageSize; // 34 35 36 37
    int xPixelsPerM; // 38 39 40 41
    int yPixelsPerM; // 42 43 44 45
    int colorsUsed; // 46 47 48 49
    int importantColors; // 50 51 52 53
};

#endif //HEADER_STRUCT_H
