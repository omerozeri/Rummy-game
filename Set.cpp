#include "Set.h"



Card** SET::realloc(Card* card)
{
	Card** tmp;
	if (card == NULL) {// for case to add card if card==NULL
		tmp = new Card * [size_arrey + 1];
		for (int i = 0; i < size_arrey; i++)
		{
			tmp[i] = SetCard[i];
		}

	}
	else {
		//for case to remove card if card != NULL
		tmp = new Card * [size_arrey - 1];
		for (int j=0, i = 0; i < size_arrey; i++)
		{
			if (SetCard[i] == card)continue;
			tmp[j] = SetCard[i];
			j++;
		}
	}
	SetCard = NULL;
	delete [] SetCard;
	return tmp;
}

bool SET::Same_sign()
{
	for (int i = 0; i < size_arrey-1; i++)
	{
		if (SetCard[i]->getSign() == SetCard[i + 1]->getSign())
			continue;
		else
			return false;
	}
	return true;
}

int SET::find_min()
{
	int min = SetCard[0]->getValue();
	for (int i = 1; i < size_arrey; i++)
	{
		if (SetCard[i]->getValue() <= min)
			min = SetCard[i]->getValue();
	}
	return min;
}

int SET::find_max()
{
	int max= SetCard[0]->getValue();
	for (int i = 1; i < size_arrey-1; i++)
	{
		if (SetCard[i]->getValue() >= max)
			max = SetCard[i]->getValue();
	}
	return max;
}

Card* SET::Find_card(int Value, char Sign)
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
	if (Sign != 'C' &&Sign != 'D' && Sign != 'H' && Sign != 'S') {
		cout << "the sign is not exist  " << endl; c = true;
	}
	if (c == true || num == true) return NULL;
	else {
		for (int i = 0; i < size_arrey; i++)
		{
			if (SetCard[i]->getSign() == Sign && SetCard[i]->getValue() == Value)
			{
				return SetCard[i];
			}
		}
		cout << "the card dosn't exsit" << endl;
		return NULL;
	}
}

SET::SET()
{
	size_arrey = 0;
	SetCard = NULL;
}

SET::SET(const SET& x)
{
	size_arrey = x.size_arrey;
	SetCard = new Card*[size_arrey];
	for (int i = 0; i < size_arrey; i++)
	{
		SetCard[i] = x.SetCard[i];
	}

	
}
void SET::addCard(Card* Newcard)
{
	SetCard = realloc();
 SetCard[size_arrey] = Newcard;
 size_arrey++;

}
Card* SET::extructCard(unsigned int value, char sign)
{
	Card* tmp = Find_card(value, sign);
	if(tmp==NULL)return NULL;

				SetCard = realloc(tmp);
				size_arrey--;
				return tmp;
}		
		
bool SET::isSequentail()
{
	int min = find_min();
	int max = find_max();
	if (Same_sign() == false) return false;
	
	for (int i = 0; i < size_arrey-1; i++) {
		for (int j = 0; j < size_arrey-1; j++)
		{
			if (SetCard[j]->getValue() == min + 1 )
			{
				min++;
				break;
			}
			
		}
	}
	if (min == max) return true;
	else return false;


}
bool SET::isSameValueSiriel()
{
	if (Same_sign() == true)
		return false;

	for (int i = 0; i < size_arrey - 1; i++)
	{
		if (SetCard[i]->getValue() == SetCard[i + 1]->getValue())
			continue;
		return false;
	}
	return true;
}

bool SET::isValideSet()
{
	if (size_arrey < 3) return false;
	if (isSameValueSiriel() || isSequentail())
		return true;
	else false;
}

void SET::printSet()
{
	if (isEmpty()) { cout << "EMPTY serial\n" << endl; return; }

	for (int n = 0; n < size_arrey; n++)
	{
		SetCard[n]->printCard(); cout << ",";
	}
	cout << "\n";
}

bool SET::isEmpty()
{
	if (size_arrey == 0)
		return true;
	else return false;
}

SET::~SET()
{
	delete[] SetCard;
}
