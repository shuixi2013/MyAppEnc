import os
import sys


os.system("cd modifySo/jni && ndk-build")
os.system("cp -r modifySo/libs/  ./linkerWrapper/app/libs/")