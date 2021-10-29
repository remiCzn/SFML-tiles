import matplotlib.pyplot as plt
import numpy as np
import json
import tkinter as tk

with open('./res.json') as f:
    data = json.load(f)

print(data)

x = np.array(data["x"])
y = np.array(data["y"])

plt.plot(x, y)
plt.show()
