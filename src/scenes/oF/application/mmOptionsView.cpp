#include "mmOptionsView.h"

using namespace MoMa;

Options::Options(SceneApp* app,
                 MoMa::Position position,
                 MoMa::Position alignment,
                 MoMa::Canvas* parentUI,
                 int group,
                 bool minified) : Canvas(app, "UI Options", MoMa::Canvas::Type::Group, position, alignment, NULL, parentUI, group, minified) {
  /*addLabelToggle( "SHOW 3D SCENE", app->is3dScene );
        addLabelToggle( "SHOW 3D GROUND", app->isGround );
        addLabelToggle( "SHOW NODE NAMES", app->isNodeNames );
        addLabelToggle( "SHOW ANNOTATIONS", app->isAnnotation );
        addLabelToggle( "SHOW 2D FIGURES", app->isFigure );
        addLabelToggle( "SHOW CAPTIONS", app->isCaptions );
        addLabelToggle( "SHOW TIMELINE", app->isTimeline );*/
  optionsGroup.add(_app->is3dScene);
  _app->is3dScene.addListener(this, &Options::optionsChange);

  optionsGroup.add(_app->isGround);
  _app->isGround.addListener(this, &Options::optionsChange);

  optionsGroup.add(_app->isNodeNames);
  _app->isNodeNames.addListener(this, &Options::optionsChange);

  optionsGroup.add(_app->isAnnotation);
  _app->isAnnotation.addListener(this, &Options::optionsChange);

  optionsGroup.add(_app->isFigure);
  _app->isFigure.addListener(this, &Options::optionsChange);

  optionsGroup.add(_app->isCaptions);
  _app->isCaptions.addListener(this, &Options::optionsChange);

  optionsGroup.add(_app->isTimeline);
  _app->isTimeline.addListener(this, &Options::optionsChange);

  optionsGroup.add(_app->shortcutDisplayed);
  _app->shortcutDisplayed.addListener(this, &Options::optionsChange);

  _container->add(optionsGroup);

  //   toggle3DScene = _container->add<ofxGuiToggle>("Show 3D Scene", _app->is3dScene);
  //   toggleGround = _container->add<ofxGuiToggle>("Show 3D Ground", _app->isGround);
  //   toggleNodeNames = _container->add<ofxGuiToggle>("Show Node Names", _app->isNodeNames);
  //   toggleAnnotations = _container->add<ofxGuiToggle>("Show Annotations", _app->isAnnotation);
  //   toggleFigure = _container->add<ofxGuiToggle>("Show 2D Figures", _app->isFigure);
  //   toggleCaption = _container->add<ofxGuiToggle>("Show Captions", _app->isCaptions);
  //   toggleTimeline = _container->add<ofxGuiToggle>("Show Timeline", _app->isTimeline);
  //   toggleShortcuts = _container->add<ofxGuiToggle>("Show Shortcuts", _app->shortcutDisplayed);

  //addLabelButton( "RESET OSC", false);

  setVisible(false);
  initCanvas();
}

void Options::optionsChange(bool& value) {
  for (unsigned short i = 0; i < optionsGroup.size(); ++i) {
    const bool& value = optionsGroup[i].cast<bool>();
    const string& name = optionsGroup[i].getName();

    if (name == "Show 3D Scene")
      _app->show3dScene(value);
    else if (name == "Show 3D Ground")
      _app->showGround(value);
    else if (name == "Show Node Names")
      _app->showNodeNames(value);
    else if (name == "Show Annotations")
      _app->showAnnotation(value);
    else if (name == "Show 2D Figures")
      _app->showFigures(value);
    else if (name == "Show Captions")
      _app->showCaptions(value);
    else if (name == "Show Timeline")
      _app->showTimeline(value);
    else if (name == "Show Shortcuts")
      _app->showShortcuts(value);
  }

  /*else if(e.widget->getKind() == OFX_UI_WIDGET_LABELBUTTON ) {

    if( name == "RESET OSC" ) {


    }
    }*/
}

void Options::update() {
  optionsGroup.getBool("Show 3D Scene").set(_app->is3dScene);
  optionsGroup.getBool("Show 3D Ground").set(_app->isGround);
  optionsGroup.getBool("Show Node Names").set(_app->isNodeNames);
  optionsGroup.getBool("Show Annotations").set(_app->isAnnotation);
  optionsGroup.getBool("Show 2D Figures").set(_app->isFigure);
  optionsGroup.getBool("Show Captions").set(_app->isCaptions);
  optionsGroup.getBool("Show Timeline").set(_app->isTimeline);
  optionsGroup.getBool("Show Shortcuts").set(_app->shortcutDisplayed);
}