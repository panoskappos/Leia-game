#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TRUE 1
#define FALSE 0


typedef struct Entity {
    char name;
    int life;
    int position_x;
    int position_y;
}Entity;

//rounds numbers
int roundnum(double x){
    int y;
    y = x + 0.5;
    return y;
}

//STAR WARS logo
void star_wars(void) {
    printf("\nA long time ago in a galaxy far, far away...\n");
    printf("         _____ _______       _____  \n");
    printf("        / ____|__   __|/\\   |  __ \\ \n");
    printf("       | (___    | |  /  \\  | |__) | \n");
    printf("        \\___ \\   | | / /\\ \\ |  _  / \n");
    printf("      ______) |  | |/ ____ \\| | \\ \\ \n");
    printf("     |_______/   |_/_/    \\_\\_|  \\_\\ \n");
    printf("___     _     ___  __     _____     _____  \n");
    printf("\\  \\   / \\   /   //  \\   |  __ \\   / ____|\n");
    printf(" \\  \\_/   \\_/   // /\\ \\  | |__) | | (___ \n");
    printf("  \\     __     // ____ \\ |  _  /   \\___  \\\n");
    printf("   \\   /  \\   // /    \\ \\| | \\ \\  _____)  |\n");
    printf("    \\_/    \\_//_/      \\_|_|  \\_\\|_______/\n\n");
}

//GAME OVER logo
void game_over(void) {
    printf("                                                                      \n");
    printf("   _____          __  __ ______    ______      ________ _____  \n");
    printf("  / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\ \n");
    printf(" | |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) |\n");
    printf(" | | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  / \n");
    printf(" | |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\ \n");
    printf("  \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_\\\n");
    printf("                                                                      \n");
}

//Moves Entities safely in the game
int movePlayer(Entity *entity, char direction, char ***array, int rows, int columns) {
    int k = 0;
    int p = 0;
        switch(direction) {
            case 'R':
            case 'r':
                p = entity->position_y + 1;
                k = entity->position_x;
                break;
            case 'U':
            case 'u':
                k = entity->position_x - 1;
                p = entity->position_y;
                break;
            case 'L':
            case 'l':
                p = entity->position_y - 1;
                k = entity->position_x;
                break;
            case 'D':
            case 'd':
                k = entity->position_x + 1;
                p = entity->position_y;
                break;
            case 'X':
            case 'x':
                exit(1);
                break;
            case 'H':
            case 'h':
                return 99;
                break;
            default:
                printf("Invalid input. Type 'r' for right, 'l' for left, 'u' for up, 'd' for down\n");
                return -1;
        }
    if (k >= rows || k < 0) {
        printf("You cant go there. That's outside of the board\n");
        return 0;
    }
    else if ((p+1) > columns || p < 0) {
        printf("You cant go there. That's outside of the board\n");
        return 0;
    }
    else if(array[0][k][p] == 'X') {
        printf("You cant go there. Something blocking your way\n");
        return 0;
    }
    else{
        entity->position_x = k;
        entity->position_y = p;
        if(array[0][k][p] == '@' &&  entity->name == 'L'){
            entity->life--;
            return 66;
        }
    }
    return 1;
}

int checkObj(char ***array, int x, int y) {
    if(array[0][x][y] == 'X') {
        return 1;
    }
    else if(array[0][x][y] == '.') {
        return 44;
    }
    else {
        return -1;
    }
    return 0;
}

//"killing" some Entity
void entitydeath(Entity *entity) { 
    entity->life--;
}

//filling fields for some Entity
void fillEstuff(Entity *entity, char name, int life, int numrows, int numcolumns, char ***array){
    entity->name = name;
    entity->life = life;
    entity->position_x = rand() % numrows;
    entity->position_y = rand() % numcolumns;
    while(array[0][entity->position_x][ entity->position_y] != '.') {
        entity->position_x = rand() % numrows;
        entity->position_y = rand() % numcolumns;
    }    
}

void fillDarth(Entity *entity, char name, int life, int numrows, int numcolumns, char ***array){
    entity->name = name;
    entity->life = life;
    int luck = rand() % 4;
    if(luck == 0) {
        entity->position_x = 0;
        entity->position_y = 0;
    }
    else if(luck == 1) {
        entity->position_x = 0;
        entity->position_y = numcolumns - 1;
    }
    else if(luck == 2) {
        entity->position_x = numrows - 1;
        entity->position_y = 0;
    }
    else {
        entity->position_x = numrows - 1;
        entity->position_y = numcolumns - 1;
    } 
}

//Creates 3D array
char*** createGame(int dim1, int dim2, int dim3) {
    int i, j;
    
    // Allocate memory for the first dimension
    char*** array = (char***)malloc(dim1 * sizeof(char**));
    if (array == NULL) {
        printf("Memory allocation failed for first dimension.\n");
        exit(1);
    }
    
    // Allocate memory for the second dimension
    for (i = 0; i < dim1; i++) {
        array[i] = (char**)malloc(dim2 * sizeof(char*));
        if (array[i] == NULL) {
            printf("Memory allocation failed for second dimension.\n");
            exit(1);
        }
    }
    
    // Allocate memory for the third dimension
    for (i = 0; i < dim1; i++) {
        for (j = 0; j < dim2; j++) {
            array[i][j] = (char*)malloc(dim3 * sizeof(char));
            if (array[i][j] == NULL) {
                printf("Memory allocation failed for third dimension.\n");
                exit(1);
            }
        }
    }

    return array;
}

