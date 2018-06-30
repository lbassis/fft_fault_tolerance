import math
import cmath

from sys import argv

pi = math.pi

def separate_odd_from_even(element_array):
	even = []
	odd = []
	for i, element in enumerate(element_array):
		if (i % 2 == 0):
			even.append(element)
		else:
			odd.append(element)
	return even, odd

def power_of_two(n):
	N = int(n)
	return N != 0 and ((N & (N-1)) == 0)

def fft2(coefficients, n):

	if n >= 2:
		even, odd = separate_odd_from_even(coefficients)
		even = fft2(even, n/2)
		odd = fft2(odd, n/2)
		for x in range(int(n/2)):
			e = even[x]
			o = odd[x]
			w = cmath.exp(complex(0, -2.0 * pi * x/n))
			even[x] = e + w * o
			odd[x] = e - w * o
		return even+odd
	else:
		return coefficients

if len(argv) < 2:
    print("[ERRO] passe o path do txt como parametro!")
    exit(0)

matrix = []
with open(argv[1], "r") as f:
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

new_coefficients = fft2(coefficients, height * width)

# duplication
matrix2 = []
with open(argv[1], "r") as f2:
	height2 = int(f2.readline())
	width2 = int(f2.readline())
	for i in range(height2):
		row2 = []
		for j in range(width2):
			row.append(int(f2.readline()))
		matrix2.append(row2)


coefficients2 = []
for row in matrix2:
	for item in row:
		coefficients2.append(complex(item, 0))

new_coefficients2 = fft2(coefficients2, height2 * width2)

if new_coefficients != new_coefficients2:
	fault_found = True
else:
	fault_found = False
	with open(argv[2], "w") as output:
	        for e in new_coefficients:
	                output.write("".join("{}\n".format(str(e))))