#pragma once
#include "Set.h"
#include<iostream>
class Player
{

	char* Name;
	Card** card_player;
	int size_card;
	Card** realloc(Card* card=NULL);
	Card* Find_card(char Sign, int Value);
public:
	Player(char *name=NULL);
	
	void setName(char* name);
	void setCard(Card* card);
	Card* extructCard(char sign='\0', int value =0 );
	char* getName() { return Name; };
	int getNumberOfCards() { return size_card; };
	void printHand();
	~Player();
};

