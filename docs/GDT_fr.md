# La GDT (Global Descriptor Table)

La **Global Descriptor Table (GDT)**
est une structure de données utilisée dans les architectures x86 pour
définir les caractéristiques des segments de mémoire. Elle est
essentielle pour la gestion de la mémoire en mode protégé, permettant de
définir les droits d'accès, les limites et les bases des segments.

## Structure de la GDT

La GDT est composée d'un tableau de descripteurs de segments. Chaque
descripteur de segment est une structure de 8 octets qui décrit un
segment de mémoire. Voici les structures de données utilisées pour
représenter la GDT et ses entrées :

### Structure du pointeur GDT (`gdt_ptr_t`)

```
typedef struct gdt_ptr_s {
    uint16_t limite;  // La limite de la GDT (taille - 1)
    uint32_t base;    // L'adresse de base de la GDT
} __attribute__ ((packed)) gdt_ptr_t;
```

* **limite** : La taille totale de la GDT moins 1. Cela indique la dernière adresse valide dans la table.
* **base** : L'adresse mémoire de début de la GDT.

### Structure d'une entrée GDT (`gdt_entry_t`)

```
typedef struct gdt_entry_s {
    uint16_t limit_low;        // Les 16 bits de poids faible de la limite
    uint16_t base_low;         // Les 16 bits de poids faible de la base
    uint8_t base_high_low;     // Les 8 bits suivants de la base (bits 16-23)
    uint8_t access;            // Byte d'accès (droit d'accès et flags)
    uint8_t flags;             // Flags (dont les 4 bits de poids fort de la limite)
    uint8_t limit_high;        // Les 4 bits de poids fort de la limite
    uint8_t base_high_high;    // Les 8 bits de poids fort de la base (bits 24-31)
} __attribute__ ((packed)) gdt_entry_t;
```

## Détails des champs d'une entrée GDT

### `limit_low` et `limit_high`

* **limit_low** : Les 16 bits de poids faible de la limite du segment.
* **limit_high** : Les 4 bits de poids fort de la limite du segment.
* **flags** : Contient également les 4 bits de poids fort de la limite (bits 16-19).

La limite totale du segment est calculée en combinant `limit_low` et les 4 bits de poids fort de `limit_high`. La limite définit la taille du segment.

### `base_low`, `base_high_low`, et `base_high_high`

* **base_low** : Les 16 bits de poids faible de l'adresse de base du segment.
* **base_high_low** : Les 8 bits suivants de l'adresse de base (bits 16-23).
* **base_high_high** : Les 8 bits de poids fort de l'adresse de base (bits 24-31).

L'adresse de base totale du segment est calculée en combinant ces trois champs.

### `access` (Byte d'accès)

Le byte d'accès définit les droits d'accès et les propriétés du segment. Il est structuré comme suit :


| Bit | Nom                       | Description                                                                                                                       |
| ----- | --------------------------- | ----------------------------------------------------------------------------------------------------------------------------------- |
| 7   | Present (P)               | 1 si le segment est présent en mémoire, 0 sinon.                                                                                |
| 6-5 | Privilege (DPL)           | Niveau de privilège (0 = noyau, 3 = utilisateur).                                                                                |
| 4   | Descriptor Type (S)       | 1 pour les segments de code/données, 0 pour les segments système.                                                               |
| 3   | Executable (E)            | 1 si le segment est exécutable (code), 0 sinon (données).                                                                       |
| 2   | Direction/Conforming (DC) | Pour les segments de données : 0 = croissant, 1 = décroissant. Pour les segments de code : 0 = non-conforme, 1 = conforme.      |
| 1   | Readable/Writable (RW)    | Pour les segments de code : 1 = lisible, 0 = non lisible. Pour les segments de données : 1 = inscriptible, 0 = non inscriptible. |
| 0   | Accessed (A)              | Mis à 1 par le CPU lorsque le segment est accédé.                                                                              |

### `flags`

Les flags contiennent des informations supplémentaires sur le segment :


