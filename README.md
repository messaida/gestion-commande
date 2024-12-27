# gestion-commande
Application pour gérer des commandes et les commandes en attente
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMANDES 100

// Structure pour représenter une commande

typedef struct {
    int id;
    char description[256];
    int isPending;
} Commande;

Commande commandes[MAX_COMMANDES];

int commandeCount = 0;

// Fonction pour ajouter une commande

void ajouterCommande() {
if (commandeCount >= MAX_COMMANDES) {
        printf("Erreur: Nombre maximum de commandes atteint.\n");
        return;
    }
    int id;
     char description[256];
    printf("Entrez l'ID de la commande: ");
    scanf("%d", &id);
    getchar(); // Pour consommer le caractère de nouvelle ligne restant
    printf("Entrez la description de la commande: ");
    fgets(description, 256, stdin);
    description[strcspn(description, "\n")] = 0; // Supprimer le saut de ligne
    commandes[commandeCount].id = id;
    strncpy(commandes[commandeCount].description, description, 256);
    commandes[commandeCount].isPending = 1; // Par défaut, une commande est en attente
    commandeCount++;
    printf("Commande #%d ajoutée avec succès.\n", id);
}


// Fonction pour annuler une commande
void annulerCommande() {
    int id;
    printf("Entrez l'ID de la commande à annuler: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < commandeCount; i++) {
        if (commandes[i].id == id) {
            found = 1;
            for (int j = i; j < commandeCount - 1; j++) {
                commandes[j] = commandes[j + 1];
            }
            commandeCount--;
            printf("Commande #%d annulée avec succès.\n", id);
            break;
        }
    }
    if (!found) {
        printf("Erreur: Commande #%d non trouvée.\n", id);
    }
}

// Fonction pour afficher les commandes en attente
void afficherCommandesEnAttente() {
    printf("Commandes en attente:\n");
    for (int i = 0; i < commandeCount; i++) {
        if (commandes[i].isPending) {
            printf("- Commande #%d: %s\n", commandes[i].id, commandes[i].description);
        }
    }
}

// Fonction pour traiter une commande
void traiterCommande() {
    int id;
    printf("Entrez l'ID de la commande à traiter: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < commandeCount; i++) {
        if (commandes[i].id == id && commandes[i].isPending) {
            commandes[i].isPending = 0;
            found = 1;
            printf("Commande #%d traitée avec succès.\n", id);
            break;
        }
    }
    if (!found) {
        printf("Erreur: Commande #%d non trouvée ou déjà traitée.\n", id);
    }
}

// Menu interactif pour l'utilisateur
void menu() {
    int choix;
    do {
        printf("\nGestion des commandes:\n");
        printf("1. Ajouter une commande\n");
        printf("2. Annuler une commande\n");
        printf("3. Afficher les commandes en attente\n");
        printf("4. Traiter une commande\n");
        printf("5. Quitter\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouterCommande();
                break;
            case 2:
                annulerCommande();
                break;
            case 3:
                afficherCommandesEnAttente();
                break;
            case 4:
                traiterCommande();
                break;
            case 5:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    } while (choix != 5);
}

int main(int argc, char *argv[]) {
	 menu();
	return 0;
}
