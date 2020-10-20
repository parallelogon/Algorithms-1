#include <iostream>
#include <vector>

class QuickUnion
{
	std::vector<int> id;

	public:
		QuickUnion(int);
		bool connectedQU(int, int);
		void unionQU(int, int);
		int root(int);
};

QuickUnion::QuickUnion(int N)
{
	id.resize(N);
	for(int i = 0; i < N; i++)
		id[i] = i;
}

int QuickUnion::root(int q)
{
	if(id[q] == q)
		return (q);
	root(id[q]);
}

bool QuickUnion::connectedQU(int p, int q)
{
	return(root(p) == root(q));
}

void QuickUnion::unionQU(int p, int q)
{
	int ridp = root(p);
	int ridq = root(q);

	id[ridp] = ridq;
}

int main()
{
	QuickUnion test(5);

	test.unionQU(1,2);
	test.unionQU(2,3);

	std::cout << test.connectedQU(1,3) << "\n";
	return (0);
}
