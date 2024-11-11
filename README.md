## Informe 
1. Introducción
En esta tarea, se modificó el sistema operativo xv6-RISC-V para agregar dos nuevas llamadas al sistema: mprotect() y munprotect(). Estas funciones permiten marcar una región de la memoria de un proceso como solo lectura (read-only) y desmarcarla para permitir lectura/escritura (read/write), respectivamente.

El objetivo principal es evitar que un programa sobrescriba accidentalmente su propia sección de código o datos sensibles, implementando así una forma básica de protección de memoria.

2. Descripción de las Llamadas al Sistema
2.1 mprotect(void *addr, int len)
Descripción: Marca una región de memoria, comenzando en la dirección addr y de longitud len, como de solo lectura (read-only).
Funcionamiento: Esta llamada al sistema recorre las páginas de la tabla de paginación del proceso y modifica el bit de escritura (W) de cada entrada de tabla de página (PTE) para deshabilitar la escritura.
Retorno: Devuelve 0 en caso de éxito y -1 en caso de error.
2.2 munprotect(void *addr, int len)
Descripción: Revertir la protección de solo lectura en una región de memoria, permitiendo lectura y escritura (read/write).
Funcionamiento: Similar a mprotect(), recorre las páginas de la tabla de paginación y habilita el bit de escritura (W) para las PTEs afectadas.
Retorno: Devuelve 0 en caso de éxito y -1 en caso de error.
3. Implementación
La implementación de ambas funciones se realizó en los archivos kernel/vm.c y kernel/sysproc.c. A continuación, se describe el código y las consideraciones tomadas.

3.1 Función mprotect()
3.2 Función munprotect()
3.3 Llamadas al Sistema en sysproc.c
3.4 Manejo de Errores
Los siguientes casos se manejaron adecuadamente:

Dirección inválida (addr): Si la dirección proporcionada no es válida o no pertenece al espacio de direcciones del proceso, la llamada devuelve -1.
Longitud inválida (len): Si la longitud es menor o igual a 0, la llamada también devuelve -1.
Página no válida: Si alguna de las páginas no es válida (bit PTE_V deshabilitado), la función retorna error.
5. Conclusiones
La implementación de mprotect() y munprotect() en xv6-RISC-V permite proteger regiones de memoria, evitando modificaciones accidentales o maliciosas.
El manejo de errores garantiza que las llamadas al sistema devuelvan -1 en caso de direcciones inválidas o fallos en la validación de páginas.
Las pruebas demostraron que la protección de memoria funciona correctamente y que las regiones de solo lectura son efectivas para prevenir escrituras.
