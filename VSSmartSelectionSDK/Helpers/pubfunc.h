//
//  pubfunc.h
//  GreenScreenSDK
//
//  Created by sheen on 2020/2/5.
//

#ifndef authchecker_h
#define authchecker_h

#include <time.h>
#include <stdio.h>
#include "CommonMarco.h"

#if __ObfuscatedCode__
#define auth_info_s s1e29d01427f3aa69
#define auth_info s843fb8508a1c901a
#define end_time m8e362717b3ad3d01
#define vaildBid md062543f0148fe60
#define modelDisable m2e474ff6feb04ca0
#define vaildateTime mb5a3efe1ed46d7a3
#define vaildateDate m5f014066d7b6fae1
#define vaildateInfo m104a691c126f8899
#define convertDate m98a06d3e8e1272cc
#define modelKey m7b05371e75d6fc54
#define modelV2Key m3b587e07a9a48946
#define licenseKey mbf763c3a9771e6de
#define modelAESBytes c7821fe702e91fe78
#define modelV2AESBytes c4b0af9190b0c49ac
#define licenseRsaBytes cf997068d028e4a1a
#define bytes2str m14252af3969661c7
#define authInfo g66ce5d2b22aacad1
#endif


typedef struct auth_info_s {
    time_t end_time;
    int vaildBid;
    int modelDisable;
} auth_info;

extern auth_info authInfo;

time_t convertDate(const char* date);
int vaildateTime(time_t check_time);
int vaildateDate(const char* date);
int vaildateInfo(void);
void modelKey(char* s);
void modelV2Key(char* str);
void licenseKey(char* s);

//#if DEBUG
//void printBytesArray(char* str)
//#endif

#endif /* authchecker_h */
