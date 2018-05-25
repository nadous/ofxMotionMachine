#include "mmOptionsView.h"

using namespace MoMa;

Options::Options(SceneApp* app,
                 MoMa::Position position,
                 MoMa::Position alignment,
                 MoMa::Canvas* parentUI,
                 int group,
                 bool minified) : Canvas(app, "View Options", MoMa::Canvas::Type::Panel, position, alignment, NULL, parentUI, group, minified) {
  /*addLabelToggle( "SHOW 3D SCENE", app->is3dScene );
        addLabelToggle( "SHOW 3D GROUND", app->isGround );
        addLabelToggle( "SHOW NODE NAMES", app->isNodeNames );
        addLabelToggle( "SHOW ANNOTATIONS", app->isAnnotation );
        addLabelToggle( "SHOW 2D FIGURES", app->isFigure );
        addLabelToggle( "SHOW CAPTIONS", app->isCaptions );
        addLabelToggle( "SHOW TIMELINE", app->isTimeline );*/

  viewOptionsGroup.add(_app->is3dScene.set("Show 3D Scene", true));
  _app->is3dScene.addListener(this, &Options::viewOptionsChange);

  viewOptionsGroup.add(_app->isGround.set("Show 3D Ground", true));
  _app->isGround.addListener(this, &Options::viewOptionsChange);

  viewOptionsGroup.add(_app->isNodeNames.set("Show Node Names", false));
  _app->isNodeNames.addListener(this, &Options::viewOptionsChange);

  viewOptionsGroup.add(_app->isAnnotation.set("Show Annotations", false));
  _app->isAnnotation.addListener(this, &Options::viewOptionsChange);

  viewOptionsGroup.add(_app->isFigure.set("Show 2D Figures", true));
  _app->isFigure.addListener(this, &Options::viewOptionsChange);

  viewOptionsGroup.add(_app->isCaptions.set("Show Captions", false));
  _app->isCaptions.addListener(this, &Options::viewOptionsChange);

  viewOptionsGroup.add(_app->isTimeline.set("Show Timeline", false));
  _app->isTimeline.addListener(this, &Options::viewOptionsChange);

  viewOptionsGroup.add(_app->shortcutDisplayed.set("Show Shortcuts", true));
  _app->shortcutDisplayed.addListener(this, &Options::viewOptionsChange);

  container->addSpacer(0, 10);
  //   toggle3DScene = container->add<ofxGuiToggle>("Show 3D Scene", _app->is3dScene);
  //   toggleGround = container->add<ofxGuiToggle>("Show 3D Ground", _app->isGround);
  //   toggleNodeNames = container->add<ofxGuiToggle>("Show Node Names", _app->isNodeNames);
  //   toggleAnnotations = container->add<ofxGuiToggle>("Show Annotations", _app->isAnnotation);
  //   toggleFigure = container->add<ofxGuiToggle>("Show 2D Figures", _app->isFigure);
  //   toggleCaption = container->add<ofxGuiToggle>("Show Captions", _app->isCaptions);
  //   toggleTimeline = container->add<ofxGuiToggle>("Show Timeline", _app->isTimeline);
  //   toggleShortcuts = container->add<ofxGuiToggle>("Show Shortcuts", _app->shortcutDisplayed);

  //addLabelButton( "RESET OSC", false);

  setVisible(false);
  initCanvas();
}

void Options::viewOptionsChange(bool& value) {
  for (unsigned short i = 0; i < viewOptionsGroup.size(); ++i) {
    const bool& value = viewOptionsGroup[i].cast<bool>();
    const string& name = viewOptionsGroup[i].getName();

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
      _app->displayShortcuts(value);
  }
  //   string name = e.widget->getName();  // We grab the name and test it
  /*if( e.widget->getKind() == OFX_UI_WIDGET_LABELTOGGLE ) {

    ofxUILabelToggle *toggle = (ofxUILabelToggle *) e.widget; // Toggle

    if( name == "SHOW 3D SCENE" ) app->show3dScene( toggle->getValue() );
    else if( name == "SHOW 3D GROUND" ) app->showGround( toggle->getValue() );
    else if( name == "SHOW NODE NAMES" ) app->showNodeNames( toggle->getValue() );
    else if( name == "SHOW ANNOTATIONS" ) app->showAnnotation( toggle->getValue() );
    else if( name == "SHOW 2D FIGURES" ) app->showFigures( toggle->getValue() );
    else if( name == "SHOW CAPTIONS" ) app->showCaptions( toggle->getValue() );
    else if( name == "SHOW TIMELINE" ) app->showTimeline( toggle->getValue() );
    }*/

  //   if (e.widget->getKind() == OFX_UI_WIDGET_TOGGLE) {
  //     ofxUIToggle* toggle = (ofxUIToggle*)e.widget;  // Toggle

  //     if (name == "Show 3D Scene")
  //       _app->show3dScene(toggle->getValue());
  //     else if (name == "Show 3D Ground")
  //       _app->showGround(toggle->getValue());
  //     else if (name == "Show Node Names")
  //       _app->showNodeNames(toggle->getValue());
  //     else if (name == "Show Annotations")
  //       _app->showAnnotation(toggle->getValue());
  //     else if (name == "Show 2D Figures")
  //       _app->showFigures(toggle->getValue());
  //     else if (name == "Show Captions")
  //       _app->showCaptions(toggle->getValue());
  //     else if (name == "Show Timeline")
  //       _app->showTimeline(toggle->getValue());
  //     else if (name == "Show Shortcuts")
  //       _app->displayShortcuts(toggle->getValue());
  //   }

  /*else if(e.widget->getKind() == OFX_UI_WIDGET_LABELBUTTON ) {

    if( name == "RESET OSC" ) {


    }
    }*/
}

void Options::update() {
  viewOptionsGroup.getBool("Show 3D Scene").set(_app->is3dScene);
  viewOptionsGroup.getBool("Show 3D Ground").set(_app->isGround);
  viewOptionsGroup.getBool("Show Node Names").set(_app->isNodeNames);
  viewOptionsGroup.getBool("Show Annotations").set(_app->isAnnotation);
  viewOptionsGroup.getBool("Show 2D Figures").set(_app->isFigure);
  viewOptionsGroup.getBool("Show Captions").set(_app->isCaptions);
  viewOptionsGroup.getBool("Show Timeline").set(_app->isTimeline);
  viewOptionsGroup.getBool("Show Shortcuts").set(_app->shortcutDisplayed);
}