//free's memmory for 3D array
void freeGame(char*** array, int dim1, int dim2) {
    int i, j;
    
// Free memory for the third dimension
    for (i = 0; i < dim1; i++) {
        for (j = 0; j < dim2; j++) {
            free(array[i][j]);
        }
    }
    
// Free memory for the second dimension
    for (i = 0; i < dim1; i++) {
        free(array[i]);
    }
    
// Free memory for the first dimension
    free(array);
}

int moveObj(char ***array, char a[5], Entity *obj, int objnum) {
    int i;
    int deletterP = a[0] - 97;
    int deletterA = a[3] - 97;
    int denumberP = a[1] - 49;
    int denumberA = a[4] - 49;
    int num = checkObj(array, denumberP, deletterP);
    if(num == 1) {//Checks for the obj
        num = checkObj(array, denumberA, deletterA);
        if(num == 44) {//checks if any Entities are in the coordinates
            for(i = 0; i < objnum; i++) {
                if(obj[i].position_x == denumberP && obj[i].position_y == deletterP) {
                    obj[i].position_x = denumberA;
                    obj[i].position_y = deletterA;
                    array[0][denumberP][deletterP] =  '.';
                    array[0][obj[i].position_x][obj[i].position_y] =  obj[i].name;
                }
            }
            return 30;
        }
        printf("Leia: There is something there i cant move the object\n");
        return 0;
    }
    else {
        printf("Leia: There is no object to move there\n");
        return 0;
    }
    return 1;
}

