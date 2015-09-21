#include "HelloWorldScene.h"
#include "PhysicsShapeCache.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);    // 'layer' is an autorelease object
   
    scene->getPhysicsWorld()->setGravity(Vec2(0,0));
    auto layer = HelloWorld::create();
    
    layer->setPhyWorld(scene->getPhysicsWorld());
    
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    PhysicsShapeCache::getInstance()->addShapesWithFile("test.plist");
//    PhysicsShapeCache::getInstance()->addShapesWithFile("test02.plist");
    
    //添加监听器
    auto contactListener=EventListenerPhysicsContact::create();
    //设置监听器的碰撞开始函数
    contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
    //添加到事件分发器中
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    Size winSize=Director::getInstance()->getWinSize();
    Sprite * bg=Sprite::create("HelloWorld.png");
   
    bg->setPosition(winSize.width/2,winSize.height/2);
    PhysicsShapeCache::getInstance()->setBodyOnSprite("HelloWorld.png",bg);

    bg->setTag(1);
    addChild(bg);
  
    
    
    Sprite * sp=Sprite::create("CloseNormal.png");
    sp->setPosition(winSize.width/3,winSize.height/3);
    

    PhysicsShapeCache::getInstance()->setBodyOnSprite("CloseNormal.png",sp);
    sp->setTag(2);
    addChild(sp);
    
    sp->runAction(RepeatForever::create(Sequence::create(
                                                         MoveTo::create(2.0F, Vec2( winSize.width/2,winSize.height/2)),
                                                         MoveTo::create(2.0F, Vec2( winSize.width/3,winSize.height/3)), NULL)));
    
    
    return true;
}


bool HelloWorld::onContactBegin(const PhysicsContact& contact)
{
    int bodyTag1=contact.getShapeA()->getBody()->getTag();
    int bodyTag2=contact.getShapeB()->getBody()->getTag();
    Sprite* bg=(Sprite*)contact.getShapeA()->getBody()->getNode();
    Sprite* sp=(Sprite*)contact.getShapeB()->getBody()->getNode();
    
    printf("tag Sprite tag is shapeA=%d, shapeB=%d\n",bg->getTag(),sp->getTag());
    printf("tag Body tag is shapeA=%d, shapeB=%d\n",bodyTag1,bodyTag2);

    bg->removeFromParent();
    sp->removeFromParent();
//    m_world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
    return true;
    
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
