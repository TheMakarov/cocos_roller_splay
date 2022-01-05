#include "Scene1.h"
#include "audio/include/AudioEngine.h"
USING_NS_CC;

Scene* Scene1::createScene() {
  return Scene1::create();
}

Sprite* ball_scene1;
Sprite* map_1;


float possible_moves_scene1[][2] ={  {403, 403}, {365, 403}, {327, 403}, {289, 403}, {251, 403}, {213, 403}, {175, 403}, {137, 403},   {403, 137}, {365, 137}, {327, 137}, {289, 137}, {251, 137}, {213, 137}, {175, 137}, {137, 137},   {403,175}, {403, 213}, {403, 251}, {403, 289}, {403, 327}, {403, 365},   {137,175}, {137, 213}, {137, 251}, {137, 289}, {137, 327}, {137, 365}   };

int total_possible_move_scene1 = sizeof(possible_moves_scene1)/sizeof(possible_moves_scene1[0]);

void Scene1::move_sound() {
  auto arbit = rand() % 100;
  if ( arbit >= 50) AudioEngine::play2d("move_ball_1.wav", false, 0.3f, nullptr);
  else AudioEngine::play2d("move_ball_2.wav", false, 0.3f, nullptr);
}

void Scene1::draw_succes() {

  auto restart_button = cocos2d::ui::Button::create("restart.png","restart_selected.png" );
  auto next_button = cocos2d::ui::Button::create("next.png", "next_selected.png");

  next_button->setAnchorPoint(Vec2(0.5, 0.5));
  next_button->setPosition(Vec2(403, 41 ));
  this->addChild(next_button);

  restart_button->setAnchorPoint(Vec2(0.5,0.5));
  restart_button->setPosition(Vec2(327, 41));
  this->addChild(restart_button);

  next_button->addClickEventListener([this](Ref* sender) {
    auto director = Director::getInstance();
    director->replaceScene(TransitionSlideInT::create(1, Scene2::createScene()));
  });
  restart_button->addClickEventListener([this](Ref* sender){

    auto director = Director::getInstance();
    director->replaceScene(TransitionFade::create(1, this->createScene()));
  });
}

bool Scene1::legalMove_scene(float x, float y) {
  for (int i = 0 ; i <= total_possible_move_scene1; i++) {
    if (possible_moves_scene1[i][0] == x && possible_moves_scene1[i][1] == y ){
      log("legal moove");
      return true;
    }
  }
  log("checking failed");
  return false;
}



void Scene1::return_floor(int x, int y) {
  std::vector <cocos2d::Sprite *> floor = this->floor;
  for (int i = 0; i < total_possible_move_scene1 ; i++) {
    if (floor[i]->getPositionX() == x && floor[i]->getPositionY() == y ){
      this->floor[i]->setGlobalZOrder(2);
    }
    continue;
  }
  this->floor = floor;
  checkGoals();
}


void Scene1::checkGoals(){
  bool all_checked;
  int count = 0;

  for (int i = 0; i < total_possible_move_scene1 ; i++) {
    if (this->floor[i]->getGlobalZOrder() == 2){
      count+=1;
      continue;
    }
  }

  if(count == 28) {
    done = false;
    Scene1::draw_succes();
    auto dd = cocos2d::AudioEngine::play2d("won_sound.wav", false, 0.3f, nullptr);
    auto label = Label::createWithTTF("Congrats ", "fonts/Marker Felt.ttf", 24);
    // position the label on the center of the screen
    label->setPosition(Vec2(this->origin.x + this->size.width/2,
                            this->origin.y + this->size.height - label->getContentSize().height));
    // add the label as a child to this layer
    this->addChild(label, 6);
  }
}

