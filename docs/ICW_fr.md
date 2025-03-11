### ICW : **Initialization Command Word**

Les **ICW (Initialization Command Words)** sont des commandes utilisées pour configurer et initialiser les contrôleurs d'interruption programmables (**PIC** , notamment le 8259A) au démarrage du système. Ces commandes définissent le comportement du PIC, les priorités des interruptions, et d'autres aspects essentiels à la gestion des interruptions.

Le PIC 8259A nécessite une séquence de 4 commandes ICW (parfois 2 ou 3 selon la configuration) pour être correctement initialisé.

---

#### **Les quatre ICW**

1. **ICW1** : Déclenche la séquence d'initialisation et définit les caractéristiques de base du PIC.
   * Le PIC bascule en mode d'initialisation après avoir reçu cette commande.
   * ICW1 est envoyé au **port de commande** du PIC (0x20 pour le maître, 0xA0 pour l'esclave).
2. **ICW2** : Définit la base des vecteurs d'interruptions.
   * Les vecteurs sont utilisés pour identifier les routines d'interruption associées aux IRQ.
   * Par exemple, si la base est 0x20 (32 en décimal), l'IRQ 0 correspondra au vecteur d'interruption 32.
3. **ICW3** : Configure la relation entre le PIC maître et ses esclaves (utilisée uniquement dans un environnement cascade).
   * Pour le **PIC maître** : indique sur quelle IRQ le PIC esclave est connecté.
   * Pour le **PIC esclave** : spécifie l'identifiant (ID) attribué par le maître.
4. **ICW4** : Définit les modes avancés de fonctionnement du PIC, comme le mode entièrement imbriqué, le mode bufferisé, et l'AEOI (Automatic End of Interrupt).

---

#### **Description des bits des ICW**

##### **ICW1 (port 0x20 ou 0xA0)** :


| Bits | Signification                                                                                                                                                                                                                                            |
| ------ | :--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 0    | Si 1, activer les fonctionnalités de l'ICW4                                                                                                                                                                                                             |
| 1    | Si 1, mode à un seul PIC ; si 0, mode en cascade<br />. Le système utilise plusieurs PICs en cascade (connecter les PICs esclaves aux maitres afin de doubler le nombre d'IRQs pouvant etre gerees, IRQ 0-7 pour le maitre et IRQ 8-15 pour l'esclave) |
| 2    | Si 1, Interval d'adresse d'appels a 4 bits ; si 0, 8 bits                                                                                                                                                                                                |
| 3    | Si 1, déclenchement par niveau ; si 0, déclenchement par front                                                                                                                                                                                         |
| 4    | Toujours à 1 pour activer la séquence d'initialisation                                                                                                                                                                                                 |
| 5-7  | 0                                                                                                                                                                                                                                                        |

Exemple de valeur :
`0x1B` signifie que :

* ICW4 sera utilisé.
* Le système utilise plusieurs PICs en cascade (activer les PICs esclaves pour doubler le nombre d'Interruptions pouvant etre gerees par exemple IRQ 0-7 pour le maitre et IRQ 8-15 pour l'esclave).
* Les interruptions sont déclenchées par des fronts (edge-triggered, un simple "pulse" (changement rapide de 0 à 1 et retour à 0) suffit pour générer une interruption. Dans le cas contraire cela nécessite une gestion plus complexe, car il faut que le périphérique désactive le signal une fois l'interruption traitée. Si ce n'est pas fait, l'interruption pourrait rester active indéfiniment).

---

##### **ICW2 (port 0x21 ou 0xA1)**

L'ICW2 dit Interrupt Vector Offset defini a quel emplacement dans l'IDT les IRQs commencent.


| Bits | Signification                     |
| ------ | ----------------------------------- |
| 7-3  | Base des vecteurs d'interruptions |
| 2-0  | Toujours à 0                     |

Exemple :

Dans notre cas les indices 0-31 de notre IDT sont reserves aux **interruptions d'exceptions materielles** (exemple: IDT[0] sera l'interruption generee par une division par zero).

Nous indiquons alors au PIC maitre de chercher les IRQ a IDT[32 + n] et au PIC esclave de chercher a IDT[40 + n] grace a l'ICW2.

---

##### **ICW3 (port 0x21 ou 0xA1)** :

* **PIC maître** : indique quelles lignes IRQ sont connectées aux esclaves.
  Exemple : `0x04` signifie que le PIC esclave est connecté à IRQ2 (3eme bit actif).
* **PIC esclave** : indique l'ID attribué par le maître, contrairement au maitre on envoi la valeur "directe" qui identifie l'IRQ et non pas un masque de bits.
  Exemple : `0x02` signifie que le PIC esclave est connecté à IRQ2.

  Cet ICW permet simplement de definir via quel IRQ maitre et esclave vont communiquer.

---

##### **ICW4 (port 0x21 ou 0xA1)** :


| Bits | Signification                                                                                                                                                                                                                                                     |
| ------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 7-5  | Non utilisés                                                                                                                                                                                                                                                     |
| 4    | Si 1, mode entièrement imbriqué (Nested mode). Permet de creer un hierarchie plus complexe de PICs si besoin de gerer plus de 15 IRQs.                                                                                                                          |
| 3    | Si 1, mode bufferisé actif (Dans ce mode, les**PICs esclaves** peuvent **mettre en tampon** les interruptions avant qu'elles ne soient traitées, le maitre peut alors lire ce tampon quand bon lui semble, optimisant d'avantage la gestion des interruptions). |
| 2    | Si 1, active le mode bufferise pour le maitre egalement.                                                                                                                                                                                                          |
| 1    | Si 1, activer le mode AEOI (Auto End of Interrupt)                                                                                                                                                                                                                |
| 0    | Si 1, activer le mode 8086/88 (mode MCS-80/85 sinon)                                                                                                                                                                                                              |

Exemple de valeur :

* `0x01` active le mode 8086/88.
* `0x03` active le mode 8086/88 avec l'AEOI.

---

#### **Ordre de configuration des ICW**

1. Écrire **ICW1** dans le port de commande.
2. Écrire **ICW2** dans le port de données.
3. Si nécessaire, écrire **ICW3** dans le port de données.
4. Écrire **ICW4** dans le port de données, si demandé par ICW1.

Chaque ICW est envoyé à des ports spécifiques dans un ordre bien défini. La distinction entre ICW2, ICW3, etc., est déterminée par **l'ordre d'écriture** et **le contexte d'initialisation** .

---

#### **Exemple de configuration des PICs (Maître et Esclave)**


| Étape | Port       | Valeur | Description                                   |
| -------- | ------------ | -------- | ----------------------------------------------- |
| ICW1   | 0x20, 0xA0 | 0x11   | Séquence d'initialisation activée           |
| ICW2   | 0x21, 0xA1 | 0x20   | Base des vecteurs pour le maître : 32        |
|        |            | 0x70   | Base des vecteurs pour l'esclave : 96         |
| ICW3   | 0x21, 0xA1 | 0x04   | L'esclave est connecté à IRQ2               |
|        |            | 0x02   | L'esclave indique qu'il est connecté à IRQ2 |
| ICW4   | 0x21, 0xA1 | 0x01   | Mode 8086/88 activé                          |

---

### **Conclusion**

Les ICW permettent de configurer le PIC pour gérer correctement les interruptions. En maîtrisant ces commandes, on peut personnaliser les vecteurs d'interruptions et les relations entre les PICs maître et esclave, ce qui est essentiel pour la gestion des périphériques dans un système x86.
