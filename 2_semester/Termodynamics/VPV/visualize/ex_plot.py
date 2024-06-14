import matplotlib.pyplot as plt
import numpy as np

r1 = 1
r2 = 2
t1 = 300
t2 = 400
n = 1/2

fig = plt.figure(figsize=(6,6))
plt.rcParams.update({
    "text.usetex": True,
    "font.family": "Helvetica"
})
x = np.linspace(r1,r2,50)
y = ((np.log(x/r1)/np.log(r2/r1))*(t2**(n+1)-t1**(n+1))+t1**(n+1))**(1/(n+1))
plt.plot(x,y,color='k',label="$n=0.5$")
n = 1
y = ((np.log(x/r1)/np.log(r2/r1))*(t2**(n+1)-t1**(n+1))+t1**(n+1))**(1/(n+1))
plt.plot(x,y,color='red',label="$n=1$")
n = 1.5
y = ((np.log(x/r1)/np.log(r2/r1))*(t2**(n+1)-t1**(n+1))+t1**(n+1))**(1/(n+1))
plt.plot(x,y,color='blue',label="$n=1.5$")
n = 10
y = ((np.log(x/r1)/np.log(r2/r1))*(t2**(n+1)-t1**(n+1))+t1**(n+1))**(1/(n+1))
plt.plot(x,y,color='orange',label="$n=10$")
plt.grid()
plt.xlabel(r'$r$, m',fontsize=12)
plt.ylabel(r'$T$, K',fontsize=12)
plt.legend()
plt.show()