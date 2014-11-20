#include "AppDelegate.h"
#include "GameScene.h"
#include "ScreenLog.h"

USING_NS_CC;



AppDelegate::AppDelegate() {
//#ifdef USE_SCREEN_LOG
//    g_screenLog = new ScreenLog();
//    g_screenLog->setLevelMask( LL_DEBUG | LL_INFO | LL_WARNING | LL_ERROR | LL_FATAL );
//    g_screenLog->setFontFile( "UbuntuMono-R.ttf" );
//    g_screenLog->setTimeoutSeconds( 15 );
//#endif
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    // record the resource path
//    //static std::string s_strResourcePath = "";
//    std::string filePath = FileUtils::getInstance()->getWritablePath();
//    std::string zipFile = "img_100.zip";
//    std::string resourceFile = "img_100/f001.png";
//    std::string path = filePath.c_str() + zipFile;
//    unsigned long size = 0;
//    unsigned char* buf;
//    
//    // As noted in the documentation, this is where expansion files are saved to:
//    // /Android/obb//[main|patch]...obb
//    if ( path.find( "Android/obb/" ) != std::string::npos )
//    {
//        // Read from expansion
//        buf =  FileUtils::getInstance()->getFileDataFromZip(path.c_str() ,zipFile.c_str(),(ssize_t*)&size);
//    }
//    else if (resourceFile[0] != '/')
//    {
//        // read from apk
//        zipFile.insert(0, "assets/");
//        buf =  FileUtils::getInstance()->getFileDataFromZip(path.c_str() ,zipFile.c_str(),(ssize_t*)&size);
//    }
//#endif
    
#ifdef USE_SCREEN_LOG
    g_screenLog = new ScreenLog();
    g_screenLog->setLevelMask( LL_DEBUG | LL_INFO | LL_WARNING | LL_ERROR | LL_FATAL );
    g_screenLog->setFontFile( "UbuntuMono-R.ttf" );
    g_screenLog->setTimeoutSeconds( 15 );
#endif
    
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::createWithRect("My Game",Rect(0,0,320,480));
        director->setOpenGLView(glview);
    }

    director->setDisplayStats(false);
    director->setAnimationInterval(1.0 / 60);
    auto scene = GameLayer::createScene();
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
