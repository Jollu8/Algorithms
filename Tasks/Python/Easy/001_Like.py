# You probably know the "like" system from Facebook and other pages. People can "like" blog posts, pictures or other items. We want to create the text that should be displayed next to such an item.

# Implement the function which takes an array containing the names of people that like an item. It must return the display text as shown in the examples:

# []                                -->  "no one likes this"
# ["Peter"]                         -->  "Peter likes this"
# ["Jacob", "Alex"]                 -->  "Jacob and Alex like this"
# ["Max", "John", "Mark"]           -->  "Max, John and Mark like this"
# ["Alex", "Jacob", "Mark", "Max"]  -->  "Alex, Jacob and 2 others like this"



# def likes(n):
#     if len(n) == 0:
#         return "no one likes this"
#     elif len(n) == 1:
#         return n[0] + " like this"
#     elif len(n) == 2:
#         return n[0] + " and  " + n[1] + " like this"
#     elif len(n) == 3:
#         return n[0] + ", " + n[1] + "  and like this"
#     elif len(n) > 3:
#         x = len(n) - 2
#         return n[0] + ", " + n[1] + " and " + str(x) + " others like this"


print(likes(""))
n = ["Alex"]
print(likes(n))
n1 = ["Alex", "Peter"]
print(likes(n1))
n2 = ["Alex", "John", "Jacob"]
print(likes(n2))
n3 = ["Kim", "Lord", "Some", "Alexander"]
print(likes(n3))
