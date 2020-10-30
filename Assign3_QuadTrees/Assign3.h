#ifndef QUADTREES_H
#define QUADTREES_H

#include <cmath>
#include <algorithm>
#include <iostream>

// typedef long long int lli;
// const int MOD = 1e9 + 7;

class quad_tree
{
	// size of matrix
	int sizen;

	// -1 for non-leaf node
	// 0 for white
	// 1 for black
	int data;

	// Children
	quad_tree *nw;
	quad_tree *ne;
	quad_tree *se;
	quad_tree *sw;

	int countones() const;
	// void deleteTree(quad_tree *quad);
public:
	quad_tree();
	quad_tree(int n);
	quad_tree(quad_tree const &Q);
	~quad_tree();

	void set(int x1, int y1, int x2, int y2, int b);
	int get(int x1, int y1) const;
	int size() const;
	void overlap(quad_tree const &Q);
	void intersect(quad_tree &Q);
	void complement();
	void resize(int m);
	void extract(int x1, int y1, int m);
};

quad_tree::quad_tree()
{
	this->sizen = 0;
	this->data = 0;
	this->nw = nullptr;
	this->ne = nullptr;
	this->se = nullptr;
	this->sw = nullptr;
}

quad_tree::quad_tree(int n)
{
	this->sizen = n;
	this->data = 0;
	this->nw = nullptr;
	this->ne = nullptr;
	this->se = nullptr;
	this->sw = nullptr;
}

quad_tree::quad_tree(quad_tree const &Q)
{
	this->sizen = Q.size();
	this->data = Q.data;
	if (Q.nw == nullptr)
		return;
	this->nw = new quad_tree(*(Q.nw));
	this->ne = new quad_tree(*(Q.ne));
	this->se = new quad_tree(*(Q.se));
	this->sw = new quad_tree(*(Q.sw));
}

quad_tree::~quad_tree()
{
	if (this != nullptr) {
		delete this->nw;
		delete this->ne;
		delete this->se;
		delete this->sw;
	}
}

void quad_tree::set(int x1, int y1, int x2, int y2, int b)
{
	// for (int i = 0; i < (1 << this->size()); ++i) {
	// 	for (int j = 0; j < (1 << this->size()); ++j)
	// 		std::cout << this->get(i, j) << " ";
	// 	std::cout << std::endl;
	// }
	int len = (1 << this->size());
	if ((x1 == 0) && (x2 == len - 1) && (y1 == 0) && (y2 == len - 1)) {
		this->data = b;
		if (this->nw != nullptr) {
			this->nw->~quad_tree();
			this->ne->~quad_tree();
			this->se->~quad_tree();
			this->sw->~quad_tree();
			this->nw = nullptr;
			this->ne = nullptr;
			this->se = nullptr;
			this->sw = nullptr;
		}
		return;
	}

	bool nwact, neact, seact, swact;
	nwact = neact = seact = swact = true;

	int midd = len / 2;
	int coords[4][4];
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			coords[i][j] = -1;

	// x1,x2,y1,y2 nw
	// x1,x2,y1,y2 ne
	// etc
	if (y1 >= midd) { nwact = false; swact = false;	}
	if (x1 >= midd) { neact = false; nwact = false;	}
	if (y2 < midd) { neact = false; seact = false;	}
	if (x2 < midd) { seact = false;	swact = false;	}
	// nw
	if (nwact) {
		coords[0][0] = x1;
		coords[0][1] = std::min(midd - 1, x2);
		coords[0][2] = y1;
		coords[0][3] = std::min(midd - 1, y2);
	}
	if (neact) {
		coords[1][0] = x1;
		coords[1][1] = std::min(midd - 1, x2);
		coords[1][2] = std::max(midd, y1) - midd;
		coords[1][3] = y2 - midd;
	}
	if (seact) {
		coords[2][0] = std::max(midd, x1) - midd;
		coords[2][1] = x2 - midd;
		coords[2][2] = std::max(midd, y1) - midd;
		coords[2][3] = y2 - midd;
	}
	if (swact) {
		coords[3][0] = std::max(midd, x1) - midd;
		coords[3][1] = x2 - midd;
		coords[3][2] = y1;
		coords[3][3] = std::min(midd - 1, y2);
	}

	// for (int i = 0; i < 4; ++i)
	// {
	// 	for (int j = 0; j < 4; ++j)
	// 	{
	// 		std::cout << coords[i][j] << " ";
	// 	}
	// 	std::cout << std::endl;
	// }

	if (this->nw == nullptr) {
		this->nw = new quad_tree(this->size() - 1);
		this->ne = new quad_tree(this->size() - 1);
		this->se = new quad_tree(this->size() - 1);
		this->sw = new quad_tree(this->size() - 1);
		this->nw->set(0, 0, midd - 1, midd - 1, this->data);
		this->ne->set(0, 0, midd - 1, midd - 1, this->data);
		this->se->set(0, 0, midd - 1, midd - 1, this->data);
		this->sw->set(0, 0, midd - 1, midd - 1, this->data);
	}
	if (nwact)
		this->nw->set(coords[0][0], coords[0][2], coords[0][1], coords[0][3], b);
	if (neact)
		this->ne->set(coords[1][0], coords[1][2], coords[1][1], coords[1][3], b);
	if (seact)
		this->se->set(coords[2][0], coords[2][2], coords[2][1], coords[2][3], b);
	if (swact)
		this->sw->set(coords[3][0], coords[3][2], coords[3][1], coords[3][3], b);
}

