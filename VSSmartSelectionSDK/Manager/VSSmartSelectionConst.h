//
//  VSSmartSelectionConst.h
//  AI_Selector
//
//  Created by guoxianghui on 2020/5/14.
//  Copyright © 2020 guoxianghui. All rights reserved.
//

#ifndef VSSmartSelectionConst_h
#define VSSmartSelectionConst_h

#import <UIKit/UIKit.h>
#import <CoreML/CoreML.h>

struct VSInputDataSet {
    /// 原图
    UIImage *oriImage;
    /// 上一次的图片信息
    UIImage *preImage;
    /// 画笔图片
    UIImage *brushImage;
    ///判断画笔状态是正选还是反选  默认是正选
    BOOL isReverseChoice;
};

typedef struct VSInputDataSet VSInputDataSet;

#endif /* VSSmartSelectionConst_h */
