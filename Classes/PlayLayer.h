
#ifndef __PLAY_LAYER_SCENE_H__
#define __PLAY_LAYER_SCENE_H__

#include "cocos2d.h"

class PlayLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(PlayLayer);

    void displayTitleWin(int player);
    void displayOWin(cocos2d::Vec2 a, cocos2d::Vec2 b, cocos2d::Vec2 c);
    void displayXWin(cocos2d::Vec2 a, cocos2d::Vec2 b, cocos2d::Vec2 c);
    void checkWin( float dt);
    void checkGrid(float dt); 
    bool isOChecked();  
    // set lượt tiếp theo cho người chơi kia
    void setOChecked(bool x);
    void setMatrixChecked(char x, char y);
    void initMaTrixChecked();
    // nếu phần tử x y  chưa được đánh thì trả về true;
    bool isEmptyGridComp(char x, char y);

    void replayGame();
    
    void showProgressTimer();
    void xpause();
    void xcontinue();
    cocos2d::ProgressTimer *progressTimer;
private:
    bool m_enableOChecked = true;
    char m_MatrixChecked[3][3]; // chưa click 0, O click 1, X click 2
    int m_time;
    int numPlayer;
};

#endif // __PLAY_LAYER_SCENE_H__
