# Projet C - François MARTINEL
## Installation:
```bash
git clone https://github.com/ms-martinel/c-projet
sudo apt-get update
sudo apt-get install libssl-dev
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