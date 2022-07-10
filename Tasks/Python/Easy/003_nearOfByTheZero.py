# Digital root is the recursive sum of all the digits in a number.

# Given n, take the sum of the digits of n. If that value has more than one digit, continue reducing in this way until a single-digit number is produced. The input will be a non-negative integer.

# Examples
#     16  -->  1 + 6 = 7
#    942  -->  9 + 4 + 2 = 15  -->  1 + 5 = 6
# 132189  -->  1 + 3 + 2 + 1 + 8 + 9 = 24  -->  2 + 4 = 6
# 493193  -->  4 + 9 + 3 + 1 + 9 + 3 = 29  -->  2 + 9 = 11  -->  1 + 1 = 2


a = [0] + [0, 9, 6, 0, 7, 3, 6, 5, 2, 0, 0, 8, 4, 1] + [int(1e9)]
n = len(a)
for i in range(n - 2, -1, -1):
    if a[i]:
        a[i] = a[i + 1] + 1
for i in range(2, n):
    if a[i]:
        a[i] = min(a[i - 1] + 1, a[i])
print(a[1:-1])
