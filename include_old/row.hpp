#pragma once
#include "cell.hpp"

class sheet;

class row
{
	public:
	row();
	~row();

	int init(xmlNodePtr node, sheet *parent);
	cell *operator[](size_t index);

	protected:

	private:

	cell *top;
	sheet *parent;
};