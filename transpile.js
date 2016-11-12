/**
 * transpile second order JSON markov chain to C++ map-map-map form
 * Copyright (C) 2016 Alyssa Rosenzweig
 * ALL RIGHTS REVERSED
 */

const fs = require("fs"),
      chain = JSON.parse(fs.readFileSync(process.argv[2]).toString());

var out = [];

Object.keys(json).forEach(A => Object.keys(json[A]).forEach(B => Object.keys(json[A][B]).forEach(C => {
    out.push(`${A} ${B} ${C} ${json[A][B][C]}`)
})));

console.log(out.join("\n"));
