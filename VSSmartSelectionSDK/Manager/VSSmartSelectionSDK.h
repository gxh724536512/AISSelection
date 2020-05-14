//
//  VSSmartSelectionSDK.h
//  AI_Selector
//
//  Created by guoxianghui on 2020/5/14.
//  Copyright © 2020 guoxianghui. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VSSmartSelectionConst.h"

NS_ASSUME_NONNULL_BEGIN

@interface VSSmartSelectionSDK : NSObject

/**
 设置模型路径
 
 @param path 设置模型本地路径
*/
+ (void)setModelPath:(NSString *)path;


/// 输入一组image集合返回一个mask
/// @param mode image集合
+ (CVPixelBufferRef)maskPBWithFrameMode:(VSInputDataSet)mode;

@end

NS_ASSUME_NONNULL_END
