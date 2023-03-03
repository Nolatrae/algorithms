import time
from sys import getsizeof

n = 10

for i in range(1,9):
  startTime = time.perf_counter_ns()
  dict = {a: a for a in range(n**i)}
  endTime = time.perf_counter_ns()
  print(n**i, getsizeof(dict), endTime - startTime)
