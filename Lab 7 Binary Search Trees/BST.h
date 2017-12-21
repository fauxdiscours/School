#ifndef BST_H
#define BST_H

#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template <class TKey>
class bst {
	struct node {
		node(int);

		void print();

		TKey key;
		int ID;

		node *parent;
		node *link[2];
	};

	public:
	class iterator {
		public:
			//	default constructor (no argument)
			iterator() { p = NULL; }	
			//	overloaded operators (++, *, ==, !=)
			//check for NULL, if NULL return iterator,
			//if link[0] read parent, go right, if coming from link[1] go up		
			iterator operator++();
			TKey operator*() {return p->key;}
			bool operator==(const iterator &) const;
			bool operator !=(const iterator &) const;
		private:
			friend class bst<TKey>;
			//	constructor (with argument)
			iterator(node* newNode) { p = newNode; } 
			node *p;
	};
//Returns leftmost node in BST
	iterator begin() {
		node *current = Troot;
		if(current){
			while(current->link[0] != NULL){
				current = current->link[0];
			}
		}
		return iterator(current);
	}
//Returns a NULL pointer indicating end of BST
	iterator end() { 
		return iterator(NULL);
	}

	public:
	bst() { Troot=NULL; total = 0; }
	~bst() { clear(Troot); }

	bool empty() { return Troot==NULL; }

	void insert(TKey &);

	void print_bylevel();

	iterator lower_bound(const TKey &);
	iterator upper_bound(const TKey &);
	private:
	void clear(node *);
	node *insert(node *, TKey &);

	int total;
	node *Troot;
};
//Creates a node with ID 0
	template <class TKey>
bst<TKey>::node::node(int id = 0) 
{
	ID = id;
	parent = NULL;
}

	template <typename TKey>
void bst<TKey>::node::print()
{
	cout << setw(3) << key << setw(4) << ID << " :";

	//  output node and parent ID information
	//  change below to output subtree ID information
	if(parent==NULL){ cout << setw(3) << " ROOT "; }
	else { cout << "P= " << setw(3) << parent->ID; }
	if (link[0]) cout << " L=" << setw(3) << link[0]->ID;
	else         cout << "      ";
	if (link[1]) cout << " R=" << setw(3) << link[1]->ID;
	else         cout << "      ";

	cout << "\n";
}
//Operator overloading from Iterator handout
template <typename TKey>
typename bst<TKey>::iterator bst<TKey>::iterator::operator++(){
	//if NULL return iterator
	//if link[1] exists, read parent, go right then go as far left as possible
	//if link[1] DNE go to parent, if you're in link[0] 
	//Iterates ONCE through the BST, checking for right children, NULL parents
	if(p->link[1] != NULL){
		p = p->link[1];
		while(p->link[0])
			p = p->link[0];
		return *this;
	}
	while(p->parent){
		if(p->parent->link[0] == p){ 
			p = p->parent;
			return *this;
		}
		if(p->parent->link[1] == p){
			p = p->parent;
		}
	}
	p = NULL; 
	return *this;
}

template <typename T>
bool bst<T>::iterator::operator==(const iterator & iT) const {
	return p == iT.p;
}

template <typename T>
bool bst<T>::iterator::operator!=(const iterator & iT) const {
	return p != iT.p;
}

//bst<Tkey>::iterator functions not defined go above here

	template <class TKey>
void bst<TKey>::clear(node *T)
{
	if (T) {
		clear(T->link[0]);
		clear(T->link[1]);
		delete T;
		T = NULL;
	}
}

	template <class TKey>
void bst<TKey>::insert(TKey &key)
{ 
	Troot = insert(Troot, key);
}

	template <class TKey>
class bst<TKey>::node *bst<TKey>::insert(node *T, TKey &key)
{
	if (T == NULL) {
		//  update and set node ID 
		total++;
		T = new node(total);
		T->key = key;
	} else if (T->key == key) {
		;
	} else {
		//  set parent link 
		int dir = T->key < key;
		T->link[dir] = insert(T->link[dir], key);
		T->link[dir]->parent = T;
	}

	return T;
}

//bst<Tkey>::lower_bound function goes here
//key ≤ lower_bound(Tkey key)
//Returns an iterator to the first node in the tree with a key ≤ the current node's key.
//get low by lil jon plays in background
template <class TKey>
typename bst<TKey>::iterator bst<TKey>::lower_bound(const TKey &key){
	node *current = Troot;
	node *low = NULL;
	while(current != NULL){
		if(key <= current->key){
			low = current;
			current = current->link[0];
		}else{ current = current->link[1]; }
	}
	return iterator(low);
}
//bst<Tkey>::upper_bound function goes here
//key > upper_bound
//returns an iterator to the first node in the tree if the current node's key > key.
template <class TKey>
typename bst<TKey>::iterator bst<TKey>::upper_bound(const TKey &key){
	node *current = Troot;
	node *up = NULL;
	while(current != NULL){
		if(current->key > key){
			up = current;
			current = current->link[0];
		}else{ current = current->link[1]; }
	}
	return iterator(up);
}

	template <class TKey>
void bst<TKey>::print_bylevel()
{
	if (Troot == NULL)
		return;

	queue<node *> Q;
	node *T;

	Q.push(Troot);
	while (!Q.empty()) {
		T = Q.front();
		Q.pop();

		T->print();
		if (T->link[0]) Q.push(T->link[0]);
		if (T->link[1]) Q.push(T->link[1]);
	}
}
#endif
