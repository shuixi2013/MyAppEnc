import os
import sys
from optparse import OptionParser 
import decodestring
import re




packagename =""
classname =""
gstrpos=[]
garrstr=""
gstrindex =""
isneedFunc=False
arrmod1="""
    const/16 v0, %s
    new-array v0, v0, [B
    fill-array-data v0, :array_110
    sput-object v0, %s->encdata_:[B
    return-void
    :array_110
    .array-data 1
    %s
    .end array-data
"""

arrmod2="""
.method static constructor <clinit>()V
    .locals 1
    .prologue
    const/16 v0, %s
    new-array v0, v0, [B
    fill-array-data v0, :array_110
    sput-object v0, %s->encdata_:[B
    return-void
    :array_110
    .array-data 1
    %s
    .end array-data
.end method
"""

constmod="""
    const/16 %s, %s
"""
smalimod="""
    invoke-static {%s,%s,%s}, %s->papapa(III)Ljava/lang/String;
"""

resultmod="""
    move-result-object %s
"""

decmethodmod="""
.method public static papapa(III)Ljava/lang/String;
    .locals 10
    .param p0, "arg1"    # I
    .param p1, "current"    # I
    .param p2, "pos"    # I
    .prologue
    .line 28
    add-int/lit8 v3, p0, 0x77
    .line 29
    .local v3, "fixlen":I
    add-int/lit8 p2, p2, -0x6e
    .line 30
    rsub-int p1, p1, 0x17a
    .line 31
    const/4 v4, 0x0
    .line 32
    .local v4, "index":I
    const/4 v0, 0x0
    .line 33
    .local v0, "current_":I
    sget-object v6, Lcn/tongdun/stringenc/MainActivity;->encdata_:[B
    .line 34
    .local v6, "src":[B
    new-array v5, v3, [B
    .line 35
    .local v5, "ret":[B
    int-to-byte v2, p1
    .line 37
    .local v2, "encchar":B
    :goto_0
    move v7, v4
    .line 38
    .local v7, "v2":I
    int-to-byte v8, p1
    aput-byte v8, v5, v7
    .line 39
    add-int/lit8 v4, v4, 0x1
    .line 40
    if-ne v4, v3, :cond_0
    .line 49
    :try_start_0
    new-instance v8, Ljava/lang/String;
    const-string v9, "utf-8"
    invoke-direct {v8, v5, v9}, Ljava/lang/String;-><init>([BLjava/lang/String;)V
    :try_end_0
    .catch Ljava/lang/Exception; {:try_start_0 .. :try_end_0} :catch_0
    .line 53
    :goto_1
    return-object v8
    .line 42
    :cond_0
    move v0, v2
    .line 43
    aget-byte v2, v6, p2
    .line 44
    add-int/lit8 p2, p2, 0x1
    .line 45
    add-int v8, v0, v2
    add-int/lit8 p1, v8, -0xa
    .line 46
    goto :goto_0
    .line 50
    :catch_0
    move-exception v1
    .line 51
    .local v1, "e":Ljava/lang/Exception;
    invoke-virtual {v1}, Ljava/lang/Exception;->printStackTrace()V
    .line 53
    const/4 v8, 0x0
    goto :goto_1
.end method
"""

decmethodmod2="""
wait it 
"""

javafuncmod="""
    public static String linkxxxxx(String bb , int bbx) {
        try {
            int length = bb.length() / 2;
            char[] hexChars = bb.toCharArray();
            byte[] enc = new byte[length];
            for (int i = 0; i < length; i++) {
                    int pos = i * 2;
                    enc[i] = (byte) ("0123456789abcdef".indexOf(hexChars[pos]) << 4 | "0123456789abcdef".indexOf(hexChars[pos + 1]));
            }
            byte bbxx =(byte)(bbx ^ %d);
            int len = enc.length ;

            enc[0] = (byte)(enc[0] ^ %d) ;
            byte tmp =enc[0];
            for(int i = 1 ; i <len ; i++ ) {
                byte gg = enc[i] ;
                enc[i] = (byte)(enc[i] ^ tmp ^ bbxx);
                tmp = gg;
            }
            return new String(enc ,"utf-8");
        }catch (Exception e)
        {
            e.printStackTrace();
        }
        return null ;
    }
"""



