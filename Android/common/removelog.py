import os
import sys
import re 
import script_encstring as decodestring
import random
from optparse import OptionParser  

def srcdealwithstring(match):
    print(match.groups())
    return ""

def srcdealline(path):
        newdata=''
        pattern=r'\"([^"]+)?\"'
        prog = re.compile(pattern)
        f=open(path,'r',encoding='utf-8')
        for i in f.readlines():
            data = prog.sub(srcdealwithstring , i)
            newdata+=data
        f.close()
        f=open(path , 'w',encoding='utf-8')
        f.write(newdata)
        f.close()

def travelsrc(path):
    ifdeal = True
    cantdeal=[]
    for dirpath,dirs,files in os.walk(path):
        for filex in files :
            if not filex.endswith(".java"):
                continue
            for cannot in cantdeal : 
                if  cannot in filex :
                    ifdeal = False
            if ifdeal:
                srcdealline(dirpath+os.sep+filex)
            ifdeal=True

def main():
    parser = OptionParser()  
    parser.add_option("-s", "--src",  dest="dirpath", default="./sdk-shell" ,help="dir path") 
    (options, args) = parser.parse_args()
    mypath = os.path.realpath(options.dirpath)
    travelsrc(mypath)


if __name__ == '__main__':
    main()