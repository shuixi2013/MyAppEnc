from optparse import OptionParser 
import zipfile
import os 
import sys 

src=''
dest='./'

def main():
    parser = OptionParser()
    parser.add_option('-s' ,'--src' , dest="src" , help='apk file path')
    parser.add_option('-o' , '--output',dest="output", help='dex file output path')

    (options ,args) = parser.parse_args()

    if options.src:
        src = options.src
    else: 
        exit() 

    if options.output:
        dest=options.output
        if not dest.endswith('/'):
            dest+='/'

    os.system('unzip -o '+ src+' -d '+ dest+'out')
    paths=os.listdir(dest+'out')
    for path in paths:
        if path.endswith('.dex'):
            dexdir=dest+path
            if not os.path.exists(dexdir):
                os.mkdir(dest+path)
            os.system('cp '+dest+'out/'+path+" "+dexdir )
            os.system('java -jar common/ShakaApktool.jar bs '+dest+path+'/'+path+" -o "+dexdir+"/out")


if __name__ == '__main__':
    main()






