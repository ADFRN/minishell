<h1 style="text-align:center">Fonctions</h1>

<h2 style="text-align:center;background: #101080">READLINE</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <stdio.h><br>
#include <readline/readline.h><br>
#include <readline/history.h><br>

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

#include <sys/types.h><br>
#include <sys/time.h><br>
#include <sys/resource.h><br>
#include <sys/wait.h><br>

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

En cas de succes : **0**<br>
En cas d'erreur : **-1**

<h2 style="text-align:center;background: #101080">SIGEMPTYSET</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <signal.h>

int sigemptyset(sigset_t *set);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Initialise un **ensemble de signaux** a vide.<br>
- **set** : Pointeur vers l'ensemble des signaux a intialiser.

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0**<br>
En cas d'erreur : **-1**

<h2 style="text-align:center;background: #101080">SIGADDSET</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <signal.h>

int sigaddset(sigset_t *set, int signo);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Ajoute un **signal specifique** a un **ensemble de signaux** a initialise.

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0**<br>
En cas d'erreur : **-1**

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

<h2 style="text-align:center;background: #101080">GETCWD</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <unistd.h>

char *getcwd(char *buf, size_t size);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

**pwd**

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **buf est renvoyé**<br>
En cas d'echec : **NULL + errno + buf undefined**

<h2 style="text-align:center;background: #101080">CHDIR</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <unistd.h>

int chdir(const char *path);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

**cd**

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0**<br>
En cas d'echec : **-1** + **errno**

<h2 style="text-align:center;background: #be0000ff">STRUCT sSTAT</h2>

*<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #be0000ff; color: #be0000ff;">struct stat</h3>*

<table>
  <thead>
    <tr>
      <th>Type</th>
      <th>Nom</th>
      <th>Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="color:red;">dev_t</td>
      <td>st_dev</td>
      <td style="color:#6a9955;">// ID du périphérique contenant le fichier</td>
    </tr>
    <tr>
      <td style="color:red;">ino_t</td>
      <td>st_ino</td>
      <td style="color:#6a9955;">// numéro d'inode</td>
    </tr>
    <tr>
      <td style="color:red;">mode_t</td>
      <td>st_mode</td>
      <td style="color:#6a9955;">// mode (permissions et type)</td>
    </tr>
    <tr>
      <td style="color:red;">nlink_t</td>
      <td>st_nlink</td>
      <td style="color:#6a9955;">// nombre de liens physiques</td>
    </tr>
    <tr>
      <td style="color:red;">uid_t</td>
      <td>st_uid</td>
      <td style="color:#6a9955;">// propriétaire</td>
    </tr>
    <tr>
      <td style="color:red;">gid_t</td>
      <td>st_gid</td>
      <td style="color:#6a9955;">// groupe</td>
    </tr>
    <tr>
      <td style="color:red;">dev_t</td>
      <td>st_rdev</td>
      <td style="color:#6a9955;">// périphérique spécial (si fichier spécial)</td>
    </tr>
    <tr>
      <td style="color:red;">off_t</td>
      <td>st_size</td>
      <td style="color:#6a9955;">// taille du fichier en octets</td>
    </tr>
    <tr>
      <td style="color:red;">blksize_t</td>
      <td>st_blksize</td>
      <td style="color:#6a9955;">// taille optimale des blocs pour I/O</td>
    </tr>
    <tr>
      <td style="color:red;">blkcnt_t</td>
      <td>st_blocks</td>
      <td style="color:#6a9955;">// nombre de blocs alloués</td>
    </tr>
    <tr>
      <td style="color:red;">time_t</td>
      <td>st_atime</td>
      <td style="color:#6a9955;">// date du dernier accès</td>
    </tr>
    <tr>
      <td style="color:red;">time_t</td>
      <td>st_mtime</td>
      <td style="color:#6a9955;">// date de la dernière modification</td>
    </tr>
    <tr>
      <td style="color:red;">time_t</td>
      <td>st_ctime</td>
      <td style="color:#6a9955;">// date du dernier changement de l’inode</td>
    </tr>
  </tbody>
</table>

<h2 style="text-align:center;background: #101080">STAT</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <sys/stat.h><br>
#include <sys/types.h>

int stat(const char *pathname, struct stat *statbuf);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

**Stock les informations** du fichier/repertoire *pathname* dans *statbuf*<br>
Si *pathname* est un **lien symbolique** : retourne les informations **du lien symbolique lui-meme**

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0**<br>
En cas d'echec : **-1** + **errno**

<h2 style="text-align:center;background: #101080">LSTAT</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <sys/types.h><br>
#include <sys/stat.h><br>
#include <unistd.h>

int lstat(const char *pathname, struct stat *statbuf);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Stock les informations du fichier/repertoire **pathname** dans *statbuf*.<br>
Si *pathname* est un **lien symbolique** : retourne les informations **du fichier cible**

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0**<br>
En cas d'echec : **-1** + **errno**

<h2 style="text-align:center;background: #101080">FSTAT</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <sys/types.h><br>
#include <sys/stat.h><br>
#include <unistd.h><br>

int fstat(int fd, struct stat *statbuf);


