import os
import sys 
import random 
import string
import re
# return a  random number 
def mRandNum(min ,max):
    return random.randint(min , max) 

# return a char 
def mRandC():
    return random.choice(string.ascii_letters) 

#generate random function name 
def generateFuncName():
    name=''
    for i in range(8 , mRandNum(16,32)):
        name += mRandC()
    return name 

def dealwithstring(match):
    name = generateFuncName()
    outfd.write(match.group(1)+" => " +name +"\n")
    return "RE(\""+name+"\")"

def dealwithline(path):
        newdata=''
        pattern=r'RE\((_.*)\)'
        prog = re.compile(pattern)
        f=open(path,'r',encoding='utf-8')
        for i in f.readlines():
            data = prog.sub(dealwithstring , i)
            newdata+=data
        f.close()
        print(newdata)
        f = open(path , 'w',encoding='utf-8')
        f.write(newdata)
        f.close()

def travel(path):
    for dirpath,dirs,files in os.walk(path):
        for filex in files :
            if filex.endswith(".c") or filex.endswith(".cpp") or filex.endswith(".m"):
                dealwithline(dirpath+os.sep+filex)  


def main():
    if len(sys.argv) != 3 :
        print("python3 obf.py  path output")
        return 
    path = sys.argv[1] 
    global outfd
    output = sys.argv[2]
    outfd = open(output, "w",encoding='utf-8')
    travel(path)
    outfd.close()

if __name__ == '__main__':
    main()