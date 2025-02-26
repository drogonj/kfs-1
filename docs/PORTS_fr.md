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

Les ports d'E/S et leurs fonctions spécifiques:


| **Adresse(s)**     | **Type de périphérique**                                                                                                                |
| :------------------- | ------------------------------------------------------------------------------------------------------------------------------------------- |
| **0x00 - 0x1F**    | Premier contrôleur DMA (généralement la puce 8237 A-5, souvent utilisé pour les disquettes).                                          |
| **0x20 - 0x3F**    | Premier contrôleur d'interruptions programmables (PIC) (généralement la puce 8259A, souvent configuré comme PIC maître).             |
| **0x40 - 0x5F**    | Temporisateur programmable (généralement la puce 8254).                                                                                 |
| **0x60 - 0x6F**    | Clavier PS/2 (toujours la puce 8042).                                                                                                     |
| **0x70 - 0x7F**    | Horloge temps réel (RTC) et masque NMI.                                                                                                  |
| **0x80 - 0x9F**    | Registres de page DMA (généralement la puce 74LS612).                                                                                   |
| **0xA0 - 0xBF**    | Deuxième contrôleur d'interruptions programmables (PIC) (généralement la puce 8259A, souvent configuré comme PIC esclave).           |
| **0xC0 - 0xDF**    | Deuxième contrôleur DMA (généralement la puce 8237 A-5).                                                                              |
| **0xE9**           | Souvent utilisé pour le "Port 0xE9 Hack". Utilisé dans certains émulateurs pour envoyer du texte directement à la console de l'hôte. |
| **0xF0 - 0xFF**    | Coprocesseur mathématique (généralement la puce 80287).                                                                                |
| **0x100 - 0x10F**  | Sélection d'options programmables (POS) (utilisé dans les systèmes PS/2).                                                              |
| **0x110 - 0x1EF**  | Canal d'entrée/sortie système.                                                                                                          |
| **0x140 - 0x15F**  | Contrôleur hôte SCSI secondaire.                                                                                                        |
| **0x170 - 0x177**  | Contrôleur de disque PATA secondaire (souvent utilisé pour les lecteurs CD/DVD ou les disques durs de sauvegarde).                      |
| **0x1F0 - 0x1F7**  | Contrôleur de disque PATA primaire (presque toujours utilisé pour le disque dur principal / disque de boot).                            |
| **0x200 - 0x20F**  | Port de jeu.                                                                                                                              |
| **0x210 - 0x217**  | Unité d'extension.                                                                                                                       |
| **0x220 - 0x233**  | Carte son Sound Blaster et la plupart des autres cartes son.                                                                              |
| **0x278 - 0x27F**  | Port parallèle 3.                                                                                                                        |
| **0x280 - 0x29F**  | Écran LCD sur Wyse 2108 PC (paramètre d'usine par défaut de SMC Elite).                                                                |
| **0x2B0 - 0x2DF**  | Contrôle d'affichage alternatif pour l'EGA (Enhanced Graphics Adapter).                                                                  |
| **0x2E8 - 0x2EF**  | Port série 4 (si disponible, souvent COM 4).                                                                                             |
| **0x2E1**          | Adaptateur GPIB/IEEE-488 0.                                                                                                               |
| **0x2E2 - 0x2E3**  | Acquisition de données.                                                                                                                  |
| **0x2F8 - 0x2FF**  | Port série 2 (si disponible, souvent COM 2).                                                                                             |
| **0x300 - 0x31F**  | Carte prototype.                                                                                                                          |
| **0x300 - 0x31F**  | Interfaces réseau Ethernet compatibles Novell NE1000.                                                                                    |
| **0x300 - 0x31F**  | Interface réseau Ethernet AMD Am7990, IRQ=5.                                                                                             |
| **0x320 - 0x323**  | Interface de disque dur ST-506 et compatibles.                                                                                            |
| **0x330 - 0x331**  | Unité de traitement MIDI MPU-401 sur la plupart des cartes son.                                                                          |
| **0x340 - 0x35F**  | Contrôleur hôte SCSI primaire.                                                                                                          |
| **0x370 - 0x377**  | Contrôleur de disquette secondaire.                                                                                                      |
| **0x378 - 0x37F**  | Port parallèle 2.                                                                                                                        |
| **0x380 - 0x38C**  | Adaptateur SDLC (Secondary Binary Synchronous Data Link Control).                                                                         |
| **0x388 - 0x389**  | Carte de synthétiseur musical AdLib.                                                                                                     |
| **0x3A0 - 0x3A9**  | Adaptateur SDLC primaire (Primary Binary Synchronous Data Link Control).                                                                  |
| **0x3B0 - 0x3BB**  | Contrôle d'affichage pour l'adaptateur monochrome (MDA). IBM VGA et prédécesseurs directs.                                             |
| **0x3BC - 0x3BF**  | Port parallèle 1 sur la carte MDA. IBM VGA et prédécesseurs directs.                                                                   |
| **0x3C0 - 0x3CF**  | Contrôle d'affichage pour l'EGA (Enhanced Graphics Adapter). IBM VGA et prédécesseurs directs.                                         |
| **0x3D0 - 0x3DF**  | Contrôle d'affichage pour l'adaptateur graphique couleur (CGA). IBM VGA et prédécesseurs directs.                                      |
| **0x3E8 - 0x3EF**  | Port série 3 (si disponible, souvent COM 3).                                                                                             |
| **0x3F0 - 0x3F7**  | Contrôleur de disquette primaire. Contrôleur IDE primaire (disque esclave) (3F6–3F7h).                                                 |
| **0x3F8 - 0x3FF**  | Port série 1 (si disponible, souvent COM1).                                                                                              |
| **0xCF8 – 0xCFC** | Espace de configuration PCI.                                                                                                              |

---

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
