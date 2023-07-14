#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <tuple>
#include <random>
#include <format>

extern std::string Board[3][3];

std::default_random_engine random_eng;
std::uniform_int_distribution<int> distribution(1, 9);

int first_random_val = distribution(random_eng);

// Fundamental functions:

void print(std::string msg)
{
	std::cout << msg << '\n';
}


std::string user_input(std::string question)
{
	std::string x{};

	print(question);
	std::cin >> x;
	print("");

	return x;
}


std::vector<int> convert_userinput_boardposition(std::string& user_input)
{
	switch (stoi(user_input))
	{
	case 1:
		if (user_input == "1") { std::vector<int> pos = { 0, 0 }; return pos; }
		break;
	case 2:
		if (user_input == "2") { std::vector<int> pos = { 0, 1 }; return pos; }
		break;
	case 3:
		if (user_input == "3") { std::vector<int> pos = { 0, 2 }; return pos; }
		break;
	case 4:
		if (user_input == "4") { std::vector<int> pos = { 1, 0 }; return pos; }
		break;
	case 5:
		if (user_input == "5") { std::vector<int> pos = { 1, 1 }; return pos; }
		break;
	case 6:
		if (user_input == "6") { std::vector<int> pos = { 1, 2 }; return pos; }
		break;
	case 7:
		if (user_input == "7") { std::vector<int> pos = { 2, 0 }; return pos; }
		break;
	case 8:
		if (user_input == "8") { std::vector<int> pos = { 2, 1 }; return pos; }
		break;
	case 9:
		if (user_input == "9") { std::vector<int> pos = { 2, 2 }; return pos; }
	}

	std::vector<int> default_vec = { -1, -1 };
	return default_vec;
}


void board_input(std::string user_in, std::string input)
{
	std::transform(input.begin(), input.end(), input.begin(), ::toupper);

	int i = convert_userinput_boardposition(user_in)[0];
	int j = convert_userinput_boardposition(user_in)[1];

	Board[i][j] = input;
}


void show_board()
{
	print(Board[0][0] + " | " + Board[0][1] + " | " + Board[0][2]);
	print("----------");
	print(Board[1][0] + " | " + Board[1][1] + " | " + Board[1][2]);
	print("----------");
	print(Board[2][0] + " | " + Board[2][1] + " | " + Board[2][2]);
}


// Game logic functions:

// Looping through the rows
int loop_rows(int num_row, int num_col, int Board_pos, std::string& user1_input, std::string& user2_input)
{
	for (int j = 0; j < num_row; j++)
	{
		int number_of_X_O = 0;
		int empty_spot{};

		for (int i = 0; i < num_col; i++)
		{
			if (Board[j][i] == user1_input)
			{
				number_of_X_O++;
			}
			else
			{
				empty_spot = i;
			}
		}

		if ((number_of_X_O == 2) && (Board[j][empty_spot] != user2_input))
		{
			Board[j][empty_spot] = user2_input;
			return 1;
		}
	}
	return 0;
}


// Looping through columns
int loop_columns(int num_row, int num_col, int empty_pos, std::string& user1_input, std::string& user2_input)
{
	for (int i = 0; i < num_col; i++)
	{
		int number_of_X_O = 0;
		int empty_spot{};

		for (int j = 0; j < num_row; j++)
		{
			if (Board[j][i] == user1_input)
			{
				number_of_X_O++;
			}
			else
			{
				empty_spot = j;
			}
		}

		if ((number_of_X_O == 2) && (Board[empty_spot][i] != user2_input))
		{
			Board[empty_spot][i] = user2_input;
			return 1;
		}
	}
	return 0;
}


