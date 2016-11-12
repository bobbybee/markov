/* translate second order JSON markov chain to delimited text files */

const fs = require("fs"),
      chain = JSON.parse(fs.readFileSync(process.argv[2]).toString());

var out = [];

Object.keys(json).forEach(A => Object.keys(json[A]).forEach(B => Object.keys(json[A][B]).forEach(C => {
    out.push(`${A} ${B} ${C} ${json[A][B][C]}`)
})));

console.log(out.join("\n"));
