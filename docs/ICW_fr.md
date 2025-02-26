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


| Bits | Signification                                                    |
| ------ | :----------------------------------------------------------------- |
| 0    | Si 1, activer les fonctionnalités de l'ICW4                     |
| 1    | Si 1, mode à un seul PIC ; si 0, mode en cascade                |
| 2    | Si 1, Interval d'adresse d'appels a 4 bits ; si 0, 8 bits        |
| 3    | Si 1, déclenchement par niveau ; si 0, déclenchement par front |
| 4    | Toujours à 1 pour activer la séquence d'initialisation         |
| 5-7  | 0                                                                |

Exemple de valeur :
`0x11` signifie que :

* ICW4 sera utilisé.
* Le système utilise plusieurs PICs en cascade.
* Les interruptions sont déclenchées par des fronts (edge-triggered).

---

##### **ICW2 (port 0x21 ou 0xA1)** :


| Bits | Signification                     |
| ------ | ----------------------------------- |
| 7-3  | Base des vecteurs d'interruptions |
| 2-0  | Toujours à 0                     |

Exemple :

* `0x20` pour un maître signifie que la base des vecteurs est 32 (décimal).
* L'IRQ 0 du PIC maître correspondra au vecteur 32.

---

##### **ICW3 (port 0x21 ou 0xA1)** :

* **PIC maître** : indique quelles lignes IRQ sont connectées aux esclaves.
  Exemple : `0x04` signifie que le PIC esclave est connecté à IRQ2.
* **PIC esclave** : indique l'ID attribué par le maître.
  Exemple : `0x02` signifie que le PIC esclave est connecté à IRQ2.

---

##### **ICW4 (port 0x21 ou 0xA1)** :


| Bits | Signification                                        |
| ------ | ------------------------------------------------------ |
| 7-5  | Non utilisés                                        |
| 4    | Si 1, mode entièrement imbriqué                    |
| 3    | Si 1, mode bufferisé actif                          |
| 2    | Si 1, le PIC est maître en mode bufferisé          |
| 1    | Si 1, activer le mode AEOI                           |
| 0    | Si 1, activer le mode 8086/88 (mode MCS-80/85 sinon) |

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
