from cs50 import get_int

n = 0

# Get height of towers
while n < 1:
    height = get_int("Height: ")
    if height < 9 and height > 0:
        n = 1

# Build pyramid
for x in range(height):
    print(" " * (height - (x + 1)), end="")
    print("#" * (x + 1), end="  ")
    print("#" * (x + 1))