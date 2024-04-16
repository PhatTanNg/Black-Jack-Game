#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Function to compare hands and print result
void compareHands(char* playerName, int playerSum, int dealerSum);

//Function to load game from Saved Game
void loadGame(const char* filename, int numOfPlayer, int playerCard[][20], char playerCardDeck[][20], int sumOfCard[], int countOfCard[], char playerName[][20]);


void main() {
  
    printf("\t\t\tWelcome to Black Jack Game Card\n\t\t\t\tIntroduction\n\tBlackjack has been one of the most popular casino games of the last hundred years and has spread throughout the world.\n\tPlayers compete against the dealer rather than each other.\n\tThe objective is to get a hand total closer to 21 than the dealer without going over 21.\n\n\n");
    
    int gameLoaded = 0;
    int numOfPlayer;
    int startNewGame = 0;
    char playOption = 'n';
    char playerOption ='n';
    char filename[20];
    char renew;
    int numOfDeck;

    int numOfcard;
    int deckCardPlay[2][208];
    int suit = 0;

    int dealerSum = 0;
    int playerCard[4][20];
    int playerCardDeck[4][20];
    int sumOfCard[4] = { 0, 0, 0, 0 };
    int countOfCard[4] = { 0, 0, 0, 0 };
    char burst[4][10];


    char leftBurst[4];
    int leftHandCard[4][20];
    int leftHandCardDeck[4][20];
    int sumOfLeftHandCard[4] = { 0, 0, 0, 0 };
    int leftCountCard[4] = { 0, 0, 0, 0 };

    char rightBurst[4];
    int rightHandCard[4][20];
    int rightHandCardDeck[4][20];
    int sumOfRightHandCard[4] = { 0, 0, 0, 0 };
    int rightCountCard[4] = { 0, 0, 0, 0 };

    char playerName[4][20];
    int splitChoice[4] = { 0 }; // Array to store split choice for each player

    do {
        dealerSum = 0;
        int sumOfCard[4] = { 0, 0, 0, 0 };
        int countOfCard[4] = { 0, 0, 0, 0 };
        
            do
            {

               
                    
                

                
                    //take number of player
                    do {
                        printf("How many players in the game? - Choose from 2 to 4 - include the dealer: ");
                        scanf("%d", &numOfPlayer);
                        printf("");
                        FILE* file1;
                        file1 = fopen("numOfPlayer.txt", "w");
                        fprintf(file1, "%d", numOfPlayer);
                        fclose(file1);
                    } while (numOfPlayer >= 5 || numOfPlayer <= 1);

                    //take name for player
                    for (int i = 0; i < numOfPlayer; i++) {
                        if (i == (numOfPlayer - 1)) {
                            printf("Enter name for dealer: ");
                            scanf("%20s", &playerName[numOfPlayer - 1]);
                            printf("");
                            i = numOfPlayer;
                        }
                        else {
                            printf("Enter name for player %d: ", i + 1);
                            scanf("%20s", &playerName[i]);
                            printf("");
                        }
                    }

                    //take number of deck
                    do {
                        printf("Hi %s, how many decks of cards do you want to use in this game? Enter from 1 to 4: ", playerName[0]);
                        scanf("%d", &numOfDeck);
                        numOfcard = numOfDeck * 52;
                        printf("\n\n");
                    } while (numOfDeck < 1 || numOfDeck > 4);


                    //set card deck to all the card
                    for (int valueOfCard = 0; valueOfCard < numOfcard; valueOfCard++) {
                        deckCardPlay[0][valueOfCard] = valueOfCard % 13 + 1;

                        if (valueOfCard % 13 == 0)
                            suit = suit + 1;

                        if (valueOfCard % 52 == 0)
                            suit = 0;

                        switch (suit) {
                        case 0:
                            deckCardPlay[1][valueOfCard] = 'H';
                            break;
                        case 1:
                            deckCardPlay[1][valueOfCard] = 'D';
                            break;
                        case 2:
                            deckCardPlay[1][valueOfCard] = 'C';
                            break;
                        case 3:
                            deckCardPlay[1][valueOfCard] = 'S';
                            break;
                        }
                    }

                    //give each player 2 card and show their card
                    for (int a = 0; a < numOfPlayer; a++) {
                        for (int b = 0; b < 2; b++) {
                            int cardRandom = rand() % numOfcard + 1;
                            int card = cardRandom % 13 + 1;
                            playerCard[a][b] = card;
                            sumOfCard[a] = sumOfCard[a] + card;
                            playerCardDeck[a][b] = deckCardPlay[1][cardRandom];
                            printf("Hi %s, your card is %d with suit %c\n", playerName[a], playerCard[a][b], playerCardDeck[a][b]);
                            countOfCard[a] = countOfCard[a] + 1;
                            if (a == (numOfPlayer - 1))
                                dealerSum = dealerSum + card;
                        }
                        printf("Your total point for now is %d\n\n\n", sumOfCard[a]);

                        //show dealer first card
                        if (a == (numOfPlayer - 1)) {
                            printf("The dealer's first card is: %d with suit %c\n", playerCard[a][0], playerCardDeck[a][0]);
                            printf("");
                        }
                        if (a == (numOfPlayer - 1) && playerCard[a][0] == 10)
                            printf("The dealer's second card is: %d with suit %c\n", playerCard[a][1], playerCardDeck[a][1]);
                    }
                






                //player's turn to play
                for (int i = 0; i < numOfPlayer - 1; i++) {
                    char playerOption;
                    printf("Player %s 's turn to play - Press 's' for Stand, 'h' for Hit and 'p' for Split: ", playerName[i]);
                    scanf(" %c", &playerOption);
                    printf("");

                    do {
                        //Stand option
                        if (playerOption == 's' || playerOption == 'S') {
                            printf("You choose to Stand with your cards.\n");
                            printf("Your total point is: %d\n", sumOfCard[i]);

                            for (int a = 0; a < countOfCard[i]; a++) {
                                printf("\tCard number %d is %d with suit %c\n", a + 1, playerCard[i][a], playerCardDeck[i][a]);
                            }
                            break;
                        }
                        //Hit Option
                        if (playerOption == 'h' || playerOption == 'H') {
                            int cardRandom = rand() % numOfcard + 1;
                            int card = cardRandom % 13 + 1;
                            playerCard[i][countOfCard[i]] = card;
                            sumOfCard[i] = sumOfCard[i] + card;
                            playerCardDeck[i][countOfCard[i]] = deckCardPlay[1][cardRandom];
                            printf("Your next card is %d with suit %c\n", playerCard[i][countOfCard[i]], playerCardDeck[i][countOfCard[i]]);
                            printf("Total value you have is: %d\n", sumOfCard[i]);
                            countOfCard[i] = countOfCard[i] + 1;

                            //if dealer burst
                            if (i == (numOfPlayer - 1)) {
                                dealerSum = dealerSum + card;

                                if (sumOfCard[i] > 21) {
                                    printf("You burst!!\nGame Over!!\n");
                                    break; // Exit the loop if the player busts
                                }
                                else {
                                    printf("Player %s 's turn to play - Press 's' for Stand, 'h' for Hit and 'p' for Split: ", playerName[i]);
                                    scanf(" %c", &playerOption);
                                    printf("");
                                }
                            }
                            else {
                                //if player burst
                                if (sumOfCard[i] > 21) {
                                    printf("You burst!!\nGame Over!!\n");
                                    break; // Exit the loop if the player busts
                                }
                                else {
                                    printf("Player %s 's turn to play - Press 's' for Stand, 'h' for Hit and 'p' for Split: ", playerName[i]);
                                    scanf(" %c", &playerOption);
                                    printf("");
                                }
                            }
                        }

                        //Split option
                        if (playerOption == 'p' || playerOption == 'P') {
                            if (playerCard[i][0] == playerCard[i][1] || playerCard[i][0] == 10 || playerCard[i][1] == 10) {
                                splitChoice[i] = 1; // Player chose to split

                                int sumOfRightHandCard[4] = { playerCard[0][1], playerCard[1][1], playerCard[2][1], playerCard[3][1] };
                                int sumOfLeftHandCard[4] = { playerCard[0][0], playerCard[1][0], playerCard[2][0], playerCard[3][0] };
                                // Left Hand Card
                                leftHandCard[i][0] = playerCard[i][0];
                                leftHandCardDeck[i][0] = playerCardDeck[i][0];
                                int leftCardRandom = rand() % numOfcard + 1;
                                int leftcard = leftCardRandom % 13 + 1;
                                leftHandCard[i][1] = leftcard;
                                leftHandCardDeck[i][1] = deckCardPlay[1][leftCardRandom];
                                sumOfLeftHandCard[i] = sumOfLeftHandCard[i] + leftcard;
                                printf("Your 2 cards on the left hand side are:\n\t\t%d with suit %c\n\t\t%d with suit %c\n", leftHandCard[i][0], leftHandCardDeck[i][0], leftHandCard[i][1], leftHandCardDeck[i][1]);
                                leftCountCard[i] = leftCountCard[i] + 1;
                                printf("Press 's' for Stand, 'h' for Hit ");
                                scanf(" %c", &playerOption);
                                printf("");

                                do {
                                    if (playerOption == 's' || playerOption == 'S') {
                                        printf("You choose to Stand with your cards.\n");
                                        for (int a = 0; a < leftCountCard[i]; a++) {
                                            printf("\tCard number %d is %d with suit %c\n", a + 1, leftHandCard[i][a], leftHandCardDeck[i][a]);
                                        }
                                        break;
                                    }

                                    if (playerOption == 'h' || playerOption == 'H') {
                                        int cardRandom = rand() % numOfcard + 1;
                                        int card = cardRandom % 13 + 1;
                                        leftHandCard[i][leftCountCard[i] + 1] = card;
                                        sumOfLeftHandCard[i] = sumOfLeftHandCard[i] + card;
                                        leftHandCardDeck[i][leftCountCard[i]] = deckCardPlay[1][cardRandom];
                                        printf("Your next card is %d with suit %c\n", leftHandCard[i][leftCountCard[i]], leftHandCardDeck[i][leftCountCard[i]]);
                                        printf("Total value you have is: %d\n", sumOfLeftHandCard[i]);
                                        leftCountCard[i] = leftCountCard[i] + 1;

                                        if (sumOfLeftHandCard[i] > 21) {
                                            leftBurst[i] = "burst";
                                            printf("You burst!!\nGame Over!!\n");
                                            break;
                                        }
                                        else {
                                            printf("Press 's' for Stand, 'h' for Hit: ");
                                            scanf(" %c", &playerOption);
                                            printf("");
                                        }
                                        if (i == numOfPlayer - 1) {
                                            dealerSum = dealerSum + card;
                                        }
                                    }
                                } while (playerOption != 's' || playerOption != 'S');

                                // Right Hand Card
                                rightHandCard[i][0] = playerCard[i][0];
                                rightHandCardDeck[i][0] = playerCardDeck[i][0];
                                int rightCardRandom = rand() % numOfcard + 1;
                                int rightcard = rightCardRandom % 13 + 1;
                                rightHandCard[i][1] = rightcard;
                                rightHandCardDeck[i][1] = deckCardPlay[1][rightCardRandom];
                                sumOfRightHandCard[i] = sumOfRightHandCard[i] + rightcard;
                                printf("Your 2 cards on the right hand side are:\n\t\t%d with suit %c\n\t\t%d with suit %c\n", rightHandCard[i][0], rightHandCardDeck[i][0], rightHandCard[i][1], rightHandCardDeck[i][1]);
                                rightCountCard[i] = rightCountCard[i] + 1;
                                printf("Press 's' for Stand, 'h' for Hit ");
                                scanf(" %c", &playerOption);
                                printf("");

                                do {
                                    if (playerOption == 's' || playerOption == 'S') {
                                        printf("You choose to Stand with your cards.\n");
                                        for (int a = 0; a < rightCountCard[i]; a++) {
                                            printf("\tCard number %d is %d with suit %c\n", a + 1, rightHandCard[i][a], rightHandCardDeck[i][a]);
                                        }
                                        break;
                                    }

                                    if (playerOption == 'h' || playerOption == 'H') {
                                        int cardRandom = rand() % numOfcard + 1;
                                        int card = cardRandom % 13 + 1;
                                        rightHandCard[i][rightCountCard[i] + 1] = card;
                                        sumOfRightHandCard[i] = sumOfRightHandCard[i] + card;
                                        rightHandCardDeck[i][rightCountCard[i]] = deckCardPlay[1][cardRandom];
                                        printf("Your next card is %d with suit %c\n", rightHandCard[i][rightCountCard[i]], rightHandCardDeck[i][rightCountCard[i]]);
                                        printf("Total value you have is: %d\n", sumOfRightHandCard[i]);
                                        rightCountCard[i] = rightCountCard[i] + 1;

                                        if (sumOfRightHandCard[i] > 21) {
                                            rightBurst[i] = "burst";
                                            printf("You burst!!\nGame Over!!\n");
                                            break;
                                        }
                                        else {
                                            printf("Press 's' for Stand, 'h' for Hit: ");
                                            scanf(" %c", &playerOption);
                                            printf("");
                                        }
                                        if (i == numOfPlayer - 1) {
                                            dealerSum = dealerSum + card;
                                        }
                                    }
                                } while (playerOption != 's' || playerOption != 'S');
                            }
                        }

                    } while (playerOption != 's' || playerOption != 'S');

                    //player options to save or exit the game

                    printf("Option for the games:\n");
                    printf("S for Save\n");
                    printf("E for exit\n");
                    printf("C for complete\n");
                    printf("O for output game status.\n");
                    scanf(" %c", &playerOption);

                    //save
                    if (playerOption == 's' || playerOption == 'S') {

                        for (int d = 0; d < numOfPlayer; d++) {
                            sprintf(filename, "player%d.txt", d + 1);
                            FILE* file = fopen(filename, "w");
                            fprintf(file, "%s\n", playerName[d]);
                            fprintf(file, "%d\n", countOfCard[d]);
                            for (int a = 0; a < countOfCard[d]; a++) {
                                fprintf(file, "%d\n", playerCard[d][a]);
                            }
                            for (int a = 0; a < countOfCard[d]; a++) {
                                fprintf(file, "%c\n", playerCardDeck[d][a]);
                            }
                            fprintf(file, "%d\n", sumOfCard[d]);
                            fclose(file);
                        }
                        //second option if player hit save
                        printf("Option for the games:\n");
                        printf("N for New Game\n");
                        printf("E for exit\n");
                        printf("S for continue Saved Game\n");
                        scanf(" %c", &playerOption);
                        //exit
                        if (playerOption == 'E' || playerOption == 'e')
                        {
                            printf("Existing the game....\n");
                            return 0;
                        }
                        //new game
                        if (playerOption == 'N' || playerOption == 'n')
                        {
                            printf("Starting a new game...\n");
                            startNewGame = 1; // Set the flag to start a new game
                            break; // Break out of the inner loop for the current player
                        }
                        //save
                        if (playerOption == 'S' || playerOption == 's') {
                            for (int d = 0; d < numOfPlayer; d++) {
                                sprintf(filename, "player%d.txt", d + 1);
                                loadGame(filename, numOfPlayer, playerCard[d], playerCardDeck[d], &sumOfCard[d], &countOfCard[d], playerName[d]);
                            }
                            for (int a = 0; a < numOfPlayer; a++) {
                                printf("Player %s:\n", playerName[a]);
                                for (int b = 0; b < countOfCard[a]; b++) {
                                    printf("\tCard number %d is %d with suit %c\n", b + 1, playerCard[a][b], playerCardDeck[a][b]);
                                }
                            }

                            printf("Game loaded successfully!\n");
                            startNewGame = 0;
                            gameLoaded = 1;
                    
                        }
                    }
                    //exit
                    if (playerOption == 'E' || playerOption == 'e')
                    {
                        printf("Existing the game....\n");
                        return 0;
                    }
                    //complete
                    if (playerOption == 'C' || playerOption == 'c')
                    {
                        printf("You completed your turn!\n");
                        gameLoaded = 0;
                    }

                    //output the game status
                    if (playerOption == 'o' || playerOption == 'O')
                    {
                        for (int a = 0; a <= i; a++)
                        {
                            printf("Player %s:\n", playerName[a]);
                            for (int b = 0; b < countOfCard[a]; b++) {
                                printf("\tCard number %d is %d with suit %c\n", b + 1, playerCard[a][b], playerCardDeck[a][b]);
                            }
                        }
                    }


                    if (startNewGame) {
                        printf("Exiting the current game...\n");
                        break; // Break out of the outer loop to start a new game

                    }

                }

            } while (playerOption == 'n' && playerOption == 'N');
        
        printf("\n\nDealer's turn:\n");
        printf("The dealer's first card is: %d with suit %c\n", playerCard[numOfPlayer - 1][0], playerCardDeck[numOfPlayer - 1][0]);
        printf("The dealer's second card is: %d with suit %c\n", playerCard[numOfPlayer - 1][1], playerCardDeck[numOfPlayer - 1][1]);
        while (dealerSum < 17) {
            int cardRandom = rand() % numOfcard + 1;
            int card = cardRandom % 13 + 1;
            dealerSum = dealerSum + card;
            printf("The dealer draws a card: %d with suit %c\n", card, deckCardPlay[1][cardRandom]);
        }

        printf("The dealer's total point is: %d\n\n", dealerSum);
        //compare dealer with player
        for (int i = 0; i < numOfPlayer - 1; i++) {
            if (splitChoice[i] == 1) {
                compareHands(playerName[i], sumOfLeftHandCard[i], dealerSum);
                compareHands(playerName[i], sumOfRightHandCard[i], dealerSum);
            }
            else {
                compareHands(playerName[i], sumOfCard[i], dealerSum);
            }
        }
        printf("Press Y (yes) or N (No) to play again: ");
        scanf(" %c", &playOption);
        printf("");
        
    } while (playOption == 'Y' || playOption == 'y');

}
// Function to compare hands and print result
void compareHands(char* playerName, int playerSum, int dealerSum)
{
    printf("%s's hand:\n", playerName);
    printf("Total point: %d\n", playerSum);

    if (playerSum > 21) {
        printf("Bust! %s loses.\n", playerName);
    }
    else if (dealerSum > 21 || playerSum > dealerSum) {
        printf("%s wins!\n", playerName);
    }
    else if (playerSum == dealerSum) {
        printf("%s and the dealer tie.\n", playerName);
    }
    else {
        printf("%s loses to the dealer.\n", playerName);
    }
}

