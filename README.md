# markov

Generate Markov chains using generate.py:

    $ cat <corpus-text> | ./generate.py

This will save a JSON Markov chain to chain.json.
Then, run transpile.py:

    $ ./transpile.py chain.json > chain

You can then load "chain" from markov.cpp.
