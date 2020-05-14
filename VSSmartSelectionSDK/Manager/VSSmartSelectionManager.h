//
//  VSSmartSelectionManager.h
//  AI_Selector
//
//  Created by guoxianghui on 2020/5/14.
//  Copyright © 2020 guoxianghui. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VSSmartSelectionConst.h"

NS_ASSUME_NONNULL_BEGIN

@interface VSSmartSelectionManager : NSObject

@property (nonatomic, copy) NSString *mlmodelPath;

+ (instancetype)manager;

- (CVPixelBufferRef)getMaskWithMode:(VSInputDataSet)mode;

@end

NS_ASSUME_NONNULL_END
