<h1 style="text-align:center">Fonctions</h1>

<h2 style="text-align:center;background: #101080">READLINE</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char *readline (const char **prompt*);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Obtient une ligne d'un utilisateur avec l'edition	

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

Renvoie le contenue de la ligne lu.

<h2 style="text-align:center;background: #101080">RL_CLEAR_HISTORY</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

void rl_clear_history(void);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Supprime tout l'historique des textes lus par readline.

<h2 style="text-align:center;background: #101080">ADD_HISTORY</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

void add_history(char *str);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Ajoute *str* dans l'historique (accessible avec les fleches comme sur le terminal)

<h2 style="text-align:center;background: #101080">RL_ON_NEW_LINE</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

void rl_on_new_line(void);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Previent a la routine d'update qu'on est sur une nouvelle ligne (generalement apres avoir sorti une nouvelle ligne)

<h2 style="text-align:center;background: #101080">RL_REPLACE_LINE</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <readline/readline.h>

void rl_replace_line(const char *str, int clear_undo);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Remplace le contenu de la **ligne courante** par *str*.<br>
**str** : nouvelle ligne a mettre dans le buffer.<br>
**clear_undo** :
 - != 0 -> La pile d'annulation interne de readline est **effacee**.
 - == 0 -> L'operation est ajoutee a l'**historique des undo** (annulation possibles).

<h2 style="text-align:center;background: #101080">RL_REDISPLAY</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <readline/readline.h>

int rl_redisplay(void);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Force *readline* a **reafficher la ligne courante** sur l'ecran.<br>
- Inclut **prompt** + **contenu du buffer** de la ligne en cours d'edition.
- Souvent utiliser apres **rl_replace_line()**

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

**0**

<h2 style="text-align:center;background: #101080">ACCESS</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <unistd.h>

int access(const char *pathname, int mode);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Verifie les permissions d'un utilisateur sur un fichier (X_OK, W_OK), possible d'utiliser **|**

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0**<br>
En cas d'erreur : **-1 + errno** 

<h2 style="text-align:center;background: #101080">WAIT3 / WAIT4</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>

pid_t wait3(int *status, int options, struct rusage *rusage);
pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Similaire a waitpid(), mais renvoient en plus des informations sur l'**utilisation des ressources par le fils** dans la structure pointee par *rusage*.<br>
- **wait3()** : Attend n'importe qu'elle fils
- **wait4()** : Attend le/les fils choisie(s)

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

Comme waitpid()

<h2 style="text-align:center;background: #101080">SIGACTION</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <signal.h>

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact); 

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

**Examiner** et **modifier** l'action associee a un signal.

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0**
<br>En cas d'erreur : **Code d'erreur non nul**


<h2 style="text-align:center;background: #101080">PTHREAD_MUTEX_UNLOCK</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <pthread.h>

int pthread_mutex_unlock(pthread_mutex_t *mutex)

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Deverrouille *mutex*. Celui-ci est **suppose verrouille** (Sinon undefined behavior), et ce par le **meme thread** qui l'a verrouille.

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0**
<br>En cas d'erreur : **Code d'erreur non nul**


<h2 style="text-align:center;background: #101080">KILL</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <sys/types.h><br>
#include <signal.h>

int kill(pid_t pid, int sig);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

**Envoie un signal à un processus**  

  >**pid \> 0** -> Signal envoye **au processus indique par *pid***
  
  >**pid == 0** -> Signal envoye a **tous les processus appartenant au meme groupe que le processus appelant.**
  
  >**pid == -1** -> Signal envoye a **tous les processus auquels le processus appelant a la permission d'envoyer des signaux** (sauf PID 1 (init))
  
  >**pid < -1 ->** Signal envoye a **tous les processus du groupe dont l'id est *-pid***
  
  >**sig == 0 ->** Aucun signal n'est envoye mais **les conditions d'erreurs** sont verifiees; utile pour **verifier l'existence** d'un id de processus ou de groupe de processus.

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes (au moins 1 signal envoye) : **0**<br>
En cas d'echec : **-1** + **errno**

