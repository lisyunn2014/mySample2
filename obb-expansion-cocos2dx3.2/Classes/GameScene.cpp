#include "GameScene.h"
#include "ScreenLog.h"

#import "external/unzip/unzip.h"

void readInZipFileName()
{
    
     //FileUtils::getInstance()->getWritablePath();
     //●●● filePath=/data/data/com.superman.plane/files/ ●●●
    
    std::string filePath = "/storage/sdcard0/Android/obb/com.superman.plane/";
    std::string zipFile = "main.2.com.superman.plane.obb";
    std::string imgFile = "assets/img_bg_1.jpg";

    std::string path = filePath + zipFile;
    
    // zipファイルをopenし、ファイル数を取得します。
    unzFile zipfile = unzOpen(path.c_str());
    log( "--- path = %s ---" ,path.c_str());
    
    unz_global_info global_info;
    if ( unzGetGlobalInfo( zipfile, &global_info ) != UNZ_OK )
    {
        log( "could not read file global infon" );
        unzClose( zipfile );
        return;
    }
    
    // ファイルの先頭にカーソルを合わせます
    unzGoToFirstFile(zipfile);
    uLong i;
    for ( i = 0; i < global_info.number_entry; ++i )
    {
        // Get info about current file.
        char filename[ 100 ];
        if ( unzGetCurrentFileInfo64(zipfile,
                                     NULL,
                                     filename,
                                     100,
                                     NULL, 0, NULL, 0)
            
            != UNZ_OK )
        {
            log( "could not read file" );
            unzClose( zipfile );
            return;
        }
        std::string str(filename);
        
        log("file[%lu] name == %s" , i , str.c_str());
        // ここでstd::vectorにでも詰めればOK
        
        // 次にカーソルを進める
        unzGoToNextFile(zipfile);
    }
    // 終わったらcloseを忘れずに。
    unzClose(zipfile);
}

cocos2d::Scene* GameLayer::createScene() {
	auto scene = Scene::create();
#ifdef USE_SCREEN_LOG
    // attach screenlog to the scene about to become active
    g_screenLog->attachToScene( scene );
#endif
	auto layer = GameLayer::create();
	scene->addChild(layer);
	return scene;
}

bool GameLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	this->setTouchEnabled(true);
	Size winSize = Director::getInstance()->getWinSize();
	char buff[15];
	int id = getRand(1, 5);
	sprintf(buff, "img_bg_%d.jpg", id);
   
    //readInZipFileName();
    
	auto over = Sprite::create(buff);
	over->setPosition(Point(winSize.width / 2, winSize.height / 2));
	this->addChild(over);
	return true;
}
int GameLayer::getRand(int start, int end) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	unsigned long int rand_seed = tv.tv_sec * 1000 + tv.tv_usec / 1000;
#ifdef USE_SCREEN_LOG
    g_screenLog->log( LL_INFO, "●●● rand_seed=%d ●●●",rand_seed );
#endif
	srand(rand_seed);
#ifdef USE_SCREEN_LOG
    g_screenLog->log( LL_INFO, "●●● start=%d, end=%d ●●●",start,end );
#endif
	float i = CCRANDOM_0_1() * (end - start + 1) + start;
#ifdef USE_SCREEN_LOG
    g_screenLog->log( LL_INFO, "●●● i=%f ●●●",i );
#endif
	return (int) i;
}

void GameLayer::onEnterTransitionDidFinish() {
	planeLayer = PlaneLayer::create();
	this->addChild(planeLayer);
	bulletSprite = BulletSprite::create();
	this->addChild(bulletSprite);
	enemyLayer = EnemyLayer::create();
	this->addChild(enemyLayer);

	this->schedule(schedule_selector(GameLayer::gameUpdate));

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	auto closeItem = MenuItemImage::create("CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(GameLayer::menuCloseCallback, this));
	closeItem->setPosition(
			Point(
					origin.x + visibleSize.width
							- closeItem->getContentSize().width / 2,
					origin.y + closeItem->getContentSize().height / 2));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
}

void GameLayer::menuCloseCallback(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
bool GameLayer::bulletCollisionEnemy(Sprite* pBullet) {
	for (auto& eEnemy : enemyLayer->vecEnemy) {
		EnemySprite* pEnemySprite = (EnemySprite*) eEnemy;
		if (pBullet->boundingBox().intersectsRect(
				pEnemySprite->getBoundingBox())) {
			if (1 == pEnemySprite->getLife()) {
				pEnemySprite->loseLife();
				enemyLayer->blowupEnemy(pEnemySprite);
			} else {
				pEnemySprite->loseLife();
			}
			bulletSprite->removeBullet(pBullet);
			return true;
		}
	}
	return false;
}

void GameLayer::gameUpdate(float dt) {
	bool bMoveButt = false;
	for (auto& eButtle : bulletSprite->vecBullet) {
		Sprite* pBullet = (Sprite*) eButtle;
		bMoveButt = bulletCollisionEnemy(pBullet);
		if (bMoveButt) {
			return;
		}
	}
	enemyCollisionPlane();
}

bool GameLayer::enemyCollisionPlane() {
	Sprite* pPlane = (Sprite*) planeLayer->getChildByTag(AIRPLANE);
	for (auto& eEnemy : enemyLayer->vecEnemy) {
		EnemySprite* pEnemySprite = (EnemySprite*) eEnemy;
		if (pPlane->boundingBox().intersectsRect(pEnemySprite->getBoundingBox())
				&& pEnemySprite->getLife() > 0) {
//			this->unscheduleAllSelectors();
			//	this->bulletLayer->StopBulletShoot();
			//	this->planeLayer->blowUp();
			return true;
		}
	}

	return false;
}
