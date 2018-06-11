#include "mmPlayBar.h"

using namespace MoMa;

PlayBar::PlayBar(SceneApp* app,
                 MoMa::Position position,
                 MoMa::Position alignment,
                 MoMa::Canvas* parentUI,
                 int group,
                 bool minified) : Canvas(app, "Player", MoMa::Canvas::Container, position, alignment, NULL, parentUI, group, minified) {
  _container->setWidth(500);

  ofxGuiGroup* header = _container->addGroup("playbar_header",
                                             ofJson({{"flex-direction", "row"},
                                                     {"width", "100%"},
                                                     {"background-color", "transparent"},
                                                     {"show-header", false}}));

  timeSlider = header->add<ofxGuiFloatSlider>(_app->timeParam.set("time", .0f, _app->lowBound.time(), _app->lowBound.time()),
                                              ofJson({{"width", "80%"},
                                                      {"precision", 2},
                                                      {"border-width", 0}}));

  _app->timeParam.addListener(this, &PlayBar::timeChange);

  header->add<ofxGuiFloatSlider>(_app->speedParam.set("speed", 1.f, 0.1f, 25.f),
                                 ofJson({{"width", "20%"},
                                         {"precision", 1}}));

  ofxGuiGroup* player = _container->addGroup("playbar_player",
                                             ofJson({{"width", "100%"},
                                                     {"flex-direction", "row"},
                                                     {"padding", 0},
                                                     {"background-color", "transparent"},
                                                     {"show-header", false}}));

  ofJson buttonStyle = ofJson({{"type", "fullsize"},
                               {"width", "20%"},
                               {"text-align", "center"},
                               {"padding", "5 0"}});

  ofParameter<void> stopParam, prevParam, nextParam;

  player->add<ofxGuiToggle>(_app->playParam.set(">", false), buttonStyle);
  _app->playParam.addListener(this, &PlayBar::playChange);

  player->add<ofxGuiButton>(stopParam.set("X"), buttonStyle);
  stopParam.addListener(this, &PlayBar::stop);

  player->add<ofxGuiToggle>(scrubParam.set("<>", false), buttonStyle);
  scrubParam.addListener(this, &PlayBar::scrubChange);

  player->addSpacer({{"whidth", 10}});

  player->add<ofxGuiButton>(prevParam.set("|<"), buttonStyle);
  prevParam.addListener(this, &PlayBar::prev);

  player->add<ofxGuiButton>(nextParam.set(">|"), buttonStyle);
  nextParam.addListener(this, &PlayBar::next);

  player->add<ofxGuiToggle>(_app->reverseParam.set("<<", false), buttonStyle);

  setVisible(true);
  initCanvas();
}

void PlayBar::initCanvas() {
  setMinified(false);
  _container->setPosition(round(ofGetWidth() * .5f - _container->getWidth() * .5f),
                          round(ofGetHeight() - 20 - _container->getHeight()));
}

void PlayBar::pause() {
  if (_app->playParam)
    _app->pause();
}

void PlayBar::stop() {
  _app->setPlaybackMode(MoMa::PLAY);
  _app->playParam = false;
  _app->stop();
}

void PlayBar::playChange(bool& value) {
  if (value) {
    _app->play();
    _app->playParam.setName("||");
  } else {
    _app->pause();
    _app->playParam.setName(">");
  }
}

void PlayBar::timeChange(float& value) {
  if (timeSlider->isMousePressed()) {
    pause();
    _app->appMoment.setTime(value);
  }
}

void PlayBar::scrubChange(bool& value) {
  if (value) {
    pause();

    if (_app->activeMode == MoMa::SCENE3D)
      _app->setActiveMode(MoMa::SCENE2D);

    _app->setPlaybackMode(MoMa::SCRUB);
  } else {
    _app->setPlaybackMode(MoMa::PLAY);
  }
}

void PlayBar::prev() {
  pause();

  _app->previousIndex();
  update();
}

void PlayBar::next() {
  pause();

  _app->nextIndex();
  update();
}

void PlayBar::update() {
  if (_app->playbackMode == MoMa::SCRUB)
    scrubParam = true;
  else
    scrubParam = false;

  if (!timeBoundary && _app->highBound.time() != 0) {
    timeBoundary = true;

    _app->timeParam.setMin(_app->lowBound.time());
    _app->timeParam.setMax(_app->highBound.time());
  }

  _app->timeParam = _app->getAppTime();
}