#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMMANDES 100
#define MAX_MENU_ITEMS 50

// Structure pour représenter une commande statique
typedef struct {
    int id;
    char description[256];
    int isPending;
} CommandeStatique;

CommandeStatique commandesStatiques[MAX_COMMANDES];
int commandeCount = 0;

// Structure pour représenter un élément de menu
typedef struct {
    int item_id;
    char item_name[50];
    float item_price;
} MenuItem;

MenuItem menuItems[MAX_MENU_ITEMS];
int menuItemCount = 0;

// Structure pour représenter une commande dynamique
typedef struct {
    int numero_commande;
    char client[50];
    char date[20];
    char statut[20];
    float total;
    int menu_item_ids[MAX_MENU_ITEMS];
    int menu_item_quantities[MAX_MENU_ITEMS];
    int item_count;
} CommandeDynamique;

CommandeDynamique *commandesDynamiques = NULL;   // Pointeur vers le tableau des commandes
int taille_commandes = 0;     // Nombre actuel de commandes
int capacite = 0;             // Capacité actuelle du tableau

// Fonction pour initialiser le menu avec des éléments prédéfinis
void initialiserMenu() {
    menuItems[0].item_id = 1;
    strcpy(menuItems[0].item_name, "Pizza Margherita");
    menuItems[0].item_price = 8.50;

    menuItems[1].item_id = 2;
    strcpy(menuItems[1].item_name, "Spaghetti Carbonara");
    menuItems[1].item_price = 12.00;

    menuItems[2].item_id = 3;
    strcpy(menuItems[2].item_name, "Tiramisu");
    menuItems[2].item_price = 6.00;

    menuItems[3].item_id = 4;
    strcpy(menuItems[3].item_name, "Caesar Salad");
    menuItems[3].item_price = 7.50;

    menuItems[4].item_id = 5;
    strcpy(menuItems[4].item_name, "Lasagna");
    menuItems[4].item_price = 10.00;

    menuItems[5].item_id = 6;
    strcpy(menuItems[5].item_name, "Bruschetta");
    menuItems[5].item_price = 5.00;

    menuItems[6].item_id = 7;
    strcpy(menuItems[6].item_name, "Garlic Bread");
    menuItems[6].item_price = 4.00;

    menuItems[7].item_id = 8;
    strcpy(menuItems[7].item_name, "Fettuccine Alfredo");
    menuItems[7].item_price = 11.00;

    menuItems[8].item_id = 9;
    strcpy(menuItems[8].item_name, "Minestrone Soup");
    menuItems[8].item_price = 6.50;

    menuItems[9].item_id = 10;
    strcpy(menuItems[9].item_name, "Ravioli");
    menuItems[9].item_price = 9.00;

    menuItems[10].item_id = 11;
    strcpy(menuItems[10].item_name, "Margherita Pizza");
    menuItems[10].item_price = 8.50;

    menuItems[11].item_id = 12;
    strcpy(menuItems[11].item_name, "Caprese Salad");
    menuItems[11].item_price = 7.50;

    menuItems[12].item_id = 13;
    strcpy(menuItems[12].item_name, "Panna Cotta");
    menuItems[12].item_price = 5.50;

    menuItems[13].item_id = 14;
    strcpy(menuItems[13].item_name, "Gelato");
    menuItems[13].item_price = 4.50;

    menuItems[14].item_id = 15;
    strcpy(menuItems[14].item_name, "Espresso");
    menuItems[14].item_price = 3.00;

    menuItemCount = 15;
}

// Fonction pour afficher le menu du restaurant
void afficherMenu() {
    printf("Menu du restaurant:\n");
    for (int i = 0; i < menuItemCount; i++) {
        printf("%d. %s - %.2f EUR\n", menuItems[i].item_id, menuItems[i].item_name, menuItems[i].item_price);
    }
    if (menuItemCount == 0) {
        printf("Le menu est vide.\n");
    }
}

// Fonction pour obtenir la date actuelle sous forme de chaîne de caractères
void obtenirDateActuelle(char* dateStr) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dateStr, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