| Bit | Nom             | Description                                                      |
| ----- | ----------------- | ------------------------------------------------------------------ |
| 7   | Granularity (G) | 1 = la limite est en pages de 4 Ko, 0 = la limite est en octets. |
| 6   | Size (D/B)      | 1 = segment 32 bits, 0 = segment 16 bits.                        |
| 5   | Reserved        | Toujours 0.                                                      |
| 4   | Available (AVL) | Disponible pour l'utilisation par le système.                   |
| 3-0 | Limit High      | Les 4 bits de poids fort de la limite (bits 16-19).              |

## Mise en place de la GDT

1. **Définir les entrées de la GDT** : Créez un tableau de `gdt_entry_t` pour stocker les descripteurs de segments.
2. **Initialiser les descripteurs** : Remplissez chaque entrée avec les valeurs appropriées pour les segments de code, données, etc.
3. **Créer le pointeur GDT** : Initialisez une structure `gdt_ptr_t` avec la limite et l'adresse de base de la GDT.
4. **Charger la GDT** : Utilisez l'instruction assembleur `LGDT` pour charger le pointeur GDT dans le registre GDTR.

### Exemple de code pour charger la GDT

```
gdt_entry_t gdt[3];  // Exemple avec 3 entrées
gdt_ptr_t gdt_ptr;

// Initialisation des entrées GDT
gdt[0] = (gdt_entry_t){0, 0, 0, 0, 0, 0, 0};  // Entrée nulle obligatoire
gdt[1] = (gdt_entry_t){0xFFFF, 0x0000, 0x00, 0x9A, 0xCF, 0x00, 0x00};  // Segment de code
gdt[2] = (gdt_entry_t){0xFFFF, 0x0000, 0x00, 0x92, 0xCF, 0x00, 0x00};  // Segment de données

// Initialisation du pointeur GDT
gdt_ptr.limite = sizeof(gdt) - 1;
gdt_ptr.base = (uint32_t)&gdt;

// Chargement de la GDT
asm volatile("lgdt %0" : : "m" (gdt_ptr));
```


## 1. Entrée nulle obligatoire (`gdt[0]`)

```
gdt[0] = (gdt_entry_t){0, 0, 0, 0, 0, 0, 0};
```

### Pourquoi cette entrée est-elle nécessaire ?

La première entrée de la GDT est **toujours nulle** .
Elle est obligatoire car le processeur utilise l'indice 0 comme un
segment invalide. Si un segment est chargé avec un sélecteur pointant
vers cette entrée, une exception sera générée.

### Détail des champs :

* **limit_low** : `0` → Limite basse à 0.
* **base_low** : `0` → Base basse à 0.
* **base_high_low** : `0` → Base haute (bits 16-23) à 0.
* **access** : `0` → Aucun droit d'accès (segment invalide).
* **flags** : `0` → Aucun flag activé.
* **limit_high** : `0` → Limite haute à 0.
* **base_high_high** : `0` → Base haute (bits 24-31) à 0.

---

## 2. Segment de code (`gdt[1]`)

### Détail des champs :

#### **limit_low** : `0xFFFF`

* Les 16 bits de poids faible de la limite du segment.
* Ici, la limite basse est `0xFFFF`, ce qui signifie que la limite totale du segment est de `0xFFFFF` (voir plus bas avec `flags`).

#### **base_low** : `0x0000`

* Les 16 bits de poids faible de la base du segment.
* La base est `0x00000000`, ce qui signifie que le segment commence à l'adresse `0` en mémoire.

#### **base_high_low** : `0x00`

* Les 8 bits suivants de la base (bits 16-23).
* Ici, `0x00`, donc la base reste `0x00000000`.

#### **access** : `0x9A`

Le byte d'accès est `0x9A`. Décomposons-le en binaire : `10011010`.


