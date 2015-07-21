/*

Copyright 2015 Adrian Dawid

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.


Created by Adrian Dawid

*/

package com.kekestudio.amazingcircle;

import org.cocos2dx.lib.Cocos2dxActivity;

import com.common.android.newsblast.PlatformCode;


public class NoGPGAppActivity extends Cocos2dxActivity{

	@Override
	public int getPlatformCode() {
		// TODO Auto-generated method stub
		return PlatformCode.GOOGLEPLAY;
	}

	@Override
	public boolean getDebugMode() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean enableEvent() {
		// TODO Auto-generated method stub
		return false;
	}
    
}
