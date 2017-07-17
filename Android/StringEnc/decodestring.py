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
class DexGuard():
    pass


def is_chinese(data):
    for uchar in data:         
        if '\u4e00' <= uchar<='\u9fff':
            return True
        else:
            return False

def getrandomstring(num):
    return ''.join(random.choice(allstring) for x in range(num))

def main():
    test1="233333"  
    test2="中国"
    print(nativenoleak(test1)) 
    #print(nativenoleak(test2.encode('utf-8')))
    #print(base64encode(test4))
    #print(base64encode(test3))
    
if __name__ == '__main__':
    main()


