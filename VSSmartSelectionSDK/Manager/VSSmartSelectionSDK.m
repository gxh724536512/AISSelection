//
//  VSSmartSelectionSDK.m
//  AI_Selector
//
//  Created by guoxianghui on 2020/5/14.
//  Copyright © 2020 guoxianghui. All rights reserved.
//

#import "VSSmartSelectionSDK.h"
#import "VSSmartSelectionManager.h"

@implementation VSSmartSelectionSDK

+ (void)setModelPath:(NSString *)path {
    if (@available(iOS 11.0, *)) {
        [[VSSmartSelectionManager manager] setMlmodelPath:path];
    } else {
        
    }
}

+ (CVPixelBufferRef)maskPBWithFrameMode:(VSInputDataSet)mode{
    if (@available(iOS 11.0, *)) {
        return [[VSSmartSelectionManager manager] getMaskWithMode:mode];
    }
    return nil;
}

@end
