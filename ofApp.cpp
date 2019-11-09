#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);

	ofColor color;
	vector<int> hex_list = { 0x247BA0, 0x70C1B3, 0xB2DBBF, 0xF3FFBD, 0xFF1654 };
	for (auto hex : hex_list) {

		color.setHex(hex);
		this->color_list.push_back(color);
	}

	this->frame_mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face_mesh.clear();
	this->frame_mesh.clear();

	auto radius = 60;
	for (auto x = radius; x < ofGetWidth(); x += radius * 2) {

		for (auto y = radius; y < ofGetHeight(); y += radius * 2) {

			this->setStarToMesh(this->face_mesh, this->frame_mesh, glm::vec3(x, y, 0), radius * 0.9);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->face_mesh.drawFaces();
	//this->frame_mesh.drawWireframe();
}

//--------------------------------------------------------------
void ofApp::setStarToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float radius) {

	int deg_start = ofRandom(360);
	ofColor color = this->color_list[(int)ofRandom(this->color_list.size())];

	for (auto deg = deg_start; deg < deg_start + 360; deg += 72) {

		int face_index = face_target.getVertices().size();

		face_target.addVertex(location + glm::vec3(radius * 0.05 * cos(deg * DEG_TO_RAD), radius * 0.05 * sin(deg * DEG_TO_RAD), 0));
		face_target.addVertex(location + glm::vec3(radius * 0.5 * cos((deg - 28) * DEG_TO_RAD), radius * 0.5 * sin((deg - 28) * DEG_TO_RAD), 0));
		face_target.addVertex(location + glm::vec3(radius * 0.5 * cos((deg + 28) * DEG_TO_RAD), radius * 0.5 * sin((deg + 28) * DEG_TO_RAD), 0));
		face_target.addVertex(location + glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0));

		
		for (auto i = face_index; i < face_target.getVertices().size(); i++) {

			auto param = (deg_start + deg + ofGetFrameNum() * 3) % 360;
			param < 330 ? face_target.addColor(ofColor(color, ofMap(param, 0, 330, 255, 0))) : face_target.addColor(ofColor(color, 0));
		}

		face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 1); face_target.addIndex(face_index + 2);
		face_target.addIndex(face_index + 3); face_target.addIndex(face_index + 1); face_target.addIndex(face_index + 2);

		int frame_index = frame_target.getVertices().size();

		frame_target.addVertex(location + glm::vec3(radius * 0.05 * cos(deg * DEG_TO_RAD), radius * 0.05 * sin(deg * DEG_TO_RAD), 0));
		frame_target.addVertex(location + glm::vec3(radius * 0.5 * cos((deg - 28) * DEG_TO_RAD), radius * 0.5 * sin((deg - 28) * DEG_TO_RAD), 0));
		frame_target.addVertex(location + glm::vec3(radius * 0.5 * cos((deg + 28) * DEG_TO_RAD), radius * 0.5 * sin((deg + 28) * DEG_TO_RAD), 0));
		frame_target.addVertex(location + glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0));

		for (auto i = frame_index; i < frame_target.getVertices().size(); i++) {

			frame_target.addColor(color);
		}

		frame_target.addIndex(face_index + 0); frame_target.addIndex(face_index + 1);
		frame_target.addIndex(face_index + 0); frame_target.addIndex(face_index + 2);
		frame_target.addIndex(face_index + 3); frame_target.addIndex(face_index + 1);
		frame_target.addIndex(face_index + 3); frame_target.addIndex(face_index + 2);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}