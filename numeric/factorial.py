import time

while True:
	n = int(input())
	beginTime = time.clock()
	ret = 1
	for i in range(2, n + 1):
		ret *= i
	endTime = time.clock()
	print(ret)
	print('cost time', endTime - beginTime, 's.')

input()
