import xml.dom.minidom
from xml.dom.minidom import parse 
import os 
import sys


#packagename= ""

def fixxmlfile(xmlpath , stubname):
    DomTree = parse(xmlpath)
    appnode = DomTree.getElementsByTagName("application")[0]
    if  appnode:
        if appnode.hasAttribute("android:name"):
            appname = appnode.getAttribute("android:name")
            # set my application
            appnode.setAttribute("android:name",stubname)
            #appnode.setAttribute("nikoprotect","service")
            metanode = DomTree.createElement("meta-data")
            metanode.setAttribute("android:name","targetapp")
            metanode.setAttribute("android:value",appname)
            appnode.appendChild(metanode)
            print("fix done")
        else :
            print("no name found")
            #set my application
            appnode.setAttribute("android:name",stubname)
            appnode.setAttribute("nikoprotect","service")
            print("fix done")
        fw = open("./fix.xml",'w')
        fw.write(DomTree.toxml())
        fw.close()
    else :
        print("can;t find application")
def main():
    if len(sys.argv) <3 :
        print("usage %s  AndroidManifest.xml stubname" %(__file__))
    stubname= sys.argv[2] 
    xmlpath = sys.argv[1]
    fixxmlfile(xmlpath,stubname) 

if __name__ == '__main__':
    main()