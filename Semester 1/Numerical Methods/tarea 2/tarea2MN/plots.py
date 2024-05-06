import numpy as np
import matplotlib.pyplot as plt
import sympy as sp

x = sp.Symbol('x')

def f1(x):
    return (x**4 + 3*x**2 -2)

def f2(x):
    return (np.sqrt((2-x**4)/3) -x)

def f3(x):
    return (pow(2-(3*pow(x,2)),1/4) -x)

def f4(x):
    return (((2-pow(x,4))/(3*x)) -x)

def f5(x):
    return (pow(((2-3*pow(x,2))/x),1/3) -x)


X = np.linspace(-1, 1.2);

fig, (ax1,ax2) = plt.subplots(1,2)
fig1, (ax3,ax4) = plt.subplots(1,2)

ax1.plot(X,[f1(y) for y in X],label="f(x)")
ax1.plot(X,[f2(y) for y in X],label="x-g_a(x)")

ax1.legend()
ax1.hlines(0,-1,1,"black",linewidth=0.5,linestyle='--')

ax2.plot(X,[f1(y) for y in X],label="f(x)")
ax2.plot(X,[f3(y) for y in X],label="x-g_b(x)")

ax2.legend()
ax2.hlines(0,-1,1,"black",linewidth=0.5,linestyle='--')

ax3.plot(X,[f1(y) for y in X],label="f(x)")
ax3.plot(X,[f4(y) for y in X],label="x-g_c(x)")

ax3.legend()
ax3.hlines(0,-1,1,"black",linewidth=0.5,linestyle='--')

ax4.plot(X,[f1(y) for y in X],label="f(x)")
ax4.plot(X,[f5(y) for y in X],label="x-g_d(x)")

ax4.legend()
ax4.hlines(0,-1,1,"black",linewidth=0.5,linestyle='--')

# plt.show()

y1 = sp.sqrt((2-x**4)/3)
y2 = pow(2-(3*pow(x,2)),1/4)
y3 = ((2-pow(x,4))/(3*x))
y4 = pow(((2-3*pow(x,2))/x),1/3)

y11 = sp.diff(y1,x)
y22 = sp.diff(y2,x)
y33 = sp.diff(y3,x)
y44 = sp.diff(y4,x)

p1 = sp.plot(y11,(x,-1,1),label="holafdasdfsfs");
p2 = sp.plot(y22,(x,-1,1));
p3 = sp.plot(y33,(x,-1,1));
p4 = sp.plot(y44,(x,-1,1));

sp.plotting.PlotGrid(2,2,p1,p2,p3,p4)

p1.legend(1)


