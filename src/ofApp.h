#pragma once

#include "ofMain.h"

struct Particle {
    ofVec3f position;
    ofVec3f velocity;
    float lifespan = 100.0f; // in frames
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
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
        
        vector<ofVec3f> positions;
        vector<ofVec3f> velocities;
        vector<float> radii;
        vector<ofColor> colors;
        vector<Particle> particles;

        ofEasyCam cam;
        ofLight pointLight;
        ofSoundPlayer sound;
        float *spectrum;
        int bands;

        int numSpheres = 500;
        float connectionDistance = 100.0f;
        int numGravityWells = 5;
        float mouseForce = 200.0f;
		
};
