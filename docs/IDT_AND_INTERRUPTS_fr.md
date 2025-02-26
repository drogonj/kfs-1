# **IDT et Interruptions**

Une **interruption** est un signal envoyé au processeur par un périphérique matériel ou logiciel pour indiquer un événement nécessitant une attention immédiate. Les interruptions permettent au processeur de réagir rapidement à des événements externes ou internes sans avoir à surveiller en permanence l'état des périphériques.

---

### **Types d'Interruptions**

1. **Interruptions matérielles (IRQ)** :
   * Générées par des périphériques externes (clavier, souris, disque dur, etc.).
   * Elles évitent au processeur de gaspiller des cycles en attente passive (*polling* ).
   * Exemple : Une touche de clavier pressée génère une IRQ pour informer le processeur.
2. **Interruptions logicielles** :
   * Déclenchées volontairement par un programme, souvent pour des appels système.
   * Exemple : Sous Linux, l'appel système `int 0x80` permet de passer en mode noyau.
3. **Exceptions** :
   * Causées par des erreurs ou événements exceptionnels durant l'exécution d'un programme.
   * Exemples : Division par zéro, défaut de page, violation de segment.

---

### **Exemple avec le Clavier**

Lorsqu'une touche est pressée :

1. Le contrôleur clavier signale une interruption au PIC (*Programmable Interrupt Controller* ).
2. Si l'interruption n'est pas masquée, le PIC notifie le processeur.
3. Le processeur exécute une routine de gestion d'interruption (*Interrupt Service Routine* , ISR) pour lire la touche et l'afficher.
4. Une fois terminé, le processeur reprend sa tâche initiale.

---

### **Le PIC (Programmable Interrupt Controller)**

##### **Rôle**

Le PIC est un composant matériel qui gère les interruptions matérielles. Il combine plusieurs sources d'interruptions en une ou quelques lignes CPU, tout en gérant les priorités entre interruptions (les plus urgentes sont traitées en premier).

##### **Système Maître-Esclave**

* Les systèmes modernes utilisent souvent deux PICs : un maître et un esclave.
* Le **PIC maître** gère les interruptions de priorité élevée (IRQ0 à IRQ7).
* Le **PIC esclave** gère les interruptions de priorité inférieure (IRQ8 à IRQ15).
* Le PIC esclave est connecté à l'une des lignes du PIC maître (généralement IRQ2), ce qui permet de chaîner les deux contrôleurs.

##### **Configuration du PIC**

* **Ports I/O** :
  * Maître : `0x20` (commandes), `0x21` (masques).
  * Esclave : `0xA0` (commandes), `0xA1` (masques).
* **ICW (Initialization Command Words)** :
  Utilisés pour initialiser le PIC.
* **OCW (Operation Command Words)** :
  Utilisés pour configurer le PIC après initialisation (masquage/démasquage des interruptions).

---

### **L'IDT (Interrupt Descriptor Table)**

##### **Rôle**

L'IDT est une structure de données utilisée par l'architecture x86 pour définir les réponses aux interruptions et exceptions. Chaque entrée de l'IDT pointe vers une routine de gestion (*Interrupt Service Routine* , ISR).

##### **Structure de l'IDT**

Chaque entrée (8 octets) contient :

* **Offset** (32 bits) : Adresse de l'ISR.
* **Sélecteur** (16 bits) : Segment de code du noyau (exemple : `0x08` pour le segment noyau en mode protégé).
* **Type** (4 bits) : Drapeaux (exemple : `INTGATE` pour les interruptions, `TRAPGATE` pour les exceptions).

```
struct idtdesc {
    u16 offset0_15;   // Bits 0-15 de l'offset
    u16 select;        // Sélecteur de segment
    u16 type;          // Type et drapeaux
    u16 offset16_31;   // Bits 16-31 de l'offset
} __attribute__((packed));
```

##### **Chargement de l'IDT**

Utilise le registre `IDTR` via l'instruction `LIDTL` :

```
struct idtr {
    u16 limite;        // Taille de l'IDT - 1
    u32 base;          // Adresse de l'IDT
} __attribute__((packed));
```

---

### **ISR (Interrupt Service Routine)**

##### **Rôle**

