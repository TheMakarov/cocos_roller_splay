#include "Scene2.h"
#include "audio/include/AudioEngine.h"
USING_NS_CC;

Scene* Scene2::createScene() {
  return Scene2::create();
}

Sprite* ball_scene2;
Sprite* map_2;


void Scene2::move_sound() {
  auto arbit = rand() % 100;
  if ( arbit >= 50) AudioEngine::play2d("move_ball_1.wav");
  else AudioEngine::play2d("move_ball_2.wav");
}



float possible_moves_scene2[][2] ={
  {403, 403}, {365, 403}, {327, 403}, {289, 403}, {251, 403}, {213, 403}, {175, 403}, {137, 403},
  {365, 137}, {403, 137}, {289, 137}, {327, 137}, {251, 137}, {213, 137}, {175, 137},
  {137, 137},{137,175}, {137, 213}, {137, 251},{137, 289}, {137, 327}, {137, 365},
  {403,175}, {403, 213}, {403, 251}, {403, 289}, {403, 327}, {403, 365},
  {213,175}, {213, 213}, {213, 289}, {213, 327},  {213, 251},
  {251, 327}, {289, 327}, {327, 327},
  {327, 289},
  {327, 213}, {289, 213}, {327, 251},{175, 137}
};
int total_possible_move2 = sizeof(possible_moves_scene2)/sizeof(possible_moves_scene2[0]);

bool Scene2::legalMove_scene(float x, float y) {
  for (int i = 0 ; i < total_possible_move2; i++) {
    if (possible_moves_scene2[i][0] == x && possible_moves_scene2[i][1] == y ){
      log("legal moove");
      return true;
    }
  }
  log("checking failed");
  return false;
}

void Scene2::draw_succes() {

  auto restart_button = cocos2d::ui::Button::create("restart.png","restart_selected.png" );
  auto next_button = cocos2d::ui::Button::create("next.png", "next_selected.png");
  auto home_button = cocos2d::ui::Button::create("home.png", "home_selected.png");
  next_button->setAnchorPoint(Vec2(0.5, 0.5));
  next_button->setPosition(Vec2(403, 41 ));
  this->addChild(next_button);

  restart_button->setAnchorPoint(Vec2(0.5,0.5));
  restart_button->setPosition(Vec2(327, 41));
  this->addChild(restart_button);

  home_button->setAnchorPoint(Vec2(0.5,0.5));
  home_button->setPosition(Vec2(251, 41));
  this->addChild(home_button);

  home_button->addClickEventListener([this] (Ref* sender) {
    auto director = Director::getInstance();
    director->replaceScene(TransitionSlideInL::create(1, Menu_scene::createScene()));
  });

  next_button->addClickEventListener([this](Ref* sender) {
    auto director = Director::getInstance();
    director->replaceScene(TransitionSlideInT::create(1, Scene3::createScene()));
  });
  restart_button->addClickEventListener([this](Ref* sender){

    auto director = Director::getInstance();
    director->replaceScene(TransitionFade::create(1, this->createScene()));
  });
}


void Scene2::return_floor(int x, int y) {
 std::vector <cocos2d::Sprite *> floor = this->floor;
  for (int i = 0; i < total_possible_move2 ; i++) {
     if (floor[i]->getPositionX() == x && floor[i]->getPositionY() == y ){
       this->floor[i]->setGlobalZOrder(2);
     }
     continue;
   }
  this->floor = floor;
  checkGoals();
}


void Scene2::checkGoals(){
  bool all_checked;
  int count = 0;

  for (int i = 0; i < total_possible_move2 ; i++) {
    if (this->floor[i]->getGlobalZOrder() == 2){
      count+=1;
      continue;
    }
  }

  if(count == 41) {
    done = false;
    draw_succes();
    auto dd = cocos2d::AudioEngine::play2d("won_sound.wav", false, 0.3f, nullptr);
    auto label = Label::createWithTTF("Congrats ", "fonts/Marker Felt.ttf", 24);
    // position the label on the center of the screen
    label->setPosition(Vec2(this->origin.x + this->size.width/2,
                            this->origin.y + this->size.height - label->getContentSize().height));
    // add the label as a child to this layer
    this->addChild(label, 6);
  }
}