def dealwithstring(match):
    global gstrindex
    reg=match.group(1)
    print(reg)
    
    strvalue = gstrpos[gstrindex]
    print(strvalue)
    mixstr=""
    mixstr+=constmod%("v1",str(hex(strvalue[0])))
    mixstr+=constmod%("v2",str(hex(strvalue[1])))
    mixstr+=constmod%("v3", str(hex(strvalue[2])))
    mixstr+=smalimod%("v1","v2","v3",classname)
    mixstr+=resultmod%(reg)
    
    gstrindex+=1 
    return mixstr

def dealStr(strings):
    strpos ,bytearr = decodestring.encMultiStr(strings)
    arrstr=""
    for bb in bytearr:
        arrstr+=str(hex(bb))+"t\n"
    return strpos , arrstr

def getclassname(data):
    pattern=r"L.*;"
    prog = re.compile(pattern)
    name = prog.search(data).group()
    return name

def dealsmalifile(path):
        #print(path)
        newdata=''
        gstrindex = 0 
        pattern=r"const-string [vp0-9]{2,3}, \"(.+)\""
        prog = re.compile(pattern)
        f = open(path,'r')
        data=f.read() 
        f.close()
        strings = prog.findall(data)
        if len(strings) == 0 :
            return 
        global gstrpos
        global garrstr
        gstrpos ,garrstr = dealStr(strings)

        f = open(path ,'r')
        olddata = f.read()
        global classname 
        classname = getclassname(olddata)
        ## main 
        ## find cinit and insert byte array
        ## replace const string with 
        ## deal with line or data
        ## for line in olddata:
        pattern=r".method.*.end method"
        prog = re.compile(pattern)
        ret =prog.search(olddata)
        print(ret)
        pattern=r"const-string ([vp0-9]{2,3}), \"(.+)\""
        prog = re.compile(pattern)
        newdata = prog.sub( dealwithstring, olddata)
        #print(newdata)
        #f =open(path , 'w',encoding='utf-8')
        #f.write(newdata)
        #f.close()

def travel2(path):
    for dirpath,dirs,files in os.walk(path):
            if packagename in dirpath:
                for filex in files:
                    if "ppt" in filex:
                        dealsmalifile(dirpath+os.sep+filex)

#######################################################################
#########
#########  one decode function in .java file 
######################################################################

def javaenc(string):
     global isneedFunc
     encstr = decodestring.encjavamode2(string ,key1,key2,key3)
     retstr = "linkxxxxx(\"%s\", %d)" %(encstr,key1)
     isneedFunc = True
     #print(retstr)
     return retstr

def srcdealwithstring(match):
    if match.group(1) == None :
        return "\"\"" 
    return  javaenc(match.group(1))


def srcdealline(path):   
        global isneedFunc
        newdata=''
        pattern=r'\"([^"]+)?\"'
        prog = re.compile(pattern)
        f=open(path,'r',encoding='utf-8')
        global key1,key2,key3
        key1,key2,key3 =decodestring.generatorRandomKey()
        strfunc = javafuncmod%(key2,key3)
        #print(strfunc)
        for i in f.readlines():
            if "@SuppressWarn" in i  or " ERROR_" in i  or "@ToJson" in i :
                newdata += i 
                continue
            data = prog.sub(srcdealwithstring , i)
            if data.startswith('}') and isneedFunc:
                data=strfunc+"\n"+data
            newdata+=data
        f.close()
        print(newdata)
        f =open(path , 'w',encoding='utf-8')
        f.write(newdata)
        f.close()
        isneedFunc = False

def javatravel(path):
    ifdeal = True
    cantdeal=['Collector.java','MainActivity.java']
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
    parser.add_option("-o", "--output",  dest="output", default="." ,help="output path") 
    parser.add_option("-s", "--src",  dest="dirpath", help="dir path") 
    parser.add_option("-p", "--package" , dest="package" , help="packagename")
    (options, args) = parser.parse_args()
    path = os.path.realpath(options.dirpath)
    output = os.path.realpath(options.output)
    global packagename
    global gstrindex
    gstrindex = 0
    packagename = options.package.replace('.',os.sep)
    javatravel(path)
    

if __name__ == '__main__':
    main()
    #strings = ['123456789','\u4e2d\u56fd','asdwqnidoenwioger']
    #encStrings(strings)