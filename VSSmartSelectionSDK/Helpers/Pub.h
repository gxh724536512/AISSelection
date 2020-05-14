/*
 @author: ideawu
 @link: https://github.com/ideawu/Objective-C-RSA
*/

#import <Foundation/Foundation.h>
#import "CommonMarco.h"

#if __ObfuscatedCode__
#define RSA VSad7b42aff5bab616
#define publicKey m059e0d71a67557e5
#define privateKey md998a500b0984584
#define key m9c15224a8228b9a9
#define encryptString mdd0f03670f6e323a
#define encryptData mf092f5aec1b86dca
#define decryptString m9320d3c7d246fe88
#define decryptData md406f240c7ea7b23
#define aesDecryptString m35ec5b76c3e9890f
#define withKeyRef m82cac6642b4a89f2
#define isSign mec873d4a4216e63b
#define addPrivateKey m827c9a5e935a074c
#define addPublicKey m826da0ebbef4aa08
#define stripPrivateKeyHeader m8e0d20a6d6d9871a
#define stripPublicKeyHeader m64ee5db85f5f9b5b
#endif

@interface RSA : NSObject

// return base64 encoded string
+ (NSString *)encryptString:(NSString *)str publicKey:(NSString *)pubKey;
// return raw data
+ (NSData *)encryptData:(NSData *)data publicKey:(NSString *)pubKey;
// return base64 encoded string
+ (NSString *)encryptString:(NSString *)str privateKey:(NSString *)privKey;
// return raw data
+ (NSData *)encryptData:(NSData *)data privateKey:(NSString *)privKey;

// decrypt base64 encoded string, convert result to string(not base64 encoded)
+ (NSString *)decryptString:(NSString *)str publicKey:(NSString *)pubKey;
+ (NSData *)decryptData:(NSData *)data publicKey:(NSString *)pubKey;
+ (NSString *)decryptString:(NSString *)str privateKey:(NSString *)privKey;
+ (NSData *)decryptData:(NSData *)data privateKey:(NSString *)privKey;

+ (NSString *)aesDecryptString:(NSString *)str key:(NSString *)priKey;
@end
