//
//  VSPBResizeTool.m
//  AI_Selector
//
//  Created by guoxianghui on 2020/5/14.
//  Copyright © 2020 guoxianghui. All rights reserved.
//

#import "VSPBResizeTool.h"
#import "CommonMarco.h"
#import <Accelerate/Accelerate.h>

@interface VSPBDataLogic : NSObject

@property (nonatomic) void *dstData;

@property (nonatomic) size_t dataLength;

@end

@implementation VSPBDataLogic

- (void)dealloc{
    [self clearData];
}

- (void)clearData{
    if (_dstData) {
        free(_dstData);
        _dstData = NULL;
        _dataLength = 0;
    }
}

- (void)setDataLength:(size_t)dataLength{
    if (_dataLength != dataLength) {
        [self clearData];
        
        _dataLength = dataLength;
        _dstData = malloc(_dataLength);
        
    }
}

@end

@interface VSPBResizeTool ()
@property (nonatomic) VSPBDataLogic *resizeLogic;
@property (nonatomic) VSPBDataLogic *cropLogic;
@end

@implementation VSPBResizeTool

void releaseCallback(void *releaseRefCon, const void *baseAddress) {
//    if(!baseAddress)
//    {
//        free((void *)baseAddress);
//    }
    // Perform additional cleanup as needed.
}



- (instancetype)init
{
    self = [super init];
    if (self) {
        self.resizeLogic = [VSPBDataLogic new];
        self.cropLogic   = [VSPBDataLogic new];
    }
    return self;
}

- (CVPixelBufferRef)resizeGrayPixelBuffer:(CVPixelBufferRef)inputPB
                               targetSize:(CGSize)targetSize
{
    CVReturn status = CVPixelBufferLockBaseAddress(inputPB, 0);
    if(kCVReturnSuccess != status)
    {
        return NULL;
    }
//    defer { CVPixelBufferUnlockBaseAddress(srcPixelBuffer, flags) }
    void* srcData = CVPixelBufferGetBaseAddress(inputPB);
    if(!srcData)
    {
        CVPixelBufferUnlockBaseAddress(inputPB, 0);
        MSGLOG(@"Error: could not get pixel buffer base address");
        return NULL;
    }
    
    size_t srcHeight = CVPixelBufferGetHeight(inputPB);
    size_t srcWidth = CVPixelBufferGetWidth(inputPB);
    
    size_t srcBytesPerRow = CVPixelBufferGetBytesPerRow(inputPB);
    vImage_Buffer srcBuffer = {
        srcData,
        srcHeight,
        srcWidth,
        srcBytesPerRow
    };
    
    CGFloat destBytesPerRow = targetSize.width;
    _resizeLogic.dataLength = targetSize.height * destBytesPerRow;
    void* destData = _resizeLogic.dstData;
    
    if(!destData)
    {
        CVPixelBufferUnlockBaseAddress(inputPB, 0);
        MSGLOG(@"Error: out of memory");
        return NULL;
    }
    vImage_Buffer destBuffer = {
        destData,
        targetSize.height,
        targetSize.width,
        destBytesPerRow
    };
    
    vImage_Error error = vImageScale_Planar8(&srcBuffer, &destBuffer, nil, 0);
    if(error != kvImageNoError)
    {
        CVPixelBufferUnlockBaseAddress(inputPB, 0);
        MSGLOG(@"Error: %zd", error);
        return NULL;
    }
    
    OSType pixelFormat = CVPixelBufferGetPixelFormatType(inputPB);
    CVPixelBufferRef dstPixelBuffer = NULL;
    status = CVPixelBufferCreateWithBytes(NULL,
                                          targetSize.width,
                                          targetSize.height,
                                          pixelFormat,
                                          destData,
                                          destBytesPerRow,
                                          releaseCallback,
                                          nil,
                                          nil,
                                          &dstPixelBuffer);
    
    if(status != kCVReturnSuccess)
    {
        CVPixelBufferUnlockBaseAddress(inputPB, 0);
        MSGLOG(@"Error: could not create new pixel buffer");
        return NULL;
    }
    
    CVPixelBufferUnlockBaseAddress(inputPB, 0);
    return dstPixelBuffer;
}

