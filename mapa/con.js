//const fs = require('fs')  
import { readFileSync } from './node_modules/file-system/test/fs.js'
function readFile(){
    
    let texto = readFileSync('./result.txt', {
        encoding: 'utf-8'
    })
    console.log(texto)
    }
//readFile()
export default readFile()
