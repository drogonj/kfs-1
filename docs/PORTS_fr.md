### Comprendre les ports, les registres et les fonctions d'E/S en x86

---

#### **1. Introduction aux ports d'E/S**

Dans l'architecture x86, les ports d'entrée/sortie (I/O ports) sont utilisés pour établir une communication entre le processeur et les périphériques matériels. Ces ports permettent de lire ou d'écrire des données pour contrôler des dispositifs tels que le clavier, l'écran, les disques, et d'autres composants essentiels.

Chaque périphérique est assigné à un ensemble spécifique de **ports d'E/S** identifiés par des adresses numériques. Ces ports sont utilisés via des instructions spécifiques du processeur (`in` et `out`).

---

#### **2. Les instructions `in` et `out`**

Les instructions `in` et `out` sont conçues pour effectuer des opérations de lecture/écriture sur un port d'E/S.

* **Instruction `in` :** Elle permet de lire une valeur depuis un port vers un registre processeur.
  * Exemple : Lire la valeur d'un registre associé à un périphérique.
  * Syntaxe générale : `in <registre_dest>, <port>`.
* **Instruction `out` :** Elle permet d'envoyer une valeur depuis un registre vers un port d'E/S.
  * Exemple : Écrire une commande ou une donnée vers un périphérique.
  * Syntaxe générale : `out <port>, <registre_source>`.

Ces instructions sont souvent utilisées ensemble pour interagir avec des périphériques complexes.

---

#### **3. Liste des ports et registres associés**

Les ports d'E/S et leurs fonctions spécifiques :


