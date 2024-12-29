import os
p = os.listdir(".")
file = input("input: ")

if os.system(f"g++ {file}.cpp -std=c++17 -Wall -Wextra -Wshadow -O2 -DLOCAL -g -fsanitize=undefined,address -o {file}") != 0:
    print("Compilation failed")
    exit(1)

for x in p:
    if x[:len(file)]==file and x[-3:]==".in":
        if os.system(f"./{file} < {x}")!=0:
            print("Runtime Error")
            exit(1)