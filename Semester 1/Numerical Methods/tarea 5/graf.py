import matplotlib.pyplot as plt

# Listas para almacenar las coordenadas x e y de los puntos
x_coords = []
y_coords = []

# Abre el archivo de texto en modo lectura
with open("puntos.txt", "r") as archivo:
    # Lee línea por línea del archivo
    for linea in archivo:
        # Divide la línea en componentes (asumiendo que los valores están separados por espacios)
        datos = linea.strip().split()
        
        # Verifica que haya al menos dos valores
        if len(datos) >= 2:
            x = float(datos[0])
            y = float(datos[1])
            
            # Agrega los valores a las listas
            x_coords.append(x)
            y_coords.append(y)
        else:
            print("Línea no válida:", linea.strip())

# Grafica los puntos
plt.scatter(x_coords, y_coords, label="Puntos", color="b")
plt.xlabel("n[umero de nodos")
plt.ylabel("Temperatura central")
plt.title("Gráfico de tempertura")
plt.legend()
plt.grid(True)

# Muestra el gráfico
plt.show()
