# encoding: utf-8

from sys import argv

import cv2

def open2(path):
    image = cv2.imread(path, 0) # já lê em P&B

    if image is None:
        print("[ERRO] imagem não encontrada")
        exit(0)

    return image

def create_file(image, filename):
    with open(filename,"w") as f:
        height, width = image.shape
        f.write("{}\n{}\n".format(height, width))

        for row in range(0,height):
            f.write("")

            for column in range(0, width):
                f.write("{}\n".format(image[row, column]))


## main ##

if len(argv) < 2:
    print("[ERRO] passe o path da imagem como parametro")
    exit(0)

image = open2(argv[1])

create_file(image, "matrix.txt")

print("feito o carreto!")
