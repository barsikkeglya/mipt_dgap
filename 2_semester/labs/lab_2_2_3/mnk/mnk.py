import numpy as np

def f(k,x,b):
    return k*x + b

def mnk(q,r,k,b):
    sum = 0
    for i in range(len(q)):
        sum += (f(k,q[i],b)-r[i])**2
    return sum

Q1 = [0.09803444,
0.38073438,
1.43909675,
3.715673,
12.5330784,
24.10519664,
40.85405256,
64.0407816,
114.1761404,
164.3877611,
202.5453826,
255.1191477


]
R1 = [24.073,
24.060,
24.053,
24.061,
24.101,
24.154,
24.231,
24.339,
24.567,
24.796,
24.971,
25.207
]

b_poss = np.linspace(21.5,25,1000)
k_poss = np.linspace(0,0.01,1000)

max_sum = -1
curr_k = -1
curr_b = -1
for b in b_poss:
    for k in k_poss:
        sum = mnk(Q1,R1,k,b)
        if max_sum == -1:
            max_sum = sum
        if sum < max_sum:
            curr_k=k
            curr_b=b
            max_sum=sum

        
print(curr_k,curr_b)
print(260000)
print(260*curr_k+curr_b)