<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Stock les informations d'un fichier **deja ouvert**, identifie par *fd*, dans *statbuf*.<br>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0**<br>
En cas d'echec : **-1** + **errno**

<h2 style="text-align:center;background: #101080">UNLINK</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <unistd.h>

int unlink(const char *pathname);   

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

**Supprime *pathname*** si il n'est ouvert par aucun processus. Sinon **attend** que le fichier soit fermer pour le supprimer.

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0**<br>
En cas d'echec : **-1** + **errno**

<h2 style="text-align:center;background: #be0000ff">STRUCT DIR</h2>

*<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #be0000ff; color: #be0000ff;">struct dirent</h3>*

<table>
  <thead>
    <tr>
      <th>Type</th>
      <th>Nom</th>
      <th>Description</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="color:red;">ino_t</td>
      <td>d_ino</td>
      <td style="color:#6a9955;">// numéro d'inode</td>
    </tr>
    <tr>
      <td style="color:red;">off_t</td>
      <td>d_off</td>
      <td style="color:#6a9955;">// offset dans le répertoire</td>
    </tr>
    <tr>
      <td style="color:red;">unsigned short</td>
      <td>d_reclen</td>
      <td style="color:#6a9955;">// longueur de cette structure</td>
    </tr>
    <tr>
      <td style="color:red;">unsigned char</td>
      <td>d_type</td>
      <td style="color:#6a9955;">// type de fichier</td>
    </tr>
    <tr>
      <td style="color:red;">char</td>
      <td>d_name[]</td>
      <td style="color:#6a9955;">// nom de l'entrée</td>
    </tr>
  </tbody>
</table>


<h2 style="text-align:center;background: #101080">OPENDIR</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <dirent.h>

DIR *opendir(const char *name);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Ouvre le repertoire *name*

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **Pointeur sur le flux repertoire**<br>
En cas d'echec : **NULL**

<h2 style="text-align:center;background: #101080">READDIR</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <dirent.h>

struct dirent *readdir(DIR *dirp);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Consulte le repertoire

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **Pointeur sur *struct dirent***<br>
En cas d'echec OU fin de repertoire : **NULL**

<h2 style="text-align:center;background: #101080">CLOSEDIR</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <dirent.h>

int closedir(DIR *dir);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Ferme le repertoire *dir*

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0***<br>
En cas d'echec : **-1** + **errno**

<h2 style="text-align:center;background: #101080">ISATTY</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <unistd.h>

int isatty(int fd);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Verifie si *fd* se rapporte a un terminal.

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

Est connecte a un terminal : **1***<br>
N'est pas connecte a un terminal : **0**

<h2 style="text-align:center;background: #101080">TTYNAME</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <unistd.h>

char *ttyname(int fd);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Obtient le nom du terminal associe a *fd*.

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **Nom du terminal***<br>
En cas d'echec : **NULL + errno**

<h2 style="text-align:center;background: #101080">TTYSLOT</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <unistd.h>

int ttyslot(void);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Retourne le numero du terminal associe a **stdin**<br>
Ce numero correspond a l'entree dans `/etc/ttys` ou `/dev/ttyX`<br>
**Determine quel terminal est utilise par le processus courant** 

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

**\>= 0** : Numero de slot du terminal<br>
**-1** : Erreur (aucun terminal associe a **stdin**)

<h2 style="text-align:center;background: #101080">IOCTL</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <sys/ioctl.h>

int ioctl(int d, int requête, ...);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Permet de **controler les peripheriques**.<br>
Fonction **generique** qui permet d'envoyer des **commandes specifiques a un peripherique ou a un fichier special**<br>
- **fd** : Descripteur de fichier ouvert
- **reques** : Numero de commande specifique au peripherique.
- **Argument optionnel** : Depend de la commande

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **>= 0** selon la commande<br>
En cas d'echec : **-1** + **errno**

<h2 style="text-align:center;background: #101080">GETENV</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <stdlib.h>

char *getenv(const char *name);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Lire une variable d'environnement.<br>
Rechercher *name* dans la liste des **variables d'environnement**

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **Pointeur sur la valeur correspondante**<br>
En cas d'echec : **NULL** si 0 correspondance

<h2 style="text-align:center;background: #101080">TCSETATTR</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <termios.h>
#include <unistd.h>

int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Modifie les attributs du terminal ouvert par *fd*.<br>
- `fd` : Terminal concerne
- `optional_actions` :
	- `TCSANOW` — Immediatement
	- `TCSADRAIN` — Apres vidage des sorties en attente
	- `TCSAFLUSH` — Apres vidage des sorties et suppression des entrees en attente
- `termio_p` : Pointeur vers une structure `struct termios` contenant les nouveaux parametres<br>

La structure `struct termios` contient des champs pour :
- Modes d'entree (`c_iflag`)
- Modes de sortie (`c_oflag`)
- Modes de controle (`c_cflag`)
- Modes locaux (`c_lflag`)
- Caracteres speciaux (`c_cc`)

Exemple : Activer ou desactiver l'echo des caracteres, configurer le mode canonique/ non canonique, etc.

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0**<br>
En cas d'echec : **-1** + **errno**