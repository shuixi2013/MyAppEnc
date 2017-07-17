import os
import sys
from optparse import OptionParser 
import decodestring

def dealwithstring(match):
    print(match.groups())
    if match.group(0) == None :
        return "\"\"" 
    encdata =encString(match.group(0))
    return encdata


def dealwithfile(path):
    print(path)
    f=open(path,'r')
    data=f.read() 
    f.close()
    pattern=r'const-string.*\".*\"'
    prog = re.compile(pattern)
    data = prog.sub(dealwithstring , data)
    #print(data)



def travel2(path):
    for dirpath,dirs,files in os.walk(path):
        if "android\support" in dirpath :
            continue
        for x in fixpackage:
            if x in dirpath : 
                for smalifile in files:
                    if smalifile == "MainActivity.smali":
                        dealwithfile(dirpath+os.sep+smalifile)

def main():
    parser = OptionParser()  

    parser.add_option("-o", "--output",  dest="output", help="output path") 
    parser.add_option("-s", "--src",  dest="dirpath", help="dir path") 
    (options, args) = parser.parse_args()
    path = os.path.realpath(options.dirpath)
    travel2(path)

if __name__ == '__main__':
    main()