Une ISR est une routine exécutée par le processeur lorsqu'une interruption ou une exception se produit. Elle doit :

1. Sauvegarder le contexte du processeur (registres, état du programme).
2. Traiter l'interruption (exemple : lire une touche de clavier).
3. Restaurer le contexte et revenir à l'exécution normale.

##### **Exemple d'ISR en Assembleur**

```
%macro ISR 1
global _asm_isr%1
_asm_isr%1:
    SAVE_REGS          // Sauvegarde des registres
    push %1           // Numéro d'interruption
    call isr_handler  // Appel du gestionnaire C
    add esp, 4        // Nettoyage de la pile
    mov al, 0x20      // Acquittement PIC (EOI)
    out 0x20, al
    RESTORE_REGS      // Restauration des registres
    iret              // Retour d'interruption
%endmacro
```

---

### **Initialisation des Interruptions**

##### **Configuration du PIC**

```
void init_pic(void) {
    // ICW1 : Initialisation avec ICW4
    io.outb(0x20, 0x11);  // Maître
    io.outb(0xA0, 0x11);  // Esclave

    // ICW2 : Vecteurs de base
    io.outb(0x21, 0x20);  // Maître → interruptions à partir de 0x20 (32)
    io.outb(0xA1, 0x70);  // Esclave → à partir de 0x70 (112)

    // ICW3 : Cascade
    io.outb(0x21, 0x04);  // Maître : IRQ2 connecte l'esclave
    io.outb(0xA1, 0x02);  // Esclave : identifiant 2

    // ICW4 : Mode 8086
    io.outb(0x21, 0x01);
    io.outb(0xA1, 0x01);

    // Masquage : autoriser toutes les interruptions
    io.outb(0x21, 0x00);
    io.outb(0xA1, 0x00);
}
```

##### **Remplissage de l'IDT**

```
void init_idt_desc(u16 select, u32 offset, u16 type, struct idtdesc *desc) {
    desc->offset0_15 = (offset & 0xffff);
    desc->select = select;
    desc->type = type;
    desc->offset16_31 = (offset && 0xffff0000) >> 16;
}

void init_idt(void) {
    // Initialisation par défaut
    for (int i = 0; i < IDTSIZE; i++) {
        init_idt_desc(0x08, (u32)_asm_default, INTGATE, &kidt[i]);
    }

    // Exceptions
    init_idt_desc(0x08, (u32)_asm_exc_gp, INTGATE, &kidt[13]);  // #GP
    init_idt_desc(0x08, (u32)_asm_exc_pf, INTGATE, &kidt[14]);  // #PF

    // Interruptions matérielles
    init_idt_desc(0x08, (u32)_asm_irq_timer, INTGATE, &kidt[32]);  // IRQ0 (timer)
    init_idt_desc(0x08, (u32)_asm_irq_kbd, INTGATE, &kidt[33]);    // IRQ1 (clavier)

    // Appels système
    init_idt_desc(0x08, (u32)_asm_syscall, TRAPGATE, &kidt[48]);   // int 0x30
    init_idt_desc(0x08, (u32)_asm_syscall, TRAPGATE, &kidt[128]);  // int 0x80

    // Chargement de l'IDT
    kidtr.limite = IDTSIZE * sizeof(struct idtdesc) - 1;
    kidtr.base = (u32)kidt;
    asm("lidtl (%0)" : : "r"(&kidtr));
}
```

---

### **Détails Techniques Supplémentaires**

##### **Acquittement du PIC (EOI)**

Après avoir traité une interruption, le PIC doit être informé que l'interruption a été traitée. Cela se fait en envoyant un **EOI (End Of Interrupt)** au PIC via le port `0x20` (maître) ou `0xA0` (esclave).

##### **Masquage des Interruptions**

Le PIC permet de masquer des interruptions spécifiques en écrivant dans ses registres de masque (`0x21` pour le maître, `0xA1` pour l'esclave). Chaque bit correspond à une ligne IRQ.

##### **Priorités des Interruptions**

Le PIC utilise un système de priorités fixes : IRQ0 est la plus prioritaire, IRQ7 la moins prioritaire. Pour le PIC esclave, IRQ8 est plus prioritaire que IRQ15.
