# Projet C - François MARTINEL
Code en langage C qui permet de générer des condensats (G) et de rechercher parmi une liste de condensats (L pour lookup).
## Installation:
```bash
git clone https://github.com/ms-martinel/c-projet
sudo apt-get update
sudo apt-get install -y build-essential libssl-dev make gcc
```
## Execution:
```bash
cd c-projet
make
./main
```

## Exemples de commandes:
### Pour Generate un tableau .t3c a partir d'une liste de mdp:
```bash
./main G -i list.txt -o output.t3c
```
### Pour Lookup a partir d'une table .t3c une liste de condensats:
```bash
./main L -t output.t3c -c condensats.txt
```
### Pour saisir les condensats au clavier:
```bash
./main L -t output.t3c
```

### Pour Generate un tableau .t3c a partir d'une liste de mdp avec choix de l'algo:
```bash
./main G -i list.txt -o output.t3c -a sha512
```
Pour le hachage: sha1, ripemd160, sha224, sha256, sha384, sha512, md5.