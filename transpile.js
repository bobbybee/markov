/**
 * transpile second order JSON markov chain to C++ map-map-map form
 * Copyright (C) 2016 Alyssa Rosenzweig
 * ALL RIGHTS REVERSED
 */

const fs = require("fs"),
      chain = JSON.parse(fs.readFileSync(process.argv[2]).toString()),
      serialized = serialize(chain);

console.log(serialized);

function serialize(json) {
    let out = [];

    Object.keys(json).forEach(A => Object.keys(json[A]).forEach(B => Object.keys(json[A][B]).forEach(C => {
        out.push(`${A} ${B} ${C} ${json[A][B][C]}`)
    })));

    return out.join("\n");
}
