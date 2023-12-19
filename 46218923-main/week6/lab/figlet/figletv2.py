from pyfiglet import Figlet
import sys
import random

def ex():
    print("invalid usage")
    sys.exit(1)

figlet = Figlet()

# check user command-line args
argc = len(sys.argv)

if argc != 1 and argc != 3:
    ex()
elif argc == 1:
    font = random.choice(figlet.getFonts())

elif argc == 3:
    opt = sys.argv[1]
    font = sys.argv[2]
    # check the option argument -f and --font
    if opt in ["-f", "--font"]:
        figlet.setFont(font = font)

    else:
        ex()

text = input("Input: ")
print(f"Output: {figlet.renderText(text)}")
