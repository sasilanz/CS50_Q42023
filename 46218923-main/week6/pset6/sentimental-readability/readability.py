# TODO
from cs50 import get_string
import re


input = get_string("Text: ")
i = input.lower()

# found regex (re) here: https://stackoverflow.com/a/73209272
count_letters = len(re.findall(r"[a-z]", i))
# code testing
# print(count_letters)

# studying this tutorial: https://datagy.io/python-count-words/
count_words = len(i.split())
# code testing
# print(count_words)

# similar approach as for letters count
count_sentences = len(re.findall(r".+?[\.|!|?]+", i))
# code testing
# print(f"Sentences: {count_sentences}")
# average number of letters per 100 words in the text
L = (count_letters / count_words) * 100

# average number of sentencs per 100 words in the text
S = (count_sentences / count_words) * 100

X = 0.0588 * L - 0.296 * S - 15.8

if X < 1:
    print("Before Grade 1")

elif X >= 16:
    print("Grade 16+")

else:
    print(f"Grade {round(X)}")
