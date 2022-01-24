#include "PlayWithAi.h"
#include "AI.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ui/UILoadingBar.h"
#include <iostream>

USING_NS_CC;

Scene* PlayWithAi::createScene()
{
    auto scene = Scene::create();
    auto layer = PlayWithAi::create();
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
bool PlayWithAi::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    initMaTrixChecked();
    
    // lấy UI từ cocosstudio
    auto mainMenu = CSLoader::getInstance()->createNode("csb/playLayer.csb");
    this->addChild(mainMenu);

    this->schedule(schedule_selector(PlayWithAi::checkGrid, ), 0.1);
    this->schedule(schedule_selector(PlayWithAi::checkWin, ), 0.1);

    showProgressTimer();
    replayGame();
    xcontinue();
    xpause();
    return true;
}


void PlayWithAi::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();;
}

void PlayWithAi::displayOWin(cocos2d::Vec2 a, cocos2d::Vec2 b, cocos2d::Vec2 c)
{

    std::string _a = "Owin" + std::to_string((int)a.x) + std::to_string((int)a.y);
    std::string _b = "Owin" + std::to_string((int)b.x) + std::to_string((int)b.y);
    std::string _c = "Owin" + std::to_string((int)c.x) + std::to_string((int)c.y);

    utils::findChild<ui::ImageView*>(this, _a)->setVisible(true);
    utils::findChild<ui::ImageView*>(this, _b)->setVisible(true);
    utils::findChild<ui::ImageView*>(this, _c)->setVisible(true);

    displayTitleWin(1);
    
}

// người chơi O là 1, X là 2
void PlayWithAi::displayTitleWin(int player)
{
    if (player == 1)
    {
        this->removeChildByName("progressTimer");
        utils::findChild<ui::ImageView*>(this, "Owin")->setVisible(true);

    }
    if (player == 2)
    {
        this->removeChildByName("progressTimer");
        utils::findChild<ui::ImageView*>(this, "Xwin")->setVisible(true);
    }
    xpause();
}

void PlayWithAi::displayXWin(cocos2d::Vec2 a, cocos2d::Vec2 b, cocos2d::Vec2 c)
{
    std::string _a = "Xwin" + std::to_string((int)a.x) + std::to_string((int)a.y);
    std::string _b = "Xwin" + std::to_string((int)b.x) + std::to_string((int)b.y);
    std::string _c = "Xwin" + std::to_string((int)c.x) + std::to_string((int)c.y);

    utils::findChild<ui::ImageView*>(this, _a)->setVisible(true);
    utils::findChild<ui::ImageView*>(this, _b)->setVisible(true);
    utils::findChild<ui::ImageView*>(this, _c)->setVisible(true);
    displayTitleWin(2);
}

void PlayWithAi::checkWin(float dt)
{
    // kiểm tra thời gian
    auto am = Director::getInstance()->getActionManager();
    if (!am->getNumberOfRunningActions())
    {
        if (isOChecked())
        {
            displayTitleWin(2);
        }
        else
        {
            displayTitleWin(1);
        }
    }

    // kiểm tra người chơi O
    
    for (int i = 0; i < 3; i++)
    {
        // kieemr tra cot
        if ((m_MatrixChecked[i][0] == 1) && (m_MatrixChecked[i][1] == 1) && (m_MatrixChecked[i][2] == 1)) { displayOWin(Point(i, 0), Point(i, 1), Point(i, 2)); }
        // kiem tra hang
        if ((m_MatrixChecked[0][i] == 1) && (m_MatrixChecked[1][i] == 1) && (m_MatrixChecked[2][i] == 1)) { displayOWin(Point(0, i), Point(1, i), Point(2, i)); };
    }
    // kiểm tra chéo
    {
        if ((m_MatrixChecked[0][0] == 1) && (m_MatrixChecked[1][1] == 1) && (m_MatrixChecked[2][2] == 1)) { displayOWin(Point(0, 0), Point(1, 1), Point(2, 2)); };
        if ((m_MatrixChecked[2][0] == 1) && (m_MatrixChecked[1][1] == 1) && (m_MatrixChecked[0][2] == 1)) { displayOWin(Point(2, 0), Point(1, 1), Point(0, 2)); };
    }
    
    // kiểm tra người chơi X
    for (int i = 0; i < 3; i++)
    {
        // kieemr tra cot
        if ((m_MatrixChecked[i][0] == 2) && (m_MatrixChecked[i][1] == 2) && (m_MatrixChecked[i][2] == 2)) { displayXWin(Point(i, 0), Point(i, 1), Point(i, 2)); }
        // kiem tra hang
        if ((m_MatrixChecked[0][i] == 2) && (m_MatrixChecked[1][i] == 2) && (m_MatrixChecked[2][i] == 2)) { displayXWin(Point(0, i), Point(1, i), Point(2, i)); };
    }
    // kiểm tra chéo
    {
        if ((m_MatrixChecked[0][0] == 2) && (m_MatrixChecked[1][1] == 2) && (m_MatrixChecked[2][2] == 2)) { displayXWin(Point(0, 0), Point(1, 1), Point(2, 2)); };
        if ((m_MatrixChecked[2][0] == 2) && (m_MatrixChecked[1][1] == 2) && (m_MatrixChecked[0][2] == 2)) { displayXWin(Point(2, 0), Point(1, 1), Point(0, 2)); };
    }
}

