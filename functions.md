<h1 style="text-align:center">Fonctions</h1>

<h2 style="text-align:center; background: #101080; color: white; color: white">READLINE</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <stdio.h><br>
#include <readline/readline.h><br>
#include <readline/history.h><br>

char *readline (const char **prompt*);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Obtient une ligne d'un utilisateur avec l'edition

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

Renvoie le contenue de la ligne lu.

<h2 style="text-align:center;background: #101080; color: white">RL_CLEAR_HISTORY</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

void rl_clear_history(void);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Supprime tout l'historique des textes lus par readline.

<h2 style="text-align:center;background: #101080; color: white">ADD_HISTORY</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

void add_history(char *str);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Ajoute *str* dans l'historique (accessible avec les fleches comme sur le terminal)

<h2 style="text-align:center;background: #101080; color: white">RL_ON_NEW_LINE</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

void rl_on_new_line(void);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Previent a la routine d'update qu'on est sur une nouvelle ligne (generalement apres avoir sorti une nouvelle ligne)

<h2 style="text-align:center;background: #101080; color: white">RL_REPLACE_LINE</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <readline/readline.h>

void rl_replace_line(const char *str, int clear_undo);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Remplace le contenu de la **ligne courante** par *str*.<br>
**str** : nouvelle ligne a mettre dans le buffer.<br>
**clear_undo** :
 - != 0 -> La pile d'annulation interne de readline est **effacee**.
 - == 0 -> L'operation est ajoutee a l'**historique des undo** (annulation possibles).

<h2 style="text-align:center;background: #101080; color: white">RL_REDISPLAY</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <readline/readline.h>

int rl_redisplay(void);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Force *readline* a **reafficher la ligne courante** sur l'ecran.<br>
- Inclut **prompt** + **contenu du buffer** de la ligne en cours d'edition.
- Souvent utiliser apres **rl_replace_line()**

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

**0**

<h2 style="text-align:center;background: #101080; color: white">ACCESS</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <unistd.h>

int access(const char *pathname, int mode);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Verifie les permissions d'un utilisateur sur un fichier (X_OK, W_OK), possible d'utiliser **|**

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0**<br>
En cas d'erreur : **-1 + errno**

<h2 style="text-align:center;background: #101080; color: white">WAIT3 / WAIT4</h2>

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

<h2 style="text-align:center;background: #101080; color: white">SIGACTION</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <signal.h>

int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

**Examiner** et **modifier** l'action associee a un signal.

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0**<br>
En cas d'erreur : **-1**

<h2 style="text-align:center;background: #101080; color: white">SIGEMPTYSET</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <signal.h>

int sigemptyset(sigset_t *set);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Initialise un **ensemble de signaux** a vide.<br>
- **set** : Pointeur vers l'ensemble des signaux a intialiser.

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0**<br>
En cas d'erreur : **-1**

<h2 style="text-align:center;background: #101080; color: white">SIGADDSET</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <signal.h>

int sigaddset(sigset_t *set, int signo);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Ajoute un **signal specifique** a un **ensemble de signaux** a initialise.

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0**<br>
En cas d'erreur : **-1**

<h2 style="text-align:center;background: #101080; color: white">KILL</h2>

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

<h2 style="text-align:center;background: #101080; color: white">GETCWD</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <unistd.h>

char *getcwd(char *buf, size_t size);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

**pwd**

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **buf est renvoyé**<br>
En cas d'echec : **NULL + errno + buf undefined**

<h2 style="text-align:center;background: #101080; color: white">CHDIR</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <unistd.h>

int chdir(const char *path);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

**cd**

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0**<br>
En cas d'echec : **-1** + **errno**

<h2 style="text-align:center;background: #be0000ff; color: white">STRUCT STAT</h2>

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

<h2 style="text-align:center;background: #101080; color: white">STAT</h2>

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

<h2 style="text-align:center;background: #101080; color: white">LSTAT</h2>

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

<h2 style="text-align:center;background: #101080; color: white">FSTAT</h2>

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

<h2 style="text-align:center;background: #101080; color: white">UNLINK</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <unistd.h>

int unlink(const char *pathname);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

**Supprime *pathname*** si il n'est ouvert par aucun processus. Sinon **attend** que le fichier soit fermer pour le supprimer.

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0**<br>
En cas d'echec : **-1** + **errno**

<h2 style="text-align:center;background: #be0000ff; color: white">STRUCT DIR</h2>

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

<h2 style="text-align:center;background: #101080; color: white">OPENDIR</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <dirent.h>

