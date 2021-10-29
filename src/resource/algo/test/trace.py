import matplotlib.pyplot as plt
import numpy as np
import json

with open('./res.json') as f:
    data = json.load(f)

print(data)

x = np.array(data["x"])
y = np.array(data["y"])

plt.plot(x, y)
plt.show()