// Fonction pour ajouter une commande
void ajouterCommandeDynamique() {
    if (taille_commandes >= capacite) {
        capacite *= 2;
        CommandeDynamique *temp = realloc(commandesDynamiques, capacite * sizeof(CommandeDynamique));
        if (temp == NULL) {
            printf("Erreur de réallocation mémoire.\n");
            free(commandesDynamiques);
            exit(1);
        }
        commandesDynamiques = temp;
    }

    CommandeDynamique nouvelle_commande;
    nouvelle_commande.item_count = 0;

    printf("Entrez le numéro de commande : ");
    scanf("%d", &nouvelle_commande.numero_commande);
    getchar(); // Consommer le saut de ligne restant
    printf("Entrez le nom du client : ");
    fgets(nouvelle_commande.client, 50, stdin);
    nouvelle_commande.client[strcspn(nouvelle_commande.client, "\n")] = 0;

    // Obtenir la date actuelle
    obtenirDateActuelle(nouvelle_commande.date);
    strcpy(nouvelle_commande.statut, "en attente");
    nouvelle_commande.total = 0.0;

    // Afficher le menu et permettre à l'utilisateur de choisir des éléments
    int choix;
    do {
        afficherMenu();
        printf("Entrez l'ID de l'élément de menu à ajouter à la commande (0 pour arrêter) : ");
        scanf("%d", &choix);
        if (choix != 0) {
            int quantity;
            printf("Entrez la quantité : ");
            scanf("%d", &quantity);

            for (int i = 0; i < menuItemCount; i++) {
                if (menuItems[i].item_id == choix) {
                    nouvelle_commande.menu_item_ids[nouvelle_commande.item_count] = choix;
                    nouvelle_commande.menu_item_quantities[nouvelle_commande.item_count] = quantity;
                    nouvelle_commande.total += menuItems[i].item_price * quantity;
                    nouvelle_commande.item_count++;
                }
            }
        }
    } while (choix != 0);

    commandesDynamiques[taille_commandes] = nouvelle_commande;
    taille_commandes++;

    // Afficher le reçu
    printf("\n--- Reçu de la commande ---\n");
    printf("Numéro de commande: %d\n", nouvelle_commande.numero_commande);
    printf("Nom du client: %s\n", nouvelle_commande.client);
    printf("Date: %s\n", nouvelle_commande.date);
    printf("Statut: %s\n", nouvelle_commande.statut);
    printf("Détails de la commande:\n");
    for (int i = 0; i < nouvelle_commande.item_count; i++) {
        int item_id = nouvelle_commande.menu_item_ids[i];
        int quantity = nouvelle_commande.menu_item_quantities[i];
        for (int j = 0; j < menuItemCount; j++) {
            if (menuItems[j].item_id == item_id) {
                printf("- %s x%d: %.2f EUR\n", menuItems[j].item_name, quantity, menuItems[j].item_price * quantity);
            }
        }
    }
    printf("Total: %.2f EUR\n", nouvelle_commande.total);
    printf("---------------------------\n");
}

// Fonction pour afficher l'historique des commandes dynamiques
void afficher_historique_dynamiques() {
    system("cls"); // Effacer l'écran (Windows)
    if (taille_commandes == 0) {
        printf("L'historique des commandes est vide.\n");
    } else {
        printf("Historique des commandes :\n");
        printf("No\tClient\t\tDate\t\tStatut\t\tTotal\n");
        printf("-------------------------------------------------------------\n");
        for (int i = 0; i < taille_commandes; i++) {
            printf("%d\t%s\t%s\t%s\t%.2f\n",
                   commandesDynamiques[i].numero_commande,
                   commandesDynamiques[i].client,
                   commandesDynamiques[i].date,
                   commandesDynamiques[i].statut,
                   commandesDynamiques[i].total);
        }
    }
    printf("\nAppuyez sur une touche pour continuer...");
    getchar(); // Pause avant de revenir au menu
}

// Rechercher une commande dynamique par son numéro
void rechercher_commande(int numero) {
    for (int i = 0; i < taille_commandes; i++) {
        if (commandesDynamiques[i].numero_commande == numero) {
            CommandeDynamique* commande = &commandesDynamiques[i];
            printf("\n--- Détails de la commande ---\n");
            printf("Numéro de commande: %d\n", commande->numero_commande);
            printf("Nom du client: %s\n", commande->client);
            printf("Date: %s\n", commande->date);
            printf("Statut: %s\n", commande->statut);
            printf("Détails de la commande:\n");
            for (int j = 0; j < commande->item_count; j++) {
                int item_id = commande->menu_item_ids[j];
                int quantity = commande->menu_item_quantities[j];
                for (int k = 0; k < menuItemCount; k++) {
                    if (menuItems[k].item_id == item_id) {
                        printf("- %s x%d: %.2f EUR\n", menuItems[k].item_name, quantity, menuItems[k].item_price * quantity);
                    }
                }
            }
            printf("Total: %.2f EUR\n", commande->total);
            printf("---------------------------\n");
            return;
        }
    }
    printf("Commande #%d non trouvée.\n", numero);
}

