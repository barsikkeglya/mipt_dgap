import numpy as np
import pandas as pd
import math
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

df = pd.read_csv('C:/mipt_dgap/2_semester/labs/lab_2_2_1/data/20240326_1711439001210_41.csv', sep=',', header=0)

data = df.to_numpy()
#print(data)
t = []
u = []
sigmat = []
for x in data:
    t.append(x[0])
    u.append(x[1])
    sigmat.append(x[1]*0.001)
tnp = np.array(t)
unp = np.array(u)
sigmanp = np.array(sigmat)

f = lambda x, u0, tau: u0*pow(2.71828,-x/tau)

popt, pcov = curve_fit(f,tnp,unp,sigma = sigmanp)
uf = popt[0]
tf = popt[1]

xlin = np.linspace(0,600,1000)
plt.figure(figsize=(6,6))
plt.plot(xlin,f(xlin,uf,tf))
plt.title('dasgsdfddsa funny plot')
plt.xlabel('funny xlabel')
plt.savefig('C:/mipt_dgap/2_semester/labs/lab_2_2_1/data/fig1.eps',format='eps')
plt.show()