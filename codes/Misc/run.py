import os

f = "pA"

while 1:
    i = input("input: ")
    p = os.listdir(".")
    if i != "":
        f = i
    print(f"file = {f}")
    if os.system(f"g++ {f}.cpp -std=c++17 -Wall -Wextra -Wshadow -O2 -D LOCAL -g -fsanitize=undefined,address -o {f}"):
        print("CE")
        continue
    os.system("clear")

    for x in sorted(p):
        if f in x and ".in" in x:
            print(x)
            if os.system(f"./{f} < {x}"):
                print("RE")
            print()