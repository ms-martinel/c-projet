#include <stdio.h>
#include <hellomake.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/crypto.h>

int main() {
    helloWorld();
    int g = generate("list.txt", "output.t3c");
    if(g != 0) {
        printf("\nErreur Generate");
    }

    int l = lookup("output.t3c", "condensats.txt");
    if(l != 0) {
        printf("\nErreur Lookup");
    }
    
    return 0;
}