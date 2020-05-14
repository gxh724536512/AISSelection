//
//  UIImage+DrawImage.h
//  AI_Selector
//
//  Created by guoxianghui on 2020/5/14.
//  Copyright © 2020 guoxianghui. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIImage (DrawImage)

/// 绘制指定大小的 ‘mask image’
+ (UIImage *)drawMaskImageOfSize:(CGSize)size;

/// 截取指定size的image
- (UIImage *)imageClipsUseSize:(CGSize)size;

/// 截取指定区域的image
- (UIImage *)clippingDesignatedArea:(CGRect)rect;

/// alpha image 处理
- (UIImage*)maskAlphaImage;

@end

NS_ASSUME_NONNULL_END
