#include "mmTextDialog.h"

using namespace MoMa;
using namespace std;

TextDialog::TextDialog(SceneApp* app) : Canvas(app, "Dialog", MoMa::Canvas::Type::Group, NULL) {
  _container->setConfig(ofJson({{"width", "100%"}}));

  // ofxGuiGroup* header = _container->addGroup("header", ofJson({{"flex-direction", "row"},
  //                                                              {"width", "100%"},
  //                                                              {"background-color", "transparent"},
  //                                                              {"show-header", false}}));

  _container->add<ofxGuiTextField>(txtInput.set("label"), ofJson({{"width", 250}}));

  ofxGuiGroup* form = _container->addGroup("dialog_form",
                                           ofJson({{"flex-direction", "row"},
                                                   {"width", "50%"},
                                                   {"padding", 0},
                                                   {"align-self", "flex-end"},
                                                   {"background-color", "transparent"},
                                                   {"show-header", false}}));

  ofJson buttonStyle = ofJson({{"type", "fullsize"},
                               {"text-align", "right"},
                               {"padding", "5 10 5 8"}});

  ofParameter<void> okParam, cancelParam;
  form->add<ofxGuiButton>(okParam.set("OK"), buttonStyle);
  okParam.addListener(this, &TextDialog::inputConfirm);

  form->add<ofxGuiButton>(cancelParam.set("cancel"), buttonStyle);
  cancelParam.addListener(this, &TextDialog::inputCancel);

  initCanvas();
}

void TextDialog::initCanvas() {
  setVisible(false);
  setMinified(false);
  _container->setPosition(round(ofGetWidth() * .5f - _container->getWidth() * .5f),
                          round(ofGetHeight() * .5f - _container->getHeight() * .5f));
}

void TextDialog::inputConfirm() {
  _app->storeEditorValue();
  setVisible(false);
}

void TextDialog::inputCancel() {
  --_app->selectedLabelIdx;
  _app->mouseEventRegLabelList->erase(_app->mouseEventRegLabelList->end());
  setVisible(false);
}