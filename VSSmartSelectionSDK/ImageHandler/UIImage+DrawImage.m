//
//  UIImage+DrawImage.m
//  AI_Selector
//
//  Created by guoxianghui on 2020/5/14.
//  Copyright © 2020 guoxianghui. All rights reserved.
//

#import "UIImage+DrawImage.h"

@implementation UIImage (DrawImage)

+ (UIImage *)drawMaskImageOfSize:(CGSize)size{
    
    UIGraphicsBeginImageContextWithOptions(size, NO, 1);
    
    CGContextRef context = UIGraphicsGetCurrentContext();
    
    CGContextSetFillColorWithColor(context, [UIColor blackColor].CGColor);
    
    UIImage *img = UIGraphicsGetImageFromCurrentImageContext();

    UIGraphicsEndImageContext();
        
    return img;
}


- (UIImage *)clippingDesignatedArea:(CGRect)rect{
    CGImageRef cgImage = CGImageCreateWithImageInRect(self.CGImage, rect);
    
    UIGraphicsBeginImageContextWithOptions(rect.size, NO, 1);
    CGContextRef contxt = UIGraphicsGetCurrentContext();
    
    CGContextTranslateCTM(contxt, 0, rect.size.height);
    CGContextScaleCTM(contxt, 1.0, -1.0);
    CGContextDrawImage(contxt, rect, cgImage);
    
    UIImage *img = [UIImage imageWithCGImage:cgImage];
    
    CGImageRelease(cgImage);
    UIGraphicsEndImageContext();
    
    return img;
}

- (UIImage *)imageClipsUseSize:(CGSize)size{
    
    UIGraphicsBeginImageContextWithOptions(size, NO, 1);
    CGContextRef contxt = UIGraphicsGetCurrentContext();
    
    CGContextTranslateCTM(contxt, 0, size.height);
    CGContextScaleCTM(contxt, 1.0, -1.0);
    CGContextDrawImage(contxt, CGRectMake(0, 0, size.width, size.height), self.CGImage);
    
    UIImage *img = UIGraphicsGetImageFromCurrentImageContext();
    
    UIGraphicsEndImageContext();
    
    return img;
}

- (UIImage*)maskAlphaImage
{
    CGImageRef img = self.CGImage;
    
    CGDataProviderRef   dataProvider;
    dataProvider = CGImageGetDataProvider(img);
    
    CFDataRef dataref = CGDataProviderCopyData(dataProvider);
    
    UInt8 *data=(UInt8 *)CFDataGetBytePtr(dataref);
    CFIndex length = CFDataGetLength(dataref);
    
    size_t width = CGImageGetWidth(img);
    size_t height = CGImageGetHeight(img);
    size_t bitsPerComponent = CGImageGetBitsPerComponent(img);
    size_t bitsPerPixel = CGImageGetBitsPerPixel(img);
    size_t bytesPerRow = CGImageGetBytesPerRow(img);

    
    UInt8* tmpData = malloc(sizeof(UInt8) * length * 4);
    if(bitsPerPixel == 8)
    {
        bitsPerPixel = 32;
        bytesPerRow = 3200;
        for(int index = 0; index < length; index ++) //4 = b + g + r + alpha
        {
            UInt8 val = data[index];
           
            if(val < 127)
            {
                tmpData[index * 4 + 3] = 0;
            }
            else
            {
                tmpData[index * 4 + 0] = 255;
                tmpData[index * 4 + 1] = 0;
                tmpData[index * 4 + 2] = 0;
                tmpData[index * 4 + 3] = 255;
            }
        }
        length *= 4;
    }
    else if(bitsPerPixel == 32)
    {
        for(int index = 0; index < length/4; index ++) //4 = b + g + r + alpha
        {
            UInt8 r = data[index * 4];
            UInt8 g = 0;
            UInt8 b = 0;
            UInt8 a = r;
//            if(r == 0 && g == 0 && b == 0)
//            {
//                tmpData[index * 4 + 3] = 0;
//            }
//            else
            {
                tmpData[index * 4 + 0] = r;
                tmpData[index * 4 + 1] = g;
                tmpData[index * 4 + 2] = b;
                tmpData[index * 4 + 3] = a;
            }
        }
    }
    else
    {
        CFRelease(dataref);
        free(tmpData);
        
        return nil;
    }
    
    //    CGColorSpaceRef colorspace = CGImageGetColorSpace(img);
    CGColorSpaceRef colorspace = CGColorSpaceCreateDeviceRGB();
    CGBitmapInfo bitmapInfo = kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big;
    CFDataRef newData = CFDataCreate(NULL,tmpData,length);
    CGDataProviderRef provider = CGDataProviderCreateWithCFData(newData);
    CGImageRef newImg = CGImageCreate(width,
                                      height,
                                      bitsPerComponent,
                                      bitsPerPixel,
                                      bytesPerRow,
                                      colorspace,
                                      bitmapInfo,
                                      provider,
                                      NULL,
                                      true,
                                      kCGRenderingIntentDefault);
    UIImage* theNew = [UIImage imageWithCGImage:newImg];
    CGImageRelease(newImg);
    CGDataProviderRelease(provider);
    CFRelease(newData);
    CGColorSpaceRelease(colorspace);
    CFRelease(dataref);
    
    free(tmpData);
    
    return theNew;
}
@end
