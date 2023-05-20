#ifndef STRING_H
#define STRING_H


void myMemCpy(void* dest, const void* src, int bytes);
void myMemMove(void* dest, void* src, int bytes);

class String
{
	char* data;
	int size;
	int stringLength(const char* c) const;
	void copyString(char* dest, const char* src);
	bool isValidIndex(int index) const;
	void swap(char& a, char& b);
public:
	String();
	String(const char);
	String(const char*);
	String(const String&);
	String(String&&);
	String& operator = (const String&);
	String& operator =(String&&);
	~String();
	void input();
	void shrink();
	char& operator[](const int index);
	const char& operator[](const int index) const;
	bool operator!() const;
	int getSize() const;
	int getLength() const;
	void display() const;
	int find(const String& subStr, const int start = 0) const;
	void insert(const int index, const String&);
	void remove(const int , const int = 1);
	int replace(const String& oldSubStr, const String& newSubStr);
	void trimLeft();
	void trimRight();
	void trim();
	void makeUpper();
	void makeLower();
	void reverse();
	void resize(int);
	int operator == (const String&) const;
	String left(const int count);
	String right(const int count);
	String operator + (const String&) const;
	void operator +=(const String&);
};

istream& operator>>(istream&, String&);
ostream& operator<<(ostream&, const String&);

#endif // !STRING_H
