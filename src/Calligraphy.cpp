//
//  Calligraphy.cpp
//  MusicFFT_score
//
//  Created by JeongHo Park on 09/07/15.
//
//

#include "Calligraphy.h"


//--------------------------------------------------------------
void Calligraphy::inputFftSmoothed(float *_fft){
    
    fftSmoothed = _fft;
    
    int _index = 10;
    
    captureFFTSmoothed.clear();
    captureFFTIndex.clear();
    for(int i=0; i<_index; i++) {
        int _index = round(ofRandom(127));
        captureFFTIndex.push_back( _index );
        captureFFTSmoothed.push_back( fftSmoothed[_index] );
    }
    
}


//--------------------------------------------------------------
void Calligraphy::drawCali(float _xPos, float _yPos){
    
    ofPushStyle();
    
    ofNoFill();
    
    int _index = 10;
    
    
    float _height = 100;
    float _widthStep = 40;
    
    float _scaleUp = 0.3;
    
    
    ofSetColor(255, 120);
    
    ofBeginShape();
    
    for (int i = 0;i < _index; i++){
        float _fftFactor1 = pow(captureFFTSmoothed[ i ], _scaleUp);
        float _y1 = ofMap( _fftFactor1, 0, 1, 20, 128 );
        float _x1 = captureFFTIndex[i];
        
        float _xCircle = cos( captureFFTIndex[i] * 360 / 127.0 ) * _y1;
        float _yCircle = sin( captureFFTIndex[i] * 360 / 127.0 ) * _y1;
        
        ofCurveVertex(_xCircle + _xPos, _yCircle + _yPos);
        
    }
    
    ofEndShape();
    
    
    
    ofPopStyle();
    
}


