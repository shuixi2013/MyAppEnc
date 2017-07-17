var fs = require("fs")
var filename = "dic.txt"
var prefix = new Set()
var keys = Array('0oO', 'iL1', 'g9q', 'VvuU')

var choose = parseInt(Math.random() * 10) % 4
var len = keys[choose].length

while (prefix.size != 20) {

    let tmpstr = ''
    for (let i = 0; i < 5; i++) {
        let index = parseInt(Math.random() * 10) % len
        tmpstr += keys[choose][index]
    }

    if (tmpstr[0] > '9') {
        prefix.add(tmpstr)
    }
}

var data = ''
prefix.forEach(function(element) {
    for (var i = 0; i < 10; i++) {
        let tmpstr = ''
        let newlen = parseInt(Math.random() * 100) % 10 + 5
        for (var j = 0; j < newlen; j++) {
            let index = parseInt(Math.random() * 10) % len
            tmpstr += keys[choose][index]
        }

        element += tmpstr + '\n';
        data += element
    }
}, this);

fs.writeFileSync(filename, data)
console.log('ok')