from typing import Counter
import matplotlib.pyplot as plt
import numpy as np
import json
from tkinter import *

with open('./res.json') as f:
    data = json.load(f)

# print(data)

haut = len(data)
larg = len(data[0])
cote = 3

void = 1
solid = 0

cell = [[void for row in range (haut)] for row in range (larg)]

def generateNoise():
    for y in range (haut):
        for x in range (larg):
            if(data[x][y] > 0):
                cell[x][y] = solid
            else: 
                cell[x][y] = void

def dessiner():
    for y in range(haut):
        for x in range(larg):
            if cell[x][y] == void:
                coul = "bisque"
            elif cell[x][y] == solid:
                coul = "black"
            cell[x][y] = canvas.create_rectangle((x*cote, y*cote, (x+1)*cote, (y+1)*cote), outline="", fill=coul)

def init():
    generateNoise()

fenetre = Tk()
fenetre.title("Map")
canvas = Canvas(fenetre, width= cote * larg, height=cote * haut, highlightthickness=0)
canvas.pack()
init()
dessiner()
fenetre.mainloop()