// *********************************************************
// Image Class
// Author : Tamy Boubekeur (boubek@gmail.com).
// Copyright (C) 2010 Tamy Boubekeur.
// All rights reserved.
// *********************************************************

#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <vector>
#include <cassert>

#include "Vec3D.h"

class Image {
public:
    inline Image (unsigned int width, unsigned int height) : width (width), height (height) {
        unsigned int dataSize = 3*width*height;
        data = new float[dataSize];
        for (unsigned int i = 0; i < dataSize; i++)
            data[i] = 0.f;
    }
    inline Image (const Image & im) : width (im.getWidth ()), height (im.getHeight ()) {
        unsigned int dataSize = 3*width*height;
        data = new float[dataSize];
        for (unsigned int i = 0; i < dataSize; i++)
            data[i] = im.data[i];
    }
    inline virtual ~Image () { delete [] data; }
    
    inline Image & operator= (const Image & im) {
        delete [] data;
        width = im.getWidth ();
        height = im.getHeight ();
        unsigned int dataSize = 3*width*height;
        data = new float[dataSize];
        for (unsigned int i = 0; i < dataSize; i++)
            data[i] = im.data[i];
        return (*this);
    }        
    inline unsigned int getWidth () const { return width; }
    inline unsigned int getHeight () const { return height; }
    inline Vec3Df get (unsigned int x, unsigned int y) {
        unsigned int index = getIndex (x, y);
        return Vec3Df (data[index], data[index+1], data[index+2]);
    }
    inline void set (unsigned int x, unsigned int y, const Vec3Df & c) {
        assert (x < width && y < height);
        unsigned int index = getIndex (x, y);
        for (unsigned int i = 0; i < 3; i++)
            data[index+i] = c[i];
    }
    inline float * getData () { return data; }
        
    private:
    inline unsigned int getIndex (unsigned int x, unsigned int y) const { return 3*(y*width+x); } 
    unsigned int width;
    unsigned int height;
    float * data;
};


#endif // IMAGE_H

// Some Emacs-Hints -- please don't remove:
//
//  Local Variables:
//  mode:C++
//  tab-width:4
//  End:
