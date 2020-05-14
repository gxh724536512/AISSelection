//
//  VSBoundingBoxOperation.h
//  AI_Selector
//
//  Created by guoxianghui on 2020/5/14.
//  Copyright © 2020 guoxianghui. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface VSBoundingBoxOperation : NSObject

+ (BOOL)existerBoundingBoxOfTarget:(UIImage *)image;

+ (CGRect)getScalBoundingBoxOfImage:(UIImage *)image;

@end

NS_ASSUME_NONNULL_END
