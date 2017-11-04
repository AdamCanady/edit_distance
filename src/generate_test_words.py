import string
import random

LENGTH = 14
NUM_WORDS = 20000

with open("/Users/adamcanady/dev/tmp/edit_distance/test_words.txt", 'w') as f:
  for i in range(NUM_WORDS):
    f.write(''.join(
        random.choice(
            string.ascii_uppercase + string.digits) for _ in range(LENGTH)))
    f.write("\n")
