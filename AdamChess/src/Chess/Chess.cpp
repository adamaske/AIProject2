#include "pch.h"
#include "Chess.h"

Chess::Chess()
{
	Logger::Log("Chess created");
}

void Chess::SetupGame()
{
	Logger::Log("Chess setup game");
}

void Chess::Move(ChessMove move)
{
	BoardPosition to = move.to;
	BoardPosition from = move.from;


}

void Chess::SetMoves(std::vector<ChessMove> moves)
{
	mMoves = moves;
}

void Chess::PrintBoard()
{

}


