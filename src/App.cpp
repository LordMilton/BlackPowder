﻿#include <cstdlib>
#include "App.h"
#include "GameMaster.h"
#include "Sand.h"

App::App() : piksel::BaseApp() {
    initialize();
}

App::App(std::string title, bool fullscreen) : piksel::BaseApp(title, fullscreen) {
    initialize();
}

App::App(int width, int height, std::string title) : piksel::BaseApp(width, height, title) {
    initialize();
}

App::~App() {}

void App::initialize() {
    this->gm = std::make_unique<GameMaster>();
}

void App::setup() {
    // load fonts and images here
}

void App::draw(piksel::Graphics& g) {
    g.background(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    this->gm->run(g);
}

void App::mouseMoved(int x, int y) {
    gm->mouseMoved(x,y);
}

void App::mousePressed(int button) {
    gm->mousePressed(button);
}

void App::mouseReleased(int button) {
    gm->mouseReleased(button);
}

int main() {
	std::unique_ptr<App> app = std::make_unique<App>(800, 800, "Black Powder");
    //App app("Black Powder", false);
	app->start();
}