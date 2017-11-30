import os
import sys
import re 
import subprocess


"""


"""
def dealapkfile(path):
    print("[+]apk file path:"+path)
    aapt="aapt dump badging "+path+" | grep package:"
    apkname="aapt dump badging "+path+" | grep application-label-zh"
    packagedata = subprocess.Popen(aapt,shell=True,stdout=subprocess.PIPE).stdout.readlines()[0].decode()
    packagedata=packagedata.replace('\n','')
    print(packagedata)
    apkname =subprocess.Popen(apkname,shell=True ,stdout=subprocess.PIPE).stdout.readlines()[0].decode()
    print(apkname.replace('\n',''))

def main():
    if len(sys.argv) !=2:
        print("python3 script apk_dir/apk_file")
    path = sys.argv[1]
    
    if os.path.isdir(path):
        for i in os.listdir(path):
            if i.endswith(".apk"):
                dealapkfile(path)
    dealapkfile(path)

if __name__ == '__main__':
    main()