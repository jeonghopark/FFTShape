#pragma once

#include "ofMain.h"

#include "ofxGui.h"

#include "Calligraphy.h"


class ofApp : public ofBaseApp{
    
public:
    
    void setup();
    void update();
    void draw();
    void exit();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofSoundPlayer glassscherben;
    ofSoundPlayer spacefunk;
    
    float * fftSmoothed;
    
    int nBandsToGet;
    float prevx, prevy;
    
    void normalFFT(float _yPos = 10);
    void lineCircleFFT(float _yPos = 200);
    void lineCircleCaptureFFT(float _yPos = 450);
    vector<float> captureFFTSmoothed;
    vector<int> captureFFTIndex;
    
    ofxPanel gui;
    
    ofxIntSlider captureTimer;
    ofxButton musicChange;
    int musicChangeIndex;


    void musicChangePressed();
    
    float xPosition;
    
    
    Calligraphy calligraphy;
    
    vector<Calligraphy> calligraphies;
    int calliYShift;
    bool bClliXPosChange;
    int calliIndex;
    vector<ofVec3f> calliPos;

};

