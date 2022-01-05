#include "Menu_scene.h"
USING_NS_CC;

Scene* Menu_scene::createScene() {
  return Menu_scene::create();
}


bool Menu_scene::init() {

    auto main_label = Label::createWithTTF("Roller Splat BY makarov, Nawfal", "fonts/Marker Felt.ttf", 40);
    auto background_layer = LayerGradient::create(Color4B(0, 4, 40, 255), Color4B(0, 205, 172, 255));
    auto start = cocos2d::ui::Button::create("start.png","start_selected.png" );


    main_label->setPosition(Vec2(this->origin.x + this->size.width/2,
                            this->origin.y + this->size.height/2 + this->size.height/4));

    this->addChild(background_layer, -3);
    this->addChild(main_label, 6);

    start->setAnchorPoint(Vec2(0.5,0.5));
    start->setScale(0.5);
    start->setPosition(Vec2(this->origin.x + this->size.width/2 ,
                            this->origin.y + this->size.height/2 - 40));


    start->addClickEventListener([this](Ref* sender){
      auto director = Director::getInstance();
      director->replaceScene(TransitionFade::create(1, Scene1::createScene()));
    });
    this->addChild(start);

  return true;
}
