#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
vector<string> track(4);
std::string::size_type BridgeX;
std::string::size_type Hole;

struct Position
{
	int speed;
	unsigned int x;
	vector<int> y;
};
pair<unsigned int, std::string> decide(Position position)
{
	if (position.x >= Hole)
		return{ 0, "WAIT" };
	if (position.speed == 0)
		return{ 0, "SPEED" };
	pair<unsigned int, string> minCrashes = { position.y.size(), "WAIT" };
	{
		Position newPosition = position;
		newPosition.speed += 1;
		newPosition.x += newPosition.speed;
		for (auto y : position.y)
		{
			for (unsigned int x = position.x + 1; x <= newPosition.x; ++x)
			{
				if (track[y][x] == '0')
				{
					newPosition.y.erase(std::find(newPosition.y.begin(), newPosition.y.end(), y));
					break;
				}
			}
		}
		if (newPosition.y.size() > 0)
		{
			unsigned int crashes = (position.y.size() - newPosition.y.size()) + decide(newPosition).first;
			if (crashes == 0)
				return{ 0, "SPEED" };
			if (crashes < minCrashes.first)
				minCrashes = { crashes, "SPEED" };
		}
	}
	{
		Position newPosition = position;
		newPosition.x += newPosition.speed;
		for (auto y : position.y)
		{
			for (unsigned int x = position.x + 1; x <= newPosition.x; ++x)
			{
				if (track[y][x] == '0')
				{
					newPosition.y.erase(std::find(newPosition.y.begin(), newPosition.y.end(), y));
					break;
				}
			}
		}
		if (newPosition.y.size() > 0)
		{
			unsigned int crashes = (position.y.size() - newPosition.y.size()) + decide(newPosition).first;
			if (crashes == 0)
				return{ 0, "WAIT" };
			if (crashes < minCrashes.first)
				minCrashes = { crashes, "WAIT" };
		}
	}

	{
		Position newPosition = position;
		newPosition.x += newPosition.speed;
		for (auto y : position.y)
		{
			if (track[y][newPosition.x] == '0')
				newPosition.y.erase(std::find(newPosition.y.begin(), newPosition.y.end(), y));
		}
		if (newPosition.y.size() > 0)
		{
			unsigned int crashes = (position.y.size() - newPosition.y.size()) + decide(newPosition).first;
			if (crashes == 0)
				return{ 0, "JUMP" };
			if (crashes < minCrashes.first)
				minCrashes = { crashes, "JUMP" };
		}
	}

	if (std::find(position.y.begin(), position.y.end(), track.size() - 1) == position.y.end())
	{
		Position newPosition = position;
		newPosition.x += newPosition.speed;
		newPosition.y = {};
		for (auto y : position.y)
		{
			bool nocrash = true;
			for (unsigned int x = position.x + 1; x <= newPosition.x - 1; ++x)
			{
				if (track[y][x] == '0')
				{
					nocrash = false;
					break;
				}
			}
			for (unsigned int x = position.x + 1; x <= newPosition.x; ++x)
			{
				if (track[y + 1][x] == '0')
				{
					nocrash = false;
					break;
				}
			}
			if (nocrash)
				newPosition.y.push_back(y + 1);
		}
		if (newPosition.y.size() > 0)
		{
			unsigned int crashes = (position.y.size() - newPosition.y.size()) + decide(newPosition).first;
			if (crashes == 0)
				return{ 0, "DOWN" };
			if (crashes < minCrashes.first)
				minCrashes = { crashes, "DOWN" };
		}
	}

	if (std::find(position.y.begin(), position.y.end(), 0) == position.y.end())
	{
		Position newPosition = position;
		newPosition.x += newPosition.speed;
		newPosition.y = {};
		for (auto y : position.y)
		{
			bool nocrash = true;
			for (unsigned int x = position.x + 1; x <= newPosition.x - 1; ++x)
			{
				if (track[y][x] == '0')
				{
					nocrash = false;
					break;
				}
			}
			for (unsigned int x = position.x + 1; x <= newPosition.x; ++x)
			{
				if (track[y - 1][x] == '0')
				{
					nocrash = false;
					break;
				}
			}
			if (nocrash)
				newPosition.y.push_back(y - 1);
		}
		if (newPosition.y.size() > 0)
		{
			unsigned int crashes = (position.y.size() - newPosition.y.size()) + decide(newPosition).first;
			if (crashes == 0)
				return{ 0, "UP" };
			if (crashes < minCrashes.first)
				minCrashes = { crashes, "UP" };
		}
	}

	if (position.speed > 1)
	{
		Position newPosition = position;
		newPosition.speed -= 1;
		newPosition.x += newPosition.speed;
		for (auto y : position.y)
		{
			for (unsigned int x = position.x + 1; x <= newPosition.x; ++x)
			{
				if (track[y][x] == '0')
				{
					newPosition.y.erase(std::find(newPosition.y.begin(), newPosition.y.end(), y));
					break;
				}
			}
		}
		if (newPosition.y.size() > 0)
		{
			unsigned int crashes = (position.y.size() - newPosition.y.size()) + decide(newPosition).first;
			if (crashes == 0)
				return{ 0, "SLOW" };
			if (crashes < minCrashes.first)
				minCrashes = { crashes, "SLOW" };
		}
	}

	return minCrashes;
}
int main()
{
	int M; // the amount of motorbikes to control
	cin >> M; 
	cin.ignore();
	int V; // the minimum amount of motorbikes that must survive
	cin >> V; 
	cin.ignore();
	cin >> track[0]; 
	cin.ignore();
	cin >> track[1]; 
	cin.ignore();
	cin >> track[2]; 
	cin.ignore();
	cin >> track[3]; 
	cin.ignore();
	Hole = 0;
	Hole = max(Hole, (track[0].rfind('0') != string::npos) ? track[0].rfind('0') : 0);
	Hole = max(Hole, (track[1].rfind('0') != string::npos) ? track[1].rfind('0') : 0);
	Hole = max(Hole, (track[2].rfind('0') != string::npos) ? track[2].rfind('0') : 0);
	Hole = max(Hole, (track[3].rfind('0') != string::npos) ? track[3].rfind('0') : 0);
	BridgeX = track[0].length();
	// game loop
	while (1) {
		int S; // the motorbikes' speed
		cin >> S; 
		cin.ignore();
		Position currentPosition;
		currentPosition.speed = S;
		for (int i = 0; i < M; i++) {
			int X; // x coordinate of the motorbike
			int Y; // y coordinate of the motorbike
			int A; // indicates whether the motorbike is activated "1" or detroyed "0"
			cin >> X >> Y >> A; 
			cin.ignore();
			if (A) {
				currentPosition.x = X;
				currentPosition.y.push_back(Y);
			}
		}
		cout << decide(currentPosition).second << endl;
	}
}