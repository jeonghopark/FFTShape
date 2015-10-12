//
//  Calligraphy.h
//  MusicFFT_score
//
//  Created by JeongHo Park on 09/07/15.
//
//

#ifndef __MusicFFT_score__Calligraphy__
#define __MusicFFT_score__Calligraphy__

#include "ofMain.h"

class Calligraphy{
    
    
    vector<float> fftSmoothed;
    vector<float> captureFFTSmoothed;
    vector<int> captureFFTIndex;
    
    
public :

    Calligraphy();
    ~Calligraphy();
    
    void inputFftSmoothed(vector<float> );
    void draw(float _xPos, float _yPos);
    
    int calliSize;
};


#endif /* defined(__MusicFFT_score__Calligraphy__) */