- (CVPixelBufferRef)cropPixelBufferWithInputPb:(CVPixelBufferRef)inputPB
                                      cropRect:(CGRect)cropRect
                                    outputSize:(CGSize)outputSize
{
    int cropX = cropRect.origin.x;
    int cropY = cropRect.origin.y;
    int cropWidth = cropRect.size.width;
    int cropHeight = cropRect.size.height;
    int scaleWidth = outputSize.width;
    int scaleHeight = outputSize.height;
    
    if(CVPixelBufferLockBaseAddress(inputPB, 0) != kCVReturnSuccess)
    {
        return NULL;
    }
    
    void* inputData = CVPixelBufferGetBaseAddress(inputPB);
    if(!inputData)
    {
        MSGLOG(@"Error: could not get pixel buffer base address");
        CVPixelBufferUnlockBaseAddress(inputPB, 0);
        return NULL;
    }
    
    size_t srcBytesPerRow = CVPixelBufferGetBytesPerRow(inputPB);
    OSType pixelFormat = CVPixelBufferGetPixelFormatType(inputPB);
    
    int component = 4;
    if (pixelFormat == kCVPixelFormatType_OneComponent8) {
        component = 1;
    }
    
    int offset = (int)(cropY * srcBytesPerRow+cropX*component);
    vImage_Buffer srcBuffer = {
        inputData+offset,
        cropHeight,
        cropWidth,
        srcBytesPerRow
    };

    int destBytesPerRow = scaleWidth * component;
    _cropLogic.dataLength = scaleHeight * destBytesPerRow;
    void* destData = _cropLogic.dstData;
;
    if(!destData)
    {
        CVPixelBufferUnlockBaseAddress(inputPB, 0);
        MSGLOG(@"malloc error: out of memory");
        return NULL;
    }
    
    vImage_Buffer destBuffer = {
        destData,
        scaleHeight,
        scaleWidth,
        destBytesPerRow
    };
    
    vImage_Error error = vImageScale_ARGB8888(&srcBuffer, &destBuffer, nil, kvImageNoFlags);
    
    if(error != kvImageNoError)
    {
        CVPixelBufferUnlockBaseAddress(inputPB, 0);
        MSGLOG(@"vImageScale_ARGB8888 error: %zd", error);
        return NULL;
    }

    CVPixelBufferRef dstPixelBuffer = NULL;
    CVReturn status = CVPixelBufferCreateWithBytes(NULL,
                                                   scaleWidth,
                                                   scaleHeight,
                                                   pixelFormat,
                                                   destData,
                                                   destBytesPerRow,
                                                   releaseCallback,
                                                   nil,
                                                   nil,
                                                   &dstPixelBuffer);
    if(status != kCVReturnSuccess) {
        MSGLOG(@"create pixelbuffer error: could not create new pixel buffer");
        CVPixelBufferUnlockBaseAddress(inputPB, 0);
        return NULL;
    }

    CVPixelBufferUnlockBaseAddress(inputPB, 0);
    CVBufferRelease(inputPB);
    
    return dstPixelBuffer;
}

- (CVPixelBufferRef)mergeMaskPB:(CVPixelBufferRef)maskPB
                     onCanvasPB:(CVPixelBufferRef)canvasPB
                          inArea:(CGRect)area
                            
{
    if(!canvasPB || !maskPB)
    {
        return NULL;
    }
    
    CGFloat w0 = CVPixelBufferGetWidth(canvasPB);
    CGFloat h0 = CVPixelBufferGetHeight(canvasPB);
        
    //保存之前的bbox，然后根据这个bbox把它贴到新的画布上
    CGRect bbox = area;
    if(CGRectIsEmpty(bbox))
    {
        bbox = CGRectMake(0, 0, w0, h0);
    }
        
    size_t x1 = bbox.origin.x;
    size_t y1 = bbox.origin.y;
    size_t w1 = bbox.size.width;
    size_t h1 = bbox.size.height;

    CVPixelBufferRef alphaToUse = maskPB;

    CVReturn status = CVPixelBufferLockBaseAddress(maskPB, 0);
    if(status != kCVReturnSuccess)
    {
        return NULL;
    }
    
    /// 将mask resize到bounding box区域大小
    CVPixelBufferRef resizedAlpha = [self resizeGrayPixelBuffer:maskPB targetSize:CGSizeMake(w1, h1)];
        
    if(!resizedAlpha)
    {
        CVPixelBufferUnlockBaseAddress(maskPB, 0);
        return NULL;
    }

    CVPixelBufferRef emptyPixelBuffer = canvasPB;
    status = CVPixelBufferLockBaseAddress(emptyPixelBuffer, 0);
    if(kCVReturnSuccess != status)
    {
        CVPixelBufferRelease(emptyPixelBuffer);
        CVPixelBufferUnlockBaseAddress(maskPB, 0);
        return NULL;
    }
    
    status = CVPixelBufferLockBaseAddress(resizedAlpha, 0);
    if(kCVReturnSuccess != status)
    {
        CVPixelBufferRelease(resizedAlpha);
        CVPixelBufferRelease(emptyPixelBuffer);
        CVPixelBufferUnlockBaseAddress(maskPB, 0);
        CVPixelBufferUnlockBaseAddress(emptyPixelBuffer, 0);
        return NULL;
    }
    
    size_t bytesPerRow = CVPixelBufferGetBytesPerRow(emptyPixelBuffer);
    void* outputBuffer = CVPixelBufferGetBaseAddress(emptyPixelBuffer);
    void* inputBuffer = CVPixelBufferGetBaseAddress(resizedAlpha);
        
    for(int y = 0; y < h1; y++)
    {
        memcpy(outputBuffer + (int)((y + y1) * bytesPerRow + x1), inputBuffer + (int)(y * w1), w1);
    }

    alphaToUse = emptyPixelBuffer;

    CVPixelBufferUnlockBaseAddress(emptyPixelBuffer, 0);
    CVPixelBufferUnlockBaseAddress(resizedAlpha, 0);
    CVPixelBufferUnlockBaseAddress(maskPB, 0);
    CVPixelBufferRelease(resizedAlpha);
    
    return alphaToUse;
}

@end
