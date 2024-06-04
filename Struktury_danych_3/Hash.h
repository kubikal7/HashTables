#pragma once
class Hash
{
public:
	virtual void insert(int, int) = 0;
	virtual int find(int) = 0;
	virtual void remove(int) = 0;
	virtual void printTable() = 0;
};

