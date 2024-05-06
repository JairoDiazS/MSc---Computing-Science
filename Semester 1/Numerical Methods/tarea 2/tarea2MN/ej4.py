import math
import sympy as sp

def pol(x):
    return 1000000*math.exp(x)+(435000/x)*(math.exp(x)-1)

x = sp.Symbol('x')

y = (1000000*sp.exp(x))+(435000/x)*(sp.exp(x)-1)-1564000

sp.plot(y,(x,-0.5,0.5))