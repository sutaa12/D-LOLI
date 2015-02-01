#include"base.h"


Base::Base()
{
	this->x=0;
	this->y=0;
	this->Flag;
	this->DFlag=0.0f;
}

void Base::InputX(int px)
	{
		this->x=px;

	}
void Base::InputY(int py)
{
	this->y=py;
}
void Base::Input(int px,int py)
{
	this->x=px;
	this->y=py;
}
