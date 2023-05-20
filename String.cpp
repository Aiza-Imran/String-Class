#include <iostream>      //for I/O 
using namespace std;

#include"String.h"


//Copies specific bytes of source array into destination array .
void myMemCpy(void* dest, const void* src, int bytes)
{
	char* d = (char*)dest;
	char* s = (char*)src;
	for (int i = 0; i < bytes; i++)
	{
		*(d + i) = *(s + i);
	}
}

//copies data. Used in the case of overlapping memory
void myMemMove(void* dest, void* src, int bytes)
{
	char* d = (char*)dest;
	char* s = (char*)src;
	char* temp = new char[bytes];
	myMemCpy(temp, s, bytes);
	for (int i = 0; i < bytes; i++)
	{
		*(d + i) = *(temp + i);
	}
	delete[] temp;
}

//returns length of the string.
int String::stringLength(const char* c) const
{
	if (!c)
	{
		return 0;      //if string is null, return length 0.
	}

	int i = 0;
	while (c[i] != '\0')
	{
		i++;
	}

	return i;
}

//completely copies src string to dest string.
void String::copyString(char* dest, const char* src)
{
	if (src == nullptr)
	{
		dest[0] = '\0';
		return;
	}

	if (dest == nullptr)
	{
		return;
	}

	int i;
	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
}

//returns true if index is valid(in range).
bool String::isValidIndex(int index) const
{
	return index >= 0 && index < size;
}

//default constructor for string.
String::String()
{
	data = nullptr;
	size = 0;
}

//Parameterized constructor. Takes one character parameter. It's also a delegate constructor.
String::String(const char c):String()
{
	
	if (c == '\0')
	{
		return;
	}
	size = 2;
	data = new char[size] { c, '\0' };

}

//Also a delegate constructor and a parameterized constructor. Takes a string(char array) as parameter
String::String(const char* c):String()
{
	if (c == nullptr || c[0] == '\0')   //if passed array is null or empty
	{
		return;
	}
	size = stringLength(c) + 1;    //size is +1 because string also has a null terminator at end and stringLength returns length of string without considering null terminator.
	data = new char[size];
	copyString(data, c);
}

//Copy constructor + delegate. Deeply copies passed string(char array) to 'this' object.
String::String(const String& ref) :String()
{
	*this = ref;
}

//Move constructor + delegate. Shallow copies the string into 'this' object.
String::String(String&& ref):String()
{
	data = ref.data;
	size = ref.size;
	ref.data = nullptr;
}

//Copy assignment. Deeply copies string. Deep copy means copying the actual data of the object to another object.
String& String::operator = (const String& ref)
{
	
	if (this == &ref)      //if passed object is 'this' object.
		return *this;

	this->~String();
	
	if (!ref.data)
		return *this;

	size = ref.size;
	data = new char[size];
	for (int i = 0; i < size; i++)
		data[i] = ref.data[i];
	return *this;
}

//Move assignment. Shallow copies an object. Shallow copy means pointing to the already existing object in the memory rather than copying all elements.
String& String::operator =(String&& ref)
{
	if (this == &ref)
		return *this;

	this->~String();

	data = ref.data;
	size = ref.size;
	ref.data = nullptr;
	return *this;
}

//Destructor. Frees the space if occupied on heap and deletes char array elements
String::~String()
{
	if (data)
	{
		delete[]data;
	}
	data = nullptr;
	size = 0;
}

//Takes console input from user until new line is enetered.
void String::input()
{
	if (!data)     //if string object is null, resize it to 1 to be able to store characters.
	{
		resize(1);
	}
	char ch;
	int count = 0;
	while ((ch = cin.get()) != '\n' && ch!= EOF)
	{
		data[count] = ch;
		count++;
		if (count == size)   //checks if array is filled or not.
		{
			resize(size * 2);
		}
	}
	data[count] = '\0';
}

//Shrinks object according to its length to free extra space used by array.
void String::shrink()
{
	resize(getLength() + 1);
}

