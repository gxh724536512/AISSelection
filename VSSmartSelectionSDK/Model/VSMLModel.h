//
//  VSMLModel.h
//  AI_Selector
//
//  Created by guoxianghui on 2020/5/9.
//  Copyright © 2020 guoxianghui. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreML/CoreML.h>

NS_ASSUME_NONNULL_BEGIN

@interface VSMLModelInput : NSObject<MLFeatureProvider>

@property (nonatomic, strong) NSArray* features;

/// image_roi as color (kCVPixelFormatType_32BGRA) image buffer, 256 pixels wide by 256 pixels high
@property (readwrite, nonatomic) CVPixelBufferRef image_roi;

/// pre_mask_roi as grayscale (kCVPixelFormatType_OneComponent8) image buffer, 256 pixels wide by 256 pixels high
@property (readwrite, nonatomic) CVPixelBufferRef pre_mask_roi;

/// pos_roi as grayscale (kCVPixelFormatType_OneComponent8) image buffer, 256 pixels wide by 256 pixels high
@property (readwrite, nonatomic) CVPixelBufferRef pos_roi;

/// neg_roi as grayscale (kCVPixelFormatType_OneComponent8) image buffer, 256 pixels wide by 256 pixels high
@property (readwrite, nonatomic) CVPixelBufferRef neg_roi;

@end


@interface VSMLModel : NSObject

+ (BOOL)decryptWithPath:(NSString*)path;


@end

NS_ASSUME_NONNULL_END