void PlayWithAi::checkGrid(float dt)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            std::string buttonName = "Button" + std::to_string(i) + std::to_string(j);
            std::string imageOName = "O" + std::to_string(i) + std::to_string(j);
            auto button = utils::findChild<ui::Button*>(this, buttonName);
            if (m_MatrixChecked[i][j] != 0) continue;
            if (m_MatrixChecked[i][j] == 0)
            {
                
                button->setTouchEnabled(true);
                button->addClickEventListener([=](Ref*)
                    {
                        
                        if (isOChecked())
                        {
                            if (m_MatrixChecked[i][j] == 0)
                            {
                                this->removeChildByName("progressTimer");
                                utils::findChild<ui::ImageView*>(this, imageOName)->setVisible(true);
                                setMatrixChecked(i, j);
                                setOChecked(false);                                  
                            }

                        }
                    });

            }
            
        }
    }
    // Ai play
    if (!isOChecked())
    {
        int x, y;
        aiCheck(x, y);
        setMatrixChecked(x, y);
        setOChecked(true);
        std::string imageXName = "X" + std::to_string(x) + std::to_string(y);
        utils::findChild<ui::ImageView*>(this, imageXName)->setVisible(true);;



    }

}

bool PlayWithAi::isOChecked()
{
    return m_enableOChecked;
}

void PlayWithAi::setOChecked(bool x)
{
    m_enableOChecked = x;
    this->showProgressTimer();
    
}

void PlayWithAi::setMatrixChecked(char x, char y)
{
    if (isOChecked())
    {
        // nếu O checked vào thì set bằng true
        m_MatrixChecked[x][y] = 1;
    }
    else
    {
        m_MatrixChecked[x][y] = 2;
    }
}

void PlayWithAi::initMaTrixChecked()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            m_MatrixChecked[i][j] = 0;
        }
    }
}

bool PlayWithAi::isEmptyGridComp(char x, char y)
{
    if (m_MatrixChecked[x][y] == 0)
    {
        return true;
    }
    else
    {
        return false;
    }  
}

void PlayWithAi::replayGame()
{
    auto replay = utils::findChild<ui::Button*>(this, "ButtonReplay");
    replay->setTouchEnabled(true);
    replay->addClickEventListener([=](Ref*)
        {
            auto playLayer = PlayWithAi::createScene();
            Director::getInstance()->replaceScene(playLayer);
        });
}

void PlayWithAi::showProgressTimer()
{ 
    auto visibleSize = Director::getInstance()->getVisibleSize();
    progressTimer = ProgressTimer::create(Sprite::create("ProgressBar.png"));
    progressTimer->setType(ProgressTimer::Type::BAR);
    progressTimer->setMidpoint(Vec2(0.0f, 0.5f));
    progressTimer->setBarChangeRate(Vec2(1.0f, 0.0f));
    progressTimer->setPercentage(100);
    progressTimer->setScale(0.5);
    progressTimer->setPosition(visibleSize.width / 2, visibleSize.height*0.9);
    progressTimer->setName("progressTimer");
    progressTimer->setTag(9);
    this->addChild(progressTimer);
    progressTimer->runAction(ProgressFromTo::create(10, 100, 0));
    
       
}

void PlayWithAi::xcontinue()
{
        auto _continue = utils::findChild<ui::Button*>(this, "continue");
        auto _pause = utils::findChild<ui::Button*>(this, "Pause");
        auto _PAUSE = utils::findChild<ui::ImageView*>(this, "PAUSE");
        _continue->setTouchEnabled(true);
        _continue->addClickEventListener([=](Ref*)
            {
                _continue->setVisible(false);
                _pause->setVisible(true);
                _PAUSE->setVisible(false);
                progressTimer->resumeSchedulerAndActions();
            });
    
}

void PlayWithAi::aiCheck(int &x, int &y)
{
    
    //ai->setMatrixChecked(m_MatrixChecked);
    ai->PlacePiece(&m_MatrixChecked);
    x = ai->getXOut();
    y = ai->getYOut();
}

void PlayWithAi::xpause()
{
    auto _pause = utils::findChild<ui::Button*>(this, "Pause");
    auto _continue = utils::findChild<ui::Button*>(this, "continue");
    auto _PAUSE = utils::findChild<ui::ImageView*>(this, "PAUSE");
    _pause->setTouchEnabled(true);
    _pause->addClickEventListener([=](Ref*)
        {
            _pause->setVisible(false);
            _continue->setVisible(true);
            _PAUSE->setVisible(true);
            progressTimer->pauseSchedulerAndActions();            
        });
    
}