void Scene2::make_path() {
  std::vector <cocos2d::Sprite* > floor = this->floor;
  floor.resize(total_possible_move2);
  this->floor.resize(total_possible_move2);
  for (int i = 0; i < total_possible_move2 ; i++) {
    floor[i] = Sprite::create("tint.png");
    floor[i]->setPosition(Vec2(possible_moves_scene2[i][0], possible_moves_scene2[i][1]));
    floor[i]->setScale(2.3);
    this->addChild(floor[i], -2);
  }
  this->floor = floor;
}



// 1 2 3 4
int Scene2::moveto_scene(int  direction) {
  int d = 38;
  switch ( direction ) {
  case 1:
      while (legalMove_scene(ball_scene2->getPositionX() - d, ball_scene2->getPositionY())){
        Scene2::return_floor(ball_scene2->getPositionX() - d, ball_scene2->getPositionY());
        d+=38;
      }
      return d;
      break;
    case 2 :
      while (legalMove_scene( ball_scene2->getPositionX() + d, ball_scene2->getPositionY() )){
        Scene2::return_floor(ball_scene2->getPositionX() + d, ball_scene2->getPositionY());
        d += 38;
      }
      return d;
      break;
      case 3:
        while (legalMove_scene( ball_scene2->getPositionX(), ball_scene2->getPositionY() + d )){
          Scene2::return_floor(ball_scene2->getPositionX() , ball_scene2->getPositionY() + d);
          d+= 38;
        }
        return d;
        break;

        case 4:
          while (legalMove_scene( ball_scene2->getPositionX(), ball_scene2->getPositionY() - d )){
            Scene2::return_floor(ball_scene2->getPositionX() , ball_scene2->getPositionY() - d);
            d+= 38;
         }
          return d;
          break;
    }
}






bool Scene2::init() {

  Scene2::make_path();
  Size size = this->size;
  auto origin = this->origin;


  auto background_layer = LayerGradient::create(Color4B(222, 98, 98, 255), Color4B(115, 75, 109, 255));
  this->addChild(background_layer, -3);
  // ball section
  ball_scene2 = Sprite::create("ball.png");
  ball_scene2->setAnchorPoint(Vec2(0.5 , 0.5));
  ball_scene2->setScale(0.30);
  ball_scene2->setPosition(Vec2( 289, 213 ) );//289, 213
  this->addChild(ball_scene2, 4);
  ball_scene2->setGlobalZOrder(3);


  auto map_2 = Sprite::create("level3.png");
  map_2->setAnchorPoint(Vec2(0.5, 0.5));
  log(" Hello \n \n \n");
  map_2->setPosition(Vec2(size.width/2 + origin.x ,size.width/2 + origin.y));
  this -> addChild(map_2, 1);


  auto label_level1 = Label::createWithTTF("Level 2", "fonts/Marker Felt.ttf", 20);
    label_level1->setPosition(Vec2(this->origin.x+ 50 ,
                            this->origin.y + 50));
    this->addChild(label_level1, 6);
// touch events
  auto listener = EventListenerKeyboard::create();

  listener->onKeyPressed = [this] (EventKeyboard::KeyCode KeyCode, Event* Event){
    if (done) {
    log("key is %d is pressed ", (int) KeyCode);
    int d = 38;

    return_floor(ball_scene2->getPositionX(), ball_scene2->getPositionY());
    switch ((int) KeyCode) {
    case 28:
      ball_scene2->runAction(MoveBy::create(0.1, Vec2(0, moveto_scene(3) - d)));
      move_sound();
      break;
    case 29:
      ball_scene2->runAction(MoveBy::create(0.1,Vec2(0, -moveto_scene(4) + d)));
      move_sound();
      break;
    case 26:
      ball_scene2->runAction(MoveBy::create(0.1, Vec2(-moveto_scene(1) + d, 0)));
      move_sound();
      break;
    case 27:
      ball_scene2->runAction(MoveBy::create(0.1, Vec2(moveto_scene(2) - d, 0)));
      move_sound();
      break;
      case 130:
        log("the location x > %f n y > %f", ball_scene2->getPositionX(), ball_scene2->getPositionY());
    }}
  };


  _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);





  return true;
}