// Looping through diagonals
int loop_diagonals(std::string& user1_input, std::string& user2_input)
{
	int number_of_X_O = 0;
	int empty_spot{};

	for (int i = 0; i < 3; i++)
	{
		if (Board[i][i] == user1_input) { number_of_X_O++; }
		else { empty_spot = i; }
	}

	if ((number_of_X_O == 2) && (Board[empty_spot][empty_spot] != user2_input))
	{
		Board[empty_spot][empty_spot] = user2_input;
		return 1;
	}

	number_of_X_O = 0;
	std::tuple<int, int> t_empty_spot;

	if (Board[2][0] == user1_input) { number_of_X_O++; }
	else { t_empty_spot = std::make_tuple(2, 0); }
	
	if (Board[1][1] == user1_input) { number_of_X_O++; }
	else { t_empty_spot = std::make_tuple(1, 1); }

	if (Board[0][2] == user1_input) { number_of_X_O++; }
	else { t_empty_spot = std::make_tuple(0, 2); }

	if ((number_of_X_O == 2) && (Board[std::get<0>(t_empty_spot)][std::get<1>(t_empty_spot)] != user2_input))
	{
		Board[std::get<0>(t_empty_spot)][std::get<1>(t_empty_spot)] = user2_input;
		return 1;
	}
	return 0;
}


void AI_input_X_or_O(std::string& user1_input, std::string& user2_input)
{
	std::vector<int> empty_spots;
	int empty = 0;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			empty++;
			if ((Board[i][j] != user1_input) && (Board[i][j] != user2_input)) { empty_spots.push_back(empty); }
		}
	}

	for (int i : empty_spots)
	{
		std::string input = std::format("{}", i);
		if (i == 5) { board_input(input, user2_input); return; }
	}

	std::string input = std::format("{}", distribution(random_eng));
	board_input(input, user2_input);
}


void AI(std::string user_input)
{
	std::string user1_input = user_input;
	std::string user2_input = "";

	if (user1_input == "X") { user2_input = "O"; }
	else if (user1_input == "O") { user2_input = "X"; }

	// Number of rows and columns for looping through them
	const int num_row = 3;
	const int num_col = 3;

	int Board_pos{}; // position of the empty spot

	if (loop_rows(num_row, num_col, Board_pos, user1_input, user2_input)) { return; }

	if (loop_columns(num_row, num_col, Board_pos, user1_input, user2_input)) { return; }

	if (loop_diagonals(user1_input, user2_input)) { return; }

	AI_input_X_or_O(user1_input, user2_input);
}


bool win_or_lose()
{
	int num_row = 3;
	int num_col = 3;

	// Looping rows
	for (int j = 0; j < num_row; j++)
	{
		int number_of_X = 0;
		int number_of_O = 0;

		for (int i = 0; i < num_col; i++)
		{
			if (Board[j][i] == "X") { number_of_X++; }
			else if (Board[j][i] == "O") { number_of_O++; }
		}

		if ((number_of_X == 3) or (number_of_O == 3))
		{
			return true;
		}
	}

	// Looping columns
	for (int i = 0; i < num_col; i++)
	{
		int number_of_X = 0;
		int number_of_O = 0;

		for (int j = 0; j < num_row; j++)
		{
			if (Board[j][i] == "X") { number_of_X++; }
			else if (Board[j][i] == "O") { number_of_O++; }
		}

		if ((number_of_X == 3) or (number_of_O == 3))
		{
			return true;
		}
	}

	// Looping diagonals
	int number_of_X = 0;
	int number_of_O = 0;

	// 1st diagonal
	for (int i = 0; i < 3; i++)
	{
		if (Board[i][i] == "X") { number_of_X++; }
		else if (Board[i][i] == "O") { number_of_O++; }
	}

	if ((number_of_X == 3) or (number_of_O == 3))
	{
		return true;
	}

	// 2nd diagonal
	number_of_X = 0;
	number_of_O = 0;

	if (Board[2][0] == "X") { number_of_X++; }
	else if (Board[2][0] == "O") { number_of_O++; }

	if (Board[1][1] == "X") { number_of_X++; }
	else if (Board[1][1] == "O") { number_of_O++; }

	if (Board[0][2] == "X") { number_of_X++; }
	else if (Board[0][2] == "O") { number_of_O++; }

	if ((number_of_X == 3) or (number_of_O == 3))
	{
		return true;
	}
	return 0;

	return false;
}