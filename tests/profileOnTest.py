from genAndRunTests import *

runTests()

os.system('cat test.txt | gprof ../build/main > profile')
os.system('cat profile | python3 gprof2dot.py | dot -Tsvg -o output.svg')