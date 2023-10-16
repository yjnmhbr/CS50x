from cs50 import get_int
from cs50 import get_string

n = ""
check = 1

while (check != 0):
    check = 0
    n = get_string("Number: ")
    for i in range(len(n)):
        if (type(n[i]) == int):
            check += 1

sumhold = ""
sum1 = 0
sum2 = 0
legit = 0

if (len(n) % 2 == 0):
    for i in range(len(n)):
        if (i % 2 == 0 or i == 0):
            sumhold += str(int(n[i]) * 2)
        else:
            sum2 += int(n[i])
    for i in range(len(sumhold)):
        sum1 += int(sumhold[i])
    if ((sum1 + sum2) % 10 == 0):
        legit = 1
else:
    for i in range(len(n)):
        if (i % 2 != 0):
            sumhold += str(int(n[i]) * 2)
        else:
            sum2 += int(n[i])
    for i in range(len(sumhold)):
        sum1 += int(sumhold[i])
    if ((sum1 + sum2) % 10 == 0):
        legit = 1

f2num = int(n[0]) * 10 + int(n[1])
label = ""

if (f2num == 34 or f2num == 37):
    label = "AMEX"
elif (f2num > 50 and f2num < 56):
    label = "MASTERCARD"
elif (int(n[0]) == 4):
    label = "VISA"

if (legit == 1):
    if (len(n) == 13 and label == "VISA"):
        print("VISA")
    elif (len(n) == 15 and label == "AMEX"):
        print("AMEX")
    elif (len(n) == 16 and label == "VISA"):
        print("VISA")
    elif (len(n) == 16 and label == "MASTERCARD"):
        print("MASTERCARD")
    else:
        print("INVALID")
else:
    print("INVALID\n")