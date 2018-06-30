import numpy as np
import sys

matrix = []
with open(sys.argv[1], "r") as f:
	height = int(f.readline())
	width = int(f.readline())
	for i in range(height):
		row = []
		for j in range(width):
			row.append(int(f.readline()))
		matrix.append(row)

coefficients = []
for row in matrix:
    for item in row:
	coefficients.append(complex(item, 0))

matrix = np.array(matrix).reshape(1, height*width)

print(matrix)
result = np.fft.fft(matrix)
print(result)
