#include <iostream>
#include <vector>

class QuickFindUF
{
	std::vector<int> id;
	public:
		QuickFindUF(int);
		void unionUF(int, int);
		int connectedUF(int, int);
};


QuickFindUF::QuickFindUF(int N)
{
	id.resize(N);
	for(int i = 0; i < N; i++)
	{
		id[i] = i;
	}
}

int QuickFindUF::connectedUF(int p, int q)
{
	if(id[p] == id[q])
		return 1;
	return(0);
}

void QuickFindUF::unionUF(int p, int q)
{
	int pid = id[p];
	int qid = id[q];

	for(int i = 0; i < id.size(); i++)
	{
		if (id[i] == pid)
			id[i] = qid;
	}
}

int main()
{
	QuickFindUF test(3);

	test.unionUF(1,2);
	std::cout << test.connectedUF(1,2);
	return 0;
}

