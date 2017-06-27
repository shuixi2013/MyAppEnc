var src=''
var dest='./'
var child=require('child_process')
var path = require('path')
var fs = require('fs')

function execSystem(){
    child.execSync('unzip -o '+src+' -d '+ dest+'out')
    paths=fs.readdirSync(dest+'out')
    paths.forEach(function(ele,index){
        if(ele.endsWith('.dex')){
            dexdir=dest+ele 
            console.log(dexdir)
            if(!fs.existsSync(dexdir)){
                child.execSync('mkdir '+ dexdir)
            }

            child.execSync('cp '+dest+'out/'+ele+' '+dexdir)
            // TODO the process  end before child finish its work
            child.execSync( '  java -jar common/ShakaApktool.jar bs '+dest+path+'/'+path+" -o "+dexdir+"/out",
            function(err,stdout,stderr){
                console.log('sssss' )
            })
            console.log('unpack ok')    
         }
    })
}

function main(){
    if(process.argv.length < 4){
        console.log('ggggg')
        return 
    } 

    src = process.argv[2]
    dest = process.argv[3]
    if (!dest.endsWith('/')){
        dest+='/'
    }

    execSystem()
}





main()