DIR *opendir(const char *name);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Ouvre le repertoire *name*

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **Pointeur sur le flux repertoire**<br>
En cas d'echec : **NULL**

<h2 style="text-align:center;background: #101080; color: white">READDIR</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <dirent.h>

struct dirent *readdir(DIR *dirp);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Consulte le repertoire

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **Pointeur sur *struct dirent***<br>
En cas d'echec OU fin de repertoire : **NULL**

<h2 style="text-align:center;background: #101080; color: white">CLOSEDIR</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <dirent.h>

int closedir(DIR *dir);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Ferme le repertoire *dir*

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0***<br>
En cas d'echec : **-1** + **errno**

<h2 style="text-align:center;background: #101080; color: white">ISATTY</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <unistd.h>

int isatty(int fd);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Verifie si *fd* se rapporte a un terminal.

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

Est connecte a un terminal : **1***<br>
N'est pas connecte a un terminal : **0**

<h2 style="text-align:center;background: #101080; color: white">TTYNAME</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <unistd.h>

char *ttyname(int fd);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Obtient le nom du terminal associe a *fd*.

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **Nom du terminal***<br>
En cas d'echec : **NULL + errno**

<h2 style="text-align:center;background: #101080; color: white">TTYSLOT</h2>

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

<h2 style="text-align:center;background: #101080; color: white">IOCTL</h2>

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

<h2 style="text-align:center;background: #101080; color: white">GETENV</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <stdlib.h>

char *getenv(const char *name);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Lire une variable d'environnement.<br>
Rechercher *name* dans la liste des **variables d'environnement**

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **Pointeur sur la valeur correspondante**<br>
En cas d'echec : **NULL** si 0 correspondance

<h2 style="text-align:center;background: #be0000ff; color: white">STRUCT TERMIOS</h2>

*<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #be0000ff; color: #be0000ff;">struct termios</h3>*

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
      <td style="color:red;">tcflag_t</td>
      <td>c_iflag</td>
      <td style="color:#6a9955;">// modes d’entrée</td>
    </tr>
    <tr>
      <td style="color:red;">tcflag_t</td>
      <td>c_oflag</td>
      <td style="color:#6a9955;">// modes de sortie</td>
    </tr>
    <tr>
      <td style="color:red;">tcflag_t</td>
      <td>c_cflag</td>
      <td style="color:#6a9955;">// modes de contrôle</td>
    </tr>
    <tr>
      <td style="color:red;">tcflag_t</td>
      <td>c_lflag</td>
      <td style="color:#6a9955;">// modes locaux</td>
    </tr>
    <tr>
      <td style="color:red;">cc_t</td>
      <td>c_cc[NCCS]</td>
      <td style="color:#6a9955;">// caractères de contrôle</td>
    </tr>
	<tr>
      <td style="color:red;">speed_t</td>
      <td>c_ispeed</td>
      <td style="color:#6a9955;">// vitesse d’entrée</td>
    </tr>
	<tr>
      <td style="color:red;">speed_t</td>
      <td>c_ospeed</td>
      <td style="color:#6a9955;">// vitesse de sortie</td>
    </tr>
  </tbody>
</table>

