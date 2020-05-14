//
//  UIImage+PixelBuffer.m
//  GreenScreenSDK_Example
//
//  Created by yao on 2019/4/24.
//  Copyright © 2019 shengtao.wu. All rights reserved.
//

#import "UIImage+PixelBuffer.h"

@implementation UIImage (PixelBuffer)

- (CVPixelBufferRef)pixelBuffer {
    NSDictionary *attributes = @{
                                 (NSString *)kCVPixelBufferMetalCompatibilityKey: @(YES),
                                 (NSString *)kCVPixelBufferCGImageCompatibilityKey: @(YES),
                                 (NSString *)kCVPixelBufferCGBitmapContextCompatibilityKey: @(YES)
                                 };
    CGSize frameSize = CGSizeMake(self.size.width, self.size.height);
    CVPixelBufferRef pixelBuffer;
    CVReturn status = CVPixelBufferCreate(kCFAllocatorDefault, frameSize.width, frameSize.height, kCVPixelFormatType_32BGRA, (__bridge CFDictionaryRef _Nullable)(attributes), &pixelBuffer);
    if (status != kCVReturnSuccess) {
        return nil;
    }
    
    CVPixelBufferLockBaseAddress(pixelBuffer, kCVPixelBufferLock_ReadOnly);    
    void *data = CVPixelBufferGetBaseAddress(pixelBuffer);
    CGColorSpaceRef rgbColorSpaceRef = CGColorSpaceCreateDeviceRGB();
    
    CGContextRef context = CGBitmapContextCreate(data, frameSize.width, frameSize.height, 8, CVPixelBufferGetBytesPerRow(pixelBuffer), rgbColorSpaceRef, kCGImageAlphaNoneSkipFirst|kCGBitmapByteOrder32Little);
    CGContextDrawImage(context, CGRectMake(0, 0, self.size.width, self.size.height), self.CGImage);
    CVPixelBufferUnlockBaseAddress(pixelBuffer, kCVPixelBufferLock_ReadOnly);
    
    CGColorSpaceRelease(rgbColorSpaceRef);
    CGContextRelease(context);
    return pixelBuffer;
}

- (CVPixelBufferRef)garyscalePixelBuffer {
    NSDictionary *attributes = @{
                                 (NSString *)kCVPixelBufferMetalCompatibilityKey: @(YES),
                                 (NSString *)kCVPixelBufferCGImageCompatibilityKey: @(YES),
                                 (NSString *)kCVPixelBufferCGBitmapContextCompatibilityKey: @(YES)
                                 };
    CGSize frameSize = CGSizeMake(self.size.width, self.size.height);
    CVPixelBufferRef pixelBuffer;
    CVReturn status = CVPixelBufferCreate(kCFAllocatorDefault,
                                          frameSize.width,
                                          frameSize.height,
                                          kCVPixelFormatType_OneComponent8,
                                          (__bridge CFDictionaryRef _Nullable)(attributes),
                                          &pixelBuffer);
    if (status != kCVReturnSuccess) {
        return nil;
    }
    
    CVPixelBufferLockBaseAddress(pixelBuffer, kCVPixelBufferLock_ReadOnly);
    void *data = CVPixelBufferGetBaseAddress(pixelBuffer);
    CGColorSpaceRef rgbColorSpaceRef = CGColorSpaceCreateDeviceGray();
    
    CGContextRef context = CGBitmapContextCreate(data, frameSize.width, frameSize.height, 8, CVPixelBufferGetBytesPerRow(pixelBuffer), rgbColorSpaceRef, kCGImageAlphaNone);
    CGContextDrawImage(context, CGRectMake(0, 0, self.size.width, self.size.height), self.CGImage);
    CVPixelBufferUnlockBaseAddress(pixelBuffer, kCVPixelBufferLock_ReadOnly);
    
    CGColorSpaceRelease(rgbColorSpaceRef);
    CGContextRelease(context);
    return pixelBuffer;
}

+ (UIImage *)imageFromPixelBuffer:(CVPixelBufferRef)pixelBuffer {
    CIImage *ciImage = [CIImage imageWithCVPixelBuffer:pixelBuffer];

    CIContext *temporaryContext = [CIContext contextWithOptions:nil];
    CGImageRef videoImage = [temporaryContext
                       createCGImage:ciImage
                       fromRect:CGRectMake(0, 0,
                              CVPixelBufferGetWidth(pixelBuffer),
                              CVPixelBufferGetHeight(pixelBuffer))];

    UIImage *uiImage = [UIImage imageWithCGImage:videoImage];
    CGImageRelease(videoImage);
    return uiImage;
}




//    let bitmapInfo = CGBitmapInfo(rawValue: CGBitmapInfo.byteOrder32Little.rawValue | CGImageAlphaInfo.premultipliedFirst.rawValue)
//    let context = CGContext(data: data, width: Int(frameSize.width), height: Int(frameSize.height), bitsPerComponent: 8, bytesPerRow: CVPixelBufferGetBytesPerRow(pixelBuffer!), space: rgbColorSpace, bitmapInfo: bitmapInfo.rawValue)
//    context!.draw(self.cgImage!, in: CGRect(x: 0, y: 0, width: self.size.width, height: self.size.height))
//

//    return pixelBuffer
//}

@end
