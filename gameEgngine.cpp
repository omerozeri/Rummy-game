#include "gameEgngine.h"

void gameEgngine::crate_card()
{
	char sign[] = { 'C','D','H','S' };
	int num = 1;
	
	for (int i = 0; i < 104; )
	{
		for (int j = 0; j < 4; j++)
		{
			Card* card = new Card;
			card->setCard(sign[j], num);
			cards[i] = card;
			i++;
		}
		num++;
			if (num == 14)num = 1;
	}
	
}

void gameEgngine::crate_set()
{
	boardSets = realloc(boardSets);
	SET* newset = new SET;
	boardSets[numOFset-1] = newset;
	cout << "----Board status ----:" << endl;
	for (int i = 0; i < numOFset; i++)
	{
		cout << "set no #" << i + 1 << ":"; boardSets[i]->printSet();
	}
	
}

void gameEgngine::addToSet(Player& player)
{
	char sign;
	unsigned int value, index;
	Card* card;
	cout << "----Board status ----:" << endl;
	for (int i = 0; i < numOFset; i++)
	{
		cout << "set no" << i + 1 << ":"; boardSets[i]->printSet();
	}
	cout << "\t\t---player hand:---\n"; player.printHand();
	cout << "Which card? enter sign(S{?}/C{?}/H{?}/D{?}) and value\n";
	do
	{
		cin.clear();
		cout << "sign:";
		do
		{	cin >> sign;
		if (sign>122||sign<65) cout << "enter sign of card again:";
			
		} while (sign > 122 || sign < 65);
		cin.clear();
		cout << "\nvalue:";
		do
		{
			cin >> value;
			if (sizeof(value) != sizeof(int)) cout << "enter value of card again:";

		} while (sizeof(value) != sizeof(int));

		card = player.extructCard(sign, value);
		if (card == NULL) cout << "enter sign and value again" << endl;
	} while (card == NULL);
	cout << "----Board status ----:" << endl;

	for (int i = 0; i < numOFset; i++)
	{
		cout << "set no" << i + 1 << ":"; boardSets[i]->printSet();
	}

	cout << "Which set no?";
	if (numOFset != 0)
		do
		{
			cin.clear();
			cin >> index;
			if (index > numOFset)cout << "invalid set chose again" << endl;
		} while (index > numOFset);
	else { crate_set(); index = 1; }

	temp_card = realloc();
	temp_card[num_card_drop - 1] = card;
	boardSets[index - 1]->addCard(card);	
	for (int i = 0; i < numOFset; i++)
	{
		cout << "set no" << i + 1 << ":"; boardSets[i]->printSet();
	}
}

void gameEgngine::allocate(Player& player)
{
	unsigned int setout, setin, value;
	char sign;
	Card* card;
	cout << "Which Set no to allocate from?" << endl;
	do
	{
		cin >> setout;
		if (setout > numOFset)cout << "invalid set chose again" << endl;
	} while (setout > numOFset);
	cout << "Which card? enter sign(S{?}/C{?}/H{?}/D{?}) and value: " << endl;
	do
	{
		cin.clear();
		cout << "sign:";
		do
		{
			cin >> sign;
			if (sign > 122 || sign < 65) cout << "enter sign of card again:";

		} while (sign > 122 || sign < 65);
		cin.clear();
		cout << "\nvalue:";
		do
		{
			cin >> value;
			if (sizeof(value) != sizeof(int)) cout << "enter value of card again:";

		} while (sizeof(value) != sizeof(int));
card=boardSets[setout-1]->extructCard(value, sign);
if (card == NULL)cout << "enter llegal sign(S{?}/C{?}/H{?}/D{?}) and value : ";
	} while (card==NULL); 
	
	cout << "Which Set no to allocate to?" << endl;
	do
	{cin >> setin;
		if (setin > numOFset)cout << "invalid set chose again" << endl;
	} while (setin > numOFset);
	boardSets[setin-1]->addCard(card);
}

bool gameEgngine::endturn(Player& player)
{

	char sign;
	int value;
	Card* card;
	bool valid;
	cout << "----Board status:----" << endl;
	for (int i = 0; i < numOFset; i++)
	{
		cout << "set no" << i+1 << ":"; boardSets[i]->printSet();
	}
	cout << "---player hand:---"; player.printHand();
	for (int i = 0; i < numOFset; i++)
	{
		valid = boardSets[i]->isValideSet();
		if (!valid) {
			cout << "\t\t\t******* the set is not valid *******\n";
			rollback(player);
			num_card_drop = 0;
		}
		else {
			delete[]temp_card;
			for (int i = 0; i < num_tmp_set; i++)
			{
				delete temp_set[i];
			}
			delete[] temp_set;
		}
		}
		if (player.getNumberOfCards() == 0)
		{
			cout << "the winner is :" << player.getName();
			return false;
		}
		cout << "Which card? enter sign(S{?}/C{?}/H{?}/D{?}) and value:";
		do
		{
			cin >> sign; cin >> value;
			card = player.extructCard(sign, value);
			if (card == NULL) cout << "the card didnt found enter again sign(S{?}/C{?}/H{?}/D{?}) and value: ";
		} while (card == NULL);
		trash.push(card);
		if (player.getNumberOfCards() == 0)
		{
			cout << "the winner is :" << player.getName();
			return false;
		}
		else return true;

	
}

	bool gameEgngine::quit(Player& player)
	{
		for (int i = 0; i < player.getNumberOfCards(); i++)
		{
			deck.push(player.extructCard());
		}
		deck.shuffle();
		
		Player** tmp_players = new Player * [numOFplayer - 1];
		for (int j=0,i = 0; i < numOFplayer; i++)
		{
			if (strcmp(players[i]->getName(), player.getName()) == 0) continue;
			tmp_players[j] = players[i];
			j++;
		}
		delete& player;
		numOFplayer--;
		if (numOFplayer == 1)
		{
			cout << "The winner of the game is :" << tmp_players[0]->getName() << endl;
			return false;
		}

		else return true;
	}


