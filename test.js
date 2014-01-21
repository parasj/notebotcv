var cv = require('./build/Release/nodebotcv');

// console.log(cv.buildInformation());
// console.log(cv.add(1, 2));
console.log(cv.houghLines("./tmp/image.jpg", "./tmp/image.out.jpg"));