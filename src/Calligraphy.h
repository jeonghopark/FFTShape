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
    
    
    float * fftSmoothed;
    vector<float> captureFFTSmoothed;
    vector<int> captureFFTIndex;
    
    
public :

    void inputFftSmoothed(float * _fft);
    void drawCali(float _xPos, float _yPos);
    
    
};


#endif /* defined(__MusicFFT_score__Calligraphy__) */
