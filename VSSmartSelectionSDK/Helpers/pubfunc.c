//
//  pubfunc.c
//  GreenScreenSDK
//
//  Created by sheen on 2020/2/5.
//

#include "pubfunc.h"
#include <string.h>
#include <stdlib.h>

//#if DEBUG
//void printBytesArray(char* str)
//{
//    printf("{");
//    while (*str) {
//        printf("ProcessBts(0x%X), ", *str);
//        str++;
//    }
//    printf("0x00}");
//}
//#endif

auth_info authInfo = (auth_info){0,0,0};

#define ProcessBts(c) (0xFF - c)
const char modelAESBytes[] = {ProcessBts(0x72), ProcessBts(0x6A), ProcessBts(0x76), ProcessBts(0x6C), ProcessBts(0x77), ProcessBts(0x7A), ProcessBts(0x6A), ProcessBts(0x62), ProcessBts(0x63), ProcessBts(0x76), ProcessBts(0x6C), ProcessBts(0x69), ProcessBts(0x78), ProcessBts(0x74), ProcessBts(0x6A), ProcessBts(0x6D), 0x00};
const char modelV2AESBytes[] = {ProcessBts(0x76), ProcessBts(0x6C), ProcessBts(0x44), ProcessBts(0x61), ProcessBts(0x30), ProcessBts(0x6A), ProcessBts(0x63), ProcessBts(0x6C), ProcessBts(0x46), ProcessBts(0x64), ProcessBts(0x39), ProcessBts(0x6A), ProcessBts(0x74), ProcessBts(0x73), ProcessBts(0x66), ProcessBts(0x63), 0x00};
const char licenseRsaBytes[] = {ProcessBts(0x2D), ProcessBts(0x2D), ProcessBts(0x2D), ProcessBts(0x2D), ProcessBts(0x2D), ProcessBts(0x42), ProcessBts(0x45), ProcessBts(0x47), ProcessBts(0x49), ProcessBts(0x4E), ProcessBts(0x20), ProcessBts(0x50), ProcessBts(0x52), ProcessBts(0x49), ProcessBts(0x56), ProcessBts(0x41), ProcessBts(0x54), ProcessBts(0x45), ProcessBts(0x20), ProcessBts(0x4B), ProcessBts(0x45), ProcessBts(0x59), ProcessBts(0x2D), ProcessBts(0x2D), ProcessBts(0x2D), ProcessBts(0x2D), ProcessBts(0x2D), ProcessBts(0x4D), ProcessBts(0x49), ProcessBts(0x49), ProcessBts(0x43), ProcessBts(0x64), ProcessBts(0x77), ProcessBts(0x49), ProcessBts(0x42), ProcessBts(0x41), ProcessBts(0x44), ProcessBts(0x41), ProcessBts(0x4E), ProcessBts(0x42), ProcessBts(0x67), ProcessBts(0x6B), ProcessBts(0x71), ProcessBts(0x68), ProcessBts(0x6B), ProcessBts(0x69), ProcessBts(0x47), ProcessBts(0x39), ProcessBts(0x77), ProcessBts(0x30), ProcessBts(0x42), ProcessBts(0x41), ProcessBts(0x51), ProcessBts(0x45), ProcessBts(0x46), ProcessBts(0x41), ProcessBts(0x41), ProcessBts(0x53), ProcessBts(0x43), ProcessBts(0x41), ProcessBts(0x6D), ProcessBts(0x45), ProcessBts(0x77), ProcessBts(0x67), ProcessBts(0x67), ProcessBts(0x4A), ProcessBts(0x64), ProcessBts(0x41), ProcessBts(0x67), ProcessBts(0x45), ProcessBts(0x41), ProcessBts(0x41), ProcessBts(0x6F), ProcessBts(0x47), ProcessBts(0x42), ProcessBts(0x41), ProcessBts(0x4C), ProcessBts(0x49), ProcessBts(0x47), ProcessBts(0x6C), ProcessBts(0x6B), ProcessBts(0x2F), ProcessBts(0x63), ProcessBts(0x6E), ProcessBts(0x71), ProcessBts(0x79), ProcessBts(0x63), ProcessBts(0x46), ProcessBts(0x30), ProcessBts(0x48), ProcessBts(0x57), ProcessBts(0x70), ProcessBts(0x2F), ProcessBts(0x62), ProcessBts(0x46), ProcessBts(0x6C), ProcessBts(0x5A), ProcessBts(0x49), ProcessBts(0x6C), ProcessBts(0x57), ProcessBts(0x6E), ProcessBts(0x4A), ProcessBts(0x70), ProcessBts(0x4C), ProcessBts(0x50), ProcessBts(0x63), ProcessBts(0x41), ProcessBts(0x46), ProcessBts(0x48), ProcessBts(0x64), ProcessBts(0x70), ProcessBts(0x31), ProcessBts(0x43), ProcessBts(0x38), ProcessBts(0x44), ProcessBts(0x36), ProcessBts(0x72), ProcessBts(0x39), ProcessBts(0x2F), ProcessBts(0x37), ProcessBts(0x43), ProcessBts(0x56), ProcessBts(0x75), ProcessBts(0x34), ProcessBts(0x34), ProcessBts(0x68), ProcessBts(0x76), ProcessBts(0x77), ProcessBts(0x62), ProcessBts(0x64), ProcessBts(0x6E), ProcessBts(0x77), ProcessBts(0x4D), ProcessBts(0x75), ProcessBts(0x6E), ProcessBts(0x45), ProcessBts(0x77), ProcessBts(0x6E), ProcessBts(0x5A), ProcessBts(0x2B), ProcessBts(0x52), ProcessBts(0x77), ProcessBts(0x54), ProcessBts(0x76), ProcessBts(0x34), ProcessBts(0x75), ProcessBts(0x4B), ProcessBts(0x45), ProcessBts(0x59), ProcessBts(0x33), ProcessBts(0x4E), ProcessBts(0x33), ProcessBts(0x75), ProcessBts(0x31), ProcessBts(0x38), ProcessBts(0x37), ProcessBts(0x43), ProcessBts(0x73), ProcessBts(0x39), ProcessBts(0x41), ProcessBts(0x37), ProcessBts(0x50), ProcessBts(0x53), ProcessBts(0x41), ProcessBts(0x4F), ProcessBts(0x71), ProcessBts(0x59), ProcessBts(0x36), ProcessBts(0x65), ProcessBts(0x4B), ProcessBts(0x4C), ProcessBts(0x73), ProcessBts(0x46), ProcessBts(0x39), ProcessBts(0x78), ProcessBts(0x49), ProcessBts(0x46), ProcessBts(0x37), ProcessBts(0x4A), ProcessBts(0x51), ProcessBts(0x39), ProcessBts(0x62), ProcessBts(0x33), ProcessBts(0x30), ProcessBts(0x6B), ProcessBts(0x38), ProcessBts(0x54), ProcessBts(0x49), ProcessBts(0x4D), ProcessBts(0x68), ProcessBts(0x48), ProcessBts(0x65), ProcessBts(0x66), ProcessBts(0x59), ProcessBts(0x6F), ProcessBts(0x75), ProcessBts(0x6C), ProcessBts(0x44), ProcessBts(0x70), ProcessBts(0x39), ProcessBts(0x4C), ProcessBts(0x2F), ProcessBts(0x54), ProcessBts(0x47), ProcessBts(0x61), ProcessBts(0x4E), ProcessBts(0x70), ProcessBts(0x32), ProcessBts(0x4A), ProcessBts(0x64), ProcessBts(0x6A), ProcessBts(0x54), ProcessBts(0x38), ProcessBts(0x39), ProcessBts(0x34), ProcessBts(0x45), ProcessBts(0x34), ProcessBts(0x78), ProcessBts(0x4F), ProcessBts(0x59), ProcessBts(0x79), ProcessBts(0x4D), ProcessBts(0x67), ProcessBts(0x62), ProcessBts(0x78), ProcessBts(0x30), ProcessBts(0x59), ProcessBts(0x63), ProcessBts(0x49), ProcessBts(0x31), ProcessBts(0x63), ProcessBts(0x65), ProcessBts(0x41), ProcessBts(0x30), ProcessBts(0x72), ProcessBts(0x72), ProcessBts(0x77), ProcessBts(0x7A), ProcessBts(0x39), ProcessBts(0x76), ProcessBts(0x57), ProcessBts(0x2B), ProcessBts(0x6B), ProcessBts(0x79), ProcessBts(0x4A), ProcessBts(0x52), ProcessBts(0x68), ProcessBts(0x41), ProcessBts(0x67), ProcessBts(0x4D), ProcessBts(0x42), ProcessBts(0x41), ProcessBts(0x41), ProcessBts(0x45), ProcessBts(0x43), ProcessBts(0x67), ProcessBts(0x59), ProcessBts(0x45), ProcessBts(0x41), ProcessBts(0x68), ProcessBts(0x61), ProcessBts(0x71), ProcessBts(0x71), ProcessBts(0x65), ProcessBts(0x34), ProcessBts(0x59), ProcessBts(0x6A), ProcessBts(0x34), ProcessBts(0x57), ProcessBts(0x68), ProcessBts(0x46), ProcessBts(0x6B), ProcessBts(0x68), ProcessBts(0x71), ProcessBts(0x51), ProcessBts(0x2F), ProcessBts(0x4A), ProcessBts(0x6B), ProcessBts(0x34), ProcessBts(0x42), ProcessBts(0x34), ProcessBts(0x5A), ProcessBts(0x69), ProcessBts(0x56), ProcessBts(0x64), ProcessBts(0x73), ProcessBts(0x67), ProcessBts(0x64), ProcessBts(0x73), ProcessBts(0x69), ProcessBts(0x70), ProcessBts(0x6C), ProcessBts(0x55), ProcessBts(0x74), ProcessBts(0x78), ProcessBts(0x6C), ProcessBts(0x47), ProcessBts(0x64), ProcessBts(0x31), ProcessBts(0x66), ProcessBts(0x35), ProcessBts(0x6D), ProcessBts(0x56), ProcessBts(0x2F), ProcessBts(0x6A), ProcessBts(0x6B), ProcessBts(0x33), ProcessBts(0x50), ProcessBts(0x2F), ProcessBts(0x37), ProcessBts(0x68), ProcessBts(0x54), ProcessBts(0x55), ProcessBts(0x72), ProcessBts(0x71), ProcessBts(0x6D), ProcessBts(0x44), ProcessBts(0x35), ProcessBts(0x32), ProcessBts(0x37), ProcessBts(0x67), ProcessBts(0x4F), ProcessBts(0x71), ProcessBts(0x70), ProcessBts(0x65), ProcessBts(0x6B), ProcessBts(0x78), ProcessBts(0x2F), ProcessBts(0x5A), ProcessBts(0x79), ProcessBts(0x4B), ProcessBts(0x4E), ProcessBts(0x35), ProcessBts(0x57), ProcessBts(0x6D), ProcessBts(0x31), ProcessBts(0x31), ProcessBts(0x76), ProcessBts(0x66), ProcessBts(0x6D), ProcessBts(0x30), ProcessBts(0x74), ProcessBts(0x78), ProcessBts(0x6C), ProcessBts(0x66), ProcessBts(0x58), ProcessBts(0x68), ProcessBts(0x48), ProcessBts(0x45), ProcessBts(0x64), ProcessBts(0x6F), ProcessBts(0x6B), ProcessBts(0x70), ProcessBts(0x2F), ProcessBts(0x62), ProcessBts(0x58), ProcessBts(0x70), ProcessBts(0x42), ProcessBts(0x6A), ProcessBts(0x67), ProcessBts(0x75), ProcessBts(0x33), ProcessBts(0x6E), ProcessBts(0x63), ProcessBts(0x4B), ProcessBts(0x75), ProcessBts(0x4C), ProcessBts(0x67), ProcessBts(0x73), ProcessBts(0x63), ProcessBts(0x63), ProcessBts(0x6D), ProcessBts(0x77), ProcessBts(0x46), ProcessBts(0x6B), ProcessBts(0x6F), ProcessBts(0x75), ProcessBts(0x33), ProcessBts(0x52), ProcessBts(0x59), ProcessBts(0x7A), ProcessBts(0x58), ProcessBts(0x5A), ProcessBts(0x54), ProcessBts(0x42), ProcessBts(0x39), ProcessBts(0x47), ProcessBts(0x44), ProcessBts(0x79), ProcessBts(0x42), ProcessBts(0x34), ProcessBts(0x61), ProcessBts(0x2B), ProcessBts(0x69), ProcessBts(0x36), ProcessBts(0x76), ProcessBts(0x35), ProcessBts(0x4F), ProcessBts(0x57), ProcessBts(0x67), ProcessBts(0x62), ProcessBts(0x71), ProcessBts(0x48), ProcessBts(0x76), ProcessBts(0x67), ProcessBts(0x6F), ProcessBts(0x6B), ProcessBts(0x35), ProcessBts(0x39), ProcessBts(0x62), ProcessBts(0x73), ProcessBts(0x57), ProcessBts(0x39), ProcessBts(0x4C), ProcessBts(0x43), ProcessBts(0x34), ProcessBts(0x58), ProcessBts(0x43), ProcessBts(0x39), ProcessBts(0x48), ProcessBts(0x7A), ProcessBts(0x41), ProcessBts(0x50), ProcessBts(0x55), ProcessBts(0x62), ProcessBts(0x6A), ProcessBts(0x34), ProcessBts(0x71), ProcessBts(0x55), ProcessBts(0x45), ProcessBts(0x43), ProcessBts(0x51), ProcessBts(0x51), ProcessBts(0x44), ProcessBts(0x6E), ProcessBts(0x30), ProcessBts(0x6F), ProcessBts(0x44), ProcessBts(0x57), ProcessBts(0x55), ProcessBts(0x4A), ProcessBts(0x36), ProcessBts(0x47), ProcessBts(0x53), ProcessBts(0x4D), ProcessBts(0x53), ProcessBts(0x46), ProcessBts(0x79), ProcessBts(0x36), ProcessBts(0x6D), ProcessBts(0x73), ProcessBts(0x44), ProcessBts(0x72), ProcessBts(0x61), ProcessBts(0x51), ProcessBts(0x79), ProcessBts(0x5A), ProcessBts(0x31), ProcessBts(0x71), ProcessBts(0x52), ProcessBts(0x41), ProcessBts(0x49), ProcessBts(0x4F), ProcessBts(0x4E), ProcessBts(0x5A), ProcessBts(0x38), ProcessBts(0x73), ProcessBts(0x73), ProcessBts(0x6F), ProcessBts(0x44), ProcessBts(0x6F), ProcessBts(0x68), ProcessBts(0x38), ProcessBts(0x74), ProcessBts(0x4E), ProcessBts(0x58), ProcessBts(0x4A), ProcessBts(0x4C), ProcessBts(0x76), ProcessBts(0x38), ProcessBts(0x32), ProcessBts(0x70), ProcessBts(0x62), ProcessBts(0x54), ProcessBts(0x30), ProcessBts(0x42), ProcessBts(0x53), ProcessBts(0x2B), ProcessBts(0x37), ProcessBts(0x4E), ProcessBts(0x77), ProcessBts(0x63), ProcessBts(0x2B), ProcessBts(0x65), ProcessBts(0x64), ProcessBts(0x74), ProcessBts(0x58), ProcessBts(0x70), ProcessBts(0x57), ProcessBts(0x55), ProcessBts(0x62), ProcessBts(0x48), ProcessBts(0x34), ProcessBts(0x73), ProcessBts(0x6A), ProcessBts(0x50), ProcessBts(0x6F), ProcessBts(0x2F), ProcessBts(0x64), ProcessBts(0x44), ProcessBts(0x77), ProcessBts(0x32), ProcessBts(0x31), ProcessBts(0x41), ProcessBts(0x66), ProcessBts(0x58), ProcessBts(0x32), ProcessBts(0x4A), ProcessBts(0x5A), ProcessBts(0x41), ProcessBts(0x6B), ProcessBts(0x45), ProcessBts(0x41), ProcessBts(0x78), ProcessBts(0x4A), ProcessBts(0x66), ProcessBts(0x41), ProcessBts(0x74), ProcessBts(0x51), ProcessBts(0x41), ProcessBts(0x47), ProcessBts(0x69), ProcessBts(0x6E), ProcessBts(0x47), ProcessBts(0x41), ProcessBts(0x32), ProcessBts(0x78), ProcessBts(0x36), ProcessBts(0x56), ProcessBts(0x68), ProcessBts(0x77), ProcessBts(0x6A), ProcessBts(0x38), ProcessBts(0x53), ProcessBts(0x42), ProcessBts(0x46), ProcessBts(0x53), ProcessBts(0x77), ProcessBts(0x65), ProcessBts(0x4A), ProcessBts(0x74), ProcessBts(0x78), ProcessBts(0x2B), ProcessBts(0x2F), ProcessBts(0x79), ProcessBts(0x75), ProcessBts(0x73), ProcessBts(0x39), ProcessBts(0x6F), ProcessBts(0x49), ProcessBts(0x44), ProcessBts(0x4E), ProcessBts(0x32), ProcessBts(0x58), ProcessBts(0x52), ProcessBts(0x33), ProcessBts(0x4B), ProcessBts(0x35), ProcessBts(0x6E), ProcessBts(0x51), ProcessBts(0x44), ProcessBts(0x6D), ProcessBts(0x36), ProcessBts(0x71), ProcessBts(0x33), ProcessBts(0x55), ProcessBts(0x38), ProcessBts(0x30), ProcessBts(0x46), ProcessBts(0x34), ProcessBts(0x50), ProcessBts(0x32), ProcessBts(0x36), ProcessBts(0x6D), ProcessBts(0x53), ProcessBts(0x4E), ProcessBts(0x4A), ProcessBts(0x32), ProcessBts(0x53), ProcessBts(0x61), ProcessBts(0x70), ProcessBts(0x66), ProcessBts(0x65), ProcessBts(0x67), ProcessBts(0x58), ProcessBts(0x4C), ProcessBts(0x73), ProcessBts(0x75), ProcessBts(0x45), ProcessBts(0x6E), ProcessBts(0x6F), ProcessBts(0x55), ProcessBts(0x50), ProcessBts(0x7A), ProcessBts(0x59), ProcessBts(0x61), ProcessBts(0x78), ProcessBts(0x53), ProcessBts(0x51), ProcessBts(0x4A), ProcessBts(0x42), ProcessBts(0x41), ProcessBts(0x4B), ProcessBts(0x44), ProcessBts(0x6A), ProcessBts(0x71), ProcessBts(0x35), ProcessBts(0x38), ProcessBts(0x53), ProcessBts(0x48), ProcessBts(0x4C), ProcessBts(0x4D), ProcessBts(0x39), ProcessBts(0x31), ProcessBts(0x59), ProcessBts(0x61), ProcessBts(0x32), ProcessBts(0x4C), ProcessBts(0x6D), ProcessBts(0x2F), ProcessBts(0x48), ProcessBts(0x56), ProcessBts(0x6C), ProcessBts(0x56), ProcessBts(0x75), ProcessBts(0x56), ProcessBts(0x39), ProcessBts(0x33), ProcessBts(0x6B), ProcessBts(0x6A), ProcessBts(0x54), ProcessBts(0x69), ProcessBts(0x6E), ProcessBts(0x5A), ProcessBts(0x6D), ProcessBts(0x31), ProcessBts(0x7A), ProcessBts(0x42), ProcessBts(0x5A), ProcessBts(0x78), ProcessBts(0x63), ProcessBts(0x67), ProcessBts(0x6E), ProcessBts(0x43), ProcessBts(0x53), ProcessBts(0x69), ProcessBts(0x7A), ProcessBts(0x67), ProcessBts(0x56), ProcessBts(0x53), ProcessBts(0x2F), ProcessBts(0x39), ProcessBts(0x4C), ProcessBts(0x4A), ProcessBts(0x57), ProcessBts(0x31), ProcessBts(0x79), ProcessBts(0x57), ProcessBts(0x72), ProcessBts(0x72), ProcessBts(0x30), ProcessBts(0x39), ProcessBts(0x67), ProcessBts(0x36), ProcessBts(0x79), ProcessBts(0x59), ProcessBts(0x4E), ProcessBts(0x46), ProcessBts(0x2F), ProcessBts(0x71), ProcessBts(0x58), ProcessBts(0x44), ProcessBts(0x63), ProcessBts(0x33), ProcessBts(0x4D), ProcessBts(0x49), ProcessBts(0x62), ProcessBts(0x52), ProcessBts(0x65), ProcessBts(0x4F), ProcessBts(0x6A), ProcessBts(0x6B), ProcessBts(0x68), ProcessBts(0x76), ProcessBts(0x7A), ProcessBts(0x36), ProcessBts(0x79), ProcessBts(0x45), ProcessBts(0x43), ProcessBts(0x51), ProcessBts(0x47), ProcessBts(0x41), ProcessBts(0x39), ProcessBts(0x64), ProcessBts(0x67), ProcessBts(0x35), ProcessBts(0x6C), ProcessBts(0x6F), ProcessBts(0x38), ProcessBts(0x34), ProcessBts(0x55), ProcessBts(0x67), ProcessBts(0x4B), ProcessBts(0x4E), ProcessBts(0x45), ProcessBts(0x56), ProcessBts(0x71), ProcessBts(0x6B), ProcessBts(0x54), ProcessBts(0x67), ProcessBts(0x67), ProcessBts(0x56), ProcessBts(0x35), ProcessBts(0x7A), ProcessBts(0x59), ProcessBts(0x79), ProcessBts(0x79), ProcessBts(0x33), ProcessBts(0x31), ProcessBts(0x46), ProcessBts(0x59), ProcessBts(0x71), ProcessBts(0x76), ProcessBts(0x67), ProcessBts(0x2B), ProcessBts(0x33), ProcessBts(0x74), ProcessBts(0x65), ProcessBts(0x63), ProcessBts(0x75), ProcessBts(0x64), ProcessBts(0x34), ProcessBts(0x64), ProcessBts(0x33), ProcessBts(0x70), ProcessBts(0x31), ProcessBts(0x77), ProcessBts(0x76), ProcessBts(0x2B), ProcessBts(0x39), ProcessBts(0x74), ProcessBts(0x35), ProcessBts(0x47), ProcessBts(0x39), ProcessBts(0x32), ProcessBts(0x31), ProcessBts(0x2B), ProcessBts(0x44), ProcessBts(0x72), ProcessBts(0x39), ProcessBts(0x58), ProcessBts(0x52), ProcessBts(0x51), ProcessBts(0x62), ProcessBts(0x53), ProcessBts(0x2B), ProcessBts(0x4D), ProcessBts(0x47), ProcessBts(0x4C), ProcessBts(0x39), ProcessBts(0x56), ProcessBts(0x5A), ProcessBts(0x6A), ProcessBts(0x76), ProcessBts(0x33), ProcessBts(0x54), ProcessBts(0x38), ProcessBts(0x59), ProcessBts(0x57), ProcessBts(0x6C), ProcessBts(0x38), ProcessBts(0x54), ProcessBts(0x69), ProcessBts(0x6F), ProcessBts(0x6C), ProcessBts(0x6B), ProcessBts(0x43), ProcessBts(0x51), ProcessBts(0x41), ProcessBts(0x54), ProcessBts(0x78), ProcessBts(0x6D), ProcessBts(0x58), ProcessBts(0x57), ProcessBts(0x32), ProcessBts(0x49), ProcessBts(0x4F), ProcessBts(0x61), ProcessBts(0x68), ProcessBts(0x32), ProcessBts(0x4C), ProcessBts(0x53), ProcessBts(0x6A), ProcessBts(0x77), ProcessBts(0x37), ProcessBts(0x44), ProcessBts(0x69), ProcessBts(0x74), ProcessBts(0x63), ProcessBts(0x2F), ProcessBts(0x79), ProcessBts(0x64), ProcessBts(0x6C), ProcessBts(0x76), ProcessBts(0x78), ProcessBts(0x62), ProcessBts(0x4A), ProcessBts(0x49), ProcessBts(0x4C), ProcessBts(0x34), ProcessBts(0x2B), ProcessBts(0x4A), ProcessBts(0x46), ProcessBts(0x51), ProcessBts(0x56), ProcessBts(0x42), ProcessBts(0x75), ProcessBts(0x2F), ProcessBts(0x4E), ProcessBts(0x35), ProcessBts(0x6C), ProcessBts(0x77), ProcessBts(0x41), ProcessBts(0x70), ProcessBts(0x49), ProcessBts(0x43), ProcessBts(0x4C), ProcessBts(0x2B), ProcessBts(0x54), ProcessBts(0x72), ProcessBts(0x53), ProcessBts(0x74), ProcessBts(0x4E), ProcessBts(0x49), ProcessBts(0x53), ProcessBts(0x4D), ProcessBts(0x45), ProcessBts(0x32), ProcessBts(0x39), ProcessBts(0x31), ProcessBts(0x2F), ProcessBts(0x36), ProcessBts(0x74), ProcessBts(0x59), ProcessBts(0x4E), ProcessBts(0x67), ProcessBts(0x41), ProcessBts(0x50), ProcessBts(0x72), ProcessBts(0x4C), ProcessBts(0x52), ProcessBts(0x50), ProcessBts(0x62), ProcessBts(0x32), ProcessBts(0x70), ProcessBts(0x2F), ProcessBts(0x53), ProcessBts(0x42), ProcessBts(0x44), ProcessBts(0x42), ProcessBts(0x6C), ProcessBts(0x4B), ProcessBts(0x69), ProcessBts(0x73), ProcessBts(0x3D), ProcessBts(0x2D), ProcessBts(0x2D), ProcessBts(0x2D), ProcessBts(0x2D), ProcessBts(0x2D), ProcessBts(0x45), ProcessBts(0x4E), ProcessBts(0x44), ProcessBts(0x20), ProcessBts(0x50), ProcessBts(0x52), ProcessBts(0x49), ProcessBts(0x56), ProcessBts(0x41), ProcessBts(0x54), ProcessBts(0x45), ProcessBts(0x20), ProcessBts(0x4B), ProcessBts(0x45), ProcessBts(0x59), ProcessBts(0x2D), ProcessBts(0x2D), ProcessBts(0x2D), ProcessBts(0x2D), ProcessBts(0x2D), 0x00};

