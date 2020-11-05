#ifndef QUADTREES_H
#define QUADTREES_H

#include <cmath>
#include <algorithm>
#include <iostream>

typedef long long int lli;

class quad_tree
{
	// size of matrix
	int sizen;

	// 0 for white
	// 1 for black
	int data;

	// Children
	quad_tree *nw;
	quad_tree *ne;
	quad_tree *se;
	quad_tree *sw;

	lli countones() const;
	quad_tree* ext(int x1, int y1, int m);

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
	this->nw = nullptr;
	this->ne = nullptr;
	this->se = nullptr;
	this->sw = nullptr;
	if (Q.nw == nullptr)
		return;
	this->nw = new quad_tree(*(Q.nw));
	this->ne = new quad_tree(*(Q.ne));
	this->se = new quad_tree(*(Q.se));
	this->sw = new quad_tree(*(Q.sw));
}

quad_tree::~quad_tree()
{
	if (this->nw != nullptr) {
		delete this->nw;
	}
	if (this->ne != nullptr) {
		delete this->ne;
	}
	if (this->se != nullptr) {
		delete this->se;
	}
	if (this->sw != nullptr) {
		delete this->sw;
	}
}

void quad_tree::set(int x1, int y1, int x2, int y2, int b)
{
	lli len = (1 << this->size());
	if ((x1 == 0) && (x2 == len - 1) && (y1 == 0) && (y2 == len - 1)) {
		this->data = b;
		if (this->nw != nullptr) {
			delete this->nw;
			delete this->ne;
			delete this->se;
			delete this->sw;
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

	// Tree compression subroutine !
	// std::cout << "too many checks" << std::endl;
	if (this->nw->nw == nullptr && this->ne->nw == nullptr
	        && this->se->nw == nullptr && this->sw->nw == nullptr)
	{
		if (this->nw->data == this->ne->data && this->ne->data == this->se->data
		        && this->se->data == this->sw->data)
		{
			this->data = this->nw->data;
			delete this->nw;
			delete this->ne;
			delete this->se;
			delete this->sw;
			this->nw = nullptr;
			this->ne = nullptr;
			this->se = nullptr;
			this->sw = nullptr;
		}
	}
}

int quad_tree::size() const
{
	return this->sizen;
}

int quad_tree::get(int x1, int y1) const
{
	if (this->nw == nullptr)
		return this->data;

	lli midd = (1 << this->size()) / 2;
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
	return 0;
}

void quad_tree::overlap(quad_tree const &Q)
{
	if (Q.nw == nullptr && this->nw == nullptr) {
		this->data = (this->data) | (Q.data);
		return;
	}
	if (Q.nw == nullptr) {
		if (Q.data == 1) {
			delete this->nw;
			delete this->ne;
			delete this->se;
			delete this->sw;
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

	// Tree compression subroutine !
	// std::cout << "too many checks" << std::endl;
	if (this->nw->nw == nullptr && this->ne->nw == nullptr
	        && this->se->nw == nullptr && this->sw->nw == nullptr)
	{
		if (this->nw->data == this->ne->data && this->ne->data == this->se->data
		        && this->se->data == this->sw->data)
		{
			this->data = this->nw->data;
			delete this->nw;
			delete this->ne;
			delete this->se;
			delete this->sw;
			this->nw = nullptr;
			this->ne = nullptr;
			this->se = nullptr;
			this->sw = nullptr;
		}
	}
}

void quad_tree::intersect(quad_tree &Q)
{
	if (Q.nw == nullptr && this->nw == nullptr) {
		this->data = (this->data) & (Q.data);
		return;
	}
	if (Q.nw == nullptr) {
		if (Q.data == 0) {
			delete this->nw;
			delete this->ne;
			delete this->se;
			delete this->sw;
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

	// Tree compression subroutine !
	// std::cout << "too many checks" << std::endl;
	if (this->nw->nw == nullptr && this->ne->nw == nullptr
	        && this->se->nw == nullptr && this->sw->nw == nullptr)
	{
		if (this->nw->data == this->ne->data && this->ne->data == this->se->data
		        && this->se->data == this->sw->data)
		{
			this->data = this->nw->data;
			delete this->nw;
			delete this->ne;
			delete this->se;
			delete this->sw;
			this->nw = nullptr;
			this->ne = nullptr;
			this->se = nullptr;
			this->sw = nullptr;
		}
	}
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

lli quad_tree::countones() const
{
	if (this->nw == nullptr) {
		if (this->data == 1) {
			lli pow = (1 << this->size());
			return pow * pow;
		}
		return 0;
	}
	return (this->nw->countones() + this->ne->countones() + this->se->countones() + this->sw->countones());
}

void quad_tree::resize(int m)
{
	if (m == this->size())
		return;

	if (m > this->size()) {
		this->sizen = m;
		if (this->nw == nullptr)
			return;
		this->nw->resize(m - 1);
		this->ne->resize(m - 1);
		this->se->resize(m - 1);
		this->sw->resize(m - 1);
		return;
	}
	if (m < this->size()) {
		if (m == 0) {
			lli tempsize = (1 << this->size());
			tempsize *= tempsize;
			lli ones = this->countones();
			if (ones >= (tempsize / 2))
				this->data = 1;
			else
				this->data = 0;
			this->sizen = m;

			delete this->nw;
			delete this->ne;
			delete this->se;
			delete this->sw;
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

		// Tree compression subroutine !
		// std::cout << "too many checks" << std::endl;
		if (this->nw->nw == nullptr && this->ne->nw == nullptr
		        && this->se->nw == nullptr && this->sw->nw == nullptr)
		{
			if (this->nw->data == this->ne->data && this->ne->data == this->se->data
			        && this->se->data == this->sw->data)
			{
				this->data = this->nw->data;
				delete this->nw;
				delete this->ne;
				delete this->se;
				delete this->sw;
				this->nw = nullptr;
				this->ne = nullptr;
				this->se = nullptr;
				this->sw = nullptr;
			}
		}
	}
}

quad_tree* quad_tree::ext(int x1, int y1, int m)
{
	if (this->nw == nullptr) {
		quad_tree *tempret = new quad_tree(m);
		tempret->data = this->data;
		return tempret;
	}

	if (m == this->sizen) {
		quad_tree *tempret = new quad_tree(m);
		tempret->data = this->data;
		tempret->nw = this->nw;
		tempret->ne = this->ne;
		tempret->se = this->se;
		tempret->sw = this->sw;
		this->nw = nullptr;
		this->ne = nullptr;
		this->se = nullptr;
		this->sw = nullptr;
		return tempret;
	}

	int len = (1 << m);
	int midd = len / 2;
	int thislen = (1 << this->sizen);
	int thismidd = thislen / 2;

	if ((x1 + len <= thismidd) && (y1 + len <= thismidd))	{
		//nw
		return this->nw->ext(x1, y1, m);
	}
	else if ((x1 + len <= thismidd) && (y1 >= thismidd))	{
		//ne
		return this->ne->ext(x1, y1 - thismidd, m);
	}
	else if ((x1 >= thismidd) && (y1 >= thismidd))	{
		//se
		return this->se->ext(x1 - thismidd, y1 - thismidd, m);
	}
	else if ((x1 >= thismidd) && (y1 + len <= thismidd))	{
		//sw
		return this->sw->ext(x1 - thismidd, y1, m);
	}
	else {
		quad_tree *ret = new quad_tree(m);
		ret->nw = this->ext(x1, y1, m - 1);
		ret->ne = this->ext(x1, y1 + midd, m - 1);
		ret->se = this->ext(x1 + midd, y1 + midd, m - 1);
		ret->sw = this->ext(x1 + midd, y1, m - 1);

		// Tree compression subroutine
		if (ret->nw->nw == nullptr && ret->ne->nw == nullptr
		        && ret->se->nw == nullptr && ret->sw->nw == nullptr)
		{
			if (ret->nw->data == ret->ne->data && ret->ne->data == ret->se->data
			        && ret->se->data == ret->sw->data)
			{
				ret->data = ret->nw->data;
				delete ret->nw;
				delete ret->ne;
				delete ret->se;
				delete ret->sw;
				ret->nw = nullptr;
				ret->ne = nullptr;
				ret->se = nullptr;
				ret->sw = nullptr;
			}
		}
		return ret;
	}
}

void quad_tree::extract(int x1, int y1, int m)
{
	if (m == 0)
	{
		this->data = this->get(x1, y1);
		delete this->nw;
		delete this->ne;
		delete this->se;
		delete this->sw;
		this->nw = nullptr;
		this->ne = nullptr;
		this->se = nullptr;
		this->sw = nullptr;
		this->sizen = 0;
		return;
	}
	int midd = (1 << (m - 1));
	quad_tree *nw = this->ext(x1, y1, m - 1);
	quad_tree *ne = this->ext(x1, y1 + midd, m - 1);
	quad_tree *se = this->ext(x1 + midd, y1 + midd, m - 1);
	quad_tree *sw = this->ext(x1 + midd, y1, m - 1);
	delete this->nw;
	delete this->ne;
	delete this->se;
	delete this->sw;
	this->sizen = m;
	this->nw = nw;
	this->ne = ne;
	this->se = se;
	this->sw = sw;

	if (this->nw->nw == nullptr && this->ne->nw == nullptr
	        && this->se->nw == nullptr && this->sw->nw == nullptr)
	{
		if (this->nw->data == this->ne->data && this->ne->data == this->se->data
		        && this->se->data == this->sw->data)
		{
			this->data = this->nw->data;
			delete this->nw;
			delete this->ne;
			delete this->se;
			delete this->sw;
			this->nw = nullptr;
			this->ne = nullptr;
			this->se = nullptr;
			this->sw = nullptr;
		}
	}
}

#endif
