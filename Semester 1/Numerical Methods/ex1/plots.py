import matplotlib.pyplot as plt

# Listas para almacenar los datos del archivo
x_values = []
y_values = []

# Leer datos del archivo
with open("datos.txt", "r") as file:
    for line in file:
        values = line.strip().split("\t")  # Cambia "\t" por "," si los datos están separados por comas
        x_values.append(float(values[0]))
        y_values.append(float(values[1]))

# Crear un gráfico de dispersión
plt.figure(figsize=(10, 6))
plt.scatter(x_values, y_values, marker='o', color='b', label='Datos')

# Configuración del gráfico
plt.title('Aproximacion numerica del numero de euler (e)')
plt.xlabel('valor de k (10^k)')
plt.ylabel('aproximacion e')
plt.grid(True)
plt.legend()

# Mostrar el gráfico
plt.show()
