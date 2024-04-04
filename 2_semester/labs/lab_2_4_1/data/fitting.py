
import numpy as np
import pandas as pd
import math
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

paths = ['C:/mipt_dgap/2_semester/labs/lab_2_4_1/data/hotter.csv']

for path in paths:
    df = pd.read_csv(path,sep=',',header=0)
    data = df.to_numpy()
    t = []
    p = []
    et = []
    ep = []
    for x in data:
        t.append(x[0])
        p.append(x[1])
        et.append(x[2])
        ep.append(x[3])
    tn = np.array(t)
    pn = np.array(p)
    etn = np.array(et)
    epn = np.array(ep)
    
    f = lambda x, k, b: k*x+b

    popt,pcov=curve_fit(f,tn,pn,sigma = epn)
    kf = popt[0]
    bf = popt[1]
    print (kf,bf)
    print (np.diag(pcov))
