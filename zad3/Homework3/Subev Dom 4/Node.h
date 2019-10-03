#pragma once
template <typename T>
struct node {
	T data;
	node<T> *left;
	node<T> *right;
};