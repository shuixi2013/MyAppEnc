import os
from optparse import OptionParser 
import struct 
import sys 




def getfiledata(path,flag='rb'):
    fd = open(path , flag)
    return fd.read() 

def deal(shellpath , mainpath ,outpath):
    shelldata = getfiledata(shellpath)
    print("[+]shell data size is "+str(len(shelldata)))
    maindata = getfiledata(mainpath)
    print("[+]main data size is "+str(len(maindata)))
    fdOutput = open(outpath,'wb')
    fdOutput.write(shelldata)
    fdOutput.close()


def main():
    parser = OptionParser()
    parser.add_option('-m' ,'--main' , dest='main', help= "main.so")
    parser.add_option('-s' ,'--shell' , dest="src" , help='shell.so')
    parser.add_option('-o' , '--output',dest="output", help='so file output path')

    (options ,args) = parser.parse_args()
    if options.src == None or options.main  ==None :
        print("%s -s shell.so  -m main.so  -o output.so",__file__)
        exit(-1)
    shellpath=options.src 
    mainpath=options.main
    outpath='./out.so'
    if options.output != None :
        outpath=outpath.output
    deal(shellpath,mainpath,outpath)

if __name__ == '__main__':
    main()