void moveDarth(char ***array, Entity *entity1, Entity *entity2, int rows, int columns) {
    int tryx;
    int tryy;
    if(entity1->position_x == entity2->position_x && entity1->position_y > entity2->position_y) {
        tryy = entity1->position_y - 1;
        tryx = entity1->position_x;
        if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
            if((tryx + 1) >= rows) {
                tryy = entity1->position_y - 1;
                tryx = entity1->position_x;
            }
            else {
                tryy = entity1->position_y - 1;
                tryx = entity1->position_x + 1;
            }
            if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                if((tryx - 1) < rows) {
                    tryy = entity1->position_y - 1;
                    tryx = entity1->position_x;
                }
                else {
                    tryy = entity1->position_y - 1;
                    tryx = entity1->position_x - 1;
                }
                if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                    if((tryx + 1) >= rows) {
                        tryy = entity1->position_y - 1;
                        tryx = entity1->position_x;
                    }
                    else {
                        tryy = entity1->position_y;
                        tryx = entity1->position_x + 1;
                    }
                    if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                        if((tryx - 1) < rows) {
                            tryy = entity1->position_y - 1;
                            tryx = entity1->position_x;
                        }
                        else {
                            tryy = entity1->position_y;
                            tryx = entity1->position_x - 1;
                        }
                        if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                            if((tryx + 1) >= rows || (tryy + 1) >= columns) {
                                tryy = entity1->position_y - 1;
                                tryx = entity1->position_x;
                            }
                            else {
                                tryy = entity1->position_y + 1;
                                tryx = entity1->position_x + 1;
                            }
                            if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                                if((tryx - 1) < rows) {
                                    tryy = entity1->position_y - 1;
                                    tryx = entity1->position_x;
                                }
                                else {
                                    tryy = entity1->position_y + 1;
                                    tryx = entity1->position_x - 1;
                                }
                                if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                                    if((tryy + 1) >= columns) {
                                        tryy = entity1->position_y - 1;
                                        tryx = entity1->position_x;
                                    }
                                    else {
                                        tryy = entity1->position_y + 1;
                                        tryx = entity1->position_x;
                                    }
                                    if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                                        tryy = entity1->position_y;
                                        tryx = entity1->position_x;
                                        printf("Leia: Guess i am lucky this round Darth Vader cant move\n");
                                    }
                                }
                            }
                        }        
                    }
                }
            }
        }
    }
    else if(entity1->position_x == entity2->position_x && entity1->position_y < entity2->position_y) {
        tryy = entity1->position_y + 1;
        tryx = entity1->position_x;
        if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
            if((tryx - 1) < rows) {
                tryy = entity1->position_y + 1;
                tryx = entity1->position_x;
            }
            else {
                tryy = entity1->position_y + 1;
                tryx = entity1->position_x - 1;
            }
            if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                if((tryx + 1) >= rows) {
                    tryy = entity1->position_y + 1;
                    tryx = entity1->position_x;
                }
                else {
                    tryy = entity1->position_y + 1;
                    tryx = entity1->position_x + 1;
                }
                if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                    if((tryx + 1) >= rows) {
                        tryy = entity1->position_y + 1;
                        tryx = entity1->position_x;
                    }
                    else {
                        tryy = entity1->position_y;
                        tryx = entity1->position_x + 1;
                    }
                    if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                        if((tryx - 1) < rows) {
                            tryy = entity1->position_y + 1;
                            tryx = entity1->position_x;
                        }
                        else {
                            tryy = entity1->position_y;
                            tryx = entity1->position_x - 1;
                        }
                        if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                            if((tryx + 1) >= rows || (tryy - 1) < columns) {
                                tryy = entity1->position_y + 1;
                                tryx = entity1->position_x;
                            }
                            else {
                                tryy = entity1->position_y - 1;
                                tryx = entity1->position_x + 1;
                            }
                            if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                                if((tryx - 1) < rows || (tryy - 1) < columns) {
                                    tryy = entity1->position_y + 1;
                                    tryx = entity1->position_x;
                                }
                                else {
                                    tryy = entity1->position_y - 1;
                                    tryx = entity1->position_x - 1;
                                }
                                if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                                    if((tryy - 1) < columns) {
                                        tryy = entity1->position_y + 1;
                                        tryx = entity1->position_x;
                                    }
                                    else {
                                        tryy = entity1->position_y - 1;
                                        tryx = entity1->position_x;
                                    }
                                    if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                                        tryy = entity1->position_y;
                                        tryx = entity1->position_x;
                                        printf("Leia: Guess i am lucky this round Darth Vader cant move\n");
                                    }
                                }
                            }
                        }        
                    }
                }
            }
        }
    }
    else if(entity1->position_x > entity2->position_x && entity1->position_y == entity2->position_y) {
        tryy = entity1->position_y;
        tryx = entity1->position_x - 1;
        if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
            if((tryy + 1) >= columns) {
                tryy = entity1->position_y;
                tryx = entity1->position_x - 1;
            }
            else {
                tryy = entity1->position_y + 1;
                tryx = entity1->position_x - 1;
            }
            if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                if((tryy - 1) < columns) {
                    tryy = entity1->position_y;
                    tryx = entity1->position_x  - 1;
                }
                else {
                    tryy = entity1->position_y - 1;
                    tryx = entity1->position_x - 1;
                }
                if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                    if((tryy + 1) >= columns) {
                        tryy = entity1->position_y;
                        tryx = entity1->position_x  - 1;
                    }
                    else {
                        tryy = entity1->position_y + 1;
                        tryx = entity1->position_x;
                    }
                    if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                        if((tryy - 1) < columns) {
                            tryy = entity1->position_y;
                            tryx = entity1->position_x - 1;
                        }
                        else {
                            tryy = entity1->position_y - 1;
                            tryx = entity1->position_x;
                        }
                        if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                            if((tryx + 1) >= rows || (tryy + 1) >= columns) {
                                tryy = entity1->position_y;
                                tryx = entity1->position_x - 1;
                            }
                            else {
                                tryy = entity1->position_y + 1;
                                tryx = entity1->position_x + 1;
                            }
                            if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                                if((tryx + 1) >= rows || (tryy - 1) < columns) {
                                    tryy = entity1->position_y;
                                    tryx = entity1->position_x - 1;
                                }
                                else {
                                    tryy = entity1->position_y - 1;
                                    tryx = entity1->position_x + 1;
                                }
                                if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                                    if((tryx + 1) >= rows) {
                                        tryy = entity1->position_y;
                                        tryx = entity1->position_x - 1;
                                    }
                                    else {
                                        tryy = entity1->position_y;
                                        tryx = entity1->position_x + 1;
                                    }
                                    if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                                        tryy = entity1->position_y;
                                        tryx = entity1->position_x;
                                        printf("Leia: Guess i am lucky this round Darth Vader cant move\n");
                                    }
                                }
                            }
                        }        
                    }
                }
            }
        }
    }
    else if(entity1->position_x < entity2->position_x && entity1->position_y == entity2->position_y) {
        tryy = entity1->position_y;
        tryx = entity1->position_x + 1;
        if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
            if((tryy + 1) >= columns) {
                tryy = entity1->position_y;
                tryx = entity1->position_x + 1;
            }
            else {
                tryy = entity1->position_y + 1;
                tryx = entity1->position_x + 1;
            }
            if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                if((tryy - 1) < columns) {
                    tryy = entity1->position_y;
                    tryx = entity1->position_x + 1;
                }
                else {
                    tryy = entity1->position_y - 1;
                    tryx = entity1->position_x + 1;
                }
                if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                    if((tryy + 1) >= columns) {
                        tryy = entity1->position_y;
                        tryx = entity1->position_x + 1;
                    }
                    else {
                        tryy = entity1->position_y + 1;
                        tryx = entity1->position_x;
                    }
                    if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                        if((tryy - 1) < columns) {
                            tryy = entity1->position_y;
                            tryx = entity1->position_x + 1;
                        }
                        else {
                            tryy = entity1->position_y - 1;
                            tryx = entity1->position_x;
                        }
                        if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                            if((tryx - 1) < rows || (tryy + 1) >= columns) {
                                tryy = entity1->position_y;
                                tryx = entity1->position_x + 1;
                            }
                            else {
                                tryy = entity1->position_y + 1;
                                tryx = entity1->position_x - 1;
                            }
                            if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                                if((tryx - 1) < rows || (tryy - 1) < columns) {
                                    tryy = entity1->position_y;
                                    tryx = entity1->position_x + 1;
                                }
                                else {
                                    tryy = entity1->position_y - 1;
                                    tryx = entity1->position_x - 1;
                                }
                                if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                                    if((tryx - 1) < rows) {
                                        tryy = entity1->position_y;
                                        tryx = entity1->position_x + 1;
                                    }
                                    else {
                                        tryy = entity1->position_y;
                                        tryx = entity1->position_x - 1;
                                    }
                                    if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                                        tryy = entity1->position_y;
                                        tryx = entity1->position_x;
                                        printf("Leia: Guess i am lucky this round Darth Vader cant move\n");
                                    }
                                }
                            }
                        }        
                    }
                }
            }
        }
    }
    else if(entity1->position_x > entity2->position_x && entity1->position_y > entity2->position_y) {
        tryy = entity1->position_y - 1;
        tryx = entity1->position_x - 1;
        if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
            if((tryx - 1) < rows) {//its impossible because Lx<Dx but so safety
                tryy = entity1->position_y - 1;
                tryx = entity1->position_x - 1;
            }
            else {
                tryy = entity1->position_y;
                tryx = entity1->position_x - 1;
            }
            if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                if((tryy - 1) < columns) {//its impossible because Ly<Dy but so safety
                    tryy = entity1->position_y - 1;
                    tryx = entity1->position_x - 1;
                }
                else {
                    tryy = entity1->position_y - 1;
                    tryx = entity1->position_x;
                }
                if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                    if((tryx + 1) >= rows || (tryy - 1) < columns) {
                        tryy = entity1->position_y - 1;
                        tryx = entity1->position_x - 1;
                    }
                    else {
                        tryy = entity1->position_y - 1;
                        tryx = entity1->position_x + 1;
                    }
                    if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                        if((tryx - 1) < rows || (tryy + 1) >= columns) {
                            tryy = entity1->position_y - 1;
                            tryx = entity1->position_x - 1;
                        }
                        else {
                            tryy = entity1->position_y + 1;
                            tryx = entity1->position_x - 1;
                        }
                        if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                            if((tryy + 1) >= columns) {
                                tryy = entity1->position_y - 1;
                                tryx = entity1->position_x - 1;
                            }
                            else {
                                tryy = entity1->position_y + 1;
                                tryx = entity1->position_x;
                            }
                            if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                                if((tryx + 1) >= rows) {
                                    tryy = entity1->position_y - 1;
                                    tryx = entity1->position_x - 1;
                                }
                                else {
                                    tryy = entity1->position_y;
                                    tryx = entity1->position_x + 1;
                                }
                                if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                                    if((tryx + 1) >= rows || (tryy + 1) >= columns) {
                                        tryy = entity1->position_y - 1;
                                        tryx = entity1->position_x - 1;
                                    }
                                    else {
                                        tryy = entity1->position_y + 1;
                                        tryx = entity1->position_x + 1;
                                    }
                                    if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                                        tryy = entity1->position_y;
                                        tryx = entity1->position_x;
                                        printf("Leia: Guess i am lucky this round Darth Vader cant move\n");
                                    }
                                }
                            }
                        }        
                    }
                }
            }
        }
    }////////////////////
    else if(entity1->position_x < entity2->position_x && entity1->position_y < entity2->position_y) {
        tryy = entity1->position_y + 1;
        tryx = entity1->position_x + 1;
        if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
            if((tryx + 1) >= rows) {//its impossible because Lx>Dx but so safety
                tryy = entity1->position_y + 1;
                tryx = entity1->position_x + 1;
            }
            else {
                tryy = entity1->position_y;
                tryx = entity1->position_x + 1;
            }
            if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                if((tryy + 1) >= columns) {//its impossible because Ly>Dy but so safety
                    tryy = entity1->position_y + 1;
                    tryx = entity1->position_x + 1;
                }
                else {
                    tryy = entity1->position_y + 1;
                    tryx = entity1->position_x;
                }
                if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                    if((tryx + 1) >= rows || (tryy - 1) < columns) {
                        tryy = entity1->position_y + 1;
                        tryx = entity1->position_x + 1;
                    }
                    else {
                        tryy = entity1->position_y - 1;
                        tryx = entity1->position_x + 1;
                    }
                    if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                        if((tryx - 1) < rows || (tryy + 1) >= columns){
                            tryy = entity1->position_y + 1;
                            tryx = entity1->position_x + 1;
                        }
                        else {
                            tryy = entity1->position_y + 1;
                            tryx = entity1->position_x - 1;
                        }
                        if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                            if((tryy - 1) < columns) {
                                tryy = entity1->position_y + 1;
                                tryx = entity1->position_x + 1;
                            }
                            else {
                                tryy = entity1->position_y - 1;
                                tryx = entity1->position_x;
                            }
                            if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                                if((tryx - 1) < rows) {
                                    tryy = entity1->position_y + 1;
                                    tryx = entity1->position_x + 1;
                                }
                                else {
                                    tryy = entity1->position_y;
                                    tryx = entity1->position_x - 1;
                                }
                                if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                                    if((tryx - 1) < rows || (tryy - 1) < columns) {
                                        tryy = entity1->position_y + 1;
                                        tryx = entity1->position_x + 1;
                                    }
                                    else {
                                        tryy = entity1->position_y - 1;
                                        tryx = entity1->position_x - 1;
                                    }
                                    if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                                        tryy = entity1->position_y;
                                        tryx = entity1->position_x;
                                        printf("Leia: Guess i am lucky this round Darth Vader cant move\n");
                                    }
                                }
                            }
                        }        
                    }
                }
            }
        }
    }
    else if(entity1->position_x > entity2->position_x && entity1->position_y < entity2->position_y) {
        tryy = entity1->position_y + 1;
        tryx = entity1->position_x - 1;
        if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
            if((tryy + 1) >= columns) {//its impossible because Ly>Dy but for safety
                tryy = entity1->position_y + 1;
                tryx = entity1->position_x - 1;
            }
            else {
                tryy = entity1->position_y + 1;
                tryx = entity1->position_x;
            }
            if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                if((tryx - 1) < rows) {//its impossible because Lx<Dx but for safety
                    tryy = entity1->position_y + 1;
                    tryx = entity1->position_x - 1;
                }
                else {
                    tryy = entity1->position_y;
                    tryx = entity1->position_x - 1;
                }
                if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                    if((tryx + 1) >= rows || (tryy + 1) >= columns) {
                        tryy = entity1->position_y + 1;
                        tryx = entity1->position_x - 1;
                    }
                    else {
                        tryy = entity1->position_y + 1;
                        tryx = entity1->position_x + 1;
                    }
                    if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                        if((tryx - 1) < rows || (tryy - 1) < columns) {
                            tryy = entity1->position_y + 1;
                            tryx = entity1->position_x - 1;
                        }
                        else {
                            tryy = entity1->position_y - 1;
                            tryx = entity1->position_x - 1;
                        }
                        if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                            if((tryx + 1) >= rows) {
                                tryy = entity1->position_y + 1;
                                tryx = entity1->position_x - 1;
                            }
                            else {
                                tryy = entity1->position_y;
                                tryx = entity1->position_x + 1;
                            }
                            if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                                if((tryy - 1) < columns) {
                                    tryy = entity1->position_y + 1;
                                    tryx = entity1->position_x - 1;
                                }
                                else {
                                    tryy = entity1->position_y - 1;
                                    tryx = entity1->position_x;
                                }
                                if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                                    if((tryx + 1) >= rows || (tryy - 1) < columns) {
                                        tryy = entity1->position_y + 1;
                                        tryx = entity1->position_x - 1;
                                    }
                                    else {
                                        tryy = entity1->position_y - 1;
                                        tryx = entity1->position_x + 1;
                                    }
                                    if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                                        tryy = entity1->position_y;
                                        tryx = entity1->position_x;
                                        printf("Leia: Guess i am lucky this round Darth Vader cant move\n");
                                    }
                                }
                            }
                        }        
                    }
                }
            }
        }
    }
    else if(entity1->position_x < entity2->position_x && entity1->position_y > entity2->position_y) {
        tryy = entity1->position_y - 1;
        tryx = entity1->position_x + 1;
        if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
            if((tryy - 1) < columns) {//its impossible because Ly<Dy but for safety
                tryy = entity1->position_y - 1;
                tryx = entity1->position_x + 1;
            }
            else {
                tryy = entity1->position_y - 1;
                tryx = entity1->position_x;
            }
            if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                if((tryx + 1) >= rows) {//its impossible because Lx>Dx but for safety
                    tryy = entity1->position_y - 1;
                    tryx = entity1->position_x + 1;
                }
                else {
                    tryy = entity1->position_y;
                    tryx = entity1->position_x + 1;
                }
                if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                    if((tryx - 1) < rows || (tryy - 1) < columns) {
                        tryy = entity1->position_y - 1;
                        tryx = entity1->position_x + 1;
                    }
                    else {
                        tryy = entity1->position_y - 1;
                        tryx = entity1->position_x - 1;
                    }
                    if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                        if((tryx + 1) >= rows || (tryy + 1) >= columns) {
                            tryy = entity1->position_y - 1;
                            tryx = entity1->position_x + 1;
                        }
                        else {
                            tryy = entity1->position_y + 1;
                            tryx = entity1->position_x + 1;
                        }
                        if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                            if((tryy + 1) >= columns) {
                                tryy = entity1->position_y - 1;
                                tryx = entity1->position_x + 1;
                            }
                            else {
                                tryy = entity1->position_y + 1;
                                tryx = entity1->position_x;
                            }
                            if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                                if((tryx - 1) < rows) {
                                    tryy = entity1->position_y - 1;
                                    tryx = entity1->position_x + 1;
                                }
                                else {
                                    tryy = entity1->position_y;
                                    tryx = entity1->position_x - 1;
                                }
                                if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                                    if((tryx - 1) < rows || (tryy + 1) >= columns) {
                                        tryy = entity1->position_y - 1;
                                        tryx = entity1->position_x + 1;
                                    }
                                    else {
                                        tryy = entity1->position_y + 1;
                                        tryx = entity1->position_x - 1;
                                    }
                                    if(array[0][tryx][tryy] == 'X' || array[0][tryx][tryy] == 'R' || array[0][tryx][tryy] == '@') {
                                        tryy = entity1->position_y;
                                        tryx = entity1->position_x;
                                        printf("Leia: Guess i am lucky this round Darth Vader cant move\n");
                                    }
                                }
                            }
                        }        
                    }
                }
            }
        }
    }
    else {
        exit(66);
    }
    entity1->position_x = tryx;
    entity1->position_y = tryy;
}
//doesnt work
// int moveTkpos(char ***array,int *special, Entity *tk, int num, int rows, int columns) {
//     int tryx, tryy;
//     if(special[num] == 0) {
//         tryx = tk[num].position_x + 1;
//     }
//     else {
//         tryy = tk[num].position_y + 1;
//     }
//     if(array[0][tryx][tryy] != '.' || tryx >= rows || tryy >= columns) {
//         return 0;
//     }
//     else {
//         tk[num].position_x = tryx;
//         tk[num].position_y = tryy;
//         array[0][tk[num].position_x][tk[num].position_y] = tk[num].name;
//         return 1;
//     }
// }
// //doesnt work
// int moveTkneg(char ***array,int *special, Entity *tk, int num, int rows, int columns) {
//     int tryx, tryy;
//     if(special[num] == 0) {
//         tryx = tk[num].position_x - 1;
//     }
//     else {
//         tryy = tk[num].position_y - 1;
//     }
//     if(array[0][tryx][tryy] != '.' || tryx < rows || tryy < columns) {
//         return 0;
//     }
//     else {
//         tk[num].position_x = tryx;
//         tk[num].position_y = tryy;
//         array[0][tk[num].position_x][tk[num].position_y] = tk[num].name;
//         return 1;
//     }
// }
// for(i = 0; i <tknum; i++) {
//                 if(mad == 0) {
//                     ret = moveTkpos(game, spTk, tk, i, rows, columns);
//                     if(ret == 0) {
//                         mad = 1;                   
//                     }
//                 }
//                 if(mad == 1){
//                     ret = moveTkneg(game, spTk, tk, i, rows, columns);
//                     if(ret == 0) {
//                         mad = 0;                   
//                     }
//                 }
//             }


