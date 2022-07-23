#pragma once
#include "xml.h"

class cell;

class h_entry
{
	public:
	h_entry();
	~h_entry();

	const char *column();
	void set(xmlNodePtr node);
	cell *head = 0x0;
	cell *tail = 0x0;

	protected:

	private:
	char *_column;
};

class header
{
	public:
	header(xmlNodePtr node);
	~header();

	size_t num_entries = 0;
	h_entry *operator[](size_t index);

	protected:

	private:
	
	h_entry *columns;
};