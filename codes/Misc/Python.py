# system setting
sys.setrecursionlimit(100000)
sys.set_int_max_str_digits(10000)

# turtle
from turtle import *

N = 3000000010
setworldcoordinates(-N, -N, N, N)
hideturtle()
speed(100)

def draw_line(a, b, c, d):
    teleport(a, b)
    goto(c, d)

def write_dot(x, y, text, diff=1): # diff = 文字的偏移
    teleport(x, y)
    dot(5, "red")

    teleport(x+N/100*diff, y+N/100*diff)
    write(text, font=("Arial", 5, "bold"))

# usage
draw_line(*a[i], *(a[i-1]))
write_dot(*a[i], str(a[i]))