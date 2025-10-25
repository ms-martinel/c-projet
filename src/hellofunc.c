#include <stdio.h>
#include "hellomake.h"
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/crypto.h>

void helloWorld() {
    printf("Hello World!\n");
}

void printError(char * message) {
    printf("Erreur: %s", message);
}

const EVP_MD* choix(char *name) {
	if (strcmp(name, "sha1") == 0) {
		return EVP_sha1();
	} else if (strcmp(name, "ripemd160") == 0) {
		return EVP_ripemd160();
	} else if (strcmp(name, "sha224") == 0) {
		return EVP_sha224();
	} else if (strcmp(name, "sha256") == 0) {
		return EVP_sha256();
	} else if (strcmp(name, "sha384") == 0) {
		return EVP_sha384();
	} else if (strcmp(name, "sha512") == 0) {
		return EVP_sha512();
	} else if (strcmp(name, "md5") == 0) {
		return EVP_md5();
	}
	return NULL;
}

// https://wiki.openssl.org/index.php/EVP_Message_Digests
void digest_message(const unsigned char *message, size_t message_len, unsigned char **digest, unsigned int *digest_len, char *name) {
	EVP_MD_CTX *mdctx;
	const EVP_MD *hachage = choix(name);
	if(!hachage) {
		return;
	}
	if((mdctx = EVP_MD_CTX_new()) == NULL) return;
	if(1 != EVP_DigestInit_ex(mdctx, hachage, NULL)) return;
	if(1 != EVP_DigestUpdate(mdctx, message, message_len)) return;
	if((*digest = (unsigned char *)OPENSSL_malloc(EVP_MD_size(hachage))) == NULL) return;
	if(1 != EVP_DigestFinal_ex(mdctx, *digest, digest_len)) return;
	EVP_MD_CTX_free(mdctx);
}

int filtre(char *s) {
    int n = (int)strlen(s);
    while (n > 0 && (s[n-1] =='\n' ||s[n-1] == '\r')) {
		s[n-1] = '\0';
		n = n-1;
	}
    return n;
}

int generate(char *fichier, char *fichier_output, char* hachage) {
	FILE *fp = fopen(fichier, "r");
	if(!fp) {
		return 1;
	}

	FILE *fo = fopen(fichier_output, "w");
	if(!fo) {
		return 1;
	}

	printf("\nhachage utilise: %s", hachage);
	char ligne[1024];
	while(fgets(ligne, sizeof(ligne), fp)) {
		filtre(ligne);
		if (ligne[0] == '\0') continue;
		unsigned char *digest = NULL;
		unsigned int digest_len = 0;
		digest_message((unsigned char*)ligne, strlen(ligne), &digest, &digest_len, hachage);
		if(!digest) {
			fclose(fp);
			fclose(fo);
			return 1;
		}
		for(unsigned int i = 0; i<digest_len; i++) {
        	fprintf(fo, "%02x", digest[i]);
    	}
		fprintf(fo, "\t%s\n", ligne);
		OPENSSL_free(digest);
	}
	fclose(fp);
	fclose(fo);
	return 0;
}

Node* create_node(char *hash, char *valeur) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->condensat = strdup(hash);
    node->chaine = strdup(valeur);
    node->gauche = NULL;
	node->droite = NULL;
    return node;
}

Node* insert_node(Node *noeud, char *hash, char *valeur) { 
    if (!noeud) {
		return create_node(hash, valeur);
	}
    int calcul = strcmp(hash, noeud->condensat);
    if (calcul < 0) {
        noeud->gauche = insert_node(noeud->gauche, hash, valeur);
    } else if (calcul > 0) {
        noeud->droite = insert_node(noeud->droite, hash, valeur);
    } else {
        char *valid = strdup(valeur);
        if (valid) {
			free(noeud->chaine);
			noeud->chaine = valid;
		}
    }
    return noeud;
}

Node* find_node(Node *node, char *hash) {
    while (node) {
        int calcul = strcmp(hash, node->condensat);
        if (calcul == 0) {
			return node;
		}
        if (calcul < 0) {
            node = node->gauche;
		} else {
            node = node->droite;
        }
    }
    return NULL;
}

void free_node(Node *node) {
    if (!node) {
		return;
	}
    free_node(node->gauche);
    free_node(node->droite);
    free(node->condensat);
    free(node->chaine);
    free(node);
}

Node* load(char *fichier) {
	FILE *fp = fopen(fichier, "r");
	if(!fp) {
		return NULL;
	}
	Node *node = NULL;
	char ligne[1024];

	while(fgets(ligne, sizeof(ligne), fp)) {
		char *strip = strchr(ligne, '\t');
		if(!strip) {
			continue;
		}
		*strip = '\0';
		char *hash = ligne;
		char *valeur = strip+1;
		node = insert_node(node, hash, valeur);
	}
	fclose(fp);
	return node;
}

int lookup(char *fichier_t3c, char *cible) {
	Node *node = load(fichier_t3c);
	if(!node) {
		return 1;
	}

	FILE *c = fopen(cible, "r");
	if(!c) {
		free_node(node);
		return 1;
	}
	char ligne[1024];
	while(fgets(ligne, sizeof(ligne), c)) {
		filtre(ligne);
		Node *n = find_node(node, ligne);
		if(n) {
			printf("\nMot de passe trouve:\nHash: %s\nMDP: %s\n", n->condensat, n->chaine);
		}
	}
	fclose(c);
	free_node(node);
	return 0;
}

int lookup_entree(char *fichier_t3c) {
	Node *node = load(fichier_t3c);
	if(!node) {
		return 1;
	}
	char ligne[1024];
	while(fgets(ligne, sizeof(ligne), stdin)) {
		filtre(ligne);
		Node *n = find_node(node, ligne);
		if(n) {
			printf("\nMot de passe trouve:\nHash: %s\nMDP: %s\n", n->condensat, n->chaine);
		}
	}
	free_node(node);
	return 0;
}