time_t convertDate(const char* date)
{
    if(strcmp("None", date) == 1)
    {
        struct tm t = {0};
        t.tm_year = 9999;
        t.tm_mon = 12;
        t.tm_mday = 1;
        time_t check_time = mktime(&t);
        return check_time;
    }
    
    char* clone_date = malloc(strlen(date));
    strcpy(clone_date, date);
    
    struct tm t = {0};
    char* time_str = strtok(clone_date, "-");
    t.tm_hour = 0;
    t.tm_min = 0;
    t.tm_sec = 0;
    int index = 0;
    while (time_str != NULL) {
        int time = atoi(time_str);
        switch (index) {
            case 0:
                t.tm_year = time - 1900;
                break;
            case 1:
                t.tm_mon = time - 1;
                break;
            case 2:
                t.tm_mday = time;
                break;
            default:
                //格式不对
                return mktime(&t);
        }
        time_str = strtok(NULL, "-");
        index++;
    }
    free(clone_date);
    clone_date = NULL;
    
    return mktime(&t);
}

int vaildateTime(time_t ct)
{
    return time(NULL) < ct ? 0 : 1000;
}

int vaildateDate(const char* date)
{
    time_t check_time = convertDate(date);
    return vaildateTime(check_time);
}

int vaildateInfo(void)
{
    if(vaildateTime(authInfo.end_time) != 0)
    {
        return 1000;
    }
    else if(!authInfo.vaildBid)
    {
        return 1001;
    }
    else if(authInfo.modelDisable)
    {
        return 1004;
    }
    
    return 0;
}

