#!/usr/bin/env python3
import json
import re
import sys

ORDER = 2
NUM_WORDS = 1  # Number of words at the end of each chain

print("Loading corpus...")
corpus = sys.stdin.read()
words = []
for word in corpus.split():
    if "--" in word and "---" not in word:
        new_words = word.split("--", 1)
        new_words.insert(1, "--")
        words += filter(None, new_words)
    elif re.fullmatch(r"\\\d+\\", word):
        pass
    elif re.fullmatch(r"\(\d+\)", word):
        pass
    elif re.fullmatch(r"<.*>", word):
        pass
    else:
        words.append(word)


def should_include_word(word, prev):
    if word in ["I", "--"]:
        return True
    if word.isupper():
        return False
    if not any(c.isalnum() for c in word):
        return False
    # if word[0].isupper() and word not in ["I"]:
    #     if prev and prev[-1] not in ".:?!":
    #         return False
    return True


def words_valid(words_):
    for i, word in enumerate(words_):
        prev = words_[i - 1] if i > 0 else None
        if not should_include_word(word, prev):
            return False
    return True


def increment(chain, keys):
    key, keys = keys[0], keys[1:]
    if not keys:
        if key not in chain:
            chain[key] = 0
        chain[key] = chain[key] + 1
        return
    if key not in chain:
        chain[key] = {}
    increment(chain[key], keys)


print("Generating chain...")
chain = {}
for i in range(len(words) - ORDER):
    start_words = words[i:i+ORDER]
    end_words = words[i+ORDER:i+ORDER+NUM_WORDS]
    if not words_valid(start_words + end_words):
        continue

    keys = start_words + [" ".join(end_words)]
    increment(chain, keys)

print("Saving chain...")
filename = (sys.argv + ["chain.json"])[1]
with open(filename, "w") as f:
    json.dump(chain, f)
