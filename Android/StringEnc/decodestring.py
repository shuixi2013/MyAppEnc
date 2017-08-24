import base64
import sys
import binascii
import random 
import string 


allstring="'0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~"

def string2byte(data):
    dd=[]
    tmp=data.encode('utf-8')
    for i in tmp:  #i is int 
        if  i >127:
            dd.append(i-256)
        else:
            dd.append(i)
    fix=str(dd).replace('[','{').replace(']','}')
    return 'new byte[]'+fix

def string2hex(data):
    return binascii.b2a_hex(data.encode('utf-8'))


def xor_string2byte(data):
    key=random.randint(0,127)
    dd=[]
    tmp=data.encode('utf-8')
    for i in tmp:  #i is int 
        if  i >127:
            dd.append(i-256)
        else:
            dd.append(i)
    
    result=[key ^ x for x in dd]
    fix=str(result).replace('[','{').replace(']','}')
    return ('new byte[]'+fix,key)
    



def xor_string2hex(data):
    key= random.randint(0,127)
    tmp=data.encode('utf-8')
    dd=[]
    for i in tmp:  #i is int 
            dd.append(i)
    result = [key ^ x for x in dd]
    return ( binascii.b2a_hex(bytes(result)).decode('utf-8'),str(key))

########################################################
def string2string(data):
    key=random.randint(0,127)
    tmp = data.encode('utf-8')
    dd=[]
    for i in tmp:  #i is int 
        if  i >127:
            dd.append(i-256)
        else:
            dd.append(i)
    result = [chr(key ^ x) for x in dd]
    print("[+]result:"+str(result))
    return (''.join(result), key)

#############################################################
def base64encode(data):
    key="NPC233"
    datalen=len(data)
    keylen=len(key)
    dd=[] 
    for index,v in enumerate(data.encode('utf-8')):
        dd.append( v ^ ord(key[index%keylen])) 
    
    result =bytes(dd)
    return str(base64.b64encode(result)).replace("'","\"")[1:]
        

############################################################
# 乱码字符 如何测试 
###############################################################
def myXorString(data):
    key="NPC110"
    datalen=len(data)
    keylen=len(key)
    dd=[] 
    for index,v in enumerate(data.encode('utf-8')):
        dd.append( v ^ ord(key[index%keylen])) 
    
    print(dd)
    result=''
    for x in dd:
        result+= chr(x)
    print(result)
    return result

#################################################################
#乱码无法测试
#################################################################

def xorWithRandKey(data):
    key=getrandomstring(random.randint(1,7))
    datalen=len(data)
    keylen=len(key)
    dd=[] 
    for index,v in enumerate(data.encode('utf-8')):
        dd.append( v ^ ord(key[index%keylen])) 
    result=''
    for x in dd:
        result+= chr(x)
    return (result,key)

######################################
### native no memory leak
########################################
########
# this function is useless in asm 23333
####
def dealnum(num):
    opr=['^' , '+' , '-',' ' ]
    choose = random.choice(opr)
    if choose == '^':
        num2 = random.randint(0,127)
        xorvalue = num2 ^ num ; 
        return str(xorvalue)+'^'+ str(num2) 
    elif choose == '+':
        num2 = random.randint(0,num)
        smallvalue = num -num2   ; 
        return str(smallvalue)+'+'+ str(num2) 
    elif choose == '-':
        num2 = random.randint(0,127)
        bigvalue = num2 + num ; 
        return str(bigvalue)+'-'+ str(num2)  
    else:
        return str(num)


def nativenoleak(string):
    data='' 
    for i in string.encode('utf-8') :
        data+=str(i)+','
    data+="\'\\0\'"
    return data
def hahah():
    a ="cG5jYUdSPCRjVlZQPCkzRg=="
    b = base64.decodestring(a)
    c = []
    for i ,Char in enumerate(b) :
        c.append(chr(ord('NPC233'[i%6]) ^ ord(Char) ))

    print(''.join(c))

