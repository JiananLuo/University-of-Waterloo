#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include "istring.h"

//see header file
iString::iString()
{
	this->length = 0;
	this->capacity = 0;
	this->chars = NULL;
}

//see header file
iString::iString(const char * other)
{
	if(other == NULL)
	{
		this->length = 0;
		this->capacity = 0;
		this->chars = NULL;
	}
	else
	{
		this->length = strlen(other);
		this->capacity = this->length;
		this->chars = new char[this->length];
		for(int i=0; i<this->length; i++)
			this->chars[i] = other[i];
	}
}

//see header file
iString::iString(const iString & other)
{
	this->length = other.length;
	this->capacity = other.capacity;
	if(other.chars == NULL)
		this->chars = NULL;
	else
	{
		this->chars = new char[this->length];
		for(int i=0; i<this->length; i++)
			this->chars[i] = other.chars[i];
	}
}

//see header file
iString& iString::operator=(const iString & other)
{
	if(this == &other)
		return *this;
	delete [] this->chars;
	this->length = other.length;
	this->capacity = other.capacity;
	if(other.chars == NULL)
		this->chars = NULL;
	else
	{
		this->chars = new char[this->length];
		for(int i=0; i<this->length; i++)
			this->chars[i] = other.chars[i];
	}
	return *this;
}

//see header file
iString operator+(const iString & s1, const iString & s2)
{
	iString s;
	s.length = s1.length + s2.length;
	s.capacity = s1.capacity + s2.capacity;
	if(s1.length == 0 && s2.length == 0)
		s.chars = NULL;
	else
	{
		s.chars = new char[s.length];
		if(s1.chars == NULL)
		{
			for(int i=0; i<s.length; i++)
				s.chars[i]=s2.chars[i];
		}
		else if(s2.chars == NULL)
		{       
			for(int i=0; i<s.length; i++)
				s.chars[i]=s1.chars[i];
		}
		else
		{
			for(int i=0; i<s1.length; i++)
				s.chars[i]=s1.chars[i];
			for(int i=s1.length; i<s.length; i++)
				s.chars[i]=s2.chars[i-s1.length];
		}
	}
	return s;
}

//see header file
iString operator+(const iString & s1, char * chars)
{
	iString s;
	s.length = s1.length + strlen(chars);
	s.capacity = s1.length;
	s.chars = new char[s.length];
	for(int i=0; i<s1.length; i++)
		s.chars[i] = s1.chars[i];
	for(int i=s1.length; i<s1.length; i++)
		s.chars[i] = chars[i-s1.length];
	return s;
}

//see header file
iString operator*(int n, const iString& other)
{
	int l = other.length;
	iString s;
	s.length = l * n;
	s.capacity = other.capacity * n;
	if(s.length == 0)
		s.chars = NULL;
	else
	{
		s.chars = new char[s.length];
		for(int i=0; i<n; i++)
		{
			for(int j=0; j<l; j++)
			{
				s.chars[i*l + j] = other.chars[j];
			}
		}
	}
	return s;
}

/************** doubleSize ************
     Purpose: Double the size of the capacity of the parameter iString
     Returns: Return nothing
     Error: None
************************************/
void doubleSize(iString & s)
{
	s.capacity *= 2;
	char *tmp = new char[s.capacity];
	for(int i=0; i<s.length; i++)
		tmp[i]=s.chars[i];
	delete [] s.chars;
	s.chars = tmp;
}

//see header file
std::istream &operator>>(std::istream &in, iString &s)
{
	delete [] s.chars;
	s.length=0;
	s.capacity=1;
	s.chars = new char[s.capacity];
	char c;
	if(isspace(in.peek()))
		in.ignore();
	while(!(isspace(in.peek())))
	{
		if(s.length == s.capacity)
			doubleSize(s);
		in>>c;
		s.chars[s.length]=c;
		s.length++;
	}
	return in;
}

//see header file
std::ostream &operator<<(std::ostream &out, const iString &s)
{
	if(s.length != 0)
	{
		for(int i = 0; i < s.length; i++)
			out<<s.chars[i];
	}
	return out;
}

//see header file
iString::~iString()
{
	this->length = 0;
	this->capacity = 0;
	delete [] this->chars;
}
