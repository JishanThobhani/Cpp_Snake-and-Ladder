#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 100

int board[BOARD_SIZE] = {0, 0, 0, 14, 0, 0, 0, -7, 0, 0, 13, -6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -6, 0, 0, 7, -7, 20, -10, 0, 0, 7, 13,
     0, -12, 0, -9, 0, 0, 0, 13, 0, -6, 0, 0, 0, 0, 0, 6, 0, 15, 0, 0, 0, -8, -9, 0, 0, 0, 0, 0, 0, 0, 0, -15, 0, -7,
     0, 0, -7, 0, 0, 0, 0, 0, 0, 14, 0, 0, -12, 0, 5, -11, 0, 0, 0, 0, 0, -10, 0, 0, 0, 6, 0, 0, 0, -99, 0};

int player_position[4] = {0, 0, 0, 0};
int n;


int rollDice() {

    return (rand() % 6) + 1;
}

int checkeOutOfBoard(int pos){
    if (pos>100){
        return 1;
    }
    return 0;

}

void playGame() {
    int cur_player = 1, num_dice, flag=1, player_pre_position;
    char ch;
    while(1){
        if(flag){
            printf("-----------------------Game Starts------------------------");
            flag = 0;
            scanf("%c", &ch);
            continue;
        }

        if (cur_player > n){
            printf("\n\n======================================================\n");
            printf("Current positions of players:\n");
            for(int i=0; i<n; i++){
                printf("Player-%d: %d\n", i+1, player_position[i]);
            }
            printf("======================================================\n");
            cur_player = 1;
        }


        printf("\n---------------------------------------------------------------\n");
        printf("It's Player-%d turn to throw dice. (Press enter to throw the dice)\n", cur_player);
        scanf("%c", &ch);

        num_dice = rollDice();
        printf("Player-%d has thrown %d.\n", cur_player, num_dice);


        if(!checkeOutOfBoard(player_position[cur_player-1] + num_dice)){
            player_position[cur_player-1] += num_dice;
            player_pre_position = player_position[cur_player-1];
            player_position[cur_player-1] += board[player_position[cur_player-1]];

            if(board[player_pre_position] == 0){
                printf("Player-%d has reached position %d.\n", cur_player, player_position[cur_player-1]);
            }
            else if (board[player_pre_position] < 0){
                printf("Player-%d was bitten by SNAKE and has been demoted to position %d.\n", cur_player, player_position[cur_player-1]);
            }
            else{
                printf("Player-%d claimed the LADDER and reached to position %d.\n", cur_player, player_position[cur_player-1]);
            }

        }

        else{
            printf("Player-%d did not proceed.\n", cur_player);
        }



        if (player_position[cur_player-1] == 100){
            break;
        }

        cur_player++;
    }

    printf("Player-%d wins!!!!!!!", cur_player);

}

int main() {

    num_player:

    printf("\nEnter the number of players (upto 4 players): ");
    scanf("%d", &n);

    if(n>4 || n<2){
        n>4? printf("More than 4 players can't play.\n"): printf("Atleast 2 players are required to play\n");
        goto num_player;
    }

    srand(time(NULL));

    playGame();
    return 0;
}