<h2 style="text-align:center;background: #101080">WAITPID</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <sys/wait.h>

pid_t waitpid(pid_t pid, int *status, int options); 

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

**Attend que le processus *pid* change d'etat.**

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **PID du fils** dont l'etat a change est renvoye ; si WHNOHANG etait specifie et qu'aucun fils specifie par *pid* n'a change d'etat, **0** est renvoye.<br>
En cas d'echec : **-1**

<h2 style="text-align:center;background: #be0000ff">SEMAPHORE</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #be0000ff; color: #be0000ff;">DESCRIPTION</h3>

sémaphore = mécanisme de **synchronisation** utilisé pour gérer l’accès à des ressources partagées entre **processus** (et éventuellement threads)

Un sémaphore repose sur un **compteur entier** représentant le nombre de ressources disponibles.

Un sémaphore peut être dans plusieurs états :
- Compteur > 0 : accès possible
- Compteur = 0 : accès bloqué (processus en attente)

Deux opérations atomiques :
- **P (wait)** : décrémente le compteur  
  → si le compteur devient négatif, le processus est **bloqué**
- **V (signal)** : incrémente le compteur  
  → réveille un processus en attente s’il y en a un

Contrairement au mutex :
- un sémaphore **n’a pas de notion de propriétaire**
- plusieurs processus peuvent accéder à la ressource simultanément (selon la valeur du compteur)

<h2 style="text-align:center;background: #101080">SEM_OPEN</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <fcntl.h>           /* Pour les constantes O_* */<br>
#include <sys/stat.h>        /* Pour les constantes « mode » */<br>
#include <semaphore.h>

sem_t *sem_open(const char *name, int oflag, mode_t mode, unsigned int value);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

**Initialiser et ouvrir un semaphore nomme.**<br> 
Le semaphore est identifie par *name*<br>
*oflag* -> **O_CREAT** | **O_EXCL**
*mode* -> Permissions a placer sur le nouveau semaphore.
*value* -> Valeur initiale du nouveau semaphore.

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **Adresse du nouveau semaphore**
En cas d'echec : **SEM_FAILED** + **errno**

<h2 style="text-align:center;background: #101080">SEM_OPEN</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <semaphore.h>

int sem_close(sem_t *sem);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

**Ferme et libere le semaphore *sem*.**

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0**
En cas d'echec : **-1** + **errno**

<h2 style="text-align:center;background: #101080">SEM_POST</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <semaphore.h>

int sem_post(sem_t *sem);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

**Incremente (deverouille) le semaphore *sem*.**<br>
Si a la suite de cet increment, sem value > 0 : un autre processus/thread qui attend (*sem_wait*) sera reveille et procedera au verrouillage du semaphore

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0**
En cas d'echec : **-1** + **errno**

<h2 style="text-align:center;background: #101080">SEM_WAIT</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <semaphore.h>

int sem_wait(sem_t *sem);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

**Decremente (verouille) le semaphore *sem*.**<br>
Si sem value > 0 : La decrementation s'effecture et la fonction revient *immediatement*.<br>
si sem value = 0 : L'appel bloque jusqu'a ce qu'il devienne disponible pour effectuer la decrementation (sem value > 0). **Ou alors** un gestionnaire de signaux interromp l'appel (kill). 

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0**
En cas d'echec : **-1** + **errno**

<h2 style="text-align:center;background: #101080">SEM_UNLICK</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <semaphore.h>

int sem_unlink(const char *name);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

**Supprime un semaphore nomme.**<br>
Supprime le semaphore reference par *name*.<br>
Le nom est immediatement supprime mais le semaphore est detruit une fois que tous les autres processus qui l'avaient ouvert l'ont ferme.

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0**
En cas d'echec : **-1** + **errno**