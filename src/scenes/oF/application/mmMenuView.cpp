#include "mmMenuView.h"

using namespace MoMa;

MenuView::MenuView(SceneApp* app,
                   MoMa::Position position,
                   MoMa::Position alignment,
                   MoMa::Canvas* relative,
                   bool minified) : Canvas(app, "Menu", MoMa::Canvas::Type::Group, position, alignment, relative, NULL, NULL, true) {
  /*vector<string> playNames; // Mode names		
        playNames.push_back( "SCRUB MODE" );
        playNames.push_back( "PLAY MODE" );*/

  vector<string> focusModes;  // Mode names
  focusModes.push_back("Focus on 3D Scene");
  focusModes.push_back("Focus on 2D Figures");
  focusModes.push_back("Focus on Annotation");

  focusModeGroup.setName("Scene modes");
  unsigned short i = 0;
  for (auto it = focusModes.begin(); it != focusModes.end(); ++it, ++i) {
    ofParameter<bool> modeParam;
    focusModeGroup.add(modeParam.set(*it, i == activeFocusMode));
    modeParam.addListener(this, &MenuView::focusModeToggle);
  }

  ofxGuiContainer* focusModeGroupUi = _container->addContainer(focusModeGroup);
  focusModeGroupUi->setExclusiveToggles(true);
  focusModeGroupUi->loadTheme(getAbsoluteResPath() + "theme-radio.json");

  vector<string> uiOptions;
  uiOptions.push_back("View Player");
  uiOptions.push_back("View Options");
  uiOptions.push_back("View Other Canvas");

  i = 0;
  for (auto it = uiOptions.begin(); it != uiOptions.end(); ++it, ++i) {
    ofParameter<bool> uiOptionParam;
    uiOptionsGroup.add(uiOptionParam.set(*it, i != 1));
    uiOptionParam.addListener(this, &MenuView::uiOptionsChange);
  }

  _container->addContainer(uiOptionsGroup);

  //playRadio = addRadio( "ActivePlayMode", playNames, OFX_UI_ORIENTATION_VERTICAL );
  //addSpacer();

  initCanvas();
}

void MenuView::focusModeToggle(bool& value) {
  if (!value) {
    return;
  }

  for (unsigned short i = 0; i < focusModeGroup.size(); ++i) {
    if (focusModeGroup[i].cast<bool>() == true && activeFocusMode != i) {
      activeFocusMode = i;
      focusModeChange(focusModeGroup[i].getName());
      break;
    }
  }
}

void MenuView::focusModeChange(const string& name) {
  if (name == "Focus on 3D Scene")
    _app->setActiveMode(MoMa::SCENE3D);
  else if (name == "Focus on 2D Figures")
    _app->setActiveMode(MoMa::SCENE2D);
  else if (name == "Focus on Annotation")
    _app->setActiveMode(MoMa::ANNOTATE);
  //else if( name == "SCRUB MODE") app->setPlaybackMode( MoMa::SCRUB );
  //else if( name == "PLAY MODE") app->setPlaybackMode( MoMa::PLAY );

  /*if( app->activeMode == MoMa::SCENE3D ) app->show3dScene( true );
    else if( app->activeMode == MoMa::SCENE2D ) app->showFigures( true );
    else if( app->activeMode == MoMa::ANNOTATE ) app->showAnnotation( true );*/
}

void MenuView::uiOptionsChange(bool& value) {
  for (unsigned short i = 0; i < uiOptionsGroup.size(); ++i) {
    const string& name = uiOptionsGroup[i].getName();
    const bool& value = uiOptionsGroup[i].cast<bool>();

    if (name == "View Player") {
      if (value)
        openChildren(0);
      else
        closeChildren(0);
    }

    else if (name == "View Options") {
      if (value)
        openChildren(1);
      else
        closeChildren(1);
    }

    else if (name == "View Other Canvas") {
      if (!value)
        closeOtherCanvas();
      else
        reopenOtherCanvas();  // Show/hide the canvas
    }
  }

  /*if(name == "Options group 2") {

    if(((ofxUIToggle*)(e.widget))->getValue()) openChildren(1);
    else closeChildren();
    }*/
}

void MenuView::update() {
  // We check active mode and we switch the UI representation accordingly ( coherence! )
  if (_app->activeMode == MoMa::SCENE3D)
    focusModeGroup.getBool("Focus on 3D Scene").set(true);
  else if (_app->activeMode == MoMa::SCENE2D)
    focusModeGroup.getBool("Focus on 2D Figures").set(true);
  else if (_app->activeMode == MoMa::ANNOTATE)
    focusModeGroup.getBool("Focus on Annotation").set(true);

  // playBar->setValue(childrenOpened(0));
  // viewOptions->setValue(childrenOpened(1));

  //if( app->playbackMode == MoMa::SCRUB ) playRadio->activateToggle( "SCRUB MODE" );
  //else if( app->playbackMode == MoMa::PLAY ) playRadio->activateToggle( "PLAY MODE" );
}

void MenuView::closeOtherCanvas() {
  vector<Canvas*> tmp = getAllCanvas();
  closedCanvas.clear();
  for (int i = 0; i < tmp.size(); i++) {
    if (tmp[i]->isVisible() && tmp[i] != this && tmp[i] != getChildren()[0][0] && tmp[i] != getChildren()[1][0]) {
      tmp[i]->setVisible(false);
      closedCanvas.push_back(tmp[i]);
    }
  }
}

void MenuView::reopenOtherCanvas() {
  for (int i = 0; i < closedCanvas.size(); i++) {
    closedCanvas[i]->setVisible(true);
  }
  closedCanvas.clear();
}