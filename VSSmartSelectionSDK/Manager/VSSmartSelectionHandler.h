//
//  VSSmartSelectionHandler.h
//  AI_Selector
//
//  Created by guoxianghui on 2020/5/14.
//  Copyright © 2020 guoxianghui. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VSSmartSelectionConst.h"

NS_ASSUME_NONNULL_BEGIN

@interface VSSmartSelectionHandler : NSObject

- (void)setupModelPath:(NSString *)modelPath key:(NSString *)key;

- (CVPixelBufferRef)getMaskPBWithFrameMode:(VSInputDataSet)mode;

@end

NS_ASSUME_NONNULL_END
