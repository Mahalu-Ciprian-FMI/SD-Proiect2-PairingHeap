#include <iostream>
#include <fstream>
using namespace std;
ifstream f("mergeheap.in");
ofstream g("mergeheap.out");

class node
{
public:
	int val;
	node* copil;
	node* frate;
	node()
	{
		val = -1;
		copil = NULL;
		frate = NULL;
	}
	node(int val1)
	{
		val = val1;
		copil = NULL;
		frate = NULL;
	}
};
class PairingHeap
{
	node* root;
	node* merge(node* nod1, node* nod2)
	{
		if (nod2 == nullptr)
		{
			return nod1;
		}
		if (nod1 == nullptr)
		{
			nod1 = nod2;			return nod2;
		}
		if (nod2->val > nod1->val)
		{
			swap(nod1, nod2);
		}
		nod2->frate = nod1->copil;
		nod1->copil = nod2;
		nod2 = NULL;
		return nod1;
	}
	node* twopasi(node* nod)
	{
		if (nod != NULL && nod->frate!=NULL)
		{
			node* nod1, * nod2, * helpernode;
			nod1 = nod;
			nod2 = nod->frate;
			helpernode = nod2->frate;
			nod1->frate = NULL;
			nod2->frate = NULL;
			return merge(merge(nod1, nod2), twopasi(helpernode));
		}
		return nod;
	}
public:
	PairingHeap()
	{
		root = NULL;
	}
	PairingHeap(int val1)
	{
		root = new node(val1);
	}
	int get_max()
	{
		return root->val;
	}
	void merge(PairingHeap h)
	{
		if (root->val < h.root->val)
			swap(root, h.root);
		h.root->frate = root->copil;
		root->copil = h.root;
	}
	void insert(int val1)
	{
		if (root == NULL)
		{
			root = new node(val1);
			return; 
		}
		merge(PairingHeap(val1));
	}
	void delete_root()
	{
		if (root->copil == NULL)
			root = NULL;
		else
			root = twopasi(root->copil);
	}
	void reuniune(PairingHeap &h)
	{
		root=merge(root,h.root);
		h.root = NULL;
	}
};

int main()
{
	int n, q;
	PairingHeap h[101];
	f >> n >> q;
	int operatie, m, x, y;
	for (int i = 1;i <= q;i++)
	{
		f >> operatie;
		if (operatie == 1)
		{
			f >> m >> x;
			h[m].insert(x);
		}
		if (operatie == 2)
		{
			f >> m;
			cout<< h[m].get_max() << endl;
			g << h[m].get_max() << endl;
			h[m].delete_root();
		}
		if (operatie == 3)
		{
			f >> x >> y;
			h[x].reuniune(h[y]);
		}
	}
	return 0;
}