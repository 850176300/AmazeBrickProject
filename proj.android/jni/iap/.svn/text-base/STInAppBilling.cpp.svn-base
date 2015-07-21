//
//  STInAppBilling
//
//  Created by Steven.Xc.Tian on 13-8-29.
//
//

#include "STInAppBilling.h"
#include "ST_IAB_Android.h"

void STInAppBilling::setIABDelegate(STIABDelegate* pDelegate)
{
	AndroidIAPManager::getInstance()->setIABDelegate(pDelegate);
}

void STInAppBilling::purchase(const char* sku)
{
	AndroidIAPManager::getInstance()->purchase(sku, SKU_TYPE_MANAGE);
}

void STInAppBilling::purchaseUnmanaged(const char* sku)
{
	AndroidIAPManager::getInstance()->purchase(sku, SKU_TYPE_UNMANAGE);
}

void STInAppBilling::restore()
{
	AndroidIAPManager::getInstance()->restore();
}

void STInAppBilling::query()
{
	AndroidIAPManager::getInstance()->query();
}

STInAppBilling::STInAppBilling()
{
}

STInAppBilling::~STInAppBilling()
{
}
