# VGA CRT (Cathod Ray Tub) Control Port

Le port **0x3D4** est utilisé pour interagir avec le **contrôleur CRT (Cathode Ray Tube)** du VGA. Ce port est utilisé pour sélectionner un registre interne spécifique du contrôleur, dont les données peuvent ensuite être lues ou écrites via le port **0x3D5** .

---

### Liste des registres accessibles via le port **0x3D4**

Voici une liste des principaux registres que l'on peut sélectionner avec le port 0x3D4. Chaque registre est sélectionné en écrivant son index au port 0x3D4, puis les données correspondantes sont lues ou écrites via le port 0x3D5.


| **Index (hex)** | **Nom du registre**      | **Description**                                                                                     |
| ----------------- | -------------------------- | ----------------------------------------------------------------------------------------------------- |
| **0x00**        | Horizontal Total         | Définit le nombre total de colonnes visibles et invisibles dans une ligne horizontale.             |
| **0x01**        | End Horizontal Display   | Définit la dernière colonne visible dans une ligne horizontale.                                   |
| **0x02**        | Start Horizontal Blank   | Indique où commence le "blanking" horizontal.                                                      |
| **0x03**        | End Horizontal Blank     | Indique où se termine le "blanking" horizontal.                                                    |
| **0x04**        | Start Horizontal Retrace | Détermine le début du signal de retour horizontal (retrace).                                      |
| **0x05**        | End Horizontal Retrace   | Détermine la fin du signal de retour horizontal (et d'autres configurations fines).                |
| **0x06**        | Vertical Total           | Définit le nombre total de lignes visibles et invisibles dans une trame verticale.                 |
| **0x07**        | Overflow                 | Contient les bits supplémentaires pour les registres qui dépassent 8 bits (comme Vertical Total). |
| **0x08**        | Preset Row Scan          | Configure les lignes "préréglées" pour des raisons spécifiques (rarement utilisé).             |
| **0x09**        | Maximum Scan Line        | Définit la hauteur d'une ligne (en unités de lignes de pixels).                                   |
| **0x0A**        | Cursor Start             | Détermine la ligne où commence l'affichage du curseur.                                            |
| **0x0B**        | Cursor End               | Détermine la ligne où se termine l'affichage du curseur.                                          |
| **0x0C**        | Start Address High       | Partie haute de l'adresse vidéo où commence l'affichage.                                          |
| **0x0D**        | Start Address Low        | Partie basse de l'adresse vidéo où commence l'affichage.                                          |
| **0x0E**        | Cursor Location High     | Partie haute de l'adresse mémoire de la position actuelle du curseur.                              |
| **0x0F**        | Cursor Location Low      | Partie basse de l'adresse mémoire de la position actuelle du curseur.                              |
| **0x10**        | Vertical Retrace Start   | Détermine le début du signal de retour vertical (retrace).                                        |
| **0x11**        | Vertical Retrace End     | Détermine la fin du signal de retour vertical et d'autres configurations de contrôle.             |
| **0x12**        | Vertical Display End     | Indique la dernière ligne visible dans une trame verticale.                                        |
| **0x13**        | Offset                   | Indique combien d'octets constituent une ligne horizontale dans la mémoire vidéo.                 |
| **0x14**        | Underline Location       | Définit l'emplacement de la ligne soulignée pour le mode texte.                                   |
| **0x15**        | Start Vertical Blank     | Indique où commence le "blanking" vertical.                                                        |
| **0x16**        | End Vertical Blank       | Indique où se termine le "blanking" vertical.                                                      |
| **0x17**        | Mode Control             | Configure divers paramètres comme l'affichage en mode texte/graphique.                             |
| **0x18**        | Line Compare             | Permet des comparaisons de lignes pour le défilement ou d'autres opérations avancées.            |

## Detail des registres

### **0x00 - Horizontal Total**

* **Bits utilisés** :
  * **0-7** : Nombre total de cycles d'horloge dans une ligne horizontale.
* **Bits inutilisés** : Aucun.
* **Utilité** :
  * Configure la largeur totale d'une ligne, y compris la partie visible et invisible.

---

### **0x01 - End Horizontal Display**

* **Bits utilisés** :
  * **0-7** : Dernier caractère ou pixel visible dans une ligne.
* **Bits inutilisés** : Aucun.
* **Utilité** :
  * Définit la largeur visible d'une ligne.

---

### **0x02 - Start Horizontal Blank**

* **Bits utilisés** :
  * **0-7** : Position où commence le blanking horizontal (écran désactivé horizontalement).
* **Bits inutilisés** : Aucun.
* **Utilité** :
  * Synchronise le début du blanking horizontal.

---

### **0x03 - End Horizontal Blank**

* **Bits utilisés** :
  * **0-4** : Position où se termine le blanking horizontal.
  * **5** : Indique si la durée du blanking horizontal est doublée.
* **Bits inutilisés** :**6-7** .
* **Utilité** :
  * Ajuste la fin de la période de blanking horizontal.

---

### **0x04 - Start Horizontal Retrace**

* **Bits utilisés** :
  * **0-7** : Point de départ du signal de retour horizontal.
* **Bits inutilisés** : Aucun.
* **Utilité** :
  * Configure le moment où le signal de synchronisation horizontal commence.

---

### **0x05 - End Horizontal Retrace**

* **Bits utilisés** :
  * **0-4** : Point de fin du signal de retour horizontal.
  * **5** : Active/désactive l'affichage.
  * **6** : Indique si une autre opération (comme le scrolling) est active.
* **Bits inutilisés** :**7** .
* **Utilité** :
  * Ajuste la fin du signal de retour horizontal et d'autres paramètres d'affichage.

---

### **0x06 - Vertical Total**

* **Bits utilisés** :
  * **0-7** : Nombre total de lignes verticales (visible + invisible).
* **Bits inutilisés** : Aucun.
* **Utilité** :
  * Définit la hauteur totale d'une trame verticale.

---

### **0x07 - Overflow**

* **Bits utilisés** :
  * **0** : Bit 8 de**Vertical Total** .
  * **1** : Bit 8 de**Start Vertical Display** .
  * **2** : Bit 8 de**Vertical Retrace Start** .
  * **3** : Bit 8 de**Vertical Display End** .
  * **4** : Overflow pour**Start Vertical Blank** .
* **Bits inutilisés** :**5-7** .
* **Utilité** :
  * Étend la portée des registres verticaux pour des résolutions plus élevées.

---

### **0x08 - Preset Row Scan**

* **Bits utilisés** :
  * **0-4** : Nombre de lignes préréglées (pour scrolling ou autres effets).
* **Bits inutilisés** :**5-7** .
* **Utilité** :
  * Rarement utilisé ; peut personnaliser les lignes affichées.

---

### **0x09 - Maximum Scan Line**

* **Bits utilisés** :
  * **0-4** : Hauteur en pixels d'une ligne (texte ou graphique).
  * **5** : Double hauteur pour le mode texte.
  * **6** : Mode entrelacé activé/désactivé.
* **Bits inutilisés** :**7** .
* **Utilité** :
  * Contrôle l'espacement vertical et le mode entrelacé.

---

### **0x0A - Cursor Start**

* **Bits utilisés** :
  * **0-3** : Ligne de début du curseur (en pixels).
  * **5** : Désactive le curseur si activé.
* **Bits inutilisés** :**4, 6-7** .
* **Utilité** :
  * Configure la hauteur visible du curseur et contrôle son activation.

---

### **0x0B - Cursor End**

* **Bits utilisés** :
  * **0-3** : Ligne de fin du curseur (en pixels).
* **Bits inutilisés** :**4-7** .
* **Utilité** :
  * Ajuste la hauteur totale du curseur.

---

### **0x0C - Start Address High**

* **Bits utilisés** :
  * **0-7** : Partie haute de l'adresse vidéo de départ.
* **Bits inutilisés** : Aucun.
* **Utilité** :
  * Configure le défilement matériel de l'affichage.

---

### **0x0D - Start Address Low**

* **Bits utilisés** :
  * **0-7** : Partie basse de l'adresse vidéo de départ.
* **Bits inutilisés** : Aucun.
* **Utilité** :
  * Complète l'adresse pour permettre un scrolling matériel.

---

### **0x0E - Cursor Location High**

* **Bits utilisés** :
  * **0-7** : Partie haute de l'adresse mémoire du curseur.
* **Bits inutilisés** : Aucun.
* **Utilité** :
  * Définit la position verticale du curseur.

---

### **0x0F - Cursor Location Low**

* **Bits utilisés** :
  * **0-7** : Partie basse de l'adresse mémoire du curseur.
* **Bits inutilisés** : Aucun.
* **Utilité** :
  * Complète la position pour localiser précisément le curseur.

---

### **0x10 - Vertical Retrace Start**

* **Bits utilisés** :
  * **0-7** : Début du signal de retour vertical.
* **Bits inutilisés** : Aucun.
* **Utilité** :
  * Configure la synchronisation verticale.

---

### **0x11 - Vertical Retrace End**

* **Bits utilisés** :
  * **0-3** : Fin du signal de retour vertical.
  * **4** : Active/désactive les interruptions verticales.
* **Bits inutilisés** :**5-7** .
* **Utilité** :
  * Ajuste la durée du retour vertical.

---

### **0x12 - Vertical Display End**

* **Bits utilisés** :
  * **0-7** : Dernière ligne visible verticalement.
* **Bits inutilisés** : Aucun.
* **Utilité** :
  * Configure la hauteur visible de l'écran.

---

### **0x13 - Offset**

* **Bits utilisés** :
  * **0-7** : Nombre d'octets pour passer d'une ligne à la suivante.
* **Bits inutilisés** : Aucun.
* **Utilité** :
  * Contrôle l'alignement des lignes en mémoire.

---

### **0x14 - Underline Location**

* **Bits utilisés** :
  * **0-4** : Ligne où le soulignement apparaît.
* **Bits inutilisés** :**5-7** .
* **Utilité** :
  * Ajuste le soulignement en mode texte.

---

### **0x15 - Start Vertical Blank**

* **Bits utilisés** :
  * **0-7** : Point où commence le blanking vertical.
* **Bits inutilisés** : Aucun.
* **Utilité** :
  * Configure la période où l'affichage est désactivé verticalement.

---

### **0x16 - End Vertical Blank**

* **Bits utilisés** :
  * **0-7** : Point où se termine le blanking vertical.
* **Bits inutilisés** : Aucun.
* **Utilité** :
  * Ajuste la durée totale du blanking vertical.

---

### **0x17 - Mode Control**

* **Bits utilisés** :
  * **0** : Texte ou graphique.
  * **1** : Entrelacé activé/désactivé.
  * **2** : Active/désactive l'écran.
* **Bits inutilisés** :**3-7** .
* **Utilité** :
  * Configure le mode d'affichage.

---

### **0x18 - Line Compare**

* **Bits utilisés** :
  * **0-7** : Ligne utilisée pour la comparaison.
* **Bits inutilisés** : Aucun.
* **Utilité** :
  * Configure des effets comme le défilement matériel.
