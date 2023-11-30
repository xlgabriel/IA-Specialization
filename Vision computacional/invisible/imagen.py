import cv2
import numpy as np

# Definir el rango de colores que se detectarán (en este caso, azul celeste)
lower_blue = np.array([90, 50, 50])  # Valor mínimo de azul, verde y rojo
upper_blue = np.array([130, 255, 255])  # Valor máximo de azul, verde y rojo

# Iniciar la cámara (0 representa la cámara predeterminada)
cap = cv2.VideoCapture(0)

# Capturar la imagen de fondo sin el objeto que deseas hacer invisible
background = cv2.imread('gagaga.jpg')  # Reemplaza con tu imagen de fondo
background = cv2.resize(background, (640, 480))  # Ajusta el tamaño según tu cámara

while True:
    # Capturar un cuadro de la cámara
    ret, frame = cap.read()

    if not ret:
        break

    # Convertir el cuadro de la cámara a espacio de color HSV
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Crear una máscara para el rango de colores azul celeste
    mask = cv2.inRange(hsv, lower_blue, upper_blue)

    # Invertir la máscara para seleccionar el color azul celeste
    mask_inverted = cv2.bitwise_not(mask)

    # Tomar la parte de la imagen de la cámara que no es azul celeste
    result = cv2.bitwise_and(frame, frame, mask=mask_inverted)

    # Tomar la parte de la imagen de fondo que coincide con el color azul celeste en la cámara
    background_masked = cv2.bitwise_and(background, background, mask=mask)

    # Combinar ambas partes para obtener el efecto deseado
    final_result = cv2.add(result, background_masked)

    # Mostrar el resultado
    cv2.imshow('Invisibility Cloak', final_result)

    # Romper el bucle si se presiona la tecla 'q'
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Liberar la cámara y cerrar todas las ventanas
cap.release()
cv2.destroyAllWindows()
