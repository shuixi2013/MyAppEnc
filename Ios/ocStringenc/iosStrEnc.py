import os
import sys 
import random 
import string
import re


insert_code = '''#define SOBF

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

#ifndef SOBF'''


def dealwithstring(match):
    # print match.group()
    string = match.group(2) + '\x00'

    replaced_string = '((char []) {' + ', '.join(["%i" % ((ord(c) ^ 0xAA) if c != '\0' else 0) for c in list(string)]) + '})'
    # print replaced_string
    return match.group(1) + replaced_string + match.group(3)

def dealwithline(path):
        newdata=''
        pattern=r'(NSSTRING\(|CSTRING\()"(.*?)"(\))'
        prog = re.compile(pattern)
        f=open(path,'r',encoding='utf-8')
        for i in f.readlines():
            data = prog.sub(dealwithstring , i)
            newdata+=data
        f.close()
        
        newdata =newdata.replace('#ifndef SOBF', insert_code)
        print(newdata)
        f = open(path , 'w',encoding='utf-8')
        f.write(newdata)
        f.close()

def travel(path):
    for dirpath,dirs,files in os.walk(path):
        for filex in files :
            if filex.endswith(".m"):
                dealwithline(dirpath+os.sep+filex)  


def main():
    if len(sys.argv) != 2 :
        print("python3 iosStrEnc.py  path")
        return 
    path = sys.argv[1] 
    travel(path)

if __name__ == '__main__':
    main()