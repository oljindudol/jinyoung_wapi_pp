#pragma once


class CPal
{
	//싱글턴한이유 : 브러쉬는 게임에서 항상쓰기때문
	SINGLETON(CPal);



private:
	vector<HPEN> vhp;
	vector<HBRUSH> vhb;


public:
	HPEN getHPen(COLOR _COLOR);
	HBRUSH getHBrush(COLOR _COLOR);
};

