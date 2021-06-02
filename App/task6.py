import numpy as np
import math
import matplotlib.pyplot as plt

fig, (ax1) = plt.subplots(nrows=1, ncols=1, figsize=(12, 10))
n = 10e2
dh = 10e-5

def trap(f, x0,  x1,  n):
    h = (x1 - x0)/n
    s = (f(x0) + f(x1)) / 2
    for x in np.arange( x0 + h,x1,h):
	    s += f(x)
    return s * h

def unintergate_bessel(m, x, t):
    return math.cos(m * t - x * math.sin(t))

def func(x,m):
    def f (t_n):
       return unintergate_bessel(m,x,t_n)
    return f


def besel(x,m):
    integr = trap(func(x,m),0,math.pi,n)
    return (1/math.pi)*integr


def bes0dif(x):
    dif = -(besel(x - dh,0) - besel(x + dh,0))/(2*dh)
    return dif

b_1_x = np.arange(0,2*math.pi + 0.01,0.01)
b_1_y = []
for x in b_1_x:
    b_1_y.append(besel(x,1))

b_0_x = np.arange(0,2*math.pi + 0.01,0.01)
b_0_y = []
for x in b_0_x:
    b_0_y.append(bes0dif(x))


for i in range (0,len(b_0_x)):
    print(b_0_y[i] + b_1_y[i])

ax1.plot(b_1_x,b_1_y)

ax1.plot(b_0_x,b_0_y)

plt.show()
