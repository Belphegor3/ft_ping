#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

int main(int ac, char **av){
    if (ac == 1){
        printf("ping: usage error: Destination address required\n");
        return EXIT_FAILURE;
    }
    if (ac > 2){
        //! le vrai ping marche pas avec plusieurs arg
    }
}