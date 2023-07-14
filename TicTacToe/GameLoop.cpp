#include "Utility.h"

std::string Board[3][3]{
	{" " , " " , " "},
	{" " , " " , " "},
	{" " , " " , " "}
};

std::tuple<std::string, std::string> X_O("X", "O");
bool game_QUIT = false;


void player_v_player(std::string& user_in)
{
	std::string player_1{};
	std::string player_2{};

	std::string player_1_input{};
	std::string player_2_input{};

	user_in = user_input("Player 1, do you want to be X or O? (Type 'X' for X and 'O' for O)");
	std::transform(user_in.begin(), user_in.end(), user_in.begin(), ::toupper);

	if (user_in == "X")
	{
		print("Player 2 will be 'O'");

		player_1 = "X";
		player_2 = "O";
	}
	else if (user_in == "O")
	{
		print("Player 2 will be 'X'");

		player_1 = "O";
		player_2 = "X";
	}

	while (true)
	{
		show_board();
		player_1_input = user_input("enter a nubmer from 1 through 9 to choose a position on the board for X");
		std::transform(player_1_input.begin(), player_1_input.end(), player_1_input.begin(), ::toupper); // Why are you transforming it to uppercase in a loop lmao
		board_input(player_1_input, player_1);															// or wait no I think you're transforming a number to uppercase bruh
		if (win_or_lose()) { show_board(); break; }

		show_board();

		player_2_input = user_input("enter a nubmer from 1 through 9 to choose a position on the board for O");
		std::transform(player_2_input.begin(), player_2_input.end(), player_2_input.begin(), ::toupper);
		board_input(player_2_input, player_2);
		if (win_or_lose()) { show_board(); break; }
	}
}


void player_v_computer(std::string& user_in)
{
	user_in = user_input("do you want to start off as X or O? (Type 'X' for X and 'O' for O)");

	std::transform(user_in.begin(), user_in.end(), user_in.begin(), ::toupper);

	std::string X_or_O = user_in;

	if (user_in == "X")
	{
		while (true)
		{
			show_board();
			user_in = user_input("enter a nubmer from 1 through 9 to choose a position on the board for X");
			board_input(user_in, "X");
			if (win_or_lose()) { show_board(); break; }

			AI(X_or_O);
			if (win_or_lose()) { show_board(); break; }
		}
	}
	else if (user_in == "O")
	{
		while (true)
		{
			show_board();
			user_in = user_input("enter a nubmer from 1 through 9 to choose a position on the board for O");
			board_input(user_in, "O");
			if (win_or_lose()) { show_board(); break; }

			AI(X_or_O);
			if (win_or_lose()) { show_board(); break; }
		}
	}
}


int main()
{
	std::string user_in{};

	user_in = user_input("Do you want to play agains a player or against the computer? (Type 'P'for player and 'C' for computer)");
	std::transform(user_in.begin(), user_in.end(), user_in.begin(), ::toupper);

	if (user_in == "P")
	{
		player_v_player(user_in);
	}
	else if (user_in == "C")
	{
		player_v_computer(user_in);
	}
}