
#include<iostream>
using namespace std;

class String
{

private:
	char* ptr;
	int size;
public:
	String()
	{
		this->ptr = nullptr;
		this->size = 0;
	}

	String(const char* str)
	{
		this->size = 0;
		for (int i = 0; str[i] != '\0'; i++)
			this->size++;

		this->ptr = new char[this->size + 1];

		for (int i = 0; str[i] != '\0'; i++)
			this->ptr[i] = str[i];

		ptr[this->size] = '\0';
	}

	String(const String& copy)
	{
		this->size = copy.size;

		this->ptr = new char[this->size + 1];

		for (int i = 0; copy.ptr[i] != '\0'; i++)
			this->ptr[i] = copy.ptr[i];

		this->ptr[this->size] = '\0';

	}

	String(int x)
	{
		this->size = x;

		this->ptr = new char[this->size + 1];

		for (int i = 0; i < this->size; i++)
			this->ptr[i] = NULL;

		this->ptr[this->size] = '\0';
	}

	char* getdata()
	{
		return this->ptr;
	}

	char* getData() const
	{
		return this->ptr;
	}

	char& operator[](int i) const
	{
		if (i >= 0)
		{
			if (i < this->size)
				return *(this->ptr + i);
	
		}
		else
		{
			int temp = this->size + i;

			if (temp >= 0 && temp < this->size)
				return *(this->ptr + temp);

		}
	}

	String operator+(const String& str)
	{
		String temp(this->ptr);

		delete[]this->ptr;
		this->ptr = nullptr;

		this->size = temp.size + str.size;
		this->ptr = new char[this->size + 1];
		int tempIndex = 0;

		for (int i = 0; temp.ptr[i] != '\0'; i++)
		{
			this->ptr[i] = temp.ptr[i];
			tempIndex++;
		}

		int j = 0;

		for (int i = tempIndex; i < this->size; i++)
		{
			this->ptr[i] = str.ptr[j];
			j++;
		}

		this->ptr[this->size] = '\0';

		return	*this;
	}

	String operator+(const char& str)
	{
		String temp(this->ptr);

		delete[]this->ptr;
		this->ptr = nullptr;

		this->size = temp.size + 1;
		this->ptr = new char[this->size + 1];

		for (int i = 0; i <= this->size; i++)
			this->ptr[i] = temp.ptr[i];

		this->ptr[this->size - 1] = str;
		this->ptr[this->size] = '\0';

		return *this;
	}

	String operator+(const char* str)
	{
		String temp(this->ptr);

		delete[]this->ptr;
		this->ptr = nullptr;

		int strSize = 0;
		for (int i = 0; str[i] != '\0'; i++)
			strSize++;

		this->size = temp.size + strSize;
		this->ptr = new char[this->size + 1];

		int tempIndex = 0;

		for (int i = 0; temp.ptr[i] != '\0'; i++)
		{
			this->ptr[i] = temp.ptr[i];
			tempIndex++;
		}

		int j = 0;

		for (int i = tempIndex; i < this->size; i++)
		{
			this->ptr[i] = str[j];
			j++;
		}

		this->ptr[this->size] = '\0';

		return	*this;
	}

	String operator-(const String& substr)
	{
		int loopCount = 0;
		for (int i = 0; i < this->size; i++)
		{
			if (this->ptr[i] == substr.ptr[0])
				loopCount++;
		}

		for (int k = 0; k < loopCount; k++)
		{
			int i = 0, j = 0, c = 0, endIndex = 0;

			while (this->ptr[i] != '\0')
			{
				if (this->ptr[i] != substr.ptr[j])
					i++;
				else if (this->ptr[i] == substr.ptr[j])
				{
					while (substr.ptr[j] != '\0')
					{
						if (this->ptr[i] == substr.ptr[j])
						{
							endIndex = i;
							i++;
							j++;
							c++;
						}
						else
						{
							c = 0;
							break;
						}
					}
				}
			}

			int startIndex = endIndex - (substr.size - 1);

			if (c != 0)
			{
				String temp(this->ptr);
				delete this->ptr;
				this->size = this->size - substr.size;
				this->ptr = new char[this->size + 1];
				int l = 0;
				for (int k = 0; k < temp.size; k++)
				{
					if (k<startIndex || k>endIndex)
					{
						this->ptr[l] = temp.ptr[k];
						l++;
					}
				}
				this->ptr[this->size] = '\0';
			}
		}

		return *this;
	}

	String operator-(const char& str)
	{
		int count = 0;
		String temp(this->ptr);
		for (int i = 0; i < this->size; i++)
		{
			if (this->ptr[i] == str)
				count++;
		}

		this->size -= count;

		delete this->ptr;

		this->ptr = new char[this->size + 1];

		int j = 0;

		for (int i = 0; i < temp.size; i++)
		{
			if (temp.ptr[i] != str)
			{
				this->ptr[j] = temp.ptr[i];
				j++;
			}
		}

		this->ptr[this->size] = '\0';

		return *this;
	}

