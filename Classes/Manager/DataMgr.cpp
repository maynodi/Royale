#include "DataMgr.h"

#include "JsonUtils.h"
#include "Define.h"

#include "MapLayer.h"

USING_NS_CC;

DataMgr* DataMgr::pInstance_ = nullptr;

DataMgr::DataMgr()
    : bestScore_(0)
    , score_(0)
    , level_(1)
    , lineCnt_(0)
    , limitLineCnt_(5)
    , itemCnt_(0)
    , specialBlockCnt_(-1)
{
}

DataMgr::~DataMgr()
{
}

DataMgr* DataMgr::getInstance()
{
    if(nullptr == pInstance_)
    {
        pInstance_ = new(std::nothrow) DataMgr;
        pInstance_->init();
    }
    
    return pInstance_;
}

void DataMgr::destroyInstance()
{
    if(nullptr != pInstance_)
    {
        delete pInstance_;
        pInstance_ = nullptr;
    }
}

void DataMgr::init()
{
    bestScore_ = UserDefault::getInstance()->getIntegerForKey("bestScore");
    if(false == loadData())
    {
        log("dataMgr-loadData failed.");
    }
}

bool DataMgr::updateData()
{
    if(limitLineCnt_ <= lineCnt_)
    {
        level_ += 1;
        lineCnt_ -= limitLineCnt_;
        score_ += 1000;
            
        Scene* pScene = Director::getInstance()->getRunningScene();
        MapLayer* pLayer = (MapLayer*)pScene->getChildByTag(MAPLAYER_TAG);
        pLayer->setIsChange(true);
        
        return true;
    }
    
    return false;
}

bool DataMgr::loadData()
{
    std::string filePath = FileUtils::getInstance()->getWritablePath() + "blockData.json";
    
    __String* jsonInfo = __String::createWithContentsOfFile(filePath);
    if("" == jsonInfo->_string)
        return false;
    
    JSONNode node = libjson::parse(jsonInfo->getCString());
    
    specialBlockCnt_ = JsonUtils::getInt("blockCnt", node);
    
    loadInfoVec_.reserve(specialBlockCnt_);
    
    for(int i = 0; i < specialBlockCnt_; ++i)
    {
        int posX = JsonUtils::getInt("x" + std::to_string(i), node);
        int posY = JsonUtils::getInt("y" + std::to_string(i), node);
        
        loadInfoVec_.emplace_back(Vec2(posX - 3, posY - 3));  // 중점 맞춰주려고 -3 했음
    }
    
    return true;
}
