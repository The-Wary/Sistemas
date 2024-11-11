#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
    char *addr = sbrk(0);  
    sbrk(4096);  

   
    if (mprotect(addr, 1) == -1) {
        printf("mprotect falló\n");
        exit(1);
    }

    
    char *ptr = addr;
    printf("Intentando escribir en la página protegida...\n");
    *ptr = 'A';  

   
    printf("Error: Escritura en página protegida no falló como se esperaba.\n");

  
    if (munprotect(addr, 1) == -1) {
        printf("munprotect falló\n");
        exit(1);
    }

    
    printf("Intentando escribir en la página desprotegida...\n");
    *ptr = 'B';  
    printf("Escritura exitosa en la página desprotegida, valor: %c\n", *ptr);

    exit(0);
}
