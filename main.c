#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_TABLES 5
#define MAX_COLUMNS 5
#define MAX_RECORDS 10
#define MAX_STRING 50
#define MAX_ENREGISTREMENTS 50


//Fonction de l'eleve 1

typedef struct {
    char nom[30];
    char type[20];
} Colonne;

typedef struct {
    char valeurs[MAX_COLUMNS][MAX_STRING];
} Enregistrement;

typedef struct {
    char nom[30];
    int nbColonnes;
    Colonne colonnes[MAX_COLUMNS];
    Enregistrement enregistrements[MAX_RECORDS];
    int nbEnregistrements;
} Table;

// Déclaration globale des tables pour conserver les données
Table tables[MAX_TABLES];
/*Le tableau tables[MAX_TABLES] est déclaré globalement
pour que toutes les fonctions puissent y accéder et manipuler les données.*/
int nbTables = 0;
/*Cette variable conserve
le nombre actuel de tables dans le tableau tables.*/

void creerTable(Table* table) {
    int i;
    printf("Entrez le nom de la table : ");
    scanf("%s", table->nom);
    printf("Entrez le nombre de colonnes (max %d) : ", MAX_COLUMNS);
    scanf("%d", &table->nbColonnes);

    if (table->nbColonnes > MAX_COLUMNS) {
        printf("Le nombre de colonnes dépasse la limite de %d.\n", MAX_COLUMNS);
        exit(0);
    }
    for ( i = 0; i < table->nbColonnes; i++) {
        printf("Entrez le nom de la colonne %d : ", i + 1);
        scanf("%s", table->colonnes[i].nom);

        printf("Entrez le type de la colonne %d ( int, char) : ", i + 1);
        scanf("%s", table->colonnes[i].type);
    }
}

void modifierTable(Table* table) {
    int choix,p,i;
    printf("Modification de la table '%s'\n", table->nom);
    printf("1. Ajouter une colonne\n");
    printf("2. Supprimer une colonne\n");
    printf("Votre choix : ");
    scanf("%d", &choix);
    if (choix == 1) {
        if (table->nbColonnes >= MAX_COLUMNS) {
            printf("Impossible d'ajouter une colonne : nombre maximum atteint (%d).\n", MAX_COLUMNS);
            exit(0);
        }
        printf("Entrez le nom de la nouvelle colonne : ");
        scanf("%s", table->colonnes[table->nbColonnes].nom);
        printf("Entrez le type de la nouvelle colonne (int, char) : ");
        scanf("%s", table->colonnes[table->nbColonnes].type);
        table->nbColonnes++;
        }
    else if (choix == 2) {
        if (table->nbColonnes == 0) {
            printf("Impossible de supprimer une colonne : aucune colonne dans la table.\n");
             exit(0);
        }
     printf("Entrez le numéro de la colonne à supprimer : ");
        scanf("%d", &p);
       p--;
        if (p< 0 || p >= table->nbColonnes) {
            printf("Numéro de colonne invalide.\n");
            exit(0);
        }
        for (i = p; i < table->nbColonnes - 1; i++) {
            table->colonnes[i] = table->colonnes[i + 1]; // Décaler les colonnes
        }
        table->nbColonnes--;
        }
    else {
        printf("Choix invalide.\n");
    }
}

//Fonction pour suprimmer un table
void supprimerTable(Table* tables, int* nbTables) {
    int i,p,choix;

    if (*nbTables == 0) {
        printf("Aucune table à supprimer.\n");
        exit(0);
    }
     printf("Tables disponibles :\n");
    for (int i = 0; i < *nbTables; i++) {
        printf("%d. %s\n", i + 1, tables[i].nom);
    }// Afficher les tables disponibles
    printf("Entrez le numéro de la table à supprimer : ");
    scanf("%d", &choix);
    p = choix - 1;
    printf("Suppression de la table '%s'.\n", tables[p].nom);
     for ( i = p; i < *nbTables - 1; i++) {
        tables[i] = tables[i + 1];
    }
     (*nbTables)--;
        printf("Table supprimée avec succès !\n");
}


//Fonction de l'eleve 2

