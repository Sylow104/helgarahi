#pragma once
#include "xml.h"

class h_entry
{
	public:
	h_entry();
	~h_entry();

	const char *column();
	void set(xmlNodePtr node);

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

	const h_entry *operator[](size_t index);

	protected:

	private:
	
	h_entry *columns;
};