//Index operator overload for string. This function can change data memebers value but this is not recommended at all.
char& String::operator[](const int index)
{
	if (isValidIndex(index))
	{
		return data[index];
	}
	exit(0);
}

//Const index operator overload. This function cannot change any data member's value because of const used at the end of header.
const char& String::operator[](const int index) const
{
	if (isValidIndex(index))
	{
		return data[index];
	}
	exit(0);
}

//returns true if object is empty
bool String::operator!() const
{
	if (!data || data[0] == '\0')
	{
		return true;
	}
	return false;
}

//returns size of array, not the length of string.
int String::getSize() const
{
	return size;
}

//returns length of string, not the size of array.
int String::getLength() const
{
	return stringLength(data);
}

//displays the string on screen.
void String::display() const
{
	if (data)
		cout << data;
}

//finds provided substring from given index(start) to end. Returns the starting index if substring is found else returns -1.
int String::find(const String& subStr, const int start) const
{
	if (subStr.size == 0)
	{
		exit(0);
	}

	int k, l;
	for (int i = start; data[i] != '\0'; i++)
	{
		k = 0, l = 0;
		for (int j = i; j < i + subStr.data[k] != '\0'; j++, k++)
		{
			if (data[j] == subStr.data[k])
			{
				l++;
			}
		}
		if (l == subStr.getLength())    //if complete substring matches with object's substring, then return index.
		{
			return i;
		}
	}
	return -1;
}

//inserts a substring in 'this' object at given index and manages string size accordingly.
void String::insert(const int index, const String& subStr)
{
	if (subStr.data == nullptr && data == nullptr)
	{
		return;
	}
	if (data == nullptr && subStr.data != nullptr)
	{
		resize(subStr.getLength() + 1);
		data[0] = '\0';
	}

	if (!isValidIndex(index))    //if given index is already out of range, we cannot insert in this object.
	{
		return;
	}

	if (subStr.getLength() + getLength() >= size)   //checks if existing string size can accomodate new substring or not, increases size accordingly.
	{
		int newSize = getLength() + subStr.getLength() + 1;
		resize(newSize);
	}

	int bytes = stringLength(&data[index]) + 1;
	myMemMove(&data[index + subStr.getLength()], &data[index], bytes);      //makes room for new substring
	myMemCpy(&data[index], &(subStr.data[0]), subStr.getLength());          //inserts new substring
}

//removes specified no. of characters(count) from provided index.
void String::remove(const int index, const int count)
{
	if (!isValidIndex(index))
	{
		return;
	}

	int num = index + count;

	if (num >= getLength())
	{
		data[index] = '\0';
		return;
	}

	copyString(&data[index], &data[index + count]);  //adjusts string after removing.
}

//finds all occurances of a substring(oldSubStr) from object and replaces it with new substring(newSubStr) and adjusts size accordingly
int String::replace(const String& oldSubStr, const String& newSubStr)
{
	int count = 0, index = 0;
	do    // loop repeats till all occurances are replaced.
	{
		index = find(oldSubStr, index);
		if (index != -1)
		{
			count++;
			remove(index, oldSubStr.getLength());
			insert(index, newSubStr);
			index = index + newSubStr.getLength();
		}
	} while (index != -1);

	return count; // returns  count of how many replacements have occured.
}

//removes all the white spaces(if any) from the start of the string
void String::trimLeft()
{
	int i = 0;
	while (data[i] == '\n' || data[i] == '\t' || data[i] == ' ')
	{
		i++;
	}
	copyString(&data[0], &data[i]);
}

//removes all white spaces(if any) from the end of the string.
void String::trimRight()
{
	int i = getLength() - 1;
	while (data[i] == '\n' || data[i] == '\t' || data[i] == ' ')
	{
		i--;
	}
	data[i + 1] = '\0';
}

//removes white spaces(space,tab,newline) from start and end of string.
void String::trim()
{
	trimLeft();
	trimRight();
}