void loadGame(const char* filename, int numOfPlayer, int playerCard[][20], char playerCardDeck[][20], int sumOfCard[], int countOfCard[], char playerName[][20]) {
    FILE* file = fopen(filename, "r");

    if (!file) {
        perror("Error opening the file");
        return;
    }

    int numOfPlayers;
    fscanf(file, "%d", &numOfPlayers);

    for (int i = 0; i < numOfPlayers; i++) {
        int countOfCards;
        fscanf(file, "%s", playerName[i]);  // Corrected to read player names

        fscanf(file, "%d", &countOfCards);

        for (int j = 0; j < countOfCards; j++) {
            fscanf(file, "%d", &playerCard[i][j]);
        }

        for (int j = 0; j < countOfCards; j++) {
            fscanf(file, " %c", &playerCardDeck[i][j]);
        }

        fscanf(file, "%d", &sumOfCard[i]);

        // Your existing code might need modification for other parts of the data

    }

    fclose(file);
}

//Below is the code i used for getting the saved game if the player not choose to start a new game at the beginning of the game but It could not work. It does get the data out of the file but by at some point it just 
//jump right into the dealer hand card and skip all the player turn
/* do
 {
     printf("New Game Or Save Game? Press S for save or N for new:");
     scanf(" %c", &playOption);

 } while (!(playOption == 'n' || playOption =='N'|| playOption == 's' || playOption == 'S'));

 while (playOption == 'S' || playOption == 'S')
 {
     int numOfPlayer;

     FILE* file1 = fopen("numOfPlayer.txt", "r");

     if (!file1) {
         perror("Error opening the file");
         return 1;
     }

     fscanf(file1, "%d", &numOfPlayer);
     fclose(file1);

     for (int d = 0; d < numOfPlayer; d++) {
         sprintf(filename, "player%d.txt", d + 1);
         loadGame(filename, numOfPlayer, playerCard[d], playerCardDeck[d], &sumOfCard[d], &countOfCard[d], playerName[d]);
     }
         for (int a = 0; a <= numOfPlayer; a++)
         {
             printf("Player %s:\n", playerName[a]);
             for (int b = 0; b < countOfCard[a]; b++) {
                 printf("\tCard number %d is %d with suit %c\n", b + 1, playerCard[a][b], playerCardDeck[a][b]);
             }
         }
         //player's turn to play
         for (int i = 0; i < numOfPlayer - 1; i++) {
             char playerOption;
             printf("Player %s 's turn to play - Press 's' for Stand, 'h' for Hit and 'p' for Split: ", playerName[i]);
             scanf(" %c", &playerOption);
             printf("");

             do {
                 //Stand option
                 if (playerOption == 's' || playerOption == 'S') {
                     printf("You choose to Stand with your cards.\n");
                     printf("Your total point is: %d\n", sumOfCard[i]);

                     for (int a = 0; a < countOfCard[i]; a++) {
                         printf("\tCard number %d is %d with suit %c\n", a + 1, playerCard[i][a], playerCardDeck[i][a]);
                     }
                     break;
                 }
                 //Hit Option
                 if (playerOption == 'h' || playerOption == 'H') {
                     int cardRandom = rand() % numOfcard + 1;
                     int card = cardRandom % 13 + 1;
                     playerCard[i][countOfCard[i]] = card;
                     sumOfCard[i] = sumOfCard[i] + card;
                     playerCardDeck[i][countOfCard[i]] = deckCardPlay[1][cardRandom];
                     printf("Your next card is %d with suit %c\n", playerCard[i][countOfCard[i]], playerCardDeck[i][countOfCard[i]]);
                     printf("Total value you have is: %d\n", sumOfCard[i]);
                     countOfCard[i] = countOfCard[i] + 1;

                     //if dealer burst
                     if (i == (numOfPlayer - 1)) {
                         dealerSum = dealerSum + card;

                         if (sumOfCard[i] > 21) {
                             printf("You burst!!\nGame Over!!\n");
                             break; // Exit the loop if the player busts
                         }
                         else {
                             printf("Player %s 's turn to play - Press 's' for Stand, 'h' for Hit and 'p' for Split: ", playerName[i]);
                             scanf(" %c", &playerOption);
                             printf("");
                         }
                     }
                     else {
                         //if player burst
                         if (sumOfCard[i] > 21) {
                             printf("You burst!!\nGame Over!!\n");
                             break; // Exit the loop if the player busts
                         }
                         else {
                             printf("Player %s 's turn to play - Press 's' for Stand, 'h' for Hit and 'p' for Split: ", playerName[i]);
                             scanf(" %c", &playerOption);
                             printf("");
                         }
                     }
                 }

                 //Split option
                 if (playerOption == 'p' || playerOption == 'P') {
                     if (playerCard[i][0] == playerCard[i][1] || playerCard[i][0] == 10 || playerCard[i][1] == 10) {
                         splitChoice[i] = 1; // Player chose to split

                         int sumOfRightHandCard[4] = { playerCard[0][1], playerCard[1][1], playerCard[2][1], playerCard[3][1] };
                         int sumOfLeftHandCard[4] = { playerCard[0][0], playerCard[1][0], playerCard[2][0], playerCard[3][0] };
                         // Left Hand Card
                         leftHandCard[i][0] = playerCard[i][0];
                         leftHandCardDeck[i][0] = playerCardDeck[i][0];
                         int leftCardRandom = rand() % numOfcard + 1;
                         int leftcard = leftCardRandom % 13 + 1;
                         leftHandCard[i][1] = leftcard;
                         leftHandCardDeck[i][1] = deckCardPlay[1][leftCardRandom];
                         sumOfLeftHandCard[i] = sumOfLeftHandCard[i] + leftcard;
                         printf("Your 2 cards on the left hand side are:\n\t\t%d with suit %c\n\t\t%d with suit %c\n", leftHandCard[i][0], leftHandCardDeck[i][0], leftHandCard[i][1], leftHandCardDeck[i][1]);
                         leftCountCard[i] = leftCountCard[i] + 1;
                         printf("Press 's' for Stand, 'h' for Hit ");
                         scanf(" %c", &playerOption);
                         printf("");

                         do {
                             if (playerOption == 's' || playerOption == 'S') {
                                 printf("You choose to Stand with your cards.\n");
                                 for (int a = 0; a < leftCountCard[i]; a++) {
                                     printf("\tCard number %d is %d with suit %c\n", a + 1, leftHandCard[i][a], leftHandCardDeck[i][a]);
                                 }
                                 break;
                             }

                             if (playerOption == 'h' || playerOption == 'H') {
                                 int cardRandom = rand() % numOfcard + 1;
                                 int card = cardRandom % 13 + 1;
                                 leftHandCard[i][leftCountCard[i] + 1] = card;
                                 sumOfLeftHandCard[i] = sumOfLeftHandCard[i] + card;
                                 leftHandCardDeck[i][leftCountCard[i]] = deckCardPlay[1][cardRandom];
                                 printf("Your next card is %d with suit %c\n", leftHandCard[i][leftCountCard[i]], leftHandCardDeck[i][leftCountCard[i]]);
                                 printf("Total value you have is: %d\n", sumOfLeftHandCard[i]);
                                 leftCountCard[i] = leftCountCard[i] + 1;

                                 if (sumOfLeftHandCard[i] > 21) {
                                     leftBurst[i] = "burst";
                                     printf("You burst!!\nGame Over!!\n");
                                     break;
                                 }
                                 else {
                                     printf("Press 's' for Stand, 'h' for Hit: ");
                                     scanf(" %c", &playerOption);
                                     printf("");
                                 }
                                 if (i == numOfPlayer - 1) {
                                     dealerSum = dealerSum + card;
                                 }
                             }
                         } while (playerOption != 's' || playerOption != 'S');

                         // Right Hand Card
                         rightHandCard[i][0] = playerCard[i][0];
                         rightHandCardDeck[i][0] = playerCardDeck[i][0];
                         int rightCardRandom = rand() % numOfcard + 1;
                         int rightcard = rightCardRandom % 13 + 1;
                         rightHandCard[i][1] = rightcard;
                         rightHandCardDeck[i][1] = deckCardPlay[1][rightCardRandom];
                         sumOfRightHandCard[i] = sumOfRightHandCard[i] + rightcard;
                         printf("Your 2 cards on the right hand side are:\n\t\t%d with suit %c\n\t\t%d with suit %c\n", rightHandCard[i][0], rightHandCardDeck[i][0], rightHandCard[i][1], rightHandCardDeck[i][1]);
                         rightCountCard[i] = rightCountCard[i] + 1;
                         printf("Press 's' for Stand, 'h' for Hit ");
                         scanf(" %c", &playerOption);
                         printf("");

                         do {
                             if (playerOption == 's' || playerOption == 'S') {
                                 printf("You choose to Stand with your cards.\n");
                                 for (int a = 0; a < rightCountCard[i]; a++) {
                                     printf("\tCard number %d is %d with suit %c\n", a + 1, rightHandCard[i][a], rightHandCardDeck[i][a]);
                                 }
                                 break;
                             }

                             if (playerOption == 'h' || playerOption == 'H') {
                                 int cardRandom = rand() % numOfcard + 1;
                                 int card = cardRandom % 13 + 1;
                                 rightHandCard[i][rightCountCard[i] + 1] = card;
                                 sumOfRightHandCard[i] = sumOfRightHandCard[i] + card;
                                 rightHandCardDeck[i][rightCountCard[i]] = deckCardPlay[1][cardRandom];
                                 printf("Your next card is %d with suit %c\n", rightHandCard[i][rightCountCard[i]], rightHandCardDeck[i][rightCountCard[i]]);
                                 printf("Total value you have is: %d\n", sumOfRightHandCard[i]);
                                 rightCountCard[i] = rightCountCard[i] + 1;

                                 if (sumOfRightHandCard[i] > 21) {
                                     rightBurst[i] = "burst";
                                     printf("You burst!!\nGame Over!!\n");
                                     break;
                                 }
                                 else {
                                     printf("Press 's' for Stand, 'h' for Hit: ");
                                     scanf(" %c", &playerOption);
                                     printf("");
                                 }
                                 if (i == numOfPlayer - 1) {
                                     dealerSum = dealerSum + card;
                                 }
                             }
                         } while (playerOption != 's' || playerOption != 'S');
                     }
                 }

             } while (playerOption != 's' || playerOption != 'S');

             //player options to save or exit the game
             do
             {
                 printf("Option for the games:\n");
                 printf("S for Save\n");
                 printf("E for exit\n");
                 printf("C for complete\n");
                 printf("O for output game status.\n");
                 scanf(" %c", &playerOption);

                 //save
                 if (playerOption == 's' || playerOption == 'S') {

                     for (int d = 0; d < numOfPlayer; d++) {
                         sprintf(filename, "player%d.txt", d + 1);
                         FILE* file = fopen(filename, "w");
                         fprintf(file, "%s\n", playerName[d]);
                         fprintf(file, "%d\n", countOfCard[d]);
                         for (int a = 0; a < countOfCard[d]; a++) {
                             fprintf(file, "%d\n", playerCard[d][a]);
                         }
                         for (int a = 0; a < countOfCard[d]; a++) {
                             fprintf(file, "%c\n", playerCardDeck[d][a]);
                         }
                         fprintf(file, "%d\n", sumOfCard[d]);
                         fclose(file);
                     }

                 }
                 //exit
                 if (playerOption == 'E' || playerOption == 'e')
                 {
                     printf("Existing the game....\n");
                     return 0;
                 }
                 //complete
                 if (playerOption == 'C' || playerOption == 'c')
                 {
                     printf("You completed your turn!\n");
                 }

                 //output the game status
                 if (playerOption == 'o' || playerOption == 'O')
                 {
                     for (int a = 0; a <= i; a++)
                     {
                         printf("Player %s:\n", playerName[a]);
                         for (int b = 0; b < countOfCard[a]; b++) {
                             printf("\tCard number %d is %d with suit %c\n", b + 1, playerCard[a][b], playerCardDeck[a][b]);
                         }
                     }
                 }

             } while (!(playerOption == 's' || playerOption == 'S' || playerOption == 'e' || playerOption == 'E' || playerOption == 'c' || playerOption == 'C' || playerOption == 'o' || playerOption == 'O'));

             //second option if player hit save
             if (playerOption == 'S' || playerOption == 's')
             {
                 printf("Option for the games:\n");
                 printf("N for New Game\n");
                 printf("E for exit\n");
                 printf("S for continue Saved Game\n");
                 scanf(" %c", &playerOption);
                 //exit
                 if (playerOption == 'E' || playerOption == 'e')
                 {
                     printf("Existing the game....\n");
                     return 0;
                 }
                 //new game
                 if (playerOption == 'N' || playerOption == 'n')
                 {
                     printf("Starting a new game...\n");
                     startNewGame = 1; // Set the flag to start a new game
                     break; // Break out of the inner loop for the current player
                 }
                 //save
                 if (playerOption == 'S' || playerOption == 's') {
                     for (int d = 0; d < numOfPlayer; d++) {
                         sprintf(filename, "player%d.txt", d + 1);
                         loadGame(filename, numOfPlayer, playerCard[d], playerCardDeck[d], &sumOfCard[d], &countOfCard[d], playerName[d]);
                     }
                     for (int a = 0; a < numOfPlayer; a++) {
                         printf("Player %s:\n", playerName[a]);
                         for (int b = 0; b < countOfCard[a]; b++) {
                             printf("\tCard number %d is %d with suit %c\n", b + 1, playerCard[a][b], playerCardDeck[a][b]);
                         }
                     }

                     printf("Game loaded successfully!\n");
                     startNewGame = 0;
                     gameLoaded = 1;
                     break;
                 }

             }
             if (startNewGame) {
                 printf("Exiting the current game...\n");
                 break; // Break out of the outer loop to start a new game

             }
         }



 }*/