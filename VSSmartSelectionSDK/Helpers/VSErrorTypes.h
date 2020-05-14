//
//  VSErrorTypes.h
//  Pods
//
//  Created by sheen on 2019/3/4.
//

#ifndef VSErrorTypes_h
#define VSErrorTypes_h

typedef NS_ENUM(NSInteger, VSErrorType) {
    VSErrorNone = 0,                       //没有错误
    VSErrorIsExpire = 1000,                //SDK过期
    VSErrorIsBundleIdMismatch = 1001,      //bundle id不匹配
    VSErrorOSVersionUnsupported = 1002,    //系统不支持
    VSErrorArchitectureUnsupported = 1003, //指令集不支持
    VSErrorModelMismatch = 1004,           //不符合要求的模型输入
};

typedef NS_ENUM(NSInteger, VSSDKStatus) {
    VSSDKStatusLoadingSuccess = 0,   //模型加载成功
    VSSDKStatusLoading = 1000,       // 正在加载模型
    VSSDKStatusLoadingFailed,        // 模型加载失败
};

#endif /* VSErrorTypes_h */
