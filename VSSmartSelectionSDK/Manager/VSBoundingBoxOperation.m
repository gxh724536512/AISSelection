//
//  VSBoundingBoxOperation.m
//  AI_Selector
//
//  Created by guoxianghui on 2020/5/14.
//  Copyright © 2020 guoxianghui. All rights reserved.
//

#import "VSBoundingBoxOperation.h"
#import <OpenCVUtilities/VSGetBoundingBoxesUtil.h>
#import <objc/runtime.h>

#define bbScal  1.6
#define forScal .35

@implementation VSBoundingBoxOperation

+ (BOOL)existerBoundingBoxOfTarget:(UIImage *)image{
    CGRect rect = [VSGetBoundingBoxesUtil vs_getBoundingBoxesOfImage:image];
    [self setTargetBbox:NSStringFromCGRect(rect)];
    
    if ([NSStringFromCGRect(rect) isEqualToString:NSStringFromCGRect(CGRectZero)]) {
        return NO;
    }
    return YES;
}

+ (CGRect)getScalBoundingBoxOfImage:(UIImage *)image{
    
    CGRect bbox = CGRectFromString([self targetBbox]);
    
    CGFloat oriW  = image.size.width*image.scale;
    CGFloat oriH = image.size.height*image.scale;

    /// 计算bounding box实际的大小
    CGFloat width = CGRectGetWidth(bbox)*oriW;
    CGFloat height = CGRectGetHeight(bbox)*oriH;
    CGFloat x = CGRectGetMinX(bbox)*oriW;
    CGFloat y = CGRectGetMinY(bbox)*oriH;
    CGRect actualRect = CGRectMake(x, y, width, height);

    
    /// 将bounding box 进行放大处理
    
    CGFloat scal = bbScal;
    CGFloat facScal = bbScal;
     
    CGFloat scalWidth = MAX(width*scal, image.size.width*facScal);
    CGFloat scalHeight = MAX(height*scal, image.size.height*facScal);
    
    CGFloat centerX = x+width/2;
    CGFloat centerY = y+height/2;
    
//    CGFloat dx = (scal-1)/2*width;
//    CGFloat dy = (scal-1)/2*height;
    
    CGFloat dx = (scalWidth-width)/2;
    CGFloat dy = (scalHeight-height)/2;
    CGRect scalRect = CGRectInset(actualRect, -dx, -dy);
        
    /// bounding box越界问题处理
    
    CGFloat scalX = scalRect.origin.x-MIN(scalRect.origin.x, 0);
    CGFloat scalY = MAX(scalRect.origin.y, 0);
    
    scalWidth = (centerX-scalX)*2;
    scalHeight = (centerY-scalY)*2;
    
    CGFloat maxScalY = scalY+scalHeight;
    CGFloat maxScalX = scalX+scalWidth;
    
    if (maxScalY > oriH) {
        
        CGFloat topMargin = centerY;
        CGFloat bottomMargin = (oriH-centerY) ;
        
        CGFloat max = MAX(topMargin<= oriH/2?topMargin:0, bottomMargin<= oriH/2?bottomMargin:0);
        scalHeight = max*2;
        scalY = centerY-max;
    }
    
    if (maxScalX > oriW) {
        
        CGFloat leftMargin  = centerX;
        CGFloat rightMargin = oriW-centerX ;
        
        CGFloat max = MAX(leftMargin<= oriW/2?leftMargin:0, rightMargin<= oriW/2?rightMargin:0);
        scalWidth = max*2;
        scalX = centerX-max;
    }
    
    CGRect reScalRect = CGRectMake(scalX, scalY, scalWidth, scalHeight);
    
    return reScalRect;
}


+ (NSString *)targetBbox{
    return objc_getAssociatedObject(self, _cmd);
}

+ (void)setTargetBbox:(NSString *)targetBbox{
    objc_setAssociatedObject(self, @selector(targetBbox), targetBbox, OBJC_ASSOCIATION_COPY_NONATOMIC);
}

@end
