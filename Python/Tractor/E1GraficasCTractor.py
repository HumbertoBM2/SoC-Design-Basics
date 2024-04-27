# Equipo 1
# Entregable de reto 1. Visualización gráfica de comportamiento del tractor

# Humberto Barrera 
# Catalina Isabel Muñoz 
# Erick Giovani Campos 
# Mauricio Zavala 

# Código de python para generar datos de forma aleatoria, referentes a velocidad angular,
# radio de la rueda y relación de la transmisión de un tractor con la finalidad de calcular
# las revoluciones por minuto en el mismo. Los datos son almacenados en un archivo CSV y
# posteriormente se visualizan con gráficas.


# Importar módulos y librerías a utilizar
import random
from math import pi
import pandas as pd
import matplotlib.pyplot as plt


# Función para calcular las RPM del tractor
# omega = velocidad angular de la rueda
# radioR = Radio de la rueda
# relacionT = Relación de la transmisión
def calcularRPM(omega, radioR, relacionT):
    RPM = (omega * 60) / (2 * pi * radioR * relacionT)
    return RPM


# Función para calcular las RPM del tractor variando la velocidad angular
def generarMuestraVarOmega(numDatos):

    # Se crea un arreglo vacio para almacenar los valores
    muestraVarOmega = []

    # Ciclo for usado para crear n numero de datos
    for _ in range(numDatos):
        # Se generan valores aleatorios para la omega en un rango de 5 a 15
        omega = random.uniform(5, 15)
        # Se establecen como constantes los valores del radio y la relación
        radioR = 0.5
        relacionT = 10
        # Se calculan las RPM con los valores de la iteración actual
        RPM = calcularRPM(omega, radioR, relacionT)
        # Se agregan los datos al arreglo
        muestraVarOmega.append([omega, radioR, relacionT, RPM])

    # Se guardan los valores en un archivo CSV usando pandas
    df = pd.DataFrame(
        # Se especifica que se guardaran los datos del arreglo
        muestraVarOmega,
        # Se especifica el orden de guardado y el nombre de cada columna
        columns=[
            "Velocidad angular de la rueda (rad/s)",
            "Radio de la rueda (m)",
            "Relacion de transmision",
            "RPM",
        ],
    )
    # Se especifica en nombre del archivo con la muestra
    df.to_csv("muestraTractorVarOmega.csv", index=False)
    return df


# Función para calcular las RPM del tractor variando el radio de la rueda
def generarMuestraVarRadioR(numDatos):

    # Se crea un arreglo vacio para almacenar los valores
    muestraVarRadioR = []

    # Ciclo for usado para crear n numero de datos
    for _ in range(numDatos):
        # Se establece como constante el valor de la velocidad angular
        omega = 10
        # Se generan valores aleatorios para el radio de la rueda en un rango de 0.2 a 0.8
        radioR = random.uniform(0.2, 0.8)
        # Se establece como constante el valor de la relacionT
        relacionT = 10
        # Se calculan las RPM con los valores de la iteración actual
        RPM = calcularRPM(omega, radioR, relacionT)
        # Se agregan los datos al arreglo
        muestraVarRadioR.append([omega, radioR, relacionT, RPM])

    # Se guardan los valores en un archivo CSV usando pandas
    df = pd.DataFrame(
        # Se especifica que se guardaran los datos del arreglo
        muestraVarRadioR,
        # Se especifica el orden de guardado y el nombre de cada columna
        columns=[
            "Velocidad angular de la rueda (rad/s)",
            "Radio de la rueda (m)",
            "Relacion de transmision",
            "RPM",
        ],
    )
    # Se especifica en nombre del archivo con la muestra
    df.to_csv("muestraTractorVarRadioR.csv", index=False)
    return df


# Función para visualizar los datos con gráficas
def generarGraficas(muestraVarOmega, muestraVarRadioR):

    # Se crea una figura con dos subgráficas
    fig, axs = plt.subplots(1, 2, figsize=(12, 6))
    fig.suptitle("Comportamiento del tractor", fontsize=16)

    colors = ["blue", "green"]

    # Se crea la primera subgráfica que muestra la relación entre la velocidad angular y las RPM
    axs[0].scatter(
        muestraVarOmega["Velocidad angular de la rueda (rad/s)"],
        muestraVarOmega["RPM"],
        color=colors[0],
        marker="o",
        s=50,
        alpha=0.7,
    )
    axs[0].set_title("Velocidad angular vs RPM", fontsize=14)
    axs[0].set_xlabel("Velocidad angular de la rueda (rad/s)", fontsize=12)
    axs[0].set_ylabel("RPM", fontsize=12)

    # Se crea la segunda subgráfica que muestra la relación entre el radio de la rueda y las RPM
    axs[1].scatter(
        muestraVarRadioR["Radio de la rueda (m)"],
        muestraVarRadioR["RPM"],
        color=colors[1],
        marker="o",
        s=50,
        alpha=0.7,
    )
    axs[1].set_title("Radio de la rueda vs RPM", fontsize=14)
    axs[1].set_xlabel("Radio de la rueda (m)", fontsize=12)
    axs[1].set_ylabel("RPM", fontsize=12)
    plt.tight_layout()
    plt.show()


# Función principal del código
if __name__ == "__main__":

    # Número de datos a generar
    numDatos = 200

    # Generar muestras variando omega y el radioR
    muestraVarOmega = generarMuestraVarOmega(numDatos)
    print(f"Archivo muestraTractorVarOmega.csv generado con {numDatos} datos.")
    muestraVarRadioR = generarMuestraVarRadioR(numDatos)
    print(f"Archivo muestraTractorVarRadioR.csv generado con {numDatos} datos.")

    # Generar las gráficas correspondientes
    generarGraficas(muestraVarOmega, muestraVarRadioR)
