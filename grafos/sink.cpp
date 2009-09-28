#include <iostream>

template <int N>
int sink(const int G[N][N])
{
	int sink_candidate = 0;
	int i = 0;
	while (i < N && sink_candidate < N - 1)
	{

		if (sink_candidate == i)
			sink_candidate++;
		if (G[i][sink_candidate] == 0)
			sink_candidate = i;
		i++;
	}
	bool sink = true;
	int k = 0;
	while (sink && k < N)
	{
		if (k == sink_candidate)
			sink = (G[k][k] == 0);
		else
		{
			sink = (G[sink_candidate][k] == 0 && G[k][sink_candidate] == 1);
		}
		k++;
	}
	if (sink)
		return sink_candidate;
	else
		return -1;
}

using namespace std;

int main(int argc, char *argv[])
{
	int test[3][3] = { {0,1,1}, {1,0,1}, {1,0,0} };
	cout << sink(test) << endl;
	return 0;
}
