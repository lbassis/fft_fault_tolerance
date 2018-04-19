import math
import cmath

pi = 3.14159265358979323846

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
	if not power_of_two(n):
		return -1
	elif n >= 2:
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

def main():
	nSamples = 64
	nSeconds = 1.0
	sampleRate = nSamples / nSeconds
	freqResolution = sampleRate / nSamples
	x = []
	y = []
	nFreq = 5
	freq = [2, 5, 11, 17, 29]

	for i in range(nSamples):
		x.append(complex(0.0,0.0))
		for j in range(nFreq):
			x[i] += math.sin(2*pi*freq[j]*i/nSamples)
		y.append(x[i])

	y = fft2(y,nSamples)
	print(" n	    x[]	    y[]		f")
	for i in range(nSamples):
		print(i, round(x[i].real,3), round(abs(y[i]),3), i*freqResolution)

if __name__ == '__main__':
   main()