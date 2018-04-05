import numpy as np
from PIL import Image
import sys

file = open(sys.argv[1], "r")
content = file.read().splitlines()
#content.rstrip()
#content = content.rstrip().split(" ")
print (content)
matrix = np.array(content).reshape(int(sys.argv[2]), int(sys.argv[3]))
image = np.fft.ifft(matrix)
print(matrix)

img = Image.fromarray(image, 'L')
img.save('inverted.png')
