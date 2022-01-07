# AD_AlgoritmosAvanzados
Proyectos realizados para Análisis y Diseño de Algorítmos Avanzados

# Algoritmos Utilizados
Act 1
- Algorítmo de Búsqueda KMP
- Algorítmo de Manacher para Longest Palindromic Substring
- Algorítmo de Longest Common Substring
Act 2
- Algorítmo de Floyd Warshall para Grafo Óptimo
- Algoritmo del Travelling Salesman
- Algortimo de Flord Fulkerson, implementación de Edmonds-Karps

--

## Act 1
Un programa en C++ que lea 5 archivos de texto (de nombre fijo, no se piden al usuario) que contienen exclusivamente caracteres del 0 al 9, caracteres entre A y F y saltos de línea
     transmission1.txt
     transmission2.txt
     mcode1.txt
     mcode2.txt
     mcode3.txt

Los archivos de transmision contienen caracteres de texto que representan el envío de datos de un dispositivo a otro.
Los archivos mcodex.txt representan código malicioso que se puede encontrar dentro de una transmisión.

El programa debe analizar si el contenido de los archivos mcode1.txt, mcode2.txt y mcode3.,txt están contenidos en los archivos transmission1.txt y transmission2.txt y desplegar un true o false si es que las secuencias de chars están contenidas o no. En caso de ser true, muestra true, seguido de exactamente un espacio, seguido de la posición en el archivo de transmissiónX.txt donde inicia el código de mcodeY.txt

Suponiendo que el código malicioso tiene siempre código "espejeado" (palíndromos de chars), sería buena idea buscar este tipo de código en una transmisión. El programa después debe buscar si hay código "espejeado" dentro de los archivos de transmisión. (palíndromo a nivel chars, no meterse a nivel bits). El programa muestra en una sola linea dos enteros separados por un espacio correspondientes a la posición (iniciando en 1) en donde inicia y termina el código "espejeado" más largo (palíndromo) para cada archivo de transmisión. Puede asumirse que siempre se encontrará este tipo de código.

Finalmente el programa analiza que tan similares son los archivos de transmisión, y debe mostrar la posición inicial y la posición final (iniciando en 1) del primer archivo en donde se encuentra el substring más largo común entre ambos archivos de transmisión

input
     nada, solamente deben existir los 5 archivos en la misma ruta donde se ejecuta el programa    

output
  parte 1
     (true | false) si es que el archivo transmission1.txt contiene el código (secuencia de chars) contenido en el archivo mcode1.txt    
     (true | false) si es que el archivo transmission1.txt contiene el código (secuencia de chars) contenido en el archivo mcode2.txt
     (true | false) si es que el archivo transmission1.txt contiene el código (secuencia de chars) contenido en el archivo mcode3.txt
     (true | false) si es que el archivo transmission2.txt contiene el código (secuencia de chars) contenido en el archivo mcode1.txt
     (true | false) si es que el archivo transmission2.txt contiene el código (secuencia de chars) contenido en el archivo mcode2.txt
     (true | false) si es que el archivo transmission2.txt contiene el código (secuencia de chars) contenido en el archivo mcode3.txt
  parte2
     posiciónInicial posiciónFinal (para archivo de transmisión1)
     posiciónInicial posiciónFinal (para archivo de transmisión2)
  parte3
      posiciónInicial posiciónFinal (de substring común más largo entre archivos de transmisión)
      
      
## Act 2
Escribe en C++ un programa que ayude a una empresa que quiere incursionar en los servicios de Internet respondiendo a la situación problema 2.

El programa debe:

1. leer un archivo de entrada que contiene la información de un grafo representado en forma de una matriz de adyacencias con grafos ponderados
El peso de cada arista es la distancia en kilómetros entre colonia y colonia, por donde es factible meter cableado.

El programa debe desplegar cuál es la forma óptima de cablear con fibra óptica conectando colonias de tal forma que se pueda compartir información entre cuales quiera dos colonias.

2. Debido a que las ciudades apenas están entrando al mundo tecnológico, se requiere que alguien visite cada colonia para ir a dejar estados de cuenta físicos, publicidad, avisos y notificaciones impresos. por eso se quiere saber ¿cuál es la ruta más corta posible que visita cada colonia exactamente una vez y al finalizar regresa a la colonia origen?
El programa debe desplegar la ruta a considerar, tomando en cuenta que la primera colonia se le llamará A, a la segunda B, y así sucesivamente

3. El programa también debe leer otra matriz cuadrada de N x N datos que representen la capacidad máxima de transmisión de datos entre colonias. Como estamos trabajando con ciudades con una gran cantidad de campos electromagnéticos, que pueden generar interferencia, ya se hicieron estimaciones que están reflejadas en esta matriz.

La empresa quiere conocer el flujo máximo de información del nodo inicial (A) al nodo final (n). Esto debe desplegarse también en la salida estándar.

Por último

4. Teniendo en cuenta la ubicación geográfica de varias "centrales" a las que se pueden conectar nuevas casas, la empresa quiere contar con una forma de decidir, dada una nueva contratación del servicio, cuál es la central más cercana geográficamente a esa nueva contratación. No necesariamente hay una central por cada colonia. Se pueden tener colonias sin central, y colonias con más de una central.

Entrada:
Un número entero N que representa el número de colonias en la ciudad (entrada por consola; cin >>)

Leer archivo que contenga las siguientes matrices separadas por un salto de línea:
- matriz cuadrada de N x N que representa el grafo con las distancias en kilómetros entre las colonias de la ciudad
- matriz cuadrada de N x N que representa las capacidades máximas de flujo de datos entre colonias

Lista de N pares ordenados de la forma (A,B) que representan la ubicación en un plano coordenado de las centrales (entrada por consola; cin >>)

Coordenadas de nueva contratación (entrada por consola; cin >>)

Salida:
1. Forma de cablear las colonias con fibra
(lista de arcos de la forma (A,B))
2. ruta a seguir por el personal que reparte correspondencia, considerando inicio y fin en al misma colonia.
3. valor de flujo máximo de información del nodo inicial al nodo final
4. Coordenadas de central más cercana (Representado de la forma (x,y))


Ejemplo de entrada:

cin >> 4

lectura de archivo

0 16 45 32
16  0 18 21
45 18  0  7
32 21  7  0

0 48  12  18
0  0 42 32
0 46  0 56
0 0 0  0

cin >> 4

cin >>

200 500
300 100
480 130
520 480

350 200

 

Ejemplo de salida:

1.
Forma óptima de cablear con fibra óptica las colonias:
(A, B)
(A, D)
(B, A)
(B, C)
(B, D)
(C, B)
(C, D)
(D, A)
(D, B)
(D, C)

2.
La ruta más corta posible que visita cada colonia exactamente una vez y al finalizar regresa a la colonia origen:
A-B, B-C, C-D, D-A 
16, 18, 7, 32 = 73

3.
El flujo máximo de A a D es de 78

4.
La central más cercana está ubicada en (300, 100)
