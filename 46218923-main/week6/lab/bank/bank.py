
greeting = input("Greeting: ")
greeting_lower = greeting.lower()
if "hello" in greeting_lower:
    print("$0")
elif "h" == greeting_lower[0]:
    print("$20")
else:
    print("$100")

