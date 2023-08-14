#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    ofEnableDepthTest();

    // Light setup
    pointLight.setDiffuseColor(ofColor(255, 255, 255));
    pointLight.setPosition(ofGetWidth()/2, ofGetHeight()/2, 200);

    // Generate initial positions, sizes, colors, and velocities
    for(int i = 0; i < numSpheres; i++) {
        positions.push_back(ofVec3f(ofRandom(-500, 500), ofRandom(-500, 500), ofRandom(-500, 500)));
        velocities.push_back(ofVec3f(ofRandom(-2, 2), ofRandom(-2, 2), ofRandom(-5, 5)));
        radii.push_back(0);
        colors.push_back(ofColor(0));
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    float time = ofGetElapsedTimef();

    for(int i = 0; i < numSpheres; i++) {
        float noiseValue = ofNoise(positions[i].x * 0.01, positions[i].y * 0.01, time);
        radii[i] = ofMap(noiseValue, 0, 1, 10, 50);

        // Update colors
        colors[i] = ofColor(
            ofMap(noiseValue, 0, 1, 50, 255),
            ofMap(sin(time), -1, 1, 50, 255),
            ofMap(cos(time), -1, 1, 50, 255)
        );

        // Move spheres along the z-axis
        positions[i] += velocities[i];

        // Central force causing them to revolve around the center
        ofVec3f toCenter = -positions[i];
        toCenter.normalize();
        velocities[i] += toCenter * 0.1;

        // Reset spheres that have moved too far back on z-axis
        if (positions[i].z < -1000) {
            positions[i].z += 2000;
        }
    }
}
//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();

    pointLight.enable();

    for(int i = 0; i < numSpheres; i++) {
        ofSetColor(colors[i]);
        ofDrawSphere(positions[i], radii[i]);
    }

    pointLight.disable();

    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
