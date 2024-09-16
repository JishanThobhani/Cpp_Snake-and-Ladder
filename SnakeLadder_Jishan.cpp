#include <iostream>
#include <cstdlib>
#include <ctime>

#define BOARD_SIZE 100

int board[BOARD_SIZE] = {0, 0, 0, 14, 0, 0, 0, -7, 0, 0, 13, -6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -6, 0, 0, 7, -7, 20, -10, 0, 0, 7, 13,
     0, -12, 0, -9, 0, 0, 0, 13, 0, -6, 0, 0, 0, 0, 0, 6, 0, 15, 0, 0, 0, -8, -9, 0, 0, 0, 0, 0, 0, 0, 0, -15, 0, -7,
     0, 0, -7, 0, 0, 0, 0, 0, 0, 14, 0, 0, -12, 0, 5, -11, 0, 0, 0, 0, 0, -10, 0, 0, 0, 6, 0, 0, 0, -99, 0};

int player_position[4] = {0, 0, 0, 0};
int n;

int rollDice() {
    return (rand() % 6) + 1;
}

bool isOutOfBoard(int pos) {
    return pos > 100;
}

void playGame() {
    int cur_player = 1, num_dice, player_pre_position;
    bool game_start = true;
    char ch;

    while (true) {
        if (game_start) {
            std::cout << "-----------------------Game Starts------------------------" << std::endl;
            game_start = false;
            std::cin.get(ch);  // Wait for input
            continue;
        }

        if (cur_player > n) {
            std::cout << "\n\n======================================================\n";
            std::cout << "Current positions of players:\n";
            for (int i = 0; i < n; ++i) {
                std::cout << "Player-" << i + 1 << ": " << player_position[i] << std::endl;
            }
            std::cout << "======================================================\n";
            cur_player = 1;
        }

        std::cout << "\n---------------------------------------------------------------\n";
        std::cout << "It's Player-" << cur_player << " turn to throw dice. (Press enter to throw the dice)\n";
        std::cin.get(ch);  // Wait for input

        num_dice = rollDice();
        std::cout << "Player-" << cur_player << " has thrown " << num_dice << ".\n";

        if (!isOutOfBoard(player_position[cur_player - 1] + num_dice)) {
            player_position[cur_player - 1] += num_dice;
            player_pre_position = player_position[cur_player - 1];
            player_position[cur_player - 1] += board[player_position[cur_player - 1]];

            if (board[player_pre_position] == 0) {
                std::cout << "Player-" << cur_player << " has reached position " << player_position[cur_player - 1] << ".\n";
            } else if (board[player_pre_position] < 0) {
                std::cout << "Player-" << cur_player << " was bitten by SNAKE and has been demoted to position " << player_position[cur_player - 1] << ".\n";
            } else {
                std::cout << "Player-" << cur_player << " claimed the LADDER and reached position " << player_position[cur_player - 1] << ".\n";
            }
        } else {
            std::cout << "Player-" << cur_player << " did not proceed.\n";
        }

        if (player_position[cur_player - 1] == 100) {
            break;
        }

        ++cur_player;
    }

    std::cout << "Player-" << cur_player << " wins!!!!!!!\n";
}

int main() {
    do {
        std::cout << "\nEnter the number of players (upto 4 players): ";
        std::cin >> n;

        if (n > 4 || n < 2) {
            n > 4 ? std::cout << "More than 4 players can't play.\n" : std::cout << "At least 2 players are required to play.\n";
        }
    } while (n > 4 || n < 2);

    srand(time(NULL));

    playGame();
    return 0;
}
