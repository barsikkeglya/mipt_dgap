import numpy as np
import pandas as pd
import math
import matplotlib.pyplot as plt
import matplotlib
from scipy.optimize import curve_fit

paths = ['C:/Users/George/Documents/mipt_dgap/2_semester/labs/lab_2_2_1/data/20240326_1711439001210_41.csv','C:/Users/George/Documents/mipt_dgap/2_semester/labs/lab_2_2_1/data/20240326_1711440200344_48.5.csv','C:/Users/George/Documents/mipt_dgap/2_semester/labs/lab_2_2_1/data/20240326_1711441128597_59.5.csv','C:/Users/George/Documents/mipt_dgap/2_semester/labs/lab_2_2_1/data/20240326_1711442143126_82.csv','C:/Users/George/Documents/mipt_dgap/2_semester/labs/lab_2_2_1/data/20240326_1711443254657_119.csv','C:/Users/George/Documents/mipt_dgap/2_semester/labs/lab_2_2_1/data/20240326_1711444306232_201.csv']

v = 0.0012
ls = 550

ps = []
ds = []

for path in paths:

    df = pd.read_csv(path, sep=',', header=0)

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
    d = v*ls/(2*tf)
    ps.append(float(path.split('_')[7].replace('.csv','')))
    ds.append(d*10000)
    print(path.split('_')[7].replace('.csv',''), uf, tf, np.diag(pcov))
pn = []
dn = []
for i in range(len(ps)):
    print('(',1/ps[i],',',ds[i],')')
    pn.append(1/ps[i])
    dn.append(ds[i])

f1 = lambda x, k, b: k*x+b
popt,pcov=curve_fit(f1,pn,dn)
print(popt[0],popt[1],np.diag(pcov))
print(f1(1/760,popt[0]+np.diag(pcov)[0],popt[1]))
