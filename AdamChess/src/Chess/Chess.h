#pragma once
using ChessPiece = char;

struct ChessPlayer {

};
struct BoardPosition {
	int x = 0;
	int y = 0;

	BoardPosition(int _x, int _y) : x(_x), y(_y){
	};
};

struct ChessMove {
	ChessPlayer mPlayer;
	BoardPosition to{ 0,0 };
	BoardPosition from{ 1, 1 };
	ChessMove() {
		to = BoardPosition{ 0,0 };
		from = BoardPosition{ 1,1 };
	};
};

struct ChessSlot {
	char mType = 'P';
	ChessPlayer mPlayer;
};

struct ChessBoard {
	ChessSlot board[8][8];
};


//A game of chess
class Chess {
public:
	Chess();
	void SetupGame();

	
	void Move(ChessMove move);

	void SetMoves(std::vector<ChessMove> moves);

	void PrintBoard();
	
	//We want a vector of chess games
	bool ContainsPiece();

	void NextMove();
	void PreviousMove();
private:
	//How many moves are there? How far are we along?
	std::vector<ChessMove> mMoves;
	int mMoved = 0;
	ChessBoard mBoard;
	
	//Queen = Q
	//King = K
	//Bishop = B
	//Knight = N
	//Pawn = P
	//Rook = R
};

