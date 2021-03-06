/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "PlayLayer.h"
#include "PlayWithAi.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Definitions.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene; 
}

// Print useful error message instead of segfaulting when files are not there.
// in thông báo lỗi khi file không tìm thấy
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
// bạn cần init để khởi tạo các yêu cầu của bạn
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // lấy UI từ cocosstudio
    auto mainMenu = CSLoader::getInstance()->createNode("csb/mainMenu.csb");
    this->addChild(mainMenu);

    auto button = mainMenu->getChildByName<ui::Button*>("ButtonPlay");
    button->setPressedActionEnabled(true);
    //button->setTouchEnabled(true);
    button->addClickEventListener([=](Ref*)
        {
            // call func
            goToPlayWithAi(this);
        });

    auto button1 = mainMenu->getChildByName<ui::Button*>("ButtonPlayTwoPlayer");
    button1->setPressedActionEnabled(true);
    //button->setTouchEnabled(true);
    button1->addClickEventListener([=](Ref*)
        {
            // call func
            goToPlayLayer(this);
        });

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::goToPlayLayer(cocos2d::Ref* sender)
{
    auto playLayer = PlayLayer::createScene();
    Director::getInstance()->replaceScene(playLayer);
}

void HelloWorld::goToPlayWithAi(cocos2d::Ref* sender)
{
    auto playLayer = PlayWithAi::createScene();
    Director::getInstance()->replaceScene(playLayer);
}

