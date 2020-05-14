//
//  CommonMarco.h
//  Mirror
//
//  Created by sheen on 2018/2/9.
//  Copyright © 2018年 Versa. All rights reserved.
//

#ifndef CommonMarco_h
#define CommonMarco_h


#ifdef __OBJC__
//#import "NSDateFormatter+Versa.h"
#endif


#define SYSTEM_VERSION_GREATER_THAN_OR_EQUAL_TO(v)  ([[[UIDevice currentDevice] systemVersion] compare:v options:NSNumericSearch] != NSOrderedAscending)

#define WeakObjectDef(obj) __weak typeof(obj) weak##obj = obj
#define StrongObjectDef(obj) __strong typeof(obj) strong##obj = obj
//
#define AutoObjectGetter(obj, classType) \
@synthesize obj = _##obj; \
- (classType*)obj \
{ \
    if(!_##obj) \
    { \
        _##obj = [[classType alloc] init]; \
    } \
    return _##obj; \
}

#ifdef DEBUG
#define MSGLOG  NSLog  //printf("%s %s\n",[DateFormat([NSDate date]) UTF8String],[[NSString stringWithFormat:__VA_ARGS__] UTF8String])
#define WTAssert  NSAssert
#define JPushUseProduction NO
#else
#define MSGLOG(format, ...)
#define WTAssert
#define JPushUseProduction YES
#endif

#if  (defined (__arm64__) && defined (__IOS_AVAILABLE))
#define __VERSA_SEGMENT_ENABLE__ 1
#else
#define __VERSA_SEGMENT_ENABLE__ 0
#endif

//obfuscated code enable
#if DEBUG
#define __ObfuscatedCode__ 0
#else
#define __ObfuscatedCode__ 1
#endif
#if __ObfuscatedCode__
#define Versa C564a0b7742381ed0
#endif
#endif /* CommonMarco_h */