#####################################
##
##  dexguard
## 
########################################

def encMultiStr(strings):
    print(strings)
    encdata= [] 
    info_encode=[]
    for string in strings : 
        string = string.encode().decode("unicode-escape")
        string = string.encode() # get bytes of string 
        strlen = len(string)-1
        data0 = string[0]#ord(string[0])
        data0 =  data0 if data0 < 127 else string[0]-256
        last = data0  
        for xchar in string[1:]:
            tmp = xchar #ord(xchar)
            src = xchar 
            tmp = src + 10 - last
            last = src
            tmp = tmp if tmp < 127 else tmp -256
            assert(tmp <127)
            encdata.append(tmp)
        current = len(encdata)-strlen 
        data=(strlen + 1 -119 , 378-data0 ,current+110)
        info_encode.append(data)

    return (info_encode,encdata)

#### random it 
def encMultiStr2(strings):

    randlen = random.randint(100,200)
    randfirst = random.randint(260,400)
    randpos = random.randint(100,200)
    randdec = random.randint(1,12)

    randdata=(randlen,randfirst,randpos,randdec)
    encdata= [] 
    info_encode=[]
    for string in strings : 
        string = string.encode().decode("unicode-escape")
        string = string.encode()
        strlen = len(string)-1
        data0 = string[0]
        data0 =  data0 if data0 < 127 else string[0]-256
        last = data0  
        for xchar in string[1:]:
            tmp = xchar 
            src = xchar 
            tmp = src + randdec - last
            last = src
            tmp = tmp if tmp < 127 else tmp -256
            assert(tmp <127)
            encdata.append(tmp)
        current = len(encdata)-strlen 
        data=(strlen + 1 -randlen , randfirst-data0 ,current+randpos)
        info_encode.append(data)

    return (randdata , info_encode,str(encdata).replace('[','{').replace(']','}'))

###################################################
##################################################

################################
## key1 xor key 
## key2 is used to generate second key  
## key3 .....
###############################

def generatorRandomKey():
    key1 = random.randint(0,127)
    key2 = random.randint(0,127)
    key3 = random.randint(0,127)
    return (key1,key2,key3)


############################
## string->byte  
## byte xor random key
## random key1,key2,key3 
###########################
def encjavamode2(string,key1,key2,key3):
        #print(string)
        string=repairestring(string)
        #print(string)
        stringx = string.encode().decode("utf-8")
        stringx = stringx.encode()
        keyxor = key1 ^ key2
        result =''
        data1 = stringx[0] 
        for index,bb in enumerate(stringx):
            #print(bb)
            if index == 0 : 
                data0 = stringx[0] ^ key3 
                #data0 = data0 if data0 < 127 else data0-256
                result+="%0.2x"%(data0)
            else:
                data1 = keyxor ^ data1 ^ bb
                #data1 = data1 if data1 < 127 else data1-256            
                result+="%0.2x"%(data1)
        #print(result)
        return result

    
#b'\xc3\xa4\xc2\xb8\xc2\xad\xc3\xa5\xc2\x9b\xc2\xbd\xc3\xa8\xc2\xbf\xc2\x87'


###########################################################
##########################################################
def repairestring(string):
    if "\\\\" in  string :
        return string.replace("\\\\","\\")
    elif "\\n" in string :
        return string.replace("\\n","\n")
    else:
        return string

def is_chinese(data):
    for uchar in data:         
        if '\u4e00' <= uchar<='\u9fff':
            return True
        else:
            return False

def getrandomstring(num):
    return ''.join(random.choice(allstring) for x in range(num))

def main():
    test2="中国过"
    test1="asdafdsfsd"
    print(encjavamode2(test2)) 
    print(encjavamode2(test1))
    #print(nativenoleak(test2.encode('utf-8')))
    #print(base64encode(test4))
    #print(base64encode(test3))
    
if __name__ == '__main__':
    main()


