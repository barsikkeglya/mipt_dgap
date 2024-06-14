import matplotlib.pyplot as plt
import numpy as np
import math
from mpl_toolkits.mplot3d import Axes3D

n = 1/2
r1 = 0.2286
r2 = 0.3422
t1 = 333
t2 = 326


fig = plt.figure(figsize=(10,10))
ax = Axes3D(fig)
rad = np.linspace(0.2286,0.3422,100)
phi = np.linspace(0,2*math.pi,100)
r,th = np.meshgrid(rad,phi)
z = ((np.log(r/r1)/np.log(r2/r1))*(t2**(n+1)-t1**(n+1))+t1**(n+1))**(1/(n+1))
plt.subplot(projection='polar')
plt.pcolormesh(th,r,z,cmap='jet')
plt.plot(phi,r,ls='none')

plt.grid()
plt.colorbar()
plt.show()