#pragma once


class Scriptor
{
public:
	struct lua_State* L= nullptr;

	static Scriptor* g;
public:
	Scriptor();
	~Scriptor();

	void doFile(const char* file_name);


};