void bytes2str(const char* bytes, char* str)
{
    const char* b = bytes;
    char* s = str;
    while(*b != 0x00)
    {
        *s = 0xFF - *b;
        b++;
        s++;
    }
}

void modelKey(char* str)
{
    bytes2str(modelAESBytes, str);
//    return "rjvlwzjbcvlixtjm";
}

void modelV2Key(char* str)
{
    bytes2str(modelV2AESBytes, str);
//    return "vlDa0jclFd9jtsfc";
}

void licenseKey(char* str)
{
    bytes2str(licenseRsaBytes, str);
//    return "-----BEGIN PRIVATE KEY-----MIICdwIBADANBgkqhkiG9w0BAQEFAASCAmEwggJdAgEAAoGBALIGlk/cnqycF0HWp/bFlZIlWnJpLPcAFHdp1C8D6r9/7CVu44hvwbdnwMunEwnZ+RwTv4uKEY3N3u187Cs9A7PSAOqY6eKLsF9xIF7JQ9b30k8TIMhHefYoulDp9L/TGaNp2JdjT894E4xOYyMgbx0YcI1ceA0rrwz9vW+kyJRhAgMBAAECgYEAhaqqe4Yj4WhFkhqQ/Jk4B4ZiVdsgdsiplUtxlGd1f5mV/jk3P/7hTUrqmD527gOqpekx/ZyKN5Wm11vfm0txlfXhHEdokp/bXpBjgu3ncKuLgsccmwFkou3RYzXZTB9GDyB4a+i6v5OWgbqHvgok59bsW9LC4XC9HzAPUbj4qUECQQDn0oDWUJ6GSMSFy6msDraQyZ1qRAIONZ8ssoDoh8tNXJLv82pbT0BS+7Nwc+edtXpWUbH4sjPo/dDw21AfX2JZAkEAxJfAtQAGinGA2x6Vhwj8SBFSweJtx+/yus9oIDN2XR3K5nQDm6q3U80F4P26mSNJ2SapfegXLsuEnoUPzYaxSQJBAKDjq58SHLM91Ya2Lm/HVlVuV93kjTinZm1zBZxcgnCSizgVS/9LJW1yWrr09g6yYNF/qXDc3MIbReOjkhvz6yECQGA9dg5lo84UgKNEVqkTggV5zYyy31FYqvg+3tecud4d3p1wv+9t5G921+Dr9XRQbS+MGL9VZjv3T8YWl8TiolkCQATxmXW2IOah2LSjw7Ditc/ydlvxbJIL4+JFQVBu/N5lwApICL+TrStNISME291/6tYNgAPrLRPb2p/SBDBlKis=-----END PRIVATE KEY-----";
}
 