Pour plus de details voir la [documentation](https://manpagesfr.free.fr/man/man3/termios.3.html)

<h2 style="text-align:center;background: #101080; color: white">TCSETATTR</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <termios.h>
#include <unistd.h>

int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Modifie les attributs du terminal ouvert par *fd*.<br>

<h4>Paramètres</h4>

- `fd` : Terminal concerne
- `optional_actions` :
	- `TCSANOW` — Immediatement
	- `TCSADRAIN` — Apres vidage des sorties en attente
	- `TCSAFLUSH` — Apres vidage des sorties et suppression des entrees en attente
- `termio_p` : Pointeur vers une structure `struct termios` contenant les nouveaux parametres<br>

Exemple : Activer ou desactiver l'echo des caracteres, configurer le mode canonique/ non canonique, etc.

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0**<br>
En cas d'echec : **-1** + **errno**

<h2 style="text-align:center;background: #101080; color: white">TCGETATTR</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <termios.h>

int tcgetattr(int fd, struct termios *termios_p);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Recupere les parametres du terminal associe a un descripteur de fichier **fd**.

<h4>Paramètres</h4>

- `fd` doit referencer un **terminal** (souvent STDIN / STDOUT / STDERR)
- `termios_p` pointe vers une structure **struct termios** que la fonction va remplir avec la configuration actuelle du terminal.

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0**<br>
En cas d'echec : **-1** + **errno**

<h2 style="text-align:center;background: #101080; color: white">TGETENT</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <termcap.h>

int tgetent(char *bp, const char *name);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Charge la description termcap d'un terminal donne et la rend disponible pour les autres fonctions termcap (tgetstr, tgetnum, tgetflag, etc...).

<h4>Paramètres</h4>

- `bp` est un **buffer optionnel** (peut etre **NULL**) ou la description du terminal peut etre stockee.
- `name` est le **nom du terminal** (souvent la variable d'environnement **TERM**, ex : *"xterm-256color"*)

!!! a `tgetent` doit être appelé une seule fois, au début

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **1**<br>
En cas d'echec : **0 ou -1**

<h2 style="text-align:center;background: #101080; color: white">TGETFLAG</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <termcap.h>

int tgetflag(const char *id);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Permet de savoir si le terminal courant supporte une **capacite booleene**.

<h4>Paramètre</h4>

- `id` identifiant a 2 caracteres de la capacite **termcap** (ex : `am`, `bs`, `km`) -> Voir significations avec mister GPT

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **1**<br>
En cas d'echec : **0**

<h2 style="text-align:center;background: #101080; color: white">TGETNUM</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <termcap.h>

int tgetnum(const char *id);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Permet de recuperer une **capacite numerique** du terminal courant.<br>

Une capacite numerique correspond a une **valeur entiere** decrivant une propriete du terminal :
- Nombre de colonne
- Nombre de ligne
- Délais, tailles, limites diverses

<h4>Paramètre</h4>

- `id` identifiant a 2 caracteres de la capacite numerique (ex : `co`, `li`, `it`) -> Voir significations avec mister GPT

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **1**<br>
En cas d'echec : **0**

<h2 style="text-align:center;background: #101080; color: white">TGETSTR</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <termcap.h>

char *tgetstr(const char *id, char **area);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Permet de recuperer une **capacite sous forme de chaîne de caractères**, generalement une **séquence d’échappement** utilisee pour controler le terminal.

Exemple de ce que ca retourne :
- Effacer l'ecran
- Deplacer le curseur
- Activer un mode d'affichage
- Reinitialiser des attributs

<h4>Paramètres</h4>

- `id` identifiant a 2 caracteres de la capacite numerique (ex : `cl`, `cm`, `so`, `me`) -> Voir significations avec mister GPT
- `area` **zone de stockage** :
	- `area == NULL` : La chaine retourner est stocke dans une zone statique interne.
	Simple, mais non sur si tu appelles tgetstr plusieurs fois
	- `area != NULL` : `tgetstr` copie la chaine daans `area`.

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **char \***<br>
En cas d'echec : **NULL**

<h2 style="text-align:center;background: #101080; color: white">TGOTO</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <termcap.h>

char *tgoto(const char *cap, int col, int row);

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Permet de constuire une **sequence de deplacement du curseur**, a partir de la capacite termcap `cm`.

En gros :
- `cm` décrit **comment** déplacer le curseur
- `tgoto` insère les **coordonnées** (colonne, ligne)
- Le résultat est une chaine **chaîne prête à être envoyée au terminal**

!!! a `tgoto` ne fait **rien** tout seul, elle genere une chaine qu'il faut utiliser apres avec `write` ou `tputs`.

<h4>Paramètres</h4>

- `cap` : chaine generer par `tgetstr("cm", ...)`
- `col` : position horizontal (X)
- `row` : position vertical (Y)

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **char \***<br>
En cas d'echec : **NULL**

<h2 style="text-align:center;background: #101080; color: white">TPUTS</h2>

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">PROTOTYPE</h3>

#include <termcap.h>

int tputs(const char *str, int affcnt, int (*putc)(int));

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">DESCRIPTION</h3>

Affiche une séquence de contrôle termcap sur le terminal, en respectant les délais éventuels nécessaires au matériel.

<h4>Paramètres</h4>

- `str`
	- Chaine a afficher
	- Generalement retourner par `tgetstr` ou `tgoto`
- `affcnt`
	- Nombre de ligne affecter par la commande (**1** 90% du temps)
	- Sert a calculer les delais
- `putc`
	- Pointeur vers une fonction qui ecrit un caractere. (**ft_putchar** probablement)

<h3 style="padding: 0.5em 3em; background: #aaaaaaff; border: solid 2px #101080; color: #101080;">VALEUR RENVOYEE</h3>

En cas de succes : **0**<br>
En cas d'echec : **-1**