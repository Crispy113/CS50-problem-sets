from cs50 import get_string
from sys import exit
import re


number = get_string("Number: ")
numlen = len(number)

# Check correct card length
p = re.compile('[0-9]{13,16}')
if p.match(number) == None:
    print("INVALID")
    exit()

number = int(number)
initials = int(number / (10**(numlen - 2)))

sum = 0
x = 0

while x < numlen:
    if x % 2 == 0:
        sum += number % 10
    else:
        tmp = (number % 10) * 2
        sum += (tmp % 10) + int(tmp / 10)

    number = int(number / 10)
    x += 1

if sum % 10 != 0:
    print("INVALID")
    exit()

print(int(initials / 10))

if initials == 34 or initials == 37 and numlen == 15:
    print("AMEX")
elif initials > 50 and initials < 56 and numlen == 16:
    print("MASTERCARD")
elif int(initials / 10) == 4 and (numlen == 13 or numlen == 16):
    print("VISA")
else:
    print("INVALID")
