#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <tuple>

// Fundamental Functions
void print(std::string msg);

std::string user_input(std::string question);

void board_input(std::string user_in, std::string input);

void show_board();

// Game Logic Functions
int loop_rows(int num_row, int num_col, int Board_pos, std::string& user1_input, std::string& user2_input);

int loop_columns(int num_row, int num_col, int empty_pos, std::string& user1_input, std::string& user2_input);

int loop_diagonals(std::string& user1_input, std::string& user2_input);

void input_X_or_O(std::string& user1_input, std::string& user2_input);

void AI(std::string user_input);

bool win_or_lose();