// Fonction pour ajouter un enregistrement dans une table existante
void ajouter_enregistrement() {
    Enregistrement NEnregistrement; // Structure pour le nouvel enregistrement
    char nomTable[MAX_STRING]; // Nom de la table cible
    int i, j;

    // Demander à l'utilisateur de spécifier le nom de la table
    printf("Nom de la table dans laquelle ajouter l'enregistrement : ");
    scanf("%49s", nomTable);

    // Recherche de la table correspondante par son nom
    for (i = 0; i < nbTables; i++) {
        if (strcmp(tables[i].nom, nomTable) == 0) {
            // Vérification si la table a de l'espace pour un nouvel enregistrement
            if (tables[i].nbEnregistrements < MAX_ENREGISTREMENTS) {
                printf("Entrez les valeurs pour l'enregistrement :\n");

                // Demander les valeurs pour chaque colonne
                for (j = 0; j < tables[i].nbColonnes; j++) {
                    printf("Colonne %d: ", j + 1);
                    scanf("%49s", NEnregistrement.valeurs[j]);
                }

                // Ajouter l'enregistrement à la table
                tables[i].enregistrements[tables[i].nbEnregistrements++] = NEnregistrement;
                printf("Enregistrement ajouté avec succès.\n");
                exit(0);
            } else {
                printf("Table pleine, impossible d'ajouter un nouvel enregistrement.\n");
                exit(0);
            }
        }
    }

    // Message d'erreur si la table n'existe pas
    printf("Table '%s' non trouvée.\n", nomTable);
}

// Fonction pour afficher les enregistrements d'une table
void afficher_enregistrements() {
    char nomTable[MAX_STRING]; // Nom de la table cible
    int i,j,k;

    // Demander le nom de la table à afficher
    printf("Entrez le nom de la table dont vous voulez afficher les enregistrements : ");
    scanf("%49s", nomTable);

    // Recherche de la table correspondante
    for (i = 0; i < nbTables; i++) {
        if (strcmp(tables[i].nom, nomTable) == 0) {
            printf("Enregistrements de la table '%s' :\n", nomTable);

            // Si la table est vide
            if (tables[i].nbEnregistrements == 0) {
                printf("Aucun enregistrement trouvé.\n");
                exit(0);
            }

            // Affichage des enregistrements
            for (j = 0; j < tables[i].nbEnregistrements; j++) {
                printf("Enregistrement %d : ", j + 1);
                for (k = 0; k < tables[i].nbColonnes; k++) {
                    printf("%s ", tables[i].enregistrements[j].valeurs[k]);
                }
                printf("\n");
            }
            exit(0);
        }
    }

    // Message d'erreur si la table n'existe pas
    printf("Table '%s' non trouvée.\n", nomTable);
}

// Fonction pour modifier un enregistrement dans une table
void modifier_enregistrement() {
    char nomTable[MAX_STRING]; // Nom de la table cible
    char valeur_recherche[MAX_STRING]; // Valeur à chercher
    int i, j, k;

    // Demander le nom de la table et la valeur à modifier
    printf("Entrez le nom de la table dans laquelle modifier l'enregistrement : ");
    scanf("%49s", nomTable);
    printf("Entrez la valeur de l'enregistrement à modifier : ");
    scanf("%49s", valeur_recherche);

    // Recherche de la table
    for (i = 0; i < nbTables; i++) {
        if (strcmp(tables[i].nom, nomTable) == 0) {
            // Parcourir les enregistrements de la table
            for (j = 0; j < tables[i].nbEnregistrements; j++) {
                // Recherche de la valeur dans les colonnes
                for (k = 0; k < tables[i].nbColonnes; k++) {
                    if (strcmp(tables[i].enregistrements[j].valeurs[k], valeur_recherche) == 0) {
                        printf("Enregistrement trouvé. Entrez la nouvelle valeur pour la colonne %d : ", k + 1);
                        scanf("%49s", tables[i].enregistrements[j].valeurs[k]);
                        printf("Enregistrement modifié avec succès.\n");
                        exit(0);
                    }
                }
            }

            // Message d'erreur si la valeur n'est pas trouvée
            printf("Aucun enregistrement trouvé avec la valeur '%s'.\n", valeur_recherche);
            exit(0);
        }
    }

    // Message d'erreur si la table n'existe pas
    printf("Table '%s' non trouvée.\n", nomTable);
}