Card** gameEgngine::realloc()
{
	 
		Card** tmp = new Card* [num_card_drop+1];
		for (int i = 0; i < num_card_drop; i++)
		{
			tmp[i] = temp_card[i];
		}
		num_card_drop++;
		temp_card = NULL;
		delete[] temp_card;
		return tmp;
	
}

SET** gameEgngine::realloc(SET** boardSets)
{

	SET** tmp = new SET* [numOFset + 1];
	for (int i = 0; i < numOFset; i++)
	{
		tmp[i] = boardSets[i];
	}
	numOFset++;
	boardSets = NULL;
	delete[] boardSets;
	return tmp;
}

void gameEgngine::rollback(Player& player)
{
	for (int i = 0; i < numOFset; i++)
	{
		boardSets[i] = NULL;
		delete boardSets[i];
	}
	numOFset = num_tmp_set;
	boardSets = temp_set;
	temp_set = NULL;
	delete temp_set;
	for (int i = 0; i < num_card_drop; i++)
	{
		player.setCard(temp_card[i]);
	}
	temp_card = NULL;
	delete[] temp_card;
	
	cout << "youer hand was beak to be:\n"; player.printHand();
	
}

gameEgngine::gameEgngine()
{
	crate_card();
	for (int i = 0; i < 104; i++)
	{
		deck.push(cards[i]);
	}
	deck.shuffle();
	numOFplayer = 0;
	players = NULL;
	numOFset = 0;
	boardSets = NULL;
	
}

gameEgngine::~gameEgngine()
{
	deck.~CashierStack();
	trash.~CashierStack();
	for (int i = 0; i < 104; i++)
	{
		delete[] cards[i];
	}
	for (int i = 0; i < numOFplayer; i++)
	{
		players[i]->~Player();
	} 
	delete[]players;
	for ( int i = 0; i < numOFset; i++)
	{
		boardSets[i]->~SET();
	}
	delete[] boardSets;
	
	
}

bool gameEgngine::turn(Player& Player)
{
	int answer, i;
	num_card_drop = 0;
	bool victory = true;
	Card* card_trash = trash.pop();
	temp_set = new SET * [numOFset];
	temp_set = NULL;
	num_tmp_set = numOFset;
	temp_card = NULL;
		for (int i = 0; i < numOFset; i++)
		{
			temp_set[i]=new SET(*boardSets[i]);
		}
	
		cout << "\t\t\t\t\t***********player:" << Player.getName() << " turn***********" << endl;
		
	cout << "If you would like to Quit press 0 otherwise press any other key: ";
	cin >> answer;
	if (answer == 0) return victory = quit(Player); 
	cout << " youer hand :"; Player.printHand(); cout << "\n";
	cout << "Top deck card is: "; card_trash->printCard();

	cout << "\n would you like to take top deck card(press 0) or extract new card from cashier(press 1) ";

	do
	{
		cin.clear();
		cin >> answer;
		if (answer != 1 && answer != 0)cout << "press 0 to take top deck or 1 extract new card from cashier ";
	} while (answer != 1 && answer != 0); 
	if (answer == 1) {
		Player.setCard(deck.pop());
		trash.push(card_trash);
	}
	else Player.setCard(card_trash);

	char choise;
	while (victory)
	{
		cout << "what would you like to do" << endl << "1)create new set" << endl << "2)Add to existing set a card from hand" << endl;
		cout << "3)Allocate between existing sets" << endl << "0)End turn" << endl;
		cin >> choise;
		switch (choise) {
		case '1':crate_set();
			break;
		case '2':addToSet(Player);
		break;
		case '3':allocate(Player);
			break;
		case '0': return victory = endturn(Player);
			break;
		default: cout << "invalid choise please enter again " << endl;
			break;

		
		}

	}
}

void gameEgngine::startgame()
{
	char name[50];
	bool game=true;
	cout << "HELLO how many players play ?";
	cin>> numOFplayer;
	players = new Player * [numOFplayer];
	cout << "enter the name of the players" << endl;
		for (int i = 0; i < numOFplayer; i++)
		{
			cout << "name of player#" << i + 1 << ":";
			cin >> name;
			
			players[i] = new Player(name);
			for (int j = 0; j < 14; j++)
			{
				players[i]->setCard(deck.pop());
			}
			
		}
		trash.push(deck.pop());
		int tmp_num_player =numOFplayer;
		while (game = turn(**(players)))
		{
			if (tmp_num_player>numOFplayer)
			{
				tmp_num_player -= 1;//if player quit;
				continue;
			}
		if (*(players) = players[numOFplayer-1]) (*players) = players[0];

		else
		*(players += 1);
		}


}
