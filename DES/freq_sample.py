import string
import random

f = open("text/frq_samples.txt", "w")
for i in range(0, 1000):
    f.write("{}\n".format("".join(random.choices(string.ascii_uppercase, k=16))))