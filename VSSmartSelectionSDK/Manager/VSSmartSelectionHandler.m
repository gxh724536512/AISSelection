//
//  VSSmartSelectionHandler.m
//  AI_Selector
//
//  Created by guoxianghui on 2020/5/14.
//  Copyright © 2020 guoxianghui. All rights reserved.
//

#import "VSSmartSelectionHandler.h"
#import "VSMLModel.h"
#import "UIImage+DrawImage.h"
#import "UIImage+PixelBuffer.h"
#import "VSBoundingBoxOperation.h"
#import "VSPBResizeTool.h"

@interface VSSmartSelectionHandler ()

@property (nonatomic) CVPixelBufferRef preMaskPB;

@property (nonatomic) UIImage *commonMaskImage;

@property (nonatomic, strong) MLModel *mlModel;

@property (nonatomic, strong) VSPBResizeTool *resizeTool;

@property (nonatomic) CGSize oriSize;
@property (nonatomic) CGRect oriReferBbox;
@property (nonatomic) CGSize oriReferSize;

@end

@implementation VSSmartSelectionHandler

- (instancetype)init
{
    self = [super init];
    if (self) {
        self.resizeTool = [VSPBResizeTool new];
    }
    return self;
}

- (void)setupModelPath:(NSString *)modelPath key:(NSString *)key{
    
    NSString *document = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES).firstObject;
    
    NSString* tempFolder = [NSString stringWithFormat:@"%@/%@", document, [[NSUUID UUID] UUIDString]];
        
    [[NSFileManager defaultManager] createDirectoryAtPath:tempFolder
                              withIntermediateDirectories:YES
                                               attributes:nil
                                                    error:nil];
    
    NSString* modelCopyPath = [NSString stringWithFormat:@"%@/%@", tempFolder, [NSUUID UUID].UUIDString];

    
    NSError* error = nil;
    [[NSFileManager defaultManager] removeItemAtPath:modelCopyPath error:&error];
    error = nil;
    BOOL success = NO;
    if([modelPath length] > 0)
    {
        [[NSFileManager defaultManager] copyItemAtPath:modelPath toPath:modelCopyPath error:&error];
        success = [VSMLModel decryptWithPath:modelCopyPath];
    }
    if(!success)
    {
        NSLog(@"失败");
        return;
    }
    NSURL* modelURL = [NSURL fileURLWithPath:modelCopyPath];
    error = nil;
    MLModel* model = [MLModel modelWithContentsOfURL:modelURL error:&error];
    self.mlModel = model;
}

#pragma mark - Public

- (CVPixelBufferRef)getMaskPBWithFrameMode:(VSInputDataSet)mode{
    
    VSMLModelInput *input = [self configModelInputFromModel:mode];

    NSError *error = nil;

    id<MLFeatureProvider> output = [self.mlModel predictionFromFeatures:input error:&error];

    CVPixelBufferRef outputPB = [[output featureValueForName:@"alpha"] imageBufferValue];
    
    /// 先保存一份原先的 pixelBuffer
    CVPixelBufferRef maskPB = self.preMaskPB;

    /// 获取新的混合 pixelBuffer
    CVPixelBufferRef mergePB = [self.resizeTool mergeMaskPB:outputPB onCanvasPB:maskPB inArea:self.oriReferBbox];
    
    /// 重新赋值，记录当前的混合数据
    self.preMaskPB = mergePB;
    
    return mergePB;
}

#pragma mark - Input

- (VSMLModelInput *)configModelInputFromModel:(VSInputDataSet)mode{
    
    CGSize clipSize = [self modelSize];
       
    UIImage *oriImage = mode.oriImage; /// 原图
    UIImage *brushImage = mode.brushImage; /// 笔刷图
    
    UIImage *posImage;
    UIImage *negImage;
    
    [VSBoundingBoxOperation existerBoundingBoxOfTarget:brushImage];
    CGRect brushScalRect = [VSBoundingBoxOperation getScalBoundingBoxOfImage:brushImage];
    
    self.oriSize = oriImage.size;
    self.oriReferBbox = brushScalRect;
    self.oriReferSize = brushImage.size;
    
    if (mode.isReverseChoice) { /// 反选操作
        
        posImage = [self.commonMaskImage imageClipsUseSize:clipSize];
        UIImage *scalNegImage = [brushImage clippingDesignatedArea:brushScalRect];
        negImage = [scalNegImage imageClipsUseSize:clipSize];
        
    }else{ /// 正选操作
        
        UIImage *scalPosImage = [brushImage clippingDesignatedArea:brushScalRect];
        posImage = [scalPosImage imageClipsUseSize:clipSize];
        negImage = [self.commonMaskImage imageClipsUseSize:clipSize];
    }
    
    
    CGRect oriScalRect = [VSBoundingBoxOperation getScalBoundingBoxOfImage:oriImage];

//    self.bboxView.frame = brushScalRect;
//    CVPixelBufferRef brushScalPB = [self cropPixelBufferWithInputPb:[oriBrushImg garyscalePixelBuffer] cropRect:brushScalRect outputSize:[self modelSize]];
    
    /// 上一次获取的mask
    UIImage *preImage = [UIImage imageFromPixelBuffer:self.preMaskPB];
    CGRect preScalRect = [VSBoundingBoxOperation getScalBoundingBoxOfImage:preImage];
    UIImage *preMaskImage = [preImage clippingDesignatedArea:preScalRect];
    preMaskImage = [preMaskImage imageClipsUseSize:clipSize];
    
    
    CVPixelBufferRef oriScalPB = [self.resizeTool cropPixelBufferWithInputPb:[oriImage pixelBuffer] cropRect:oriScalRect outputSize:clipSize];
    CVPixelBufferRef preMaskPB = [preMaskImage garyscalePixelBuffer];
    
    /// 笔刷
    CVPixelBufferRef posPB = [posImage garyscalePixelBuffer];
    CVPixelBufferRef negPB = [negImage garyscalePixelBuffer];
        
    VSMLModelInput *input = [VSMLModelInput new];
    
    input.image_roi = oriScalPB;
    input.pre_mask_roi = preMaskPB;
    input.pos_roi = posPB;
    input.neg_roi = negPB;
    
    return input;
}

- (CGSize)modelSize{
    MLImageConstraint *imageConstraint = [self.mlModel.modelDescription.inputDescriptionsByName valueForKey:@"image_roi"].imageConstraint;
    return CGSizeMake(imageConstraint.pixelsWide, imageConstraint.pixelsHigh);
}

- (CVPixelBufferRef)preMaskPB{
    if (!_preMaskPB) {
        UIImage *preMaskImage = [UIImage drawMaskImageOfSize:self.oriReferSize];
        _preMaskPB = [preMaskImage garyscalePixelBuffer];
    }
    return _preMaskPB;
}

- (UIImage *)commonMaskImage{
    if (!_commonMaskImage) {
        _commonMaskImage = [UIImage drawMaskImageOfSize:self.oriSize];
    }
    return _commonMaskImage;
}
@end
