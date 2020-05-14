//
//  VSSmartSelectionManager.m
//  AI_Selector
//
//  Created by guoxianghui on 2020/5/14.
//  Copyright © 2020 guoxianghui. All rights reserved.
//

#import "VSSmartSelectionManager.h"
#import "VSSmartSelectionHandler.h"
#import <os/lock.h>
#import "VSErrorTypes.h"
#import "pubfunc.h"

@interface VSSmartSelectionManager ()
{
    os_unfair_lock _ssLock;
}

@property (nonatomic, strong) VSSmartSelectionHandler *ssHandler;

@end

#define LOCK(locker) os_unfair_lock_lock(&locker)
#define UNLOCK(locker) os_unfair_lock_unlock(&locker)

static VSSmartSelectionManager *_manager;

@implementation VSSmartSelectionManager

+ (instancetype)manager{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _manager = [[self alloc] init];
    });
    return _manager;
}

+ (instancetype)allocWithZone:(struct _NSZone *)zone{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _manager = [super allocWithZone:zone];
    });
    return _manager;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        _ssLock = OS_UNFAIR_LOCK_INIT;
    }
    return self;
}

#pragma mark - Public

- (void)setMlmodelPath:(NSString *)mlmodelPath{
    _mlmodelPath = mlmodelPath;
    
    LOCK(_ssLock);
    [self.ssHandler setupModelPath:_mlmodelPath key:@""];
    UNLOCK(_ssLock);
    
}

- (CVPixelBufferRef)getMaskWithMode:(VSInputDataSet)mode{
    
    LOCK(_ssLock);
    CVPixelBufferRef pixelBuffer = [self.ssHandler getMaskPBWithFrameMode:mode];
    UNLOCK(_ssLock);
    return pixelBuffer;
}

#pragma mark - Getter

- (VSSmartSelectionHandler *)ssHandler{
    if (!_ssHandler) {
        _ssHandler = [VSSmartSelectionHandler new];
    }
    return _ssHandler;
}

@end
