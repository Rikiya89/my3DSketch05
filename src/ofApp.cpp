#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetFrameRate(60);
    ofEnableDepthTest();
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    sound.load("path_to_your_audio_file.mp3");
    sound.setLoop(true);
    sound.play();

    bands = 512;
    spectrum = new float[bands]{0};

    pointLight.setDiffuseColor(ofColor(255, 255, 255));
    pointLight.setPosition(ofGetWidth()/2, ofGetHeight()/2, 200);

    for(int i = 0; i < numSpheres; i++) {
        positions.push_back(ofVec3f(ofRandom(-500, 500), ofRandom(-500, 500), ofRandom(-500, 500)));
        velocities.push_back(ofVec3f(ofRandom(-2, 2), ofRandom(-2, 2), ofRandom(-5, 5)));
        radii.push_back(10);
        colors.push_back(ofColor(0));
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    float time = ofGetElapsedTimef();

    spectrum = ofSoundGetSpectrum(bands);

    for(int i = 0; i < numSpheres; i++) {
        float noiseValue = ofNoise(positions[i].x * 0.01, positions[i].y * 0.01, time);
        radii[i] = ofMap(spectrum[i % bands], 0, 0.1, 10, 50);

        colors[i] = ofColor(
            ofMap(noiseValue, 0, 1, 50, 255),
            ofMap(spectrum[i % bands], 0, 0.1, 50, 255),
            ofMap(cos(time), -1, 1, 50, 255),
            150 // Setting a general semi-transparency
        );

        velocities[i] *= 0.95; // Damping

        // Attraction to the mouse
        if (ofGetMousePressed()) {
            ofVec3f mousePosition = cam.screenToWorld(ofVec3f(ofGetMouseX(), ofGetMouseY(), 0));
            ofVec3f force = mousePosition - positions[i];
            force.normalize();
            velocities[i] += force * mouseForce / (positions[i].distance(mousePosition) + 1);
        }

        positions[i] += velocities[i] * spectrum[i % bands] * 10;

        // Emitting particles
        if (ofRandom(1.0) < 0.05) { // 5% chance every frame
            Particle p;
            p.position = positions[i];
            p.velocity = velocities[i] * 0.5;
            particles.push_back(p);
        }
    }

    // Update particles
    for (int i = 0; i < particles.size(); i++) {
        particles[i].position += particles[i].velocity;
        particles[i].lifespan -= 1;
        if (particles[i].lifespan <= 0) {
            particles.erase(particles.begin() + i);
            i--;
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

        for (int j = i + 1; j < numSpheres; j++) {
            if (positions[i].distance(positions[j]) < connectionDistance) {
                ofDrawLine(positions[i], positions[j]);
            }
        }
    }

    for (auto& p : particles) {
        ofSetColor(255, 255, 255, (p.lifespan / 100.0) * 255);
        ofDrawSphere(p.position, 2);
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
