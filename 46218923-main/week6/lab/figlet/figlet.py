from pyfiglet import Figlet
import sys, random

figlet = Figlet()

# manage immediate exit
def immediate_exit():
    print("invalid usage")
    sys.exit(1)

# check command-line arguments
argc = len(sys.argv)

if argc != 3 and argc != 1:
    immediate_exit()
elif argc == 3:
    switch = sys.argv[1]
    font = sys.argv[2]

    if switch not in ["-f", "--font"]:
        immediate_exit()

    if str(font) in figlet.getFonts():
        figlet.setFont(font = font)
    else:
        immediate_exit()

text = input("Input: ")
print(f"output: , {figlet.renderText(text)}")
