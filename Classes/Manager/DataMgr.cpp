#include "DataMgr.h"

USING_NS_CC;

DataMgr* DataMgr::pInstance_ = nullptr;

DataMgr::DataMgr()
    : bestScore_(0)
    , score_(0)
    , level_(1)
    , lineCnt_(0)
    , limitLineCnt_(5)
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
}

bool DataMgr::updateData()
{
    if(limitLineCnt_ <= lineCnt_)
    {
        level_ += 1;
        lineCnt_ -= limitLineCnt_;
        score_ += 1000;
        
        return true;
    }
    
    return false;
}
