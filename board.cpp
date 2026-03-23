#include <iostream>
#include <string>
#include <vector>
#include <random>

using std::vector;
using std::cout;
using std::cin;
using std::cerr;
using std::min;
using std::max;

struct Position
{
    int r;
    int c;
    Position() = default;

    Position(int rr, int cc)
        : r{rr}, c{cc}
    {
    }
};

constexpr char EMPTY_C = '.';
constexpr int TIE = 0;
constexpr int PL_WIN = -1;
constexpr int OP_WIN = 1;
constexpr int ONGOING = -10;

bool is_occupied(Position pos, vector<vector<char>>& board);
void do_player(vector<vector<char>>& board, char player_c);
void do_opponent(vector<vector<char>>& board, char oppo_c);
void print_board(vector<vector<char>>& board);
int check_win(vector<vector<char>>& board, char player_c, char opponent_c);
void auto_last_move(vector<vector<char>>& board, char player_c, char opponent_c, bool player_turn);

void opponent_ai(vector<vector<char>>& board, char oppo_c, char player_c);
void player_ai(vector<vector<char>>& board, char oppo_c, char player_c);
vector<Position> get_poss_moves(vector<vector<char>>& board);
int minimax(vector<vector<char>>& board, bool ai_turn);

int main()
{
    int state;
    vector<vector<char>> board(3, vector<char>(3, EMPTY_C));
    constexpr char player_c = 'x';
    constexpr char opponent_c = 'o';
    bool player_turn = true;
    bool game_over = false;
    while (!game_over)
    {
        if (player_turn)
        {
            cout << "Player turn: ";
            do_player(board, player_c);
            player_turn = false;
        }
        else
        {
            cout << "Opponent turn:\n";
            do_opponent(board, opponent_c);
            player_turn = true;
        }

        cout << "board:\n";
        print_board(board);

        auto_last_move(board, player_c, opponent_c, player_turn);
        state = check_win(board, player_c, opponent_c);
        if (state != ONGOING) game_over = true;
    }
    switch (state)
    {
    case PL_WIN:
        cout << "Player won.";
        break;
    case OP_WIN:
        cout << "Opponent won.";
        break;
    case TIE:
        cout << "TIE!";
        break;
    }
    return 0;
}

void do_player(vector<vector<char>>& board, char player_c)
{
    while (true)
    {
        int r, c;
        cin >> r >> c;
        if (is_occupied(Position(r, c), board))
        {
            cerr << "position already occupied";
            continue;
        }
        board[r][c] = player_c;
        return;
    }
}

void do_opponent(vector<vector<char>>& board, char oppo_c)
{
    opponent_ai(board, 'o', 'x');
}

int minimax(vector<vector<char>>& board, bool ai_turn)
{
    int state = check_win(board, 'x', 'o');
    if (state != ONGOING)
        return state;

    vector<Position> possible_moves = get_poss_moves(board);
    if (ai_turn)
    {
        int max_score = -1;
        for (Position move : possible_moves)
        {
            board[move.r][move.c] = 'o';
            max_score = max(minimax(board, false), max_score);
            board[move.r][move.c] = EMPTY_C;
        }
        return max_score;
    }
    else
    {
        int min_score = 1;
        for (Position move : possible_moves)
        {
            board[move.r][move.c] = 'x';
            min_score = min(minimax(board, true), min_score);
            board[move.r][move.c] = EMPTY_C;
        }
        return min_score;
    }
}

void opponent_ai(vector<vector<char>>& board, char oppo_c, char player_c)
{
    int best_score = -1;
    int score;
    Position best_move{0, 0};
    vector<Position> possible_moves = get_poss_moves(board);
    for (Position move : possible_moves)
    {
        cout << "Possible move is (" << move.r << ',' << move.c << ")\n";
        board[move.r][move.c] = 'o';
        int state = check_win(board, 'x', 'o');
        if (state != ONGOING)
            return;
        score = minimax(board, false);
        board[move.r][move.c] = EMPTY_C;
        if (score >= best_score)
        {
            best_score = score;
            best_move = move;
        }
    }
    board[best_move.r][best_move.c] = 'o';
    cout << "(" << best_move.r << "," << best_move.c << ")" << std::endl;
}

vector<Position> get_poss_moves(vector<vector<char>>& board)
{
    vector<Position> positions;
    for (int r = 0; r < board.size(); ++r)
    {
        for (int c = 0; c < board[0].size(); ++c)
        {
            if (board[r][c] == EMPTY_C)
            {
                positions.push_back(Position(r, c));
            }
        }
    }
    return positions;
}

bool is_occupied(Position pos, vector<vector<char>>& board)
{
    if (board[pos.r][pos.c] == EMPTY_C) return false;
    return true;
}

int check_win(vector<vector<char>>& board, char player_c, char opponent_c)
{
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) || (board[0][2] == board[1][1] && board[1][1] ==
        board[2][0]))
    {
        if (board[1][1] == player_c)
            return PL_WIN;

        if (board[1][1] == opponent_c)
            return OP_WIN;
    }
    //column check
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            if (board[0][i] == player_c)
                return PL_WIN;
            if (board[0][i] == opponent_c)
                return OP_WIN;
        }
    }
    //row check
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            if (board[i][0] == player_c)
                return PL_WIN;
            if (board[i][0] == opponent_c)
                return OP_WIN;
        }
    }

    int occupied = 0;
    for (int r = 0; r < board.size(); r++)
    {
        for (int c = 0; c < board[0].size(); c++)
        {
            if (is_occupied(Position(r, c), board))
                ++occupied;
        }
    }
    if (occupied == 9)
        return TIE;

    return ONGOING;
}

void auto_last_move(vector<vector<char>>& board, char player_c, char opponent_c, bool player_turn)
{
    int occ = 0; //cells occupied
    int r, c;
    for (int i = 0; i < board.size(); ++i)
    {
        for (int j = 0; j < board[0].size(); ++j)
        {
            if (is_occupied({i, j}, board))
            {
                ++occ;
            }
            else
            {
                r = i;
                c = j;
            }
        }
    }
    if (occ == 8)
    {
        if (player_turn)
        {
            cout << "Last move player turn\n";
            board[r][c] = player_c;
        }
        else
        {
            board[r][c] = opponent_c;
            cout << "Last move opponent turn\n";
        }
        print_board(board);
    }
}

void print_board(vector<vector<char>>& board)
{
    for (const vector<char>& row : board)
    {
        for (const char col : row)
            cout << col << ' ';
        cout << '\n';
    }
}
