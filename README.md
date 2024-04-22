# $ HCFI_{rttp} $
Implementación de algoritmo hill climbing first improvement para resolver instancias del Relaxed Traveling Tournament Problem.

# Instrucciones de compilación:
- Para compilar el programa ejecutar:
```
make
```

# Instrucciones de ejecución
- Para ejecutar el programa:
```
./RTTP instances/<nombre_archivo.txt> <iteraciones> <restarts>
```
- **Ejemplo** para ejecutar para instancia "data4.txt" con 500 iteraciones y 5 restarts:
```
./RTTP instances/data4.txt 500 5
```

# Output del programa
- El output del programa muestra por pantalla detalles de la solución obtenida.
- El programa crea un archivo "results.txt" el cual contiene la solución y detalles de esta.

# Consideraciones
- El archivo test.cpp corresponde a experimentos, por lo que no es compilado.

# Cómo contribuir
Cualquier forma de contribución es muy bienvenida.

## Pull Requests
En este proyecto se trabaja con GitFlow, a continuación se muestra como contribuir con un PR:

- Crear una copia del repositorio haciendo un fork.
- Clonar el fork del repositorio .
- Crear una rama desde la rama develop:
    - Para nuevas funcionalidades, el nombre de la rama debe cumplir con la estructura "feature/< branch-name >".
    - Para arreglo de bugs, el nombre de la rama debe cumplir con la estructura "bug/< branch-name >".
- Hacer los cambios en el código.
- Hacer un commit con los cambios.
- Crear un pull request para hacer un merge con la rama develop del repositorio original.
- Luego de esto se revisará tu pull request.git

## Issues
Una buena forma de contribuir al proyecto es enviar una issue detallada cuando encuentres un problema. También puedes crear una issue para proponer una nueva feature.