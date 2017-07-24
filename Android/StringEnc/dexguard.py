import os
import sys
from optparse import OptionParser 
import decodestring


# len , pos ,current 
def encStrings(strings):
    encdata= [] 
    info_encode=[]
    for string in strings : 
        string = string.encode().decode('unicode-escape')
        strlen = len(string)-1
        data0 = ord(string[0])
        data0 =  data0 if data0 < 127 else ord(string[0])-256 
        for xchar in string[1:]:
            tmp = ord(xchar) 
            if tmp > 127: 
                tmp -= 256 
            encdata.append(tmp)
        current = len(encdata)-strlen 
        data=(strlen , data0 ,current)
        info_encode.append(data)
    print(info_encode)
    print(encdata)



def travel2(path):
    for dirpath,dirs,files in os.walk(path):
        pass
    pass

def main():
    parser = OptionParser()  

    parser.add_option("-o", "--output",  dest="output", help="output path") 
    parser.add_option("-s", "--src",  dest="dirpath", help="dir path") 
    (options, args) = parser.parse_args()
    path = os.path.realpath(options.dirpath)
    #travel2(path)
    

if __name__ == '__main__':
    #main()
    strings = ['123456789','\u4e2d\u56fd','asdwqnidoenwioger']
    encStrings(strings)