#include "Intro.h"
#include "Menu_scene.h"
USING_NS_CC;

Scene* Intro_scene::createScene() {
  return Intro_scene::create();
}


bool Intro_scene::init() {

    auto main_label = Label::createWithTTF("Roller Splat", "fonts/Marker Felt.ttf", 40);
    auto down_label = Label::createWithTTF("Supervised by the wonderful Mr.EL Achaq ", "fonts/Marker Felt.ttf", 20);
    auto background_layer = LayerGradient::create(Color4B(0, 4, 40, 255), Color4B(0, 205, 172, 255));
    this->addChild(background_layer, -1);
    down_label->setPosition(Vec2(this->origin.x + down_label->getContentSize().width,
                            this->origin.y + down_label->getContentSize().height));
    main_label->setPosition(Vec2(this->origin.x + this->size.width/2,
                                                                                        this->origin.y + this->size.height/2 + this->size.height/4));


    auto  intro_action = Sequence::create(DelayTime::create(3), CallFunc::create(
                                                                                                  [this](){
                                                                                                      auto menu_scene = Menu_scene::createScene();
                                                                                                      Director::getInstance()->replaceScene(TransitionSlideInT::create(1, menu_scene));
                                                                                                  })
                                                           , nullptr);



    this->addChild(main_label);
    this->addChild(down_label);

    this->runAction(intro_action);

  return true;
}
