# TODO
from cs50 import get_float
import sys


# declare variables
change_owed = 0
count = 0

# check valid inputs
while True:
    change_owed = get_float("Change owed: ")
    if change_owed > 0:
        break
cents = round(change_owed * 100)


while cents > 0:
    if cents >= 25:
        cents = cents - 25
        count += 1
    elif cents >= 10:
        cents = cents - 10
        count += 1
    elif cents >= 5:
        cents = cents - 5
        count += 1
    elif cents >= 1:
        cents = cents - 1
        count += 1

print(count)