// Annuler une commande dynamique par son numéro
void annuler_commande(int numero) {
    for (int i = 0; i < taille_commandes; i++) {
        if (commandesDynamiques[i].numero_commande == numero) {
            strcpy(commandesDynamiques[i].statut, "annulée");
            printf("Commande #%d annulée avec succès.\n", numero);
            return;
        }
    }
    printf("Commande #%d non trouvée.\n", numero);
    printf("\nAppuyez sur une touche pour continuer...");
    getchar(); // Pause avant de revenir au menu
}

// Afficher les commandes dynamiques en attente
void afficher_commandes_en_attente_dynamiques() {
    system("cls"); // Effacer l'écran (Windows)
    int en_attente = 0;
    printf("Commandes en attente :\n");
    printf("No\tClient\t\tDate\t\tStatut\t\tTotal\n");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < taille_commandes; i++) {
        if (strcmp(commandesDynamiques[i].statut, "en attente") == 0) {
            printf("%d\t%s\t%s\t%s\t%.2f\n",
                   commandesDynamiques[i].numero_commande,
                   commandesDynamiques[i].client,
                   commandesDynamiques[i].date,
                   commandesDynamiques[i].statut,
                   commandesDynamiques[i].total);
            en_attente++;
        }
    }

    if (en_attente == 0) {
        printf("Aucune commande en attente.\n");
    }
    printf("\nAppuyez sur une touche pour continuer...");
    getchar(); // Pause avant de revenir au menu
}

// Libérer la mémoire allouée pour le tableau dynamique
void liberer_tableau() {
    free(commandesDynamiques);
    commandesDynamiques = NULL;
    capacite = 0;
    taille_commandes = 0;
}

// Menu interactif pour l'utilisateur (dynamique)
void menuDynamique() {
    int choix;
    do {
        system("cls"); // Effacer l'écran (Windows)
        printf("Menu :\n");
        printf("1. Ajouter une commande\n");
        printf("2. Afficher l'historique des commandes\n");
        printf("3. Rechercher une commande\n");
        printf("4. Annuler une commande\n");
        printf("5. Afficher les commandes en attente\n");
        printf("6. Afficher le menu du restaurant\n");
        printf("7. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        getchar(); // Consommer le caractère de nouvelle ligne restant

        switch (choix) {
            case 1:
                ajouterCommandeDynamique();
                break;
            case 2:
                afficher_historique_dynamiques();
                break;
            case 3: {
                int numero;
                printf("Entrez le numéro de commande à rechercher : ");
                scanf("%d", &numero);
                rechercher_commande(numero);
                printf("\nAppuyez sur une touche pour continuer...");
                getchar(); // Pause avant de revenir au menu
                break;
            }
            case 4: {
                int numero;
                printf("Entrez le numéro de commande à annuler : ");
                scanf("%d", &numero);
                annuler_commande(numero);
                printf("\nAppuyez sur une touche pour continuer...");
                getchar(); // Pause avant de revenir au menu
                break;
            }
            case 5:
                afficher_commandes_en_attente_dynamiques();
                break;
            case 6:
                afficherMenu();
                printf("\nAppuyez sur une touche pour continuer...");
                getchar(); // Pause avant de revenir au menu
                break;
            case 7:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 7);

    liberer_tableau();
}

// Fonction principale
int main(int argc, char *argv[]) {
    // Initialiser le tableau dynamique avec une capacité initiale
    capacite = 2;
    commandesDynamiques = (CommandeDynamique *)malloc(capacite * sizeof(CommandeDynamique));
    if (commandesDynamiques == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        return 1;
    }
    initialiserMenu(); // Initialiser le menu avec des éléments prédéfinis

    printf("Choisissez le mode (1: Statique, 2: Dynamique): ");
    int mode;
    scanf("%d", &mode);
    getchar(); // Consommer le caractère de nouvelle ligne restant

    if (mode == 1) {
        // menuStatique();
        printf("Mode statique non implémenté.\n");
    } else if (mode == 2) {
        menuDynamique();
    } else {
        printf("Mode invalide.\n");
    }

    return 0;
}