	String operator-(const char* str)
	{

		int strSize = 0;
		for (int i = 0; str[i] != '\0'; i++)
			strSize++;

		int loopCount = 0;
		for (int i = 0; i < this->size; i++)
		{
			if (this->ptr[i] == str[0])
				loopCount++;
		}

		for (int k = 0; k < loopCount; k++)

		{
			int i = 0, j = 0, c = 0, endIndex = 0;

			while (this->ptr[i] != '\0')
			{
				if (this->ptr[i] != str[j])
					i++;
				else if (this->ptr[i] == str[j])
				{
					while (str[j] != '\0')
					{
						if (this->ptr[i] == str[j])
						{
							endIndex = i;
							i++;
							j++;
							c++;
						}
						else
						{
							c = 0;
							break;
						}
					}
				}
			}

			int startIndex = endIndex - (strSize - 1);

			if (c != 0)
			{
				String temp(this->ptr);
				delete this->ptr;
				this->size = this->size - strSize;
				this->ptr = new char[this->size + 1];
				int l = 0;
				for (int k = 0; k < temp.size; k++)
				{
					if (k<startIndex || k>endIndex)
					{
						this->ptr[l] = temp.ptr[k];
						l++;
					}
				}
				this->ptr[this->size] = '\0';
			}
		}

		return *this;
	}

	String& operator=(const String& copy)
	{
		delete[]this->ptr;

		this->size = 0;
		this->size = copy.size;
		this->ptr = new char[this->size + 1];

		for (int i = 0; i < this->size; i++)
			this->ptr[i] = copy.ptr[i];

		this->ptr[this->size] = '\0';

		return *this;
	}

	String& operator=(char* str)
	{

		delete[]this->ptr;
		this->ptr = nullptr;

		int strSize = 0;
		for (int i = 0; str[i] != '\0'; i++)
			strSize++;

		this->size = strSize;
		this->ptr = new char[this->size + 1];

		for (int i = 0; str[i] != '\0'; i++)
			this->ptr[i] = str[i];

		this->ptr[this->size] = '\0';

		return	*this;
	}

	String& operator+=(const char& str)
	{
		String temp(this->ptr);

		delete[]this->ptr;
		this->ptr = nullptr;

		this->size = temp.size + 1;
		this->ptr = new char[this->size + 1];

		for (int i = 0; i <= this->size; i++)
			this->ptr[i] = temp.ptr[i];

		this->ptr[this->size - 1] = str;
		this->ptr[this->size] = '\0';

		return *this;
	}

	bool operator==(const String& copy) const
	{
		bool check = true;

		if (this->size == copy.size)
		{
			for (int i = 0; i < this->size; i++)
			{
				if (this->ptr[i] == copy.ptr[i])
					check = true;
				else
					check = false;

				if (check == 0)
					return false;
			}
		}
		else
			return false;

		if (check)
			return true;
	}

	bool operator==(const char* str) const
	{
		bool check = true;

		int strSize = 0;
		for (int i = 0; str[i] != '\0'; i++)
			strSize++;

		if (this->size == strSize)
		{
			for (int i = 0; i < this->size; i++)
			{
				if (this->ptr[i] == str[i])
					check = true;
				else
					check = false;

				if (check == 0)
					return false;
			}
		}
		else
			return false;

		if (check)
			return true;
	}

	bool operator!()
	{
		if (this->ptr[0] == '\0')
			return true;
		else
			return false;
	}

	int operator()(char c) const
	{
		for (int i = 0; i < this->size; i++)
		{
			if (this->ptr[i] == c)
				return i;
		}

		return -1;
	}

	int operator()(const String& substr) const
	{
		int i = 0, j = 0, c = 0, endIndex = 0;

		while (this->ptr[i] != '\0')
		{
			if (this->ptr[i] != substr.ptr[j])
				i++;
			else if (this->ptr[i] == substr.ptr[j])
			{
				while (substr.ptr[j] != '\0')
				{
					if (this->ptr[i] == substr.ptr[j])
					{
						endIndex = i;
						i++;
						j++;
						c++;
					}
					else
					{
						c = 0;
						break;
					}
				}
			}
		}

		int startIndex = endIndex - (substr.size - 1);

		if (c != 0)
			return startIndex;
		else
			return -1;

	}

	int operator()(const char* str) const
	{
		int strSize = 0;
		for (int i = 0; str[i] != '\0'; i++)
			strSize++;

		int i = 0, j = 0, c = 0, endIndex = 0;

		while (this->ptr[i] != '\0')
		{
			if (this->ptr[i] != str[j])
				i++;
			else if (this->ptr[i] == str[j])
			{
				while (str[j] != '\0')
				{
					if (this->ptr[i] == str[j])
					{
						endIndex = i;
						i++;
						j++;
						c++;
					}
					else
					{
						c = 0;
						break;
					}
				}
			}
		}

		int startIndex = endIndex - (strSize - 1);

		if (c != 0)
			return startIndex;
		else
			return -1;

	}

	operator int() const
	{
		int length = 0;
		for (int i = 0; this->ptr[i] != '\0'; i++)
			length++;

		return length;
	}

	~String()
	{
		delete[] ptr;
	}
};

ostream& operator<<(ostream& output, const String& str)
{
	output << str.getData();
	return output;
}

istream& operator>>(istream& input, String& str)
{
	char temp[1000];
	input >> temp;
	str = temp;
	return input;
}
