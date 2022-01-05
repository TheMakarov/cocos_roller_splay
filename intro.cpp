#include "Intro.h"
USING_NS_CC;

Scene* Intro_scene::createScene() {
  return Intro_scene::create();
}


bool Intro_scene::init() {

    auto main_label = Label::createWithTTF("Roller Splat", "fonts/Marker Felt.ttf", 40);
    auto down_label = Label::createWithTTF("Supervised by the wonderful Mr.EL Achaq ", "fonts/Marker Felt.ttf", 10);
    auto background_layer = LayerGradient(Color4B(2, 170, 176, 255), Color4B(0, 205, 172, 255));
    this->addChild(background_layer, -1);
    down_label->setPosition(Vec2(this->origin.x + down_label->getContentSize().width,
                            this->origin.y + down_label->getContentSize().height))
    main_label->setPosition(Vec2(this->origin.x + this->size.width/2,
                            this->origin.y + this->size.height/2 + this->size.height/4));


    this->addChild(main_label);
    this->addChild(down_label);


  return true;
}
