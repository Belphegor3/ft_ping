# FT_PING

Qu'est ce que c'est ping?

Ping envoie un message d echo ICMP a un hote a distance. Quand l'hote recoit ce message, il copie le domaine de la requete dans un message de reponse a echo et la renvoie.

## ICMP (Internet Control Message Protocol)

Pour se renseigner sur le ICMP, il va falloir se tourner vers le [RFC 792](http://patrick.monassier.free.fr/rfc/rfc792.htm).  
On va plus particulierement s'interesser a la partie "Message d'écho et de réponse à écho" puisqu on ne va faire que ce qui est demande dans le sujet.  
Et heureusement parce que seul les messages d echo et les reponses d echo peuvent etre recu et envoye directement.
Par default le kernel ne permet pas les echnages de datagrammes ICMP pour les utilisateurs (meme root).
Normalement les distributions recentes le permettent et c est pour ca que le sujet requiert une distrib plutot recente (meme si debian 7 date de 2013).  

## Explications du graph du [RFC 792](http://patrick.monassier.free.fr/rfc/rfc792.htm)

![graph](image.png)

Type: indique le type de message ICMP, 0 pour la reponse d echo (hote) ou 8 pour un message d echo (quand on envoit le ping).   
Code: c est presque toujours 0 donc on mettra toujours 0.  
Checksum: Permet de verifier que le paquet n a pas ete corrompu avec un calcul special en inversant les bits grace a l operateur '~'.  
Identificateur: sert a reconnaitre nos paquets (donc juste un getpid).  
Numero de sequence: compteur qui augmente.  
Data: le contenu du paquet. Le serveur renvoit les memes donnees.  

## Precisions du man de socket 

Dans le man de socket:
- **int socket(int domain, int type, int protocol);**
- Normally only a single protocol exists to support a particular
       socket  **type** within a given protocol family, in which case protocol can
       be specified as 0.
- **SOCK_DGRAM**  and  **SOCK_RAW**  sockets allow sending of datagrams to corre‐
       spondents named in sendto(2) calls.  Datagrams are  generally  received
       with  recvfrom(2),  which  returns the next datagram along with the ad‐
       dress of its sender.


**SOCK_DGRAM** utilise le protocol UDP qui ne nous interesse pas pour ce projet.
On va donc utiliser **SOCK_RAW**.

| ARG | VALUE | MEANING |
| ------- | ------ | ---------------- |
| domain | AF_INET | USE IPv4 Protocol |
| type | SOCK_RAW | On construit nous meme le header ICMP et le payload[^1] |
| protocol | IP_PROTOICMP | Nous restreint a l utilisation des paquets IP qui contiennent des messages ICMP |














[^1]: payload signifie "charge utile". C est la partie du paquet qui contient les donnees reellements transportees, par opposition aux informations techniques de transport (header).