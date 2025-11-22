/*

Use this program to find the optimal move for a position.

*/

#include <iostream>
#include <string>

#include "solver/position.h"
#include "solver/settings.h"
#include "solver/solver.h"

int main(int argc, const char** argv) {
    std::cout.imbue(std::locale(""));

    if (argc < 2) {
      std::cout << "Usage: bestmove <moves>" << std::endl;
      return 1;
    }
    
    Solver solver{};
    std::cout << solver.get_settings_string()
              << std::endl;

    Position pos{};
    const char* moves = argv[1];
    for (int i = 0; i < strlen(moves); i++) {
      pos.move(moves[i]-'0');
    }
    std::cout << pos.display_board()
              << std::endl;
    
    int score = solver.solve_strong(pos);
    int bestmove = -1;
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (pos.is_move_valid(i)) {
            board before_move = pos.move(i);
            int move_score = -solver.solve(pos, -score, -score + 1);
            pos.unmove(before_move);

            std::cout << i
                      //<< " " << move_score
                      << " " << (move_score<0?-1:1)*pos.moves_left(move_score)
                      << std::endl;

            if (move_score >= score) {
              bestmove = i;
            }
        }
    }
    std::cout << std::endl;
    
    std::cout << "best move: " << bestmove
              << std::endl;

    return 0;
}
