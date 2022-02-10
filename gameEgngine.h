#pragma once
#include"Player.h"
#include"cashierStack.h"
#include"card.h"
#include"Set.h"
class gameEgngine
{

	unsigned int numOFplayer, numOFset,num_card_drop,num_tmp_set;
	Card* cards[104];
	CashierStack deck;
	CashierStack trash;
	SET** boardSets;
	Player** players;
	Card** temp_card;
	SET** temp_set;
	void crate_card();
	void crate_set();
	void addToSet(Player& player);
	void allocate(Player& player);
	bool endturn(Player& player);
	bool quit(Player& player);
	Card** realloc();
	SET** realloc(SET** boardSets);
	void rollback(Player& player);

public:
	gameEgngine();
	~gameEgngine();
	bool turn(Player& Player);
	void startgame();
};

