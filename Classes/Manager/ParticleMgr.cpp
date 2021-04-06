#include "ParticleMgr.h"

#include "Define.h"

USING_NS_CC;

ParticleMgr* ParticleMgr::pInstance_ = nullptr;

ParticleMgr::ParticleMgr()
{
}

ParticleMgr::~ParticleMgr()
{
}

ParticleMgr* ParticleMgr::getInstance()
{
    if(nullptr == pInstance_)
    {
        pInstance_ = new(std::nothrow) ParticleMgr;
        pInstance_->init();
    }
    
    return pInstance_;
}

void ParticleMgr::destroyInstance()
{
    if(nullptr != pInstance_)
    {
        delete pInstance_;
        pInstance_ = nullptr;
    }
}

void ParticleMgr::init()
{
}

void ParticleMgr::particleSmog(cocos2d::Node* node, cocos2d::Vec2 pos)
{
    ParticleSmoke* pParticle = ParticleSmoke::create();
    pParticle->setPosition(pos);
    node->addChild(pParticle, ZORDER::SMOG);
    
    pParticle->setStartColor(Color4F::WHITE);
    pParticle->setEndColor(Color4F::GRAY);
    pParticle->setStartSize(400);
    pParticle->setEndSize(200);
    
    pParticle->setDuration(3.f);
    pParticle->setSpeed(10);

    pParticle->setTotalParticles(10);
    
    pParticle->setAutoRemoveOnFinish(true);
}

void ParticleMgr::particleExplosion(cocos2d::Node* node, cocos2d::Vec2 pos, Color3B color)
{
    ParticleExplosion* pParticle = ParticleExplosion::create();
    pParticle->setPosition(pos);
    node->addChild(pParticle, ZORDER::EXPLOSION);
    
    pParticle->setStartColor(Color4F(color, 1.f));
    pParticle->setEndColor(Color4F(color, 1.f));
    
    pParticle->setLife(0.5f);
    pParticle->setSpeed(20);
    
    pParticle->setTotalParticles(10);
    
    pParticle->setAutoRemoveOnFinish(true);
}
