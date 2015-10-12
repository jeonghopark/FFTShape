//
//  Calligraphy.cpp
//  MusicFFT_score
//
//  Created by JeongHo Park on 09/07/15.
//
//

#include "Calligraphy.h"


//--------------------------------------------------------------
Calligraphy::Calligraphy(){
 
    calliSize = 20;
    
}



//--------------------------------------------------------------
Calligraphy::~Calligraphy(){
    
}





//--------------------------------------------------------------
void Calligraphy::inputFftSmoothed(vector<float> _fft){
    
    fftSmoothed = _fft;
    
    captureFFTSmoothed.resize(calliSize);
    captureFFTIndex.resize(calliSize);

    for(int i=0; i<calliSize; i++) {

        int _index = round( ofRandom(60) );
        captureFFTIndex[i] = _index;
        captureFFTSmoothed[i] = fftSmoothed[_index];
        
    }
    
}


//--------------------------------------------------------------
void Calligraphy::draw(float _xPos, float _yPos){
    
    ofPushStyle();
    
    ofNoFill();
    
    ofSetColor(255);
    
    ofBeginShape();
    
    for (int i=0; i<calliSize; i++){
        float _fftFactor1 = captureFFTSmoothed[i] * 5;
        float _x1 = captureFFTIndex[i];
        
        float _xCircle = cos( captureFFTIndex[i] * 36 / 127.0 ) * _fftFactor1;
        float _yCircle = sin( captureFFTIndex[i] * 36 / 127.0 ) * _fftFactor1;
        
        ofCurveVertex(_xCircle + _xPos, _yCircle + _yPos);
        
    }
    
    ofEndShape();
    
    
    
    ofPopStyle();
    
}


