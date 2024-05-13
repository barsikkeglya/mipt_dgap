import numpy as np

#s1 = np.array([[1,1,0],[1,-1,0],[0,0,1]])
#s2 = np.array([[1,0,-1],[0,1,0],[0,0,1]])

#s = np.matmul(s1,s2)
s = np.array([[-1,-1,1]])
a = np.array([[1,2,3],[2,5,8],[3,8,14]])
c = np.array([[0],[1],[3]])

k = np.array([[]])

b = np.matmul(s,a)

print(np.matmul(b,c))
