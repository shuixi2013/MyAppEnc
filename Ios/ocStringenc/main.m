#import <Foundation/Foundation.h>


#define SOBF

static char* decryptConstString(char* string) __attribute__((always_inline));

#define NSSTRING(string) [NSString stringWithUTF8String:decryptConstString(string)]
#define CSTRING(string) decryptConstString(string)

static char* decryptConstString(char* string)
{
    char* origin_string = string;
    while(*string) {
        *string ^= 0xAA;
        string++;
    }
    return origin_string;
}

#ifndef SOBF
#define NSSTRING(string) @string 
#define CSTRING(string) string 
#endif


int main()
{
    char *a= CSTRING(((char []) {155, 152, 158, 159, 153, 158, 156, 159, 157, 0})) ; 
    NSLog(@"%@", NSSTRING(((char []) {194, 207, 198, 198, 197, 221, 197, 216, 198, 206, 0}))) ;
    printf("%s\n" ,CSTRING(((char []) {194, 207, 198, 198, 197, 138, 221, 197, 216, 198, 206, 0})) );
    return 0 ;
}