#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofColor color;
	for (int i = 0; i < 1000; i++) {

		auto deg = ofRandom(360);
		auto location = glm::vec2(200 * cos(deg * DEG_TO_RAD), 200 * sin(deg * DEG_TO_RAD));
		auto next = glm::vec2(201 * cos(deg * DEG_TO_RAD), 201 * sin(deg * DEG_TO_RAD));

		this->location_list.push_back(location);
		if (ofRandom(100) < 50) {
		
			this->velocity_list.push_back(next - location);
		}
		else {

			this->velocity_list.push_back(location - next);
		}
		this->speed_list.push_back(ofRandom(5, 10));
		this->life_list.push_back(12);

		color.setHsb(0, 255, ofRandom(255));
		this->color_list.push_back(color);
	}

	for (int i = this->location_list.size() - 1; i >= 0; i--) {

		auto fueture = glm::normalize(this->velocity_list[i]) * 30;
		auto deg = ofMap(ofNoise(glm::vec3(this->location_list[i] * 0.01, ofGetFrameNum() * 0.005)), 0, 1, -360, 360);
		fueture = fueture + glm::vec2(10 * cos(deg * DEG_TO_RAD), 10 * sin(deg * DEG_TO_RAD));
		this->location_list[i] += glm::normalize(fueture) * this->speed_list[i];
		
		
		this->life_list[i] -= 1;

		if (this->life_list[i] < 0) {

			this->location_list.erase(this->location_list.begin() + i);
			this->velocity_list.erase(this->velocity_list.begin() + i);
			this->speed_list.erase(this->speed_list.begin() + i);
			this->life_list.erase(this->life_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int i = 0; i < this->location_list.size(); i++) {

		ofSetColor(this->color_list[i], ofMap(this->life_list[i], 0, 12, 32, 255));
		ofDrawCircle(this->location_list[i], 1.5);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}