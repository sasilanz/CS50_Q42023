# TODO
# TODO
import sys


def main():
    height = get_height()
    for i in range(height):
        i += 1
        print(" " * (height - i) + "#" * i + "  " + "#" * i)


def get_height():
    while True:
        try:
            h = int(input("Height: "))
            if h in range(1, 9):
                return h
        except ValueError:
            print("Not an Integer")


main()
