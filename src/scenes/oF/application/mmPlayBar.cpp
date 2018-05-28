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

  // ofxGuiGroup* root = _container->addGroup("root", ofJson({{"width", 500}, {"show-header", false}}));
  _container->setConfig(ofJson({{"width", 500}, {"show-header", false}}));

  ofxGuiGroup* header = _container->addGroup("header",
                                             ofJson({{"flex-direction", "row"},
                                                     {"width", "100%"},
                                                     {"background-color", "transparent"},
                                                     {"show-header", false}}));

  header->add<ofxGuiFloatSlider>(_app->timeParam.set("time", .0f, _app->lowBound.time(), _app->lowBound.time()),
                                 ofJson({{"width", "80%"},
                                         {"precision", 2},
                                         {"border-width", 0}}));

  _app->timeParam.addListener(this, &PlayBar::timeChange);

  header->add<ofxGuiFloatSlider>(_app->speedParam.set("speed", 1.f, 0.1f, 25.f),
                                 ofJson({{"width", "20%"},
                                         {"precision", 1}}));

  ofxGuiGroup* player = _container->addGroup("player",
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

  player->add<ofxGuiToggle>(_app->playParam, buttonStyle);
  _app->playParam.addListener(this, &PlayBar::playChange);

  player->add<ofxGuiButton>(stopParam.set("X"), buttonStyle);
  stopParam.addListener(this, &PlayBar::stop);

  player->add<ofxGuiToggle>(scrubParam.set("<>", false), buttonStyle);
  scrubParam.addListener(this, &PlayBar::scrubChange);

  player->addSpacer(5, 0);

  player->add<ofxGuiButton>(prevParam.set("|<"), buttonStyle);
  prevParam.addListener(this, &PlayBar::prev);

  player->add<ofxGuiButton>(nextParam.set(">|"), buttonStyle);
  nextParam.addListener(this, &PlayBar::next);

  player->add<ofxGuiToggle>(_app->reverseParam.set("<<", false), buttonStyle);

  // this above is useless
  // isNext = false;
  // isPrev = false;
  // nextspeed = false;
  // prevspeed = false;
  // enteringFrame = false;
  // enteringSpeed = false;

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
  pause();
  _app->appMoment.setTime(value);
}

void PlayBar::scrubChange(bool& value) {
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

  _app->previousIndex();
  update();
}

void PlayBar::next() {
  pause();

  _app->nextIndex();
  update();
}

void PlayBar::update() {
  /*if( app->isPlaying() ) playRadio->activateToggle( "PLAY" );
    else if( app->getAppIndex()>0 ) playRadio->activateToggle( "PAUSE" );
    else playRadio->activateToggle( "STOP" );*/

  if (_app->playbackMode == MoMa::SCRUB)
    scrubParam = true;
  // bt_scrub->setValue(true);
  else
    scrubParam = false;
  // bt_scrub->setValue(false);
  //getCanvasTitle()->setLabel( "Index : " + ofToString(app->getAppIndex()) + "\t - Time : " + ofToString(app->getAppTime()) );
  //getCanvasTitle()->setLabel(ofToString(app->getAppTime()) + " s | frame " + ofToString(app->getAppIndex()));
  //txt_index->setTextString("Index : " + ofToString(app->getAppIndex()) );

  if (!timeBoundary && _app->highBound.time() != 0) {
    timeBoundary = true;

    _app->timeParam.setMin(_app->lowBound.time());
    _app->timeParam.setMax(_app->highBound.time());
  }

  _app->timeParam = _app->getAppTime();

  /*if (app->frameRate > frslider->getMax()) frslider->setMax(1.5*app->frameRate);
    frslider->setValue(app->frameRate);

    frslider->getLabelWidget()->setLabel("framerate: " + ofToString(app->frameRate));*/

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