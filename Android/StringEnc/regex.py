import os
import sys
import re 
import decodestring
import codecs
import random
from optparse import OptionParser  

xpath="C:\\Users\\qwedd\\Desktop\\AndroidKiller_v1.3.1\\projects\\app-debug\\Project\\smali"

table={"\"":'"' ,"\n":"" ,"\'":'' , '\a':'','\b':'','\t':'','\\':"23",'\r':'222'}


dirfilters=['android']
filefilters=['BuildConfig.smali','R$anim.smali','R$attr.smali','R$bool.smali','R.smali','R$styleable.smali',
'R$style.smali' ,'R$string.smali' ,'R$mipmap','R$layout.smali','R$integer.smali',]
fixpackage=[]
#########################################################
####
#### COMMON
####
#########################################################
def signapk(path):
    pass

def generateapk(path):
    pass

def generatedex(path):
    pass

def copysmali(path):
    pass


def dealBase64(plaindata):
    data=plaindata.encode().decode('unicode-escape')
    encdata=decodestring.base64encode(data)
    return encdata

def dealBase642(plaindata):
    encdata=decodestring.base64encode(plaindata)
    return encdata

def xorString2hex(plaindata):
    encdata=decodestring.xor_string2hex(plaindata)
    return encdata

def encString(data):
        preString=data[ data.find("\'")+1 :]
        value =  random.randint(0,10)
        if value > 5:
            encstr= dealBase642(preString)
            return "cn.tongdun.android.shell.utils.DecoderUtil.b642String("+encstr+")" 
        else:
            encstr ,bvalue = xorString2hex(preString)
            return "cn.tongdun.android.shell.utils.DecoderUtil.hex2String(\""+ encstr+"\", "+ bvalue +")"
            
#############################################
####
####  native 
####
##############################################

def nativeEnc2(string):
    return decodestring.nativenoleak(string)

def dealwithnativeString(string): 
    value = random.randint(0,10)
    if value > 5:
        encString = dealBase642(string)
        return "decB64("+encString+")"
    else:
        (encstr ,value) = xorString2hex(string)
        return  "decHex(\"" + encstr + "\", " + value +")"

def nativematchstring(match):
    if match.group(1) == "DECRYPTM":
        encstr = "{"+ nativeEnc2(match.group(2)) + "}"   
        return encstr 
    encstr = dealwithnativeString(match.group(2))
    if match.group(1) == 'DECRYPTL':
        return "\"%s\" ,"+encstr 
    return encstr

def nativedealwithline(path):
    newdata=''
    pattern=r'(DECRYPT[L|M]?).*\("(.*)\"\)'
    prog = re.compile(pattern)
    f=open(path,'r',encoding='utf-8')
    for i in f.readlines():
        data = prog.sub(nativematchstring , i)
        newdata+=data
    f.close()
    #print(newdata)
    f =open(path , 'w',encoding='utf-8')
    f.write(newdata)
    f.close()

def travelnative(path):
    for dirpath,dirs,files in os.walk(path):
        for filex in files :
            if filex.endswith(".c") or filex.endswith(".cpp"):
                nativedealwithline(dirpath+os.sep+filex)   

##############################################
#####
##### src 
#####
##############################################

def srcdealwithstring(match):
    if match.group(1) == None :
        return "\"\"" 
    encstr=encString(match.group(1))
    return encstr


def srcdealline(path):
        newdata=''
        pattern=r'\"([^"]+)?\"'
        prog = re.compile(pattern)
        f=open(path,'r',encoding='utf-8')
        for i in f.readlines():
            if "@SuppressWarn" in i  or " ERROR_" in i  or "@ToJson" in i :
                newdata += i 
                continue
            data = prog.sub(srcdealwithstring , i)
            newdata+=data
        f.close()
        f =open(path , 'w',encoding='utf-8')
        f.write(newdata)
        f.close()

def travelsrc(path):
    ifdeal = True
    cantdeal=['DecoderUtil.java','EncoderUtil.java' ,'Collector.java']
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

##############################################
#####
##### nosrc 
#####
##############################################

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
    pattern=r'const-string ([vp]\\d{1,2}), \"(.*)\"'
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

    parser.add_option("-t", "--type",  dest="exetype", help="native src nosrc all") 
    parser.add_option("-s", "--src",  dest="dirpath", help="dir path") 
    (options, args) = parser.parse_args()
    path = os.path.realpath(options.dirpath)
    if options.exetype == "native":
        travelnative(path)
    elif options.exetype == "src":
        travelsrc(path)
    elif options.exetype == "nosrc":
        travel2(path)
    elif options.exetype ==  "all":
        travelsrc(path)
        travelnative(path)


if __name__ == '__main__':
    main()