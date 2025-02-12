# Patrón de Numeros Primos en Coordenadas Polares (OpenGL)

![OpenGL](https://img.shields.io/badge/OpenGL-1.0+-green)
![GLUT](https://img.shields.io/badge/GLUT-3.7+-blue)

información que ayudo al desarrollo del software:

[Why do prime numbers make these spirals?](https://www.youtube.com/watch?v=EK32jo7i5LQ&t=151s&ab_channel=3Blue1Brown).

[Plotting Prime Numbers](https://jaketae.github.io/study/prime-spirals/).

Visualizador interactivo de patrones numéricos usando OpenGL. Carga datos desde archivos binarios y los representa en coordenadas polares con capacidades de zoom y navegación. Si bien se penso para graficar numeros primos se podria graficar cualquier conjunto numerico real en coordenadas polares con este programa.

## Características principales
- 🎮 Renderizado en tiempo real con OpenGL.
- 🔍 Control de zoom con teclado (`+`/`-`) y mouse (clic izquierdo/derecho).
- ⛵ Navegación con teclas WASD.
- 📊 Conversión automática de datos numéricos a coordenadas polares.
- 🪃 Gestión automática de memoria.
- 🖥️ Proyección ortográfica adaptable a la resolución de pantalla.

## Requisitos del sistema
- Compilador C++ compatible con C++11.
- Bibliotecas OpenGL y GLUT instaladas.
- Windows (por el uso de `windows.h`).

## Instalación y uso

1. **Clona el repositorio:**
   ```bash
   git clone https://github.com/sebolla-gif/Visualizador-de-datos-en-coordenadas-polares-OpenGL-.git
   ```
2. **Compila el proyecto:**
   Ajusta el nombre del archivo fuente si es necesario (en este ejemplo se asume que el código se encuentra en `main.cpp`):
   ```bash
   g++ main.cpp -o main -lGL -lGLU -lglut
   ```
3. **Ejecuta el programa:**
   ```bash
   ./main
   ```
### Ejecucion directa:

El repositorio cuenta con una carpeta `bin`, la misma contiene un ejecutable `main.exe` y los archivos binarios que contienen los numeros primos `400k`,`1M`,`10M`.

### Controles:
- **Zoom:** `+` / `-` o clic izquierdo (zoom in) y clic derecho (zoom out).
- **Movimiento:** Teclas `W`, `A`, `S`, `D` para desplazar la vista.
- **Salir:** Tecla `ESC`.

## Estructura del código

El código principal está organizado de la siguiente manera:

```cpp
// Estructura para almacenar los datos polares
struct PolarData {
    unsigned long int* numbers;  // Datos numéricos crudos
    unsigned long count;         // Cantidad de elementos
    float* vertices;             // Vértices precalculados (x, y)
};

// Pipeline principal:
// 1. LoadPolarData() -> Carga y convierte datos desde el archivo binario.
// 2. display()       -> Renderizado de los puntos en OpenGL.
// 3. keyboard/mouse  -> Gestión de interacción (zoom, desplazamiento y salida).
// 4. Cleanup()       -> Liberación de recursos y memoria.
```

## Archivos de datos

El repositorio contiene los datos de los primeros 400k, 1 millon y 10 millones de numeros primos almacenados en archivos binarios.

Los archivos fueros creados con [Generador de Números Primos](https://github.com/sebolla-gif/NumerosPrimos).

Si se compila el programa se debe modificar la ubicacion del archivo binario a donde este guardado.

Ej:
```
FILE* f = fopen("C:\\Users\\sebav\\Desktop\\PatronOpenGL\\400k.bin", "rb");
```
En caso de ejecutar el `main.exe` se debe asegurar que el binario este en la raiz. (El `main.exe` esta pensado para usar el archivo de `400k`)

El archivo debe contener un array de `unsigned long int` en orden crudo. Se recomienda un tamaño de aproximadamente 400,000 elementos para visualizar un patrón interesante.

## Mejoras futuras
- Implementar VBOs para mejorar el rendimiento del renderizado. (Para esto se debe trabajar con versiones mas actuales de OGL)
- Añadir soporte para múltiples archivos de datos. (Ej .txt)
- Desarrollar una interfaz gráfica para la selección de archivos. (QT)
- Incluir modos de visualización alternativos. (3D)
- Soporte para múltiples plataformas. (Linux, Mac, etc)

## Licencia

MIT License © 2025 Sebastián Vaccaro


