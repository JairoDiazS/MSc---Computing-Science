import matplotlib.pyplot as plt
import math

def exponencial(k):
    n=10**k
    return ((1+(1/n))**n)

for i in range(1,20):
    plt.scatter(i, exponencial(i),color="red")
    
plt.scatter(i, exponencial(i),color="red", label="n aprox")
plt.axhline(math.exp(1),linewidth=0.8,color="green",label="Cte de Euler")
plt.legend(loc="center right")


plt.show()