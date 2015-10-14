//
//  Calligraphy.h
//  MusicFFT_score
//
//  Created by JeongHo Park on 09/07/15.
//
//

#pragma once

#ifndef __MusicFFT_score__Calligraphy__
#define __MusicFFT_score__Calligraphy__

#include "ofMain.h"

#include "BaseArch.h"
#include "ofxProcessFFT.h"

class Calligraphy{
    
    vector<float> captureFFTSmoothed;
    vector<int> captureFFTIndex;
    
    vector<Calligraphy> calligraphies;
    vector<ofVec2f> calliPos;

    
public :

    Calligraphy();
    ~Calligraphy();
    
    void setup();
    void update();
    void inputBaseArch(BaseArch & _baseArch);
    void inputFFTP(ProcessFFT & _processFFT);
    void inputFftSmoothed(vector<float> );
    void draw();
    void drawElement(float _xPos, float _yPos, int _h);
    
    BaseArch * baseArch;
    ProcessFFT * processFFT;
    
    int calliSize;
    
    int calliYShift;
    bool bClliXPosChange;
    int calliIndex;

    
    
};


#endif /* defined(__MusicFFT_score__Calligraphy__) */
