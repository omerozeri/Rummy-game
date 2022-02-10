#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "card.h"
#include<iostream>
 

using namespace std;



class SET
{
private:
	int size_arrey;
	Card** SetCard;
	Card** realloc(Card* card = NULL);
	bool Same_sign();
	int find_min();
	int find_max();
	Card* Find_card(int Value, char Sign);

public:

	SET();
	SET(const SET& x);
	void addCard(Card* Newcard);
	Card* extructCard(unsigned int value, char sign);
	bool isSequentail();
	bool isSameValueSiriel();
	bool isValideSet();
	void printSet();
	bool isEmpty();
	~SET();
};