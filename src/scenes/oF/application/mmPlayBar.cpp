#include "mmPlayBar.h"

using namespace MoMa;

PlayBar::PlayBar(SceneApp* app,
                 MoMa::Position position,
                 MoMa::Position alignment,
                 MoMa::Canvas* parentUI,
                 int group,
                 bool minified) : Canvas(app, "Player", MoMa::Canvas::Container, position, alignment, NULL, parentUI, group, minified) {
  /*vector<string> buttons;
    //buttons.push_back( "PREV.");
    buttons.push_back("PLAY");
    buttons.push_back("PAUSE");
    buttons.push_back("STOP");
    //buttons.push_back("NEXT");
    playRadio = addRadio("Bar",buttons,OFX_UI_ORIENTATION_HORIZONTAL,OFX_UI_FONT_SMALL );*/

  ofxGuiGroup* root = _container->addGroup("root", ofJson({{"width", "100%"},
                                                          {"show-header", false}}));

  ofxGuiGroup* header = root->addGroup("header", ofJson({{"flex-direction", "row"},
                                                         {"width", "100%"},
                                                         {"background-color", "transparent"},
                                                         {"show-header", false}}));
  ofParameter<string> playLabel;
  playLabel.set("Player");
  header->add<ofxGuiLabel>(playLabel, ofJson({{"width", "100%"}}));

  ofxGuiGroup* player = root->addGroup("player", ofJson({{"flex-direction", "row"},
                                                         {"align-items", "space-around"},
                                                         {"align-self", "flex-end"},
                                                         {"padding", 0},
                                                         {"background-color", "transparent"},
                                                         {"show-header", false}}));

  header->add<ofxGuiTextField>(timeParam.set("time", "0.0"), ofJson({{"width", "50%"}}));
  timeParam.addListener(this, &PlayBar::timeChange);

  header->add<ofxGuiFloatInputField>(timeSpeedParam.set("speed", _app->playSpeed, .1f, 100.f), ofJson({{"width", "50%"}}));
  timeSpeedParam.addListener(this, &PlayBar::timeSpeedChange);

  // ofParameter<float> timeSlider;
  root->add<ofxGuiFloatSlider>(timeSliderParam.set(.0f), ofJson({{"width", "100%"}, {"precision", 2}}));
  timeSliderParam.addListener(this, &PlayBar::timeSliderChange);

  ofJson buttonStyle = ofJson({{"type", "fullsize"},
                               {"text-align", "right"},
                               {"padding", "5 10 5 8"}});

  ofParameter<void> playParam, stopParam, prevParam, nextParam;
  ofParameter<bool> reverseParam;

  playButton = player->add<ofxGuiButton>(playParam.set(">"), buttonStyle);
  playParam.addListener(this, &PlayBar::play);

  player->add<ofxGuiButton>(stopParam.set("X"), buttonStyle);
  stopParam.addListener(this, &PlayBar::stop);

  player->add<ofxGuiToggle>(scrubParam.set("<>", false), buttonStyle);
  scrubParam.addListener(this, &PlayBar::scrub);

  player->addSpacer(5, 0);

  player->add<ofxGuiButton>(prevParam.set("|<"), buttonStyle);
  prevParam.addListener(this, &PlayBar::prev);

  player->add<ofxGuiButton>(nextParam.set(">|"), buttonStyle);
  nextParam.addListener(this, &PlayBar::next);

  reverseButton = player->add<ofxGuiToggle>(reverseParam.set("<<", false));
  reverseParam.addListener(this, &PlayBar::reverse);

  // this above is useless
  // isNext = false;
  // isPrev = false;
  // nextspeed = false;
  // prevspeed = false;
  // enteringFrame = false;
  // enteringSpeed = false;

  playingState = app->isPlayback;
  setVisible(true);
  initCanvas();

  // string title1 = "Time (s)";
  // string title2 = "Speed";
  // int title1width = canvasTitle->getStringWidth(title1);
  // int framepos = timeinput->getRect()->getX(false);
  // int framewidth = timeinput->getRect()->getWidth();
  // int title1pos = framepos + (double)framewidth / 2 - (double)title1width / 2;
  // int title2width = canvasTitle->getStringWidth(title2);
  // int speedpos = speedinput->getRect()->getX(false);
  // int speedwidth = speedinput->getRect()->getWidth();
  // int title2pos = speedpos + (double)speedwidth / 2 - (double)title2width / 2;

  // ofxUILabel* canvasTitle1 = new ofxUILabel(title1pos, canvasTitle->getRect()->getY(false), title1width + 10, title1, title1, canvasTitle->getSize());
  // ofxUILabel* canvasTitle2 = new ofxUILabel(title2pos, canvasTitle->getRect()->getY(false), title2width + 10, title2, title2, canvasTitle->getSize());
  // addWidget(canvasTitle1);
  // addWidget(canvasTitle2);

  /*cout << "canvas title: " << canvasTitle->getRect()->getX(false) << endl;
    cout << canvasTitle->getRect()->getY(false) << endl;
    cout <<  canvasTitle->getRect()->getWidth() << endl;
    cout << "canvas title1: " << canvasTitle1->getRect()->getX(false) << endl;
    cout << canvasTitle1->getRect()->getY(false) << endl;
    cout << canvasTitle1->getRect()->getWidth() << endl;
    cout << "canvas title2: " << canvasTitle2->getRect()->getX(false) << endl;
    cout << canvasTitle2->getRect()->getY(false) << endl;
    cout << canvasTitle2->getRect()->getWidth() << endl;*/
}

