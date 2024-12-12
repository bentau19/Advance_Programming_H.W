const express = require('express')
const app = express()
app.use(express.static('public'))
const bodyParser = require('body-parser')
app.use(bodyParser.urlencoded({extended : true}))
function calc(x,y,operation){
switch (operation) {
case '0':
return x+y
case '1':
return x-y
case '2':
return x*y
case '3':
return x/y
default:
return 'incalculable'
}
}
app.post('/calc', function(req,res){
var x = parseInt(req.body.x)
var y = parseInt(req.body.y)
var operation = req.body.operation
var result = calc(x,y,operation)
res.end(`<html>
<body>
The answer is ${result}.
<a href="/index.html">reset</a>
</body>
</html>`)
})
app.listen(880)
