//
//  VSMLModel.m
//  AI_Selector
//
//  Created by guoxianghui on 2020/5/9.
//  Copyright © 2020 guoxianghui. All rights reserved.
//

#import "VSMLModel.h"
#import "Pub.h"
#import "pubfunc.h"

API_AVAILABLE(macos(10.13.2), ios(11.0), watchos(4.2), tvos(11.0)) __attribute__((visibility("hidden")))

@implementation VSMLModelInput

- (NSArray*)features
{
    if(!_features)
    {
        _features = @[@"image_roi", @"pre_mask_roi", @"pos_roi", @"neg_roi"];
    }
    
    return _features;
}

- (NSSet<NSString *> *)featureNames
{
    return [NSSet setWithArray:self.features];
}

- (nullable MLFeatureValue *)featureValueForName:(nonnull NSString *)featureName {
    if([self.features containsObject:featureName]) {
        
        if ([featureName isEqualToString:@"image_roi"]) {
            return [MLFeatureValue featureValueWithPixelBuffer:self.image_roi];
        }
        
        if ([featureName isEqualToString:@"pre_mask_roi"]) {
            return [MLFeatureValue featureValueWithPixelBuffer:self.pre_mask_roi];
        }
        
        if ([featureName isEqualToString:@"pos_roi"]) {
            return [MLFeatureValue featureValueWithPixelBuffer:self.pos_roi];
        }
        
        if ([featureName isEqualToString:@"neg_roi"]) {
            return [MLFeatureValue featureValueWithPixelBuffer:self.neg_roi];
        }
    }
    return nil;
}

- (void)dealloc{
    CVBufferRelease(self.image_roi);
    CVBufferRelease(self.pre_mask_roi);
    CVBufferRelease(self.pos_roi);
    CVBufferRelease(self.neg_roi);
}

@end

@implementation VSMLModel

+ (BOOL)decryptWithPath:(NSString*)path
{
    char s[20] = {0};
    NSString* netName = @"model.espresso.net";
    NSString* shapeName = @"model.espresso.shape";
    NSString* atNetPath = [NSString stringWithFormat:@"%@/%@.md5", path, netName];
    NSString* atV2NetPath = [NSString stringWithFormat:@"%@/%@.versa", path, netName];
    NSString* toNetPath = [NSString stringWithFormat:@"%@/%@", path, netName];
    NSString* atShapePath = [NSString stringWithFormat:@"%@/%@.md5", path, shapeName];
    NSString* atV2ShapePath = [NSString stringWithFormat:@"%@/%@.versa", path, shapeName];
    NSString* toShapePath = [NSString stringWithFormat:@"%@/%@", path, shapeName];
    
    NSDate* date = [NSDate date];
    NSString* netStr = @"";
    NSString* shapeStr = @"";
    if([[NSFileManager defaultManager] fileExistsAtPath:atNetPath])
    {
        NSString* netEnc = [NSString stringWithContentsOfFile:atNetPath encoding:NSUTF8StringEncoding error:nil];
        modelKey(s);
        NSString* privkey = [NSString stringWithUTF8String:s];
        netStr = [RSA aesDecryptString:netEnc key:privkey];
    }
    else if([[NSFileManager defaultManager] fileExistsAtPath:atV2NetPath])
    {
        NSString* netEnc = [NSString stringWithContentsOfFile:atV2NetPath encoding:NSUTF8StringEncoding error:nil];
        modelV2Key(s);
        NSString* privkey = [NSString stringWithUTF8String:s];
        netStr = [RSA aesDecryptString:netEnc key:privkey];
    }
//    MSGLOG(@"decrypt 1: %.f ms", -[date timeIntervalSinceNow] * 1000);
    
    date = [NSDate date];
    if([[NSFileManager defaultManager] fileExistsAtPath:atShapePath])
    {
        NSString* shapeEnc = [NSString stringWithContentsOfFile:atShapePath encoding:NSUTF8StringEncoding error:nil];
        modelKey(s);
        NSString* privkey = [NSString stringWithUTF8String:s];
        shapeStr = [RSA aesDecryptString:shapeEnc key:privkey];
    }
    else if([[NSFileManager defaultManager] fileExistsAtPath:atV2ShapePath])
    {
        NSString* shapeEnc = [NSString stringWithContentsOfFile:atV2ShapePath encoding:NSUTF8StringEncoding error:nil];
        modelV2Key(s);
        NSString* privkey = [NSString stringWithUTF8String:s];
        shapeStr = [RSA aesDecryptString:shapeEnc key:privkey];
    }
//    MSGLOG(@"decrypt 2: %.f ms", -[date timeIntervalSinceNow] * 1000);
    
    NSError* error1 = nil;
    NSError* error2 = nil;
    [netStr writeToFile:toNetPath atomically:YES encoding:NSUTF8StringEncoding error:&error1];
    [shapeStr writeToFile:toShapePath atomically:YES encoding:NSUTF8StringEncoding error:&error2];
    
    return (error1 == nil) && (error2 == nil);
}
@end

