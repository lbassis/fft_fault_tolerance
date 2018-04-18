import numpy as np
from PIL import Image
import sys

file = open(sys.argv[1], "r")
content = file.read().splitlines()
size = len(content)

for i in range (0, size):
    content[i] = complex(content[i])

result = np.fft.ifft(content)

image = np.array(result).reshape(int(sys.argv[2]), int(sys.argv[3]))
print(image)
img = Image.fromarray(image, 'L')
img.save('inverted.png')