void Scene1::make_path() {
  std::vector <cocos2d::Sprite* > floor = this->floor;
  floor.resize(total_possible_move_scene1);
  this->floor.resize(total_possible_move_scene1);
  for (int i = 0; i <= total_possible_move_scene1 ; i++) {
    floor[i] = Sprite::create("tint.png");
    floor[i]->setPosition(Vec2(possible_moves_scene1[i][0], possible_moves_scene1[i][1]));
    floor[i]->setScale(2.3);
    this->addChild(floor[i], -2);
  }
  this->floor = floor;
}



// 1 2 3 4
int Scene1::moveto_scene(int  direction) {
  int d = 38;
  switch ( direction ) {
  case 1:
    while (legalMove_scene(ball_scene1->getPositionX() - d, ball_scene1->getPositionY())){
      Scene1::return_floor(ball_scene1->getPositionX() - d, ball_scene1->getPositionY());
      d+=38;
    }
    return d;
    break;
  case 2 :
    while (legalMove_scene( ball_scene1->getPositionX() + d, ball_scene1->getPositionY() )){
      Scene1::return_floor(ball_scene1->getPositionX() + d, ball_scene1->getPositionY());
      d += 38;
    }
    return d;
    break;
  case 3:
    while (legalMove_scene( ball_scene1->getPositionX(), ball_scene1->getPositionY() + d )){
      Scene1::return_floor(ball_scene1->getPositionX() , ball_scene1->getPositionY() + d);
      d+= 38;
    }
    return d;
    break;

  case 4:
    while (legalMove_scene( ball_scene1->getPositionX(), ball_scene1->getPositionY() - d )){
      Scene1::return_floor(ball_scene1->getPositionX() , ball_scene1->getPositionY() - d);
      d+= 38;
    }
    return d;
    break;
  }
}






bool Scene1::init() {



  Scene1::make_path();
  Size size = this->size;
  auto origin = this->origin;

  auto background_layer = LayerGradient::create(Color4B(97, 67, 133, 255), Color4B(81, 99, 149, 255));
  this->addChild(background_layer, -3);
  // ball section
  ball_scene1 = Sprite::create("ball.png");
  ball_scene1->setAnchorPoint(Vec2(0.5 , 0.5));
  ball_scene1->setScale(0.30);
  ball_scene1->setPosition(Vec2( 403, 403 ) );//289, 213
  this->addChild(ball_scene1, 4);
  ball_scene1->setGlobalZOrder(3);


  auto map_1 = Sprite::create("level2.png");
  map_1->setAnchorPoint(Vec2(0.5, 0.5));
  log(" Hello \n \n \n");
  map_1->setPosition(Vec2(size.width/2 + origin.x ,size.width/2 + origin.y));
  this -> addChild(map_1, 1);

  auto label_level1 = Label::createWithTTF("Level 1", "fonts/Marker Felt.ttf", 20);
    label_level1->setPosition(Vec2(this->origin.x+ 50 ,
                            this->origin.y + 50));
    this->addChild(label_level1, 6);
  // touch events
  auto listener = EventListenerKeyboard::create();

  listener->onKeyPressed = [this] (EventKeyboard::KeyCode KeyCode, Event* Event){
    if (done){
    log("key is %d is pressed ", (int) KeyCode);
    int d = 38;

    return_floor(ball_scene1->getPositionX(), ball_scene1->getPositionY());
    switch ((int) KeyCode) {
    case 28:
      ball_scene1->runAction(MoveBy::create(0.1, Vec2(0, moveto_scene(3) - d)));
      move_sound();
      break;
    case 29:
      ball_scene1->runAction(MoveBy::create(0.1,Vec2(0, -moveto_scene(4) + d)));
      move_sound();
      break;
    case 26:
      ball_scene1->runAction(MoveBy::create(0.1, Vec2(-moveto_scene(1) + d, 0)));
      move_sound();
      break;
    case 27:
      ball_scene1->runAction(MoveBy::create(0.1, Vec2(moveto_scene(2) - d, 0)));
      move_sound();
      break;
    case 130:
        log("the location x > %f n y > %f", ball_scene1->getPositionX(), ball_scene1->getPositionY());
    }
    }
  };


  _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);




  return true;
}
