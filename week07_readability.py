from cs50 import get_string
import re

text = get_string("Text: ")

word_list = text.split()

# Count words
words = len(word_list)

# Count letters
letters = 0
for word in word_list:
    letters += len(word)

# Count sentences
sentence_list = re.split(r'[.:!?]', text)
sentences = len(sentence_list)

# Calculate index
L = (letters / words) * 100
S = (sentences / words) * 100

index = round(0.0588 * L - 0.296 * S - 15.8)

# Print index
if index > 15:
    print("Grade 16+")
elif index < 1:
    print ("Before Grade 1")
else:
    print(f"Grade {index}")


# Coleman-Liau index is computed as 0.0588 * L - 0.296 * S - 15.8,
# where L is the average number of letters per 100 words in the text,
# and S is the average number of sentences per 100 words in the text.

# Your program should print as output "Grade X" where X is the grade
# level computed by the Coleman-Liau formula, rounded to the nearest
# integer.

# If the resulting index number is 16 or higher (equivalent to or
# greater than a senior undergraduate reading level), your program
# should output "Grade 16+" instead of giving the exact index number.
# If the index number is less than 1, your program should output
# "Before Grade 1".