//converts all the alphabets in string to uppercase.
void String::makeUpper()
{
	for (int i = 0; data[i] != '\0'; i++)
	{
		if (data[i] >= 'a' && data[i] <= 'z')
		{
			data[i] = data[i] - 32;
		}
	}
}

//converts all the alphabets in string to lowercase.
void String::makeLower()
{
	for (int i = 0; data[i] != '\0'; i++)
	{
		if (data[i] >= 'A' && data[i] <= 'Z')
		{
			data[i] = data[i] + 32;
		}
	}
}

//swaps given characters in 'this' string
void String::swap(char& a, char& b)
{
	char temp;
	temp = a;
	a = b;
	b = temp;
}

//Reverses string. i.e. converts "hello" to "olleh"
void String::reverse()
{
	int j = getLength() - 1;
	int i = 0;
	while (i < j)
	{
		swap(data[i], data[j]);
		i++;
		j--;
	}
}

//resizes array to new provided size.
void String::resize(int newSize)
{
	if (newSize <= 0)   //checks if new size is 0, then deletes all characters and returns empty string.
	{
		this->~String();
		return;
	}

	char* temp = new char[newSize];
	int i = 0;
	while (i < newSize && i < size)
	{
		temp[i] = data[i];
		i++;
	}

	this->~String();
	size = newSize;
	data = temp;
}

//overload == operator. Returns 0 if strings match, -1 if 'this' object is smaller, 1 if 'this' object is greater than s2(parameter).
int String::operator == (const String& s2) const
{

	//checks if any string is null or empty.
	if (data == nullptr && s2.data == nullptr)
	{
		return 0;
	}
	else if (data == nullptr && s2.data != nullptr)
	{
		return -1;
	}
	else if (data != nullptr && s2.data == nullptr)
	{
		return 1;
	}
	else
	{
		int i = 0;
		while (data[i] != '\0' && s2.data[i] != '\0' && data[i] == s2.data[i])
		{
			i++;
		}
		if (data[i] == s2.data[i])
		{
			return 0;
		}
		else if (data[i] < s2.data[i])
		{
			return -1;
		}
		else
			return 1;
	}
}

//removes specified no of characters(count) from start of the string and returns removed characters
String String::left(const int count)
{
	if (count > getLength())
	{
		String ans(*this);
		data[0] = '\0';
		return ans;
	}
	else if (data == nullptr)
	{
		String s;
		return s;          //return empty string
	}

	String s1;
	s1.size = count + 1;
	s1.data = new char[s1.size];
	for (int i = 0; i < count; i++)
	{
		*(s1.data + i) = *(data + i);
	}
	*(s1.data + count) = '\0';
	copyString(&data[0], &data[count]);
	return s1;
}

//removes specified no of characters(count) from end of the string and returns removed characters
String String::right(const int count)
{
	if (count > getLength())
	{
		String ans(*this);
		data[0] = '\0';
		return ans;
	}
	else if (data == nullptr)
	{
		String s;
		return s;             //return empty string
	}
	String s1;
	s1.size = count + 1;
	s1.data = new char[s1.size];
	myMemCpy(&s1.data[0], &data[getLength() - count], count);
	s1.data[count] = '\0';
	data[getLength() - count] = '\0';
	return s1;
}

//concatenation operator overload. Returns concatenated string without affecting actual object.
String String:: operator + (const String& s1) const
{
	String res(*this);
	res.insert(res.getLength(), s1);
	return res;
}

//concantenates 'this' object with the provided string s2
void String::operator +=(const String& s2)
{
	insert(getLength(), s2);
}

//stream extraction operator overload
istream& operator>>(istream& is, String& s)
{
	s.input();
	return is;
}

//stream insertion operator overload
ostream& operator<<(ostream& os, const String& ref)
{
	if (ref.getSize() > 1)
	{
		os << &ref[0];
	}
	//s.display();
	return os;
}
