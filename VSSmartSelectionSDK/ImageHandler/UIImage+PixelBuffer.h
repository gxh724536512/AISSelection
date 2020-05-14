//
//  UIImage+PixelBuffer.h
//  GreenScreenSDK_Example
//
//  Created by yao on 2019/4/24.
//  Copyright © 2019 shengtao.wu. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIImage (PixelBuffer)
- (CVPixelBufferRef)pixelBuffer;
- (CVPixelBufferRef)garyscalePixelBuffer;

+ (UIImage *)imageFromPixelBuffer:(CVPixelBufferRef)pixelBuffer;

@end

NS_ASSUME_NONNULL_END
