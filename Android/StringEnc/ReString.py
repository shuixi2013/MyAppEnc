from com.pnfsoftware.jeb.client.api import IScript, IconType, ButtonGroupType
from com.pnfsoftware.jeb.core import RuntimeProjectUtil
from com.pnfsoftware.jeb.core.units.code.java import IJavaSourceUnit
from com.pnfsoftware.jeb.core.units.code import ICodeUnit, ICodeItem
from com.pnfsoftware.jeb.core.output.text import ITextDocument
from com.pnfsoftware.jeb.core.units.code.java import IJavaSourceUnit, IJavaStaticField, IJavaNewArray, IJavaConstant, IJavaCall, IJavaField, IJavaMethod, IJavaClass
from com.pnfsoftware.jeb.core.events import JebEvent, J
from com.pnfsoftware.jeb.core.util import DecompilerHelper

import base64
import sys 
reload(sys)

sys.setdefaultencoding('utf-8') 

stringfilter=['aes error',]
methodname=['La/auu/a;','c']

class ReString(IScript):
    def run(self, ctx):
        print('start deal with strings')
        self.ctx = ctx
        engctx = ctx.getEnginesContext()
        if not engctx:
            print('Back-end engines not initialized')
            return

        projects = engctx.getProjects()
        if not projects:
            print('There is no opened project')
            return
        # means this is current project 
        prj=projects[0]   

        self.codeunits=RuntimeProjectUtil.findUnitsByType(prj , ICodeUnit,False)
        for codeUnit in self.codeunits:
            self.decompileForCodeUnit(codeUnit)

        units = RuntimeProjectUtil.findUnitsByType(prj, IJavaSourceUnit, False)
        for unit in units:
            javaClass = unit.getClassElement()
            print('[+] decrypt:'+javaClass.getName())
            self.cstbuilder = unit.getFactories().getConstantFactory()
            self.processClass(javaClass)
            unit.notifyListeners(JebEvent(J.UnitChange))
        print('Done.')
    
    def decompileForCodeUnit(self, codeUnit):
        decomp = DecompilerHelper.getDecompiler(codeUnit)
        allClasses = codeUnit.getClasses()
        if allClasses == None:
            return 
        for c in allClasses:
            # do not decompile inner classes
            if (c.getGenericFlags() & ICodeItem.FLAG_INNER) == 0:
                a = c.getAddress()
                srcUnit = decomp.decompile(a)

    def processClass(self ,javaClass):
        if javaClass.getName() == methodname[0]:
            print("find auu")
            return 
        for method in javaClass.getMethods():
            block=method.getBody()
            i = 0 ; 
            while i < block.size():
                stm = block.get(i)
                self.checkElement(block ,stm)
                i += 1
    

    def checkElement(self,parent,e):
        if isinstance(e,IJavaCall):
            mmethod = e.getMethod()
            mname = mmethod.getName()
            msig = mmethod.getSignature()
            if mname == methodname[1] and methodname[0] in  msig :
                v=[]
                for arg in e.getArguments():
                    if isinstance(arg , IJavaConstant):
                        v.append(arg.getString())
                if len(v) == 1 :
                    decstr = self.decryptstring(v[0])
                    parent.replaceSubElement(e, self.cstbuilder.createString(decstr))

        for subelt in e.getSubElements():
            if isinstance(subelt, IJavaClass) or isinstance(subelt, IJavaField) or isinstance(subelt, IJavaMethod):
                continue
            self.checkElement(e,subelt)

    def decryptstring(self,string):
        src = []
        key = [69, 110, 99, 114, 121, 112, 116] 
        keylen = len(key)
        data = base64.decodestring(string)
        for index , char in enumerate(data):
            src.append( chr(ord(char) ^ key[index % keylen ]))

        return ''.join(src) 
        


###############################################
###
###  just for test 
###
################################################


                
    def processSourceTree(self, e):
        if e:
            self.analyzeNode(e)
            elts = e.getSubElements()
        for e in elts:
            self.processSourceTree(e)

    def getTextDocument(self, srcUnit):
        formatter = srcUnit.getFormatter()
        if formatter and formatter.getDocumentPresentations():
            doc = formatter.getDocumentPresentations()[0].getDocument()
        if isinstance(doc, ITextDocument):
            return doc
        return None

    def formatTextDocument(self, doc):
        javaCode, formattedMarks = '', ''
        # retrieve the entire document -it's a source file,
        # no need to buffer individual parts. 10 MLoC is enough 
        alldoc = doc.getDocumentPart(0, 10000000)
        for lineIndex, line in enumerate(alldoc.getLines()):
            javaCode += line.getText().toString() + '\n'
            for mark in line.getMarks():
                # 0-based line and column indexes
                formattedMarks += '%d:%d - %s (%s)\n' % (lineIndex, mark.getOffset(), mark.getName(), mark.getObject())
        return javaCode, formattedMarks
