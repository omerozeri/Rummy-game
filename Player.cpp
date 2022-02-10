#include "Player.h"
#include<iostream>

Player::Player(char* name)
{
	card_player =NULL;
	size_card = 0;
		setName(name);
	
	

}
Player::~Player()
{
	card_player = NULL;
	delete[] card_player;
	Name = NULL;
	delete[] Name;
}
void Player::setName(char* name)
{
	
	if (name != NULL) {
		delete[] Name;
		Name = new char[strlen(name) + 1];
		strcpy(Name, name);
		
	}
	else Name = NULL;
	
}
void Player::setCard(Card* card)
{
	card_player = realloc();
	card_player[size_card] = card;
	size_card++;

}
Card* Player::extructCard(char sign, int value)
{
	Card* tmp;
	if (value == 0)
	{
		tmp = card_player[0];
		card_player=realloc(card_player[0]);
		size_card--;
		return tmp;
	}
	tmp = Find_card(sign, value);
if (tmp == NULL) return NULL;
card_player =realloc(tmp);
size_card--;
return tmp;
	
}
void Player::printHand()
{
	cout << "The card's of " << Name<<": ";
	if (size_card == 0) { cout << "NO CARD" << endl; return; }
	for (int i = 0; i < size_card; i++)
	{
		card_player[i]->printCard(); cout << ",";
	}
	cout<<"\n";
}
Card** Player::realloc(Card* card)
{
	Card** tmp;
	if (card == NULL) {// for case to add card if card==NULL
		tmp = new Card * [size_card + 1];
		for (int i = 0; i < size_card; i++)
		{
			tmp[i] = card_player[i];
		}
		
	}
	else { //for case to remove card if card != NULL
		 tmp = new Card* [size_card - 1];
		for (int j=0, i = 0; i < size_card; i++)
		{
			if (card_player[i] == card)	continue;
			tmp[j] = card_player[i];
			j++;
		}
	}
	
	card_player = NULL;
	delete card_player;
	
	return tmp;

}

Card* Player::Find_card(char Sign, int Value)
{
	bool num = false;
	bool c = false;
	if (Sign < 122 && Sign>90)
		Sign -= 32;
	if (Value < 1 || Value>13)
	{
		cout << "the value is out of range " << endl;
		num = true;
	}
	if (Sign != 'C' && Sign != 'D' && Sign != 'H' && Sign != 'S') {
		cout << "the sign is not exist  " << endl; c = true;
	}
	if (c == true || num == true) return NULL;
	else {
		for (int i = 0; i < size_card; i++)
		{
			if (card_player[i]->getSign() == Sign && card_player[i]->getValue() == Value)
			{
				return card_player[i];
			}
		}
		cout << "the card dosn't exsit"<<endl;
		return NULL;
	}

}

