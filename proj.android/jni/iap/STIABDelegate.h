//
//  STIABDelegate.h
//  MysteryGuardians
//
//  Created by Steven.Xc.Tian on 13-7-15.
//
//

#ifndef MysteryGuardians_STIABDelegate_h
#define MysteryGuardians_STIABDelegate_h

/**
 *  In-app billing interface
 */
class STIABDelegate
{
public:
    /**
	 * 购买成功后的回调方法，用来更新IAP的状态
	 *
	 * @param sku
	 *            已经购买到的商品sku
	 */
    virtual void purchaseSuccessful(const char* pid) = 0;
    
    /**
	 * 购买失败后的回调方法
	 */
    virtual void purchaseFailed(const char *pid, int errorCode) = 0;
    
    /**
	 * Restore成功后的回调方法，用来更新IAP的状态
	 *
	 * @param sku
	 *            已经购买到的商品sku
	 */
    virtual void restoreSuccessful(const char* pid) = 0;
    
    /**
	 * restore失败后的回调方法
	 */
    virtual void restoreFailed(const char* pid, int errorCode) = 0;
    
    
    /**
	 * restore请求成功，但没有任务商品
	 */
    virtual void nothingRestored() = 0;
};

#endif
