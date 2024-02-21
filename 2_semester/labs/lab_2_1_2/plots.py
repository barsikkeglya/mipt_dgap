import matplotlib.pyplot as plt
import numpy as np

plt.figure(figsize=(6,6))

x = [302.2,308.1,317.2,322.3,329.1,334.3]
l=[0.124,0.160,0.206,0.236,0.259,0.260]

plt.grid()
plt.plot(x,l)
plt.show()