| Bit | Valeur | Description                                                                                                                      |
| ----- | -------- | ---------------------------------------------------------------------------------------------------------------------------------- |
| 7   | 1      | **Present (P)** : Le segment est présent en mémoire.                                                                           |
| 6-5 | 00     | **Privilege Level (DPL)** : Niveau de privilège 0 (noyau).                                                                      |
| 4   | 1      | **Descriptor Type (S)** : 1 pour un segment de code/données.                                                                    |
| 3   | 1      | **Executable (E)** : 1 pour un segment de code (exécutable).                                                                    |
| 2   | 0      | **Conforming (C)** : 0 pour un segment non-conforme (le code ne peut pas être exécuté à un niveau de privilège inférieur). |
| 1   | 1      | **Readable (R)** : 1 pour un segment de code lisible.                                                                            |
| 0   | 0      | **Accessed (A)** : 0 (mis à 1 par le CPU lors de l'accès).                                                                     |

#### **flags** : `0xCF`

Les flags sont `0xCF`. Décomposons-le en binaire : `11001111`.


| Bit | Valeur | Description                                             |
| ----- | -------- | --------------------------------------------------------- |
| 7   | 1      | **Granularity (G)** : 1 pour une granularité de 4 Ko.  |
| 6   | 1      | **Size (D/B)** : 1 pour un segment 32 bits.             |
| 5   | 0      | **Reserved** : Toujours 0.                              |
| 4   | 0      | **Available (AVL)** : 0 (non utilisé ici).             |
| 3-0 | 1111   | **Limit High** : Les 4 bits de poids fort de la limite. |

* Avec `G=1`, la limite est multipliée par 4 Ko. La limite totale est donc :
  * `limit_low = 0xFFFF`
  * `limit_high = 0xF`
  * Limite totale = `(0xFFFFF + 1) * 4 Ko = 4 Go`.

#### **limit_high** : `0x00`

* Les 4 bits de poids fort de la limite sont déjà inclus dans `flags`.

#### **base_high_high** : `0x00`

* Les 8 bits de poids fort de la base (bits 24-31).
* Ici, `0x00`, donc la base reste `0x00000000`.

---

## 3. Segment de données (`gdt[2]`)

```
gdt[2] = (gdt_entry_t){0xFFFF, 0x0000, 0x00, 0x92, 0xCF, 0x00, 0x00};
```

### Détail des champs :

#### **limit_low** : `0xFFFF`

* Identique au segment de code, la limite basse est `0xFFFF`.

#### **base_low** : `0x0000`

* La base basse est `0x0000`.

#### **base_high_low** : `0x00`

* La base haute (bits 16-23) est `0x00`.

#### **access** : `0x92`

Le byte d'accès est `0x92`. Décomposons-le en binaire : `10010010`.


| Bit | Valeur | Description                                                           |
| ----- | -------- | ----------------------------------------------------------------------- |
| 7   | 1      | **Present (P)** : Le segment est présent en mémoire.                |
| 6-5 | 00     | **Privilege Level (DPL)** : Niveau de privilège 0 (noyau).           |
| 4   | 1      | **Descriptor Type (S)** : 1 pour un segment de code/données.         |
| 3   | 0      | **Executable (E)** : 0 pour un segment de données (non exécutable). |
| 2   | 0      | **Direction (DC)** : 0 pour un segment de données croissant.         |
| 1   | 1      | **Writable (W)** : 1 pour un segment de données inscriptible.        |
| 0   | 0      | **Accessed (A)** : 0 (mis à 1 par le CPU lors de l'accès).          |

#### **flags** : `0xCF`

Identique au segment de code :

* **Granularity (G)** : 1 pour une granularité de 4 Ko.
* **Size (D/B)** : 1 pour un segment 32 bits.
* **Limit High** : `1111` pour une limite totale de 4 Go.

#### **limit_high** : `0x00`

* Les 4 bits de poids fort de la limite sont déjà inclus dans `flags`.

#### **base_high_high** : `0x00`

* La base haute (bits 24-31) est `0x00`.

---

## Résumé des valeurs choisies

* **Segment de code** :
  * **Access** : `0x9A` → Segment exécutable, lisible, niveau de privilège 0.
  * **Flags** : `0xCF` → Segment 32 bits, granularité de 4 Ko, limite de 4 Go.
* **Segment de données** :
  * **Access** : `0x92` → Segment de données, inscriptible, niveau de privilège 0.
  * **Flags** : `0xCF` → Segment 32 bits, granularité de 4 Ko, limite de 4 Go.
