#include "ToolMainLayer.h"

#include "Define.h"

USING_NS_CC;

ToolMainLayer::ToolMainLayer()
    : blockCnt_(0)
{
    for(int i = 0; i < 4; ++i)
    {
        isExisting_[i].resize(4);
    }
}

ToolMainLayer::~ToolMainLayer()
{
}

ToolMainLayer* ToolMainLayer::create()
{
    ToolMainLayer* pRet = new(std::nothrow) ToolMainLayer;
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool ToolMainLayer::init()
{
    if(false == Layer::init())
    {
        return false;
    }
    
    DrawRect();

    auto listner = EventListenerMouse::create();
    listner->onMouseUp = CC_CALLBACK_1(ToolMainLayer::onMouseUp,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listner, this);
    
    return true;
}

void ToolMainLayer::checkCollision(cocos2d::Vec2 mousePos)
{
    Vector<Node*> children = getChildren();
    for(auto& child : children)
    {
        if(child->getBoundingBox().containsPoint(mousePos))
        {
            // 스프라이트 생성
            Vec2 childPos = child->getPosition();
            
            int colIndex = childPos.x / BLOCKSIZE - 1;
            int rowIndex = childPos.y / BLOCKSIZE;
            
            // 이미 스프라이트가 존재하면 리턴
            if(true == isExisting_[rowIndex][colIndex])
                return;
            
            createBlock(childPos);
            return;
        }
    }
}

void ToolMainLayer::createBlock(cocos2d::Vec2 pos)
{
    Scene* toolScene = Director::getInstance()->getRunningScene();
    
    Sprite* pSprite = Sprite::create("white.png");
    pSprite->setAnchorPoint(Vec2(1, 0));
    pSprite->setPosition(pos);
    pSprite->setTag(TOOL_BLOCK_TAG);
    
    toolScene->addChild(pSprite);
    
    int colIndex = pos.x / BLOCKSIZE - 1;
    int rowIndex = pos.y / BLOCKSIZE;
    
    isExisting_[rowIndex][colIndex] = true;
    
    blockCnt_ += 1;
}

void ToolMainLayer::DrawRect()
{
    for(int row = 0; row < BLOCKCNT; ++row)
    {
        for(int col = 0; col < BLOCKCNT; ++col)
        {
            DrawNode* pNode = DrawNode::create();
            
            Vec2 start = Vec2(col * BLOCKSIZE, row * BLOCKSIZE);
            //Vec2 end = Vec2(start.x + BLOCKSIZE, start.y + BLOCKSIZE);
            
            pNode->drawRect(Vec2(0, 0), Vec2(BLOCKSIZE, BLOCKSIZE), Color4F::WHITE);
            pNode->setAnchorPoint(Vec2(1, 0));
            pNode->setPosition(Vec2(start.x + BLOCKSIZE, start.y));
            pNode->setContentSize(Size(BLOCKSIZE, BLOCKSIZE));
            
            this->addChild(pNode);
        }
    }
}

void ToolMainLayer::onMouseUp(cocos2d::Event* event)
{
    Vec2 cursor = {};
    cursor.x = static_cast<EventMouse*>(event)->getCursorX();
    cursor.y = static_cast<EventMouse*>(event)->getCursorY();
    
    checkCollision(cursor);
    
    log("%.2f, %.2f", cursor.x, cursor.y);
}