// Fonction pour supprimer un enregistrement
void supprimer_enregistrement() {
    char nomTable[MAX_STRING]; // Nom de la table cible
    int i, index, j;

    // Demander le nom de la table
    printf("Nom de la table pour supprimer un enregistrement : ");
    scanf("%49s", nomTable);

    // Recherche de la table
    for (i = 0; i < nbTables; i++) {
        if (strcmp(tables[i].nom, nomTable) == 0) {
            // Si la table est vide
            if (tables[i].nbEnregistrements == 0) {
                printf("Aucun enregistrement dans cette table.\n");
                exit(0);
            }

            // Demander l'index de l'enregistrement à supprimer
            printf("Entrez le numéro de l'enregistrement à supprimer (1 à %d) : ", tables[i].nbEnregistrements);
            scanf("%d", &index);
            index--; // Convertir en index base 0

            // Vérification de la validité de l'index
            if (index < 0 || index >= tables[i].nbEnregistrements) {
                printf("Index d'enregistrement invalide.\n");
                exit(0);
            }

            // Supprimer l'enregistrement en décalant les suivants
            for (j = index; j < tables[i].nbEnregistrements - 1; j++) {
                tables[i].enregistrements[j] = tables[i].enregistrements[j + 1];
            }
            tables[i].nbEnregistrements--;
            printf("Enregistrement supprimé avec succès.\n");
            exit(0);
        }
    }

    // Message d'erreur si la table n'existe pas
    printf("Table '%s' non trouvée.\n", nomTable);
}
//Fonction de l'eleve 3

//Fonction pour sauvegarder une table dans un fichier CSV
void sauvegarderTable(Table table[MAX_COLUMNS][MAX_TABLES], int nbTables,Enregistrement enrg) {
    FILE *fichier = fopen("file.txt", "w"); // Ouvrir le fichier en mode écriture
    char nomTable[30];
    int i,j;
    if (fichier == NULL) {
        printf("Erreur: Impossible d'ouvrir le fichier pour sauvegarde.\n");
        exit(0);
    }

    // Écrire le nom de la table en première ligne
    fprintf(fichier, "Table: %s\n", nomTable);

    // Parcourir les enregistrements (lignes)
    for (i = 0; i < nbEnregistrements; i++) {
        // Parcourir les colonnes de chaque enregistrement
        for (j = 0; j < nbColonnes; j++) {
            fprintf(fichier, "%s", table[i][j]); // Écrire une colonne
            if (j < nbColonnes - 1) {
                fprintf(fichier, ","); // Ajouter une virgule sauf pour la dernière colonne
            }
        }
        fprintf(fichier, "\n"); // Passer à la ligne suivante pour chaque enregistrement
    }

    fclose(fichier); // Fermer le fichier
    printf("Table sauvegardée avec succès dans %s.\n", nomFichier);
}

//Fonction pour charge un tableau d'un fichier
void chargerCSV() {
    FILE *fichier = fopen("file.txt", "r"); // R pour lire le contenu du fichier
    Table table;
    char ligne[128];
    int i = 0;
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", nomFichier);
        return 0;
    }

    fgets(ligne, sizeof(ligne), fichier); // Ignorer l'en-tête

    // Lire chaque ligne et extraire les données
    while (fgets(ligne, sizeof(ligne), fichier) != NULL && i < MAX_RECORDS) {
      if (sscanf(ligne, "%d,%9[^,],%f",&table[i].id, table[i].nom, &table[i].salaire) == 3) {
            i++;
        } else {
            printf("Erreur de lecture sur la ligne : %s\n", ligne);
        }
    }
    fclose(fichier);
}

