#pragma once
#include "Node.h"
#include <iostream>
using namespace std;
template<typename T>
class BinOrdTree
{
private:
	node<T> *root;
	void deleteTree(node<T> * &) const;
	void copy(node<T> * &, node<T> * const &) const;
	void copyTree(BinOrdTree<T> const &);
	void printFromNode(const node<T> *) const;
	void add(node<T> * &, T const &) const;
public:
	BinOrdTree();
	~BinOrdTree();
	BinOrdTree(BinOrdTree<T> const &);
	BinOrdTree& operator=(BinOrdTree<T> const &);
	T getRootData() const;
	node<T>* getRootPtr() const;
	BinOrdTree<T> leftTree() const;
	BinOrdTree<T> rightTree() const;
	bool empty()const;
	void print() const;
	void addNode(T const &);
	void deleteNode(T const &);
	void deleteNodePtr(node<T> * &, const T &);
	void createWithData(T, BinOrdTree<T>, BinOrdTree<T>);
	void create();
	void minTree(T &, BinOrdTree<T> &) const;

	//funkciqta izvurshva tursene sled vuvejdane na FN
	void find(T x);

	//izvurvshva printirane po FN
	void traverseInorder();
};


template <typename T>
BinOrdTree<T>::BinOrdTree() {
	root = NULL;
}
template <typename T>
BinOrdTree<T>::~BinOrdTree() {
	deleteTree(root);
}
template <typename T>
BinOrdTree<T>::BinOrdTree(BinOrdTree<T> const &tree) {
	copyTree(tree);
}
template <typename T>
BinOrdTree<T>& BinOrdTree<T>::operator=(BinOrdTree<T> const &tree) {
	if (this != &tree) {
		deleteTree(root);
		copyTree(tree);
	}

	return *this;
}
template <typename T>
void BinOrdTree<T>::deleteTree(node<T>* &treeRoot) const {
	if (!treeRoot) {
		return;
	}
	deleteTree(treeRoot->left);
	deleteTree(treeRoot->right);
	delete treeRoot;
	treeRoot = NULL;
}
template <typename T>
void BinOrdTree<T>::copyTree(BinOrdTree<T> const & tree) {
	copy(root, tree.root);
}
template <typename T>
void BinOrdTree<T>::copy(node<T>* &dest, node<T> * const &src) const {
	dest = NULL;
	if (src) {
		dest = new node<T>;
		dest->data = src->data;
		copy(dest->left, src->left);
		copy(dest->right, src->right);
	}
}
template <typename T>
bool BinOrdTree<T>::empty() const {
	return root == NULL;
}
template <typename T>
T BinOrdTree<T>::getRootData() const {
	return root->data;
}
template <typename T>
node<T>* BinOrdTree<T>::getRootPtr() const {
	return root;
}
template <typename T>
BinOrdTree<T> BinOrdTree<T>::leftTree() const {
	BinOrdTree<T> copiedTree;
	copy(copiedTree.root, root->left);
	return copiedTree;
}
template <typename T>
BinOrdTree<T> BinOrdTree<T>::rightTree() const {
	BinOrdTree<T> copiedTree;
	copy(copiedTree.root, root->right);
	return copiedTree;
}template <typename T>
void BinOrdTree<T>::printFromNode(const node<T> *treeNode) const {
	if (!treeNode) {
		return;
	}
	printFromNode(treeNode->left);
	cout << treeNode->data << ", ";
	printFromNode(treeNode->right);
}
template <typename T>
void BinOrdTree<T>::print() const {
	printFromNode(root);
}
template <typename T>
void BinOrdTree<T>::add(node<T> * &treeNode, T const &x) const {
	if (!treeNode) {
		treeNode = new node<T>;
		treeNode->data = x;
		treeNode->left = NULL;
		treeNode->right = NULL;
		return;
	}
	if (x == treeNode->data)
	{
		treeNode->data = x;
	}
	if (x < treeNode->data) {
		add(treeNode->left, x);
	}
	else {
		add(treeNode->right, x);
	}
}
template <typename T>
void BinOrdTree<T>::addNode(T const &x) {
	add(root, x);
}
template <typename T>
void BinOrdTree<T>::create() {
	root = NULL;
	T nodeValue; char hasNextNode;
	do {
		cout << "> ";
		cin >> nodeValue;
		addNode(nodeValue);
		cout << "next element y/n? ";
		cin >> hasNextNode;
	} while (hasNextNode == 'y');
}
template <typename T>
void BinOrdTree<T>::createWithData(T x,
	BinOrdTree<T> left,
	BinOrdTree<T> right) {
	root = new node<T>;
	root->data = x;
	copy(root->left, left.root);
	copy(root->right, right.root);
}template <typename T>
void BinOrdTree<T>::minTree(T &x, BinOrdTree<T> &mint) const {
	T a = getRootData();
	if (!root->left) {
		x = a;
		mint = rightTree();
	}
	else {
		BinOrdTree<T> updatedLeftTree;
		leftTree().minTree(x, updatedLeftTree);
		mint.createWithData(a, updatedLeftTree, rightTree());
	}
}
template <typename T>
void BinOrdTree<T>::deleteNode(T const &x) {
	if (!root) {
		return;
	}
	T a = getRootData();
	BinOrdTree<T> tempTree;
	if (a == x && !root->left) {
		*this = this->rightTree();
		return;
	}
	if (a == x && !root->right) {
		*this = leftTree();
		return;
	}
	if (a == x) {
		T rootValue;
		rightTree().minTree(rootValue, tempTree);
		createWithData(rootValue, leftTree(), tempTree);
		return;
	}
	tempTree = *this;
	if (x < a) {
		*this = leftTree();
		deleteNode(x);
		createWithData(a, *this, tempTree.rightTree());
		return;
	}
	if (x > a) {
		*this = rightTree();
		deleteNode(x);
		createWithData(a, tempTree.leftTree(), *this);
	}
}
template <typename T>
void BinOrdTree<T>::deleteNodePtr(node<T> * &root, const T &x) {
	if (!root) 
	{
		cout << "Record not found!." << endl;
		return;
	}
	if (x < root->data) {
		deleteNodePtr(root->left, x);
	}
	else if (x > root->data) {
		deleteNodePtr(root->right, x);
	}
	else {
		node<T> *tempPtr;
		if (!(root->left)) {
			tempPtr = root;
			root = root->right;
			delete tempPtr;
			cout<< "Record deleted!"<<endl;
		}
		else if (!(root->right)) {
			tempPtr = root;
			root = root->left;
			delete tempPtr;
			cout << "Record deleted!" << endl;
		}
		else {
			tempPtr = root->right;
			while (tempPtr->left) {
				tempPtr = tempPtr->left;
			}
			root->data = tempPtr->data;
			deleteNodePtr(root->right, tempPtr->data);
			cout << "Record deleted!" << endl;
		}
	}
}
template <typename T>
bool member(T a, BinOrdTree<T> const & tree) {
	if (tree.empty()) {
		return false;
	}
	if (a == tree.getRootData()) {
		return true;
	}
	if (a < tree.getRootData()) {
		return member(a, tree.leftTree());
	}
	else {
		return member(a, tree.rightTree());
	}
}
template <typename T>
//proverqva dali ima takuv element v durvoto
bool member(T a, node<T> * root) {
	if (!root) {
		return false;
	}
	if (root->data == a) {
		return true;
	}
	if (a < root->data) {
		return member(a, root->left);
	}
	else {
		return member(a, root->right);
	}
}
template<typename T>
void BinOrdTree<T>::find(T x)
{
	//tursi po FN ako nameri izkarva FN
	if (member(x, root)==true)
	{
		cout << x <<endl;

	}
	else cout << "Record not found!"<<endl;
}
template<typename T>
//printira FN
void BinOrdTree<T>::traverseInorder()
{
	printFromNode(root->left);
	cout << root->data<<", ";
	printFromNode(root->right);
}