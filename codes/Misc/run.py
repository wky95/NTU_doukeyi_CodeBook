import os
p = os.listdir(".")
f = input("input: ")

if os.system(f"g++ {f}.cpp -std=c++17 -Wall -Wextra -Wshadow -O2 -DLOCAL -g -fsanitize=undefined,address -o {f}") != 0:
    print("CE")
    exit(1)

for x in p:
    if x[:len(f)]==f and x[-3:]==".in":
        print(x)
        if os.system(f"./{f} < {x}")!=0:
            print("RE")
            exit(1)
        print()