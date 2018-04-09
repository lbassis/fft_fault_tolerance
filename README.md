# FTF

## Criação da matriz

Para criar a matriz de intensidade da imagem em P&B, é necessário ter o opencv-python (cv2) instalado. Para instalar, rode:
```
pip install opencv-python
```

Depois para executar o script:

```
python matrix_creator.py PATH_DA_IMAGEM
```

Exemplo:
```
python matrix_creator.py images/gray.jpg
```

Isto vai gerar um arquivo `matrix.txt` com a altura da imagem na primeira linha, a largura na segunda, e em diante a matriz em si.

Exemplo de `matrix.txt` gerada a partir do exemplo acima:

```
20
10
255 255 255 255 255 255 255 255 255 255
255 255 255 255 255 255 255 255 255 255
255 255 255 255 255 255 255 255 255 255
255 255 255 255 255 255 255 255 255 255
115 115 115 115 115 115 115 115 115 115
115 115 115 115 115 115 115 115 115 115
115 115 115 115 115 115 115 115 115 115
115 115 115 115 115 115 115 115 115 115
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
115 115 115 115 115 115 115 115 115 115
115 115 115 115 115 115 115 115 115 115
115 115 115 115 115 115 115 115 115 115
115 115 115 115 115 115 115 115 115 115
255 255 255 255 255 255 255 255 255 255
255 255 255 255 255 255 255 255 255 255
255 255 255 255 255 255 255 255 255 255
255 255 255 255 255 255 255 255 255 255
```
