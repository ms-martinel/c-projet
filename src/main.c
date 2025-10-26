#include <stdio.h>
#include "hellomake.h"
#include <string.h>
#include <openssl/evp.h>
#include <openssl/crypto.h>

int main(int argc, char * argv[]) {
    if(argc < 2 || strcmp(argv[1], "help") == 0 || strcmp(argv[1], "h") == 0 || strcmp(argv[1], "-h") == 0) {
        printf("Arguments invalides. Exemples valides:\nPour Generate un tableau .t3c a partir d'une liste de mdp:\n./main G -i list.txt -o output.t3c\nPour Lookup a partir d'une table .t3c une liste de condensats:\n./main L -t output.t3c -c condensats.txt\nPour saisir les condensats au clavier:\n./main L -t output.t3c\nOption -a pour choix algo avec: sha1, ripemd160, sha224, sha256, sha384, sha512, md5 (ex: -a sha256)\n");
        return 1;
    }
    if(strcmp(argv[1], "G") == 0) {
        char* dictionnaire = NULL;
        char* output = NULL;
        char* hachage = "sha256";
        for(int i=2; i<argc; i++) {
            if(strcmp(argv[i], "-i") == 0 && i+1<argc) {
                dictionnaire = argv[++i];
            } else if(strcmp(argv[i], "-o") == 0 && i+1<argc) {
                output = argv[++i];
            } else if(strcmp(argv[i], "-a") == 0 && i+1<argc) {
                hachage = argv[++i];
            } else {
                printf("\nMauvais arguments, avec G, utilisez -i FICHIER (liste mdp) et -o FICHIER (output)\n");
                return 1;
            }
        }
        if(dictionnaire == NULL || output == NULL) {
            printf("\nMauvais arguments, avec G, utilisez -i FICHIER (liste mdp) et -o FICHIER (output)\n");
            return 1;
        }
        return generate(dictionnaire, output, hachage);
    } else if(strcmp(argv[1], "L") == 0) {
        char* fichier_t3c = NULL;
        char* condensats = NULL;
        for(int i=2; i<argc; i++) {
            if(strcmp(argv[i], "-t") == 0 && i+1<argc) {
                fichier_t3c = argv[++i];
            } else if(strcmp(argv[i], "-c") == 0 && i+1<argc) {
                condensats = argv[++i];
            } else {
                printf("\nMauvais arguments, avec F, utilisez -t FICHIER (fichier t3c) voire -c FICHIER (condensats)\n");
                return 1;
            }
        }
        if(fichier_t3c == NULL) {
            printf("\nMauvais arguments, avec L, utilisez -t FICHIER (fichier t3c) voire -c FICHIER (condensats)\n");
            return 1;
        } else if(condensats == NULL) {
            printf("\nVous n'avez pas passé de fichier condensats en options, saisissez-les:\n");
            return lookup_entree(fichier_t3c);
        }
        return lookup(fichier_t3c, condensats);
    } else {
        printf("\nErreur\n");
        return 1;
    }  
    return 0;
}