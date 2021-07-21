import re

pattern = re.compile("Slowly, a new text starts appearing on the screen. It reads ...")
flagged = False

f = open("text/outputs.txt", "w")

for line in open("ssh_outputs.log"):
    if flagged:
        flagged = False
        f.write("{}\n".format(line.strip()))
    else:
        for match in re.finditer(pattern, line):
            if match:
                flagged = True