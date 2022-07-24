#pragma once
#include "header.hpp"
#include "cell.hpp"

class value : public cell
{
	public:
	value();
	~value();

	int init(xmlNodePtr node, h_entry *col);
	value *next = 0x0;

};