int quad_tree::size() const
{
	return this->sizen;
}

int quad_tree::get(int x1, int y1) const
{
	if (this->nw == nullptr)
		return this->data;

	int midd = (1 << this->size()) / 2;
	if (x1 >= midd)
		// choose from se and sw
		if (y1 >= midd)
			// se
			return this->se->get(x1 - midd, y1 - midd);
		else
			// sw
			return this->sw->get(x1 - midd, y1);
	else
		// choose from ne and nw
		if (y1 >= midd)
			// ne
			return this->ne->get(x1, y1 - midd);
		else
			// nw
			return this->nw->get(x1, y1);
	return -1;
}

void quad_tree::overlap(quad_tree const &Q)
{
	if (Q.nw == nullptr && this->nw == nullptr) {
		this->data = std::max(this->data, Q.data);
		return;
	}
	if (Q.nw == nullptr) {
		if (Q.data == 1) {
			this->nw->~quad_tree();
			this->ne->~quad_tree();
			this->se->~quad_tree();
			this->sw->~quad_tree();
			this->nw = nullptr;
			this->ne = nullptr;
			this->se = nullptr;
			this->sw = nullptr;
			this->data = 1;
		}
		return;
	}
	if (this->nw == nullptr) {
		if (this->data == 0) {
			this->nw = new quad_tree(*(Q.nw));
			this->ne = new quad_tree(*(Q.ne));
			this->se = new quad_tree(*(Q.se));
			this->sw = new quad_tree(*(Q.sw));
		}
		return;
	}
	this->nw->overlap(*(Q.nw));
	this->ne->overlap(*(Q.ne));
	this->se->overlap(*(Q.se));
	this->sw->overlap(*(Q.sw));
}

void quad_tree::intersect(quad_tree &Q)
{
	if (Q.nw == nullptr && this->nw == nullptr) {
		this->data = (this->data) & (Q.data);
		return;
	}
	if (Q.nw == nullptr) {
		if (Q.data == 0) {
			this->nw->~quad_tree();
			this->ne->~quad_tree();
			this->se->~quad_tree();
			this->sw->~quad_tree();
			this->nw = nullptr;
			this->ne = nullptr;
			this->se = nullptr;
			this->sw = nullptr;
			this->data = 0;
		}
		return;
	}
	if (this->nw == nullptr) {
		if (this->data == 1) {
			this->nw = new quad_tree(*(Q.nw));
			this->ne = new quad_tree(*(Q.ne));
			this->se = new quad_tree(*(Q.se));
			this->sw = new quad_tree(*(Q.sw));
		}
		return;
	}
	this->nw->intersect(*(Q.nw));
	this->ne->intersect(*(Q.ne));
	this->se->intersect(*(Q.se));
	this->sw->intersect(*(Q.sw));
}

void quad_tree::complement()
{
	if (this->nw == nullptr)
	{
		this->data = 1 - this->data;
		return;
	}
	this->nw->complement();
	this->ne->complement();
	this->se->complement();
	this->sw->complement();
}

int quad_tree::countones() const
{
	if (this->nw == nullptr) {
		if (this->data == 1) {
			int pow = (1 << this->size());
			return pow * pow;
		}
		return 0;
	}
	return (this->nw->countones() + this->ne->countones() + this->se->countones() + this->sw->countones());
}

void quad_tree::resize(int m)
{
	if (m > this->size()) {
		this->sizen = m;
		if (this->nw == nullptr)
			return;
		this->nw->resize(m - 1);
		this->ne->resize(m - 1);
		this->se->resize(m - 1);
		this->sw->resize(m - 1);
	}
	else if (m < this->size()) {
		int tempsize = (1 << this->size());
		tempsize *= tempsize;
		if (m == 0) {
			int ones = this->countones();
			if (ones >= tempsize / 2)
				this->data = 1;
			else
				this->data = 0;
			this->sizen = m;
			this->nw->~quad_tree();
			this->ne->~quad_tree();
			this->se->~quad_tree();
			this->sw->~quad_tree();
			this->nw = nullptr;
			this->ne = nullptr;
			this->se = nullptr;
			this->sw = nullptr;
			return;
		}
		this->sizen = m;
		if (this->nw == nullptr)
			return;
		this->nw->resize(m - 1);
		this->ne->resize(m - 1);
		this->se->resize(m - 1);
		this->sw->resize(m - 1);
	}
	else
		return;
}

void quad_tree::extract(int x1, int y1, int m)
{

}

#endif