void PlayBar::initCanvas() {
  setMinified(false);
  _container->setPosition(round(ofGetWidth() * .5f - _container->getWidth() * .5f),
                         round(ofGetHeight() - 20 - _container->getHeight()));
}

void PlayBar::play() {
  if (playingState) {
    pause();
  } else {
    _app->setPlaybackMode(MoMa::PLAY);
    _app->play();
    playButton->setName("||");
    playingState = true;
  }
}

void PlayBar::stop() {
  _app->setPlaybackMode(MoMa::PLAY);
  _app->stop();
  playButton->setName(">");
  playingState = false;
}

void PlayBar::scrub(bool& value) {
  if (value) {
    pause();

    if (_app->activeMode == MoMa::SCENE3D) {
      _app->setActiveMode(MoMa::SCENE2D);
    }

    _app->setPlaybackMode(MoMa::SCRUB);
  } else {
    _app->setPlaybackMode(MoMa::PLAY);
  }
}

void PlayBar::prev() {
  pause();
  isPrev = true;
  isNext = false;
}

void PlayBar::next() {
  pause();
  isNext = true;
  isPrev = false;
}

void PlayBar::timeChange(string& value) {
  if (!enteringFrame) {  //Beginning typing

    pause();
    enteringFrame = true;
    timeParam = "";
    // timeinput->setTextString("");
  }

  enteringFrame = false;
  double mytime;

  try {
    mytime = stof(timeParam);
    _app->appMoment.setTime(mytime);
  } catch (const std::invalid_argument& ia) {
    std::cerr << "Invalid timestamp: " << timeParam << '\n';
    // timeValue = ofStringTimesInString(_app->getAppTime())
    timeParam = ofToString(_app->getAppTime(), 2);
  }
}

void PlayBar::reverse(bool& value) {
  _app->setPlaybackMode(MoMa::PLAY);

  if (value) {
    nextspeed = false;
    prevspeed = true;
    reverseButton->setName(">>");
  } else {
    nextspeed = true;
    prevspeed = false;
    reverseButton->setName("<<");
  }
}

void PlayBar::timeSpeedChange(float& value) {
  if (!enteringSpeed) {  //Beginning typing
    _app->setPlaybackMode(MoMa::PLAY);
    enteringSpeed = true;
    timeSpeedParam = .0f;
  }

  enteringSpeed = false;
  _app->playSpeed = value;
}

void PlayBar::timeSliderChange(float& value) {
  pause();
  _app->appMoment.setTime(value);
}

void PlayBar::update() {
  /*if( app->isPlaying() ) playRadio->activateToggle( "PLAY" );
    else if( app->getAppIndex()>0 ) playRadio->activateToggle( "PAUSE" );
    else playRadio->activateToggle( "STOP" );*/

  if (playingState != _app->isPlaying()) {
    playingState = _app->isPlaying();
    if (playingState)
      playButton->setName("||");
    // bt_play->getImage()->loadImage(libPath + "GUI/bt_pause.png");
    else
      playButton->setName(">");
    // bt_play->getImage()->loadImage(libPath + "GUI/bt_play.png");
  }

  if (_app->playbackMode == MoMa::SCRUB)
    scrubParam = true;
  // bt_scrub->setValue(true);
  else
    scrubParam = false;
  // bt_scrub->setValue(false);
  //getCanvasTitle()->setLabel( "Index : " + ofToString(app->getAppIndex()) + "\t - Time : " + ofToString(app->getAppTime()) );
  //getCanvasTitle()->setLabel(ofToString(app->getAppTime()) + " s | frame " + ofToString(app->getAppIndex()));
  //txt_index->setTextString("Index : " + ofToString(app->getAppIndex()) );

  timeSliderParam.setMin(_app->lowBound.time());
  timeSliderParam.setMax(_app->highBound.time());
  timeSliderParam = _app->getAppTime();

  timeParam = ofToString(_app->getAppTime(), 2);

  if (!enteringSpeed) {
    timeSpeedParam = _app->playSpeed;
  }
  if (!enteringFrame) {
    timeParam = ofToString(_app->getAppTime(), 2);
  }

  /*if (app->frameRate > frslider->getMax()) frslider->setMax(1.5*app->frameRate);
    frslider->setValue(app->frameRate);

    frslider->getLabelWidget()->setLabel("framerate: " + ofToString(app->frameRate));*/

  if (isNext) {
    _app->nextIndex();
  } else if (isPrev) {
    _app->previousIndex();
  }
  if (nextspeed) {
    _app->playSpeed = min(_app->playSpeed + 0.1, 100.0);
  } else if (prevspeed) {
    _app->playSpeed = max(_app->playSpeed - 0.1, 0.1);
  }

  //Update text label
  /*string text;
    if (app->playbackMode == MoMa::SCRUB) text = "Press p for playback mode. ";
    else text = "Press s for scrub mode. ";
    if(app->activeMode == MoMa::SCENE3D) text = text + "Press 2/a for 2D/annotation focus. ";
    else if(app->activeMode == MoMa::SCENE2D) text = text + "Press 3/a for 3D/annotation focus. ";
    else if (app->activeMode == MoMa::ANNOTATE) text = text + "Press 2/3 for 2D/3D focus. ";
    if (app->lowBound.time() == app->minBound.time() && app->highBound.time() == app->maxBound.time()) text = text + "Hold z to zoom.";
    else text = text + "Press u to unzoom.";*/
  //textlabel->setLabel(text);
}

void PlayBar::pause() {
  _app->setPlaybackMode(MoMa::PLAY);
  _app->pause();
  playingState = false;
  playButton->setName(">");
  // bt_play->getImage()->loadImage(libPath + "GUI/bt_play.png");
}