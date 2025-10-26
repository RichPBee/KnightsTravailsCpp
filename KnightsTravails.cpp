
#include <iostream>

#include <list>

#include<string>

using namespace std;

struct Position {
	int x;
	int y;
};

class Square
{
	Position _start;
	list<Square> _moves;
	Square* _previousSquare;

public: Square(Position start, Square* previousSquare) {
	_start = start;
	_previousSquare = previousSquare;
}

	  void GenerateMoves()
	  {
		  list<Square> moves;
		  for (int i = 0; i < 8; i++)
		  {
			  Position move = CreateMove(i, _start);
			  if (IsValid(move))
			  {
				  Square* sq = new Square(move, this);
				  moves.push_back(*sq);
			  }
		  }
		  _moves = moves;
	  }

	  Position CreateMove(int index, Position start)
	  {
		  Position move;
		  switch (index)
		  {
		  case 0:
			  move = { start.x + 1, start.y + 2 };
			  break;
		  case 1:
			  move = { start.x + 2, start.y + 1 };
			  break;
		  case 2:
			  move = { start.x + 2, start.y - 1 };
			  break;
		  case 3:
			  move = { start.x + 1, start.y - 2 };
			  break;
		  case 4:
			  move = { start.x - 1, start.y - 2 };
			  break;
		  case 5:
			  move = { start.x - 2, start.y - 1 };
			  break;
		  case 6:
			  move = { start.x - 2, start.y + 1 };
			  break;
		  case 7:
			  move = { start.x - 1, start.y + 2 };
			  break;
		  default:
			  move = start;
			  break;
		  }
		  return move;
	  }

	  bool IsValid(Position move)
	  {
		  return move.x >= 0 && move.x <= 7 && move.y >= 0 && move.y <= 7;
	  }

	  list<Square> GetMoves()
	  {
		  return _moves;
	  }

	  Square* PreviousSquare()
	  {
		  return _previousSquare;
	  }

	  Position Start()
	  {
		  return _start;
	  }

	  string StringPosition()
	  {
		  string x = to_string(_start.x);
		  string y = to_string(_start.y);
		  return "{" + x + "," + y + "}";
	  }
};

string GetPositionString(Position pos)
{
	string x = to_string(pos.x);
	string y = to_string(pos.y);
	return "{" + x + "," + y + "}";
}

bool IsEndPos(Position pos, Position target)
{
	return pos.x == target.x && pos.y == target.y;
}

list<Position> ResolveAnswer(Square answer)
{
	if (!answer.PreviousSquare())
	{
		return { answer.Start() };
	}
	list<Position> allPositions = { answer.Start() };
	Square prevSquare = *(answer.PreviousSquare());
	list<Position> newPositions = ResolveAnswer(prevSquare);
	std::list<Position>::iterator it;
	for (it = newPositions.begin(); it != newPositions.end(); ++it)
	{
		allPositions.push_back(*it);
	}

	return allPositions;
}

static list<Position> KnightMoves(Position start, Position end)
{
	Square* startSquare = new Square(start, nullptr);
	list<Square*> queue;
	queue.push_back(startSquare);
	bool found = false;
	Square* answer = startSquare;
	while (!found)
	{
		Square* movePtr = queue.front();
		Square move = *movePtr;
		move.GenerateMoves();
		std::list<Square>::iterator it;
		list<Square> allMoves = move.GetMoves();
		for (it = allMoves.begin(); it != allMoves.end(); ++it)
		{
			if (IsEndPos(it->Start(), end))
			{
				found = true;
				answer = new Square(it->Start(), movePtr);
				break;
			}
			else
			{
				queue.push_back(new Square(it->Start(), movePtr));
			}
		}
		queue.pop_front();
	}
	list<Position> final = ResolveAnswer(*answer);
	final.reverse();
	return final;
}

Position GetUserInput(string inputType)
{
	int x;
	int y;
	cout << "Provide a " + inputType + " x position: ";
	cin >> x;
	cout << "Provide a " + inputType + " y position: ";
	cin >> y;
	return { x , y };
}

void Run()
{
	Position start = GetUserInput("starting");
	Position end = GetUserInput("final");
	list<Position> answer = KnightMoves(start, end);
	string answerString = "";
	size_t size = answer.size();
	for (int i = 0; i < size; i++)
	{
		Position currentPos = answer.front();
		answer.pop_front();
		if (i < size - 1)
		{
			answerString += GetPositionString(currentPos) + ",";
			continue;
		}
		answerString += GetPositionString(currentPos);
	}
	cout << answerString + '\n';
}

int main()
{
	bool finished = false;
	while (!finished)
	{
		string exit;
		Run();
		cout << "Press E key to exit program.";
		cin >> exit;
		if (exit == "E" || exit == "e")
		{
			finished = true;
			break;
		}
		continue;
	}
	return 0;
}