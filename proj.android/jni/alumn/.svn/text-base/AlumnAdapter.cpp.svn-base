//
//  AlumnAdapter.cpp
//  Doctor2
//
//  Created by tanshoumei on 13-9-18.
//
//

#include "AlumnAdapter.h"
#include "STSystemFunction.h"
#include "STFileUtility.h"
#include "Util.h"
#include <iostream>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;
void AlumnAdapter::saveToAlumn(cocos2d::CCImage *apCCImg)
{
    STSystemFunction sf;
    
    __String* _time=__String::createWithFormat("%ld", Util::getCurrentTime());
    STFileUtility::createDirectory((STFileUtility::getStoragePath()+"/Cereal").c_str());
    string path=sf.getSdCardPath()+"/Cereal/"+_time->getCString()+".jpg";
    
    CCLOG("Android: AlumnAdapter::saveToAlumn at %s", path.c_str());
    bool issuccess=apCCImg->saveToFile(path.c_str());
    if (issuccess)
    {
//        _saveTxt=dm->getLanguage("photo_save",Util::getLanguageType()).c_str();
        sf.popAlertDialog("Your image was saved to your Camera Roll!");
    }else
    {
        sf.popAlertDialog("Your image was unable to be saved. Please check your device storage and try again.");
//        _saveTxt=dm->getLanguage("photo_save_failed",Util::getLanguageType()).c_str();
    }
    sf.refreshDCIM(path);
//    string saveTxt=Util::replaceStr(_saveTxt,"\r\n","\n");
//    dialog->setContentText(saveTxt.c_str());
//    addChild(dialog,9999);
    
}