//Fonction 4eme etudiant
//Fonction pour trier les enregistrement
void Tri() {
    int i, j, indiceC = -1;
    char Nom_table[20];
    char Nom_C[20];

    Enregistrement temp;
    Table tables[MAX_TABLES];

    printf("Nom de la table : ");
    scanf("%s", Nom_table);

    printf("Nom de la colonne pour le tri : ");
    scanf("%s", Nom_C);

    // Recherche de la table
    for (i = 0; i < MAX_TABLES; i++) {
        if (strcmp(tables[i].Nom, Nom_table) == 0) {  // Comparaison avec le nom de la table
            // Recherche de l'indice de la colonne
            for (j = 0; j < tables[i].nbr_C; j++) {
                if (strcmp(tables[i].Colonnes[j], Nom_C) == 0) {  // Comparaison avec les colonnes
                    indiceC = j;
                    break;  // On sort de la boucle dès qu'on trouve la colonne
                }
            }

            // Si la colonne n'est pas trouvée
            if (indiceC == -1) {
                printf("Colonne '%s' introuvable.\n", Nom_C);
                return;
            }

            // Tri des enregistrements (tri à bulles)
            for (i = 0; i < tables[i].nbr_E - 1; i++) {
                for (j = 0; j < tables[i].nbr_E - i - 1; j++) {
                    if (strcmp(tables[i].enregistrements[j].valeurs[indiceC], tables[i].enregistrements[j + 1].valeurs[indiceC]) > 0) {
                        // Échange des enregistrements
                        temp = tables[i].enregistrements[j];
                        tables[i].enregistrements[j] = tables[i].enregistrements[j + 1];
                        tables[i].enregistrements[j + 1] = temp;
                    }
                }
            }

            // Affichage du message de confirmation
            printf("\nTable triée par '%s'.\n", Nom_C);
            exit(0);  // Sortir de la fonction après avoir trié
        }
    }

    // Si la table n'est pas trouvée
    printf("Table '%s' introuvable.\n", Nom_table);
}
}
//Fonction pour rechercher un enregistrement
void Chercher() {
    Table tables[MAX_TABLES];  // Tableau de tables
    char Nom_table[20];
    char Nom_C[20];
    char valeur[20];
    int i, j, k, indiceC = -1;  // Correction de la syntaxe des variables

    printf("Nom de la table : ");
    scanf("%s", Nom_table);

    // Recherche de la table
    for (i = 0; i < MAX_TABLES; i++) {
        if (strcmp(tables[i].Nom, Nom_table) == 0) {  // Comparer avec le nom de la table
            printf("Nom de la colonne : ");
            scanf("%s", Nom_C);
            printf("Valeur à rechercher : ");
            scanf("%s", valeur);

            // Recherche de l'indice de la colonne
            for (j = 0; j < tables[i].nbr_C; j++) {
                if (strcmp(tables[i].Colonnes[j], Nom_C) == 0) {  // Correction pour comparer avec le nom de la colonne
                    indiceC = j;
                    break;  // On sort de la boucle dès qu'on trouve la colonne
                }
            }
            if (indiceC != -1) {  // Si la colonne a été trouvée
                // Recherche de la valeur dans les enregistrements
                for (k = 0; k < tables[i].nbr_E; k++) {
                    if (strcmp(tables[i].enregistrements[k][indiceC], valeur) == 0) {
                        for (j = 0; j < tables[i].nbr_C; j++) {
                            printf("%s \t", tables[i].enregistrements[k][j]);
                        }
                        printf("\n");
                    }
                }
            } else {
                printf("Colonne %s non trouvée.\n", Nom_C);
            }
            exit(0);  // Sortir de la fonction une fois la table trouvée
        }
    }
    printf("Table %s non trouvée.\n", Nom_table);
}

//Le main
int main() {
    Table tables[MAX_TABLES];
    int nbTables = 0,choix,numTable;
    chargerCSV();
    while (1) {
        printf("\n--- Gestionnaire de base de données simplifiée ---\n");
    printf("1. Créer une table\n");
    printf("2. Modifier une table\n");
    printf("3. Supprimer une table\n");
    printf("4. Ajouter un enregistrement\n");
    printf("5. Afficher les enregistrements\n");
    printf("6. Modifier un enregistrement\n");
    printf("7. Supprimer un enregistrement\n");
    printf("8. Sauvegarder une table dans un fichier\n");
    printf("9. Charger un tableau\n");
    printf("10. Trier les enregistrements \n");
    printf("11. Rechercher un enregistrement \n");
    printf("12. Quitter\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                if (nbTables < MAX_TABLES) {
                    creerTable(&tables[nbTables]);
                    nbTables++;
                } else {
                    printf("Le nombre maximal de tables est atteint.\n");
                }
                break;
            case 2:
                printf("Sélectionner la table à modifier :\n");
                for (int i = 0; i < nbTables; i++) {
                    printf("%d. %s\n", i + 1, tables[i].nom);
                }
                printf("Entrez le numéro de la table : ");
                scanf("%d", &numTable);
                if (numTable > 0 && numTable <= nbTables) {
                    modifierTable(&tables[numTable - 1]);
                } else {
                    printf("Numéro de table invalide.\n");
                }
                break;
            case 3:
                supprimerTable(tables, &nbTables);
                break;
            case 4:
                ajouter_enregistrement(tables, nbTables);
                break;
            case 5:
                afficher_enregistrements(tables, nbTables);
                break;
            case 6:
                modifier_enregistrement(tables, nbTables);
                break;
            case 7:
                supprimer_enregistrement(tables, nbTables);
                break;
            case 8:
                sauvegarderTable(nom, nbTables);
                break;
            case 9:
                chargerCSV;
                break;
            case 10:
                Tri();
                break;
            case 11:
                Chercher();
                break;
            case 12:
                printf("Quitter le programme...\n");
                return 0;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    }
}