| **Port (hex)** | **Nom / Description**                       | **Utilisation**                                                                                                                         |
| ---------------- | --------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------------- |
| **0x00**       | N/A                                         | Port réservé                                                                                                                          |
| **0x01**       | **Keyboard Data Register**                  | Données reçues du clavier (ne sert qu'au PC XT et plus anciens, rarement utilisé sur les systèmes modernes)                         |
| **0x02**       | **Keyboard Status Register**                | Statut du clavier (rarement utilisé sur les systèmes modernes)                                                                        |
| **0x03**       | **COM1 Data Register**                      | Données série pour le port COM1                                                                                                       |
| **0x04**       | **COM1 Interrupt Enable Register**          | Activation des interruptions pour COM1                                                                                                  |
| **0x05**       | **COM1 Line Control Register**              | Contrôle de la ligne série pour COM1                                                                                                  |
| **0x06**       | **COM1 Modem Control Register**             | Contrôle du modem pour COM1                                                                                                            |
| **0x07**       | **COM1 Line Status Register**               | Statut de la ligne série pour COM1                                                                                                     |
| **0x08**       | **COM1 Modem Status Register**              | Statut du modem pour COM1                                                                                                               |
| **0x09**       | **Free (available for peripherals)**        | Réservé pour d'autres périphériques                                                                                                 |
| **0x0A**       | **COM2 Data Register**                      | Données série pour le port COM2                                                                                                       |
| **0x0B**       | **COM2 Interrupt Enable Register**          | Activation des interruptions pour COM2                                                                                                  |
| **0x0C**       | **COM2 Line Control Register**              | Contrôle de la ligne série pour COM2                                                                                                  |
| **0x0D**       | **COM2 Modem Control Register**             | Contrôle du modem pour COM2                                                                                                            |
| **0x0E**       | **COM2 Line Status Register**               | Statut de la ligne série pour COM2                                                                                                     |
| **0x0F**       | **COM2 Modem Status Register**              | Statut du modem pour COM2                                                                                                               |
| **0x10**       | **Printer Port Data Register**              | Données pour l'impression (LPT1)                                                                                                       |
| **0x11**       | **Printer Port Status Register**            | Statut du port d'impression (LPT1)                                                                                                      |
| **0x12**       | **Printer Port Control Register**           | Contrôle du port d'impression (LPT1)                                                                                                   |
| **0x13**       | **Free (available for peripherals)**        | Réservé pour d'autres périphériques                                                                                                 |
| **0x14**       | **LPT2 Data Register**                      | Données pour l'impression (LPT2)                                                                                                       |
| **0x15**       | **LPT2 Status Register**                    | Statut du port d'impression (LPT2)                                                                                                      |
| **0x16**       | **LPT2 Control Register**                   | Contrôle du port d'impression (LPT2)                                                                                                   |
| **0x17**       | **Free (available for peripherals)**        | Réservé pour d'autres périphériques                                                                                                 |
| **0x20**       | **Master PIC Command Register (ICW1)**      | Commande d'initialisation pour le PIC maître                                                                                           |
| **0x21**       | **Master PIC Data Register (ICW2)**         | Données d'initialisation pour le PIC maître (vecteur de départ)                                                                      |
| **0x22**       | **Slave PIC Command Register (ICW1)**       | Commande d'initialisation pour le PIC esclave                                                                                           |
| **0x23**       | **Slave PIC Data Register (ICW2)**          | Données d'initialisation pour le PIC esclave (vecteur de départ)                                                                      |
| **0x24**       | **Master PIC Data Register (ICW3)**         | Commande de configuration pour le PIC maître (connexion du PIC esclave)                                                                |
| **0x25**       | **Slave PIC Data Register (ICW3)**          | Commande de configuration pour le PIC esclave (indique quel est l'ID de l'esclave)                                                      |
| **0x26**       | **Master PIC Data Register (ICW4)**         | Commande de configuration pour le PIC maître (mode de fin d'interruption automatique)                                                  |
| **0x27**       | **Slave PIC Data Register (ICW4)**          | Commande de configuration pour le PIC esclave (mode de fin d'interruption automatique)                                                  |
| **0x28**       | **System CMOS/RTC (Real-Time Clock)**       | Registre pour lire/écrire dans l'horloge temps réel et la mémoire CMOS                                                               |
| **0x2F**       | **Free for peripherals**                    | Réservé pour d'autres périphériques                                                                                                 |
| **0x40**       | **Programmable Interval Timer (PIT)**       | Commandes du temporisateur programmable (PIT), utilisé pour gérer les délais, le timer system et les interruptions de périodicité. |
| **0x41**       | **Programmable Interval Timer (PIT)**       | Données du temporisateur programmable (PIT).                                                                                           |
| **0x60**       | **Keyboard Controller Command Register**    | Envoi de commandes au contrôleur du clavier.                                                                                           |
| **0x61**       | **Keyboard Controller Data Register**       | Données reçues du contrôleur du clavier.                                                                                             |
| **0x64**       | **Keyboard Controller Command Register**    | Commandes au contrôleur du clavier.                                                                                                    |
| **0x65**       | **Keyboard Controller Status Register**     | Statut du contrôleur du clavier (indique si le clavier est prêt à recevoir des données).                                            |
| **0x70**       | **CMOS/RTC (Read/Write Register)**          | Lecture ou écriture dans les registres de la mémoire CMOS (configuration de l'heure, date et paramètres systèmes)                   |
| **0x71**       | **CMOS/RTC (Read/Write Register)**          | Lire ou écrire dans les registres CMOS (stockage des configurations systèmes)                                                         |
| **0x80-0x8F**  | **DMA Controller 1 (Direct Memory Access)** | Configuration du premier contrôleur DMA pour le transfert direct de mémoire sans intervention du processeur.                          |
| **0xA0**       | **Slave PIC Command Register (ICW1)**       | Commande d'initialisation pour le PIC esclave                                                                                           |
| **0xA1**       | **Slave PIC Data Register (ICW2)**          | Données d'initialisation pour le PIC esclave (vecteur de départ)                                                                      |
| **0xC0**       | **DMA Controller 2**                        | Configuration du second contrôleur DMA                                                                                                 |
| **0xC1**       | **DMA Controller 2**                        | Données pour le second contrôleur DMA                                                                                                 |
| **0xC2**       | **DMA Controller 2**                        | Registre de commande pour le second contrôleur DMA                                                                                     |
| **0xC3**       | **DMA Controller 2**                        | Registre d'état du second contrôleur DMA                                                                                              |
| **0xC4**       | **Free for peripherals**                    | Réservé pour d'autres périphériques                                                                                                 |
| **0xF0-0xF7**  | **Math Coprocessor (FPU)**                  | Registres du coprocesseur mathématique (FPU) (pour les opérations en virgule flottante)                                               |
| **0xFF**       | **N/A**                                     | Réservé                                                                                                                               |

#### **4. Fonctionnement avec les registres VGA**

Les ports VGA (ports 0x3D4 et 0x3D5) sont utilisés pour interagir avec les registres internes du contrôleur vidéo. Le port 0x3D4 sert à **sélectionner un registre** , tandis que le port 0x3D5 est utilisé pour **lire ou écrire la valeur de ce registre sélectionné** .

##### **Étapes typiques :**

1. **Sélection du registre** : On écrit le numéro du registre voulu (par exemple,`0x0A`,`0x0E`, etc.) dans le port 0x3D4.
2. **Lire ou écrire la valeur** :
   * Une lecture via le port 0x3D5 permet de récupérer la valeur actuelle du registre.
   * Une écriture sur le port 0x3D5 permet de modifier cette valeur.

---

#### **5. Exemple avec le curseur VGA**

Pour contrôler la position du curseur sur l'écran :

* Les registres 0x0E et 0x0F contiennent les parties haute et basse de la position du curseur.
* Pour positionner le curseur, on sélectionne successivement ces registres via 0x3D4 et on écrit les nouvelles valeurs via 0x3D5.
* Pour lire la position actuelle, on utilise les mêmes étapes mais avec une instruction de lecture (lecture sur 0x3D5 après avoir sélectionné le registre avec 0x3D4).

---

#### **6. Clavier et ports associés**

Le port 0x60 est utilisé pour récupérer les données envoyées par le clavier, tandis que le port 0x64 contrôle les opérations associées au clavier.

* **Port 0x60** : Permet de lire le scan code de la touche pressée ou d'envoyer des données au contrôleur clavier.
* **Port 0x64** : Sert principalement à envoyer des commandes pour configurer le clavier ou à interroger son statut.

---

#### **7. Notes importantes**

1. **Privilèges requis** : Les instructions `in` et`out` ne peuvent être exécutées que depuis le mode superviseur (ring 0).
2. **Registres modifiés** : Les registres utilisés pour transmettre les données (`AX`,`DX`, etc.) sont modifiés après exécution.
3. **Timing** : Certains périphériques nécessitent un délai entre deux opérations. Par exemple, après une écriture sur le port 0x64, il peut être nécessaire d'attendre avant de lire le port 0x60.

---

#### **8. Ressources complémentaires**

* **Intel 80386 Programmer's Reference Manual** : Référence technique complète sur l'architecture x86.
* **OSDev Wiki** : Documentation communautaire sur les ports et le développement de systèmes d'exploitation.
