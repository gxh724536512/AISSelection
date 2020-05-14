//
//  VSPBResizeTool.h
//  AI_Selector
//
//  Created by guoxianghui on 2020/5/14.
//  Copyright © 2020 guoxianghui. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/CoreML.h>

NS_ASSUME_NONNULL_BEGIN

@interface VSPBResizeTool : NSObject

- (CVPixelBufferRef)resizeGrayPixelBuffer:(CVPixelBufferRef)inputPB
                               targetSize:(CGSize)targetSize;

- (CVPixelBufferRef)cropPixelBufferWithInputPb:(CVPixelBufferRef)inputPB
                                      cropRect:(CGRect)cropRect
                                    outputSize:(CGSize)outputSize;


/// 将蒙版合并到画布的指定位置
/// @param maskPB 蒙版
/// @param canvasPB 画布
/// @param area 指定区域
- (CVPixelBufferRef)mergeMaskPB:(CVPixelBufferRef)maskPB
                     onCanvasPB:(CVPixelBufferRef)canvasPB
                         inArea:(CGRect)area;
@end

NS_ASSUME_NONNULL_END
