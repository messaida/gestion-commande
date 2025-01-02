#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

// Structure pour représenter une commande
typedef struct {
    int numero_commande;
    char client[50];
    char date[20];
    char statut[20];
    float total;
} Commande;

// Variables globales pour le tableau dynamique
Commande *commandes = NULL;   // Pointeur vers le tableau des commandes
int taille_commandes = 0;     // Nombre actuel de commandes
int capacite = 0;             // Capacité actuelle du tableau

// Initialisation du tableau dynamique avec une capacité donnée
void initialiser_tableau(int capacite_initiale) {
    capacite = capacite_initiale;
    commandes = (Commande *)malloc(capacite * sizeof(Commande));
    if (commandes == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        exit(1);
    }
}

// Ajouter une commande au tableau dynamique
void ajouter_commande(Commande nouvelle_commande) {
    // Si le tableau est plein, doubler sa capacité
    if (taille_commandes >= capacite) {
        capacite *= 2;
        Commande *temp = realloc(commandes, capacite * sizeof(Commande));
        if (temp == NULL) {
            printf("Erreur de réallocation mémoire.\n");
            free(commandes);
            exit(1);
        }
        commandes = temp;
    }
    // Ajouter la nouvelle commande dans le tableau
    commandes[taille_commandes] = nouvelle_commande;
    taille_commandes++;
}

// Afficher l'historique des commandes
void afficher_historique() {
    clear();
    if (taille_commandes == 0) {
        printw("L'historique des commandes est vide.\n");
    } else {
        printw("Historique des commandes :\n");
        printw("No\tClient\t\tDate\t\tStatut\t\tTotal\n");
        printw("-------------------------------------------------------------\n");
        for (int i = 0; i < taille_commandes; i++) {
            printw("%d\t%s\t%s\t%s\t%.2f\n",
                   commandes[i].numero_commande,
                   commandes[i].client,
                   commandes[i].date,
                   commandes[i].statut,
                   commandes[i].total);
        }
    }
    refresh();
    getch();
}

// Rechercher une commande par son numéro
Commande* rechercher_commande(int numero) {
    for (int i = 0; i < taille_commandes; i++) {
        if (commandes[i].numero_commande == numero) {
            return &commandes[i];
        }
    }
    return NULL;
}

// Annuler une commande par son numéro
void annuler_commande(int numero) {
    Commande *commande = rechercher_commande(numero);
    if (commande != NULL) {
        strcpy(commande->statut, "annulée");
        printw("Commande annulée avec succès.\n");
    } else {
        printw("Commande non trouvée.\n");
    }
    refresh();
    getch();
}

// Afficher les commandes en attente
void afficher_commandes_en_attente() {
    clear();
    int en_attente = 0;
    printw("Commandes en attente :\n");
    printw("No\tClient\t\tDate\t\tStatut\t\tTotal\n");
    printw("-------------------------------------------------------------\n");

    for (int i = 0; i < taille_commandes; i++) {
        if (strcmp(commandes[i].statut, "en attente") == 0) {
            printw("%d\t%s\t%s\t%s\t%.2f\n",
                   commandes[i].numero_commande,
                   commandes[i].client,
                   commandes[i].date,
                   commandes[i].statut,
                   commandes[i].total);
            en_attente++;
        }
    }

    if (en_attente == 0) {
        printw("Aucune commande en attente.\n");
    }
    refresh();
    getch();
}

// Libérer la mémoire allouée pour le tableau dynamique
void liberer_tableau() {
    free(commandes);
    commandes = NULL;
    capacite = 0;
    taille_commandes = 0;
}

// Fonction principale
int main() {
    // Initialiser le tableau dynamique avec une capacité initiale
    initialiser_tableau(2);

    // Initialiser ncurses
    initscr();
    cbreak();
    noecho();

    int choix;
    do {
        clear();
        printw("Menu :\n");
        printw("1. Ajouter une commande\n");
        printw("2. Afficher l'historique des commandes\n");
        printw("3. Rechercher une commande\n");
        printw("4. Annuler une commande\n");
        printw("5. Afficher les commandes en attente\n");
        printw("6. Quitter\n");
        printw("Votre choix : ");
        refresh();
        scanw("%d", &choix);

        switch (choix) {
            case 1: {
                Commande nouvelle_commande;
                clear();
                printw("Entrez le numéro de commande : ");
                refresh();
                scanw("%d", &nouvelle_commande.numero_commande);
                printw("Entrez le nom du client : ");
                refresh();
                scanw("%s", nouvelle_commande.client);
                printw("Entrez la date (AAAA-MM-JJ) : ");
                refresh();
                scanw("%s", nouvelle_commande.date);
                printw("Entrez le statut (en attente, terminé, annulée) : ");
                refresh();
                scanw("%s", nouvelle_commande.statut);
                printw("Entrez le total : ");
                refresh();
                scanw("%f", &nouvelle_commande.total);

                ajouter_commande(nouvelle_commande);
                printw("Commande ajoutée avec succès.\n");
                refresh();
                getch();
                break;
            }
            case 2:
                afficher_historique();
                break;
            case 3: {
                int numero;
                clear();
                printw("Entrez le numéro de commande à rechercher : ");
                refresh();
                scanw("%d", &numero);

                Commande *resultat = rechercher_commande(numero);
                if (resultat != NULL) {
                    printw("\nCommande trouvée :\n");
                    printw("No : %d\nClient : %s\nDate : %s\nStatut : %s\nTotal : %.2f\n",
                           resultat->numero_commande,
                           resultat->client,
                           resultat->date,
                           resultat->statut,
                           resultat->total);
                } else {
                    printw("\nCommande non trouvée.\n");
                }
                refresh();
                getch();
                break;
            }
            case 4: {
                int numero;
                clear();
                printw("Entrez le numéro de commande à annuler : ");
                refresh();
                scanw("%d", &numero);
                annuler_commande(numero);
                break;
            }
            case 5:
                afficher_commandes_en_attente();
                break;
            case 6:
                printw("Au revoir !\n");
                refresh();
                getch();
                break;
            default:
                printw("Choix invalide. Veuillez réessayer.\n");
                refresh();
                getch();
        }
    } while (choix != 6);

    // Libérer la mémoire avant de quitter
    liberer_tableau();

    // Fermer ncurses
    endwin();

    return 0;
}