int main() {// N=x=rows and M=y=columns
    star_wars();
// Initialize the random number generator
    srand((unsigned int)time(NULL));
    char ans;
    int rows = 0, columns = 0;
    int i,j;
    int flag = FALSE;
    int on = FALSE;
    int level = 1;
//elegxos eggyrothtas
    while(!flag) {
        printf("C-3PO: Give me board size (columns, rows)\n\t\tRULES\n1)Bigger than 3 x 3 \n2)Smaller than 80 x 26:\nSuggested starting size under 20 x 20:\n");
        if(scanf("%d%d",&rows ,&columns) == 2) {
            printf("You typed %d columns and %d rows\nType 'y' for yes or 'n' for no: ",rows ,columns);
            scanf(" %c",&ans);
            if (ans == 'y' || ans == 'n' || ans == 'Y' || ans == 'N') {
                if(ans == 'y' || ans == 'Y') {
                    flag = TRUE;
                }
            }
            else {
                printf("C-3PO: Invalid input, please enter 'y' or 'n'.\n");
            }
        }
        else {
            printf("C-3PO: Invalid input, please enter two integers.\n");
            //Clear the input buffer to avoid an infinite loop
            while (getchar() != '\n');
        }
    
        if(columns > 26 || rows > 80 || columns < 4 || rows < 4 || columns * rows <= 12) {
            flag = FALSE;
            printf("\nC-3PO: Invalid board size, please read the rules.\n");
        }
    }
    flag = FALSE;
    while(!flag) {
        printf("\nChoose game difficulty\nC-3PO: e for easy, m for medium, h for hard, i for impossible: \n");
        scanf(" %c",&ans);
        if(ans!='e' && ans!='m' && ans!='h' && ans!='i') {
            printf("C-3PO: Invalid input, valid inputs are 'e', 'm', 'h', 'i' .\n");
        }
        else if(ans=='e' || ans=='m' || ans=='h' || ans=='i') {
            flag = TRUE;
        }
        // Clear the input buffer to avoid an infinite loop
        while (getchar() != '\n');
    }
    flag = FALSE;

//game
    while(on == FALSE){
        char ***game = createGame(2, rows, columns);
        int m = 2;
        int rb = columns + 2;
        int **a;
        char **b;

//malloc a,b
        a = (int **)malloc(rows * sizeof(int*));
        if (a == NULL) {
            printf("C-3PO: Memory allocation for a array failed on first dimension.\n");
            exit(1);
        }
        for(i = 0; i < rows; i++) {
            a[i] = (int *)malloc(m * sizeof(int));
            if (a[i] == NULL) {
                printf("C-3PO: Memory allocation for a array failed on second dimension.\n");
                exit(1);
            }
        }
        
        b = (char **)malloc(rb * sizeof(char*));
        if (b == NULL) {
            printf("C-3PO: Memory allocation for b array failed on first dimension.\n");
            exit(1);
        }
        for(i = 0; i < rb; i++) {
            b[i] = (char *)malloc(m * sizeof(char));
            if (b[i] == NULL) {
                printf("C-3PO: Memory allocation for b array failed on second dimension.\n");
                exit(1);
            }
        }
        
//a array
        for(i = 0; i < rows; i++) {
            for(j = 0; j < m; j++) {
                if(j == 0) 
                    a[i][j] = i+1;
                else
                    a[i][j] = 124;
            }
        }
//b array
        for(j = 0; j < rb; j++) {
            if (j < 2)
                b[0][j] = ' ';
            else
                b[0][j] = 'A' + (j-2);
            }
            for(j = 0; j < rb; j++) {
                b[1][j] = '_';
            }

//Filling first dimension with .
        for (i = 0; i < rows; i++ ) {
            for(j = 0; j < columns; j++) {
                game[0][i][j] = '.';
            }
        }

//Filling Second dimension with #
        for (i = 0; i < rows; i++ ) {
            for(j = 0; j < columns; j++) {
                game[1][i][j] = '#';
            }
        }

//Creating Leia, Darth, r2d2 and putting them in the game
        Entity leia, r2d2, darth_vader;
        fillDarth(&darth_vader, 'D', 100, rows, columns, game);
        game[0][darth_vader.position_x][darth_vader.position_y] = darth_vader.name;
        fillEstuff(&leia, 'L', 2, rows, columns, game);
        game[0][leia.position_x][leia.position_y] = leia.name;
        fillEstuff(&r2d2, 'R', 100, rows, columns, game);
        game[0][r2d2.position_x][r2d2.position_y] = r2d2.name;

//Creating Stormtroopers and objects(putting obj in the game)
        Entity *tk;
        Entity *obj;
        int sizeBoard = rows * columns;
        int tknum = 0;
        int objnum = 0;
        if(ans == 'e') {
            if(level == 1){
            printf("The difficulty is set on easy\n");    
            }  
            tknum = roundnum(sizeBoard * 0.02);
            if(tknum < 2){
                tknum = 2;
            }
            tk = (Entity*)malloc(tknum * sizeof(Entity));
            if (tk == NULL) {
                printf("C-3PO: Memory allocation for tk(i) failed.\n");
                exit(1);
            }
            for(i = 0; i < tknum; i++){
                fillEstuff(&tk[i], '@', 1, rows, columns, game);
                game[0][tk[i].position_x][tk[i].position_y] = tk[i].name;
            }
            objnum = roundnum(sizeBoard * 0.13);
            obj = (Entity*)malloc(objnum * sizeof(Entity));
            if (obj == NULL) {
                printf("C-3PO: Ohhh my, memory allocation for obj(e) failed.\n");
                exit(1);
            }
            for(i = 0; i < objnum; i++){
                fillEstuff(&obj[i], 'X', 100, rows, columns, game);
                game[0][obj[i].position_x][obj[i].position_y] = obj[i].name;
            }
        }
        else if(ans == 'm') {
            if(level == 1){
            printf("The difficulty is set on easy\n");    
            }  
            tknum = roundnum(sizeBoard * 0.05);
            if(tknum < 2){
                tknum = 2;
            }
            tk = (Entity*)malloc(tknum * sizeof(Entity));
            if (tk == NULL) {
                printf("C-3PO: Memory allocation for tk(i) failed.\n");
                exit(1);
            }
            for(i = 0; i < tknum; i++){
                fillEstuff(&tk[i], '@', 1, rows, columns, game);
                game[0][tk[i].position_x][tk[i].position_y] = tk[i].name;
            }
            objnum = roundnum(sizeBoard * 0.10);
            obj = (Entity*)malloc(objnum * sizeof(Entity));
            if (obj == NULL) {
                printf("C-3PO: Memory allocation for obj(m) failed.\n");
                exit(1);
            }
            for(i = 0; i < objnum; i++){
                fillEstuff(&obj[i], 'X', 100, rows, columns, game);
                game[0][obj[i].position_x][obj[i].position_y] = obj[i].name;
            }
        }
        else if(ans == 'h') {
            if(level == 1){
            printf("The difficulty is set on easy\n");    
            }  
            tknum = roundnum(sizeBoard * 0.10);
            if(tknum < 2){
                tknum = 2;
            }
            tk = (Entity*)malloc(tknum * sizeof(Entity));
            if (tk == NULL) {
                printf("C-3PO: Memory allocation for tk(i) failed.\n");
                exit(1);
            }
            for(i = 0; i < tknum; i++){
                fillEstuff(&tk[i], '@', 1, rows, columns, game);
                game[0][tk[i].position_x][tk[i].position_y] = tk[i].name;
            }
            objnum = roundnum(sizeBoard * 0.05);
            obj = (Entity*)malloc(objnum * sizeof(Entity));
            if (obj == NULL) {
                printf("C-3PO: Ohhh my, memory allocation for obj(h) failed.\n");
                exit(1);
            }
            for(i = 0; i < objnum; i++){
                fillEstuff(&obj[i], 'X', 100, rows, columns, game);
                game[0][obj[i].position_x][obj[i].position_y] = obj[i].name;
            }
        }
        else if(ans == 'i') {
            if(level == 1){
            printf("The difficulty is set on easy\n");    
            }  
            tknum = roundnum(sizeBoard * 0.15);
            if(tknum < 2){
                tknum = 2;
            }
            tk = (Entity*)malloc(tknum * sizeof(Entity));
            if (tk == NULL) {
                printf("C-3PO: Memory allocation for tk(i) failed.\n");
                exit(1);
            }
            for(i = 0; i < tknum; i++){
                fillEstuff(&tk[i], '@', 1, rows, columns, game);
                game[0][tk[i].position_x][tk[i].position_y] = tk[i].name;
            }
            objnum = roundnum(sizeBoard * 0);
            obj = (Entity*)malloc(objnum * sizeof(Entity));
            if (obj == NULL) {
                printf("C-3PO: Memory allocation for obj(i) failed.\n");
                exit(1);
            }
            for(i = 0; i < objnum; i++){
                fillEstuff(&obj[i], 'X', 100, rows, columns, game);
                game[0][obj[i].position_x][obj[i].position_y] = obj[i].name;
            }
        }
        else {
        return 1;
        }
//special array for tk random movement
        int *spTk;
        spTk = (int *)malloc(tknum * sizeof(int));
        if (spTk == NULL) {
            printf("C-3PO: Memory allocation for spTk array failed.\n");
            exit(1);
        }
        for(i = 0; i < tknum; i++){
            spTk[i] = rand() % 2;
        }

        int key = TRUE;
        int counter = 2;//how many times leia can move an obj
        int ret = -1;
        int value = 0;
        int view = 1;
        //int mad = 0;

        while(key == TRUE) {
            //Printing b
            for(i = 0; i < m; i++) {
                for(j = 0; j < rb; j++) {
                    printf("%c  ", b[i][j]);
                }
                printf("\n");
            }
//Printing main board
            for (i = 0; i < rows; i++ ) {
                for(j = 0; j < rb; j++) {
                    int k = j-2;
                    if(j < 2) {
                        if(a[i][j] != 124 && j < 2) {
                            if(i < 9)
                                printf("%d  ", a[i][j]);
                            else {
                                printf("%d ", a[i][j]);
                            }
                        }
                        else {
                            printf("%c ", a[i][j]);
                        }
                    }
                    else if(game[0][i][k] != '.' && game[0][i][k] != r2d2.name && game[0][i][k] != '@') {
                        printf(" %c ",game[0][i][k]);
                    }
                    else if(i == leia.position_x || k == leia.position_y) {//leia's force eyes
                        printf(" %c ",game[0][i][k]);
                    }
                    else {
                        printf(" %c ",game[view][i][k]);
                    }
                }
            printf("\n");
            }
            view = 1;
//making a game move
            printf("\nlevel:%d\n",level);
            printf("Make your move(s)\n");
            char ans2[5];
            ans2[2] = '\0';
            scanf(" %5s", &ans2);    
            if(ans2[2] == '>') {//the game now knows we want to move an obj
                if(counter > 0) {        
                    if(moveObj(game, ans2, obj, objnum) == 30) {                    
                        counter--;
                    }
                    
                }
                else {
                    printf("Leia: I cant move any more objects\n");
                }
            }
            else {
                if(value == 1) {
                    game[0][darth_vader.position_x][darth_vader.position_y] = '.';
                    moveDarth(game, &darth_vader, &leia, rows, columns);
                    game[0][darth_vader.position_x][darth_vader.position_y] = darth_vader.name;
                }

                game[0][leia.position_x][leia.position_y] = '.';
                ret = movePlayer(&leia, ans2[0], game, rows, columns);
                if(ret == 99) {
                    view = 0;
                    value = 1;
                }
                else if(ret == 66) {
                    if(leia.life <= 0) {
                        game_over();
                        exit(1);
                    }
                    printf("Leia: I killed him but got injured wont be so lucky next time watch out\n");
                }
                game[0][leia.position_x][leia.position_y] = leia.name;
                
                if((leia.position_x == darth_vader.position_x) && (leia.position_y == darth_vader.position_y)) {
                    key = FALSE;
                    game_over();
                    exit(1);
                }
                else if((leia.position_x == r2d2.position_x) && (leia.position_y == r2d2.position_y)) {
                    key = FALSE;
                    printf("next Level:\n");
                }
                if(value == 0) {
                value = 1;
                }
                else {
                    value = 0;
                }               
            }
        }
        //Free memory
        freeGame(game, 2, rows);
        free(tk);
        free(obj);
        free(a);
        free(b);
        free(spTk);
        level = level + 1;
        rows = rows - 1;
        columns = columns -1;
        sizeBoard = columns * rows;
        //Checks if we have won
        if(sizeBoard <= 12) {
            on = TRUE;
            printf("\nC-3PO:\nWe've successfully completed the mission, delivering the crucial plans for the Death Star.\nOh my, what an accomplishment! With great joy, I hereby announce our triumphant success in the \nconveyance of the most critical intelligence! Huzzah!\n");
        }
    }
    return 0;
}
