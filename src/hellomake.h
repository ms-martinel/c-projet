#include <openssl/evp.h>

void printError(char * message);
void digest_message(const unsigned char *message, size_t message_len, unsigned char **digest, unsigned int *digest_len, char *name);
int generate(char *fichier, char *fichier_output, char *hachage);

typedef struct Node {
    char *condensat;
    char *chaine;
    struct Node *gauche;
    struct Node *droite;
} Node;
const EVP_MD* choix(char *name);
int filtre(char *s);
Node* create_node(char *hash, char *valeur);
Node* insert_node(Node *noeud, char *hash, char *valeur);
Node* find_node(Node *node, char *hash);
void free_node(Node *node);
Node* load(char *fichier);
int lookup(char *fichier_t3c, char *cible);
int lookup_entree(char *fichier_t3c);