// Mahad Malik
// 23I - 0537
// BSCS - C
// Assignment 2


#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <fstream>
#include "../Assignment 2/String.h"
#include "../Assignment 2/Vector.h"

using namespace std;

void gotoxy(int x, int y);
void setConsoleColor(int color);

class WordGenerator
{
private:
	Vector<String> words;
public:
	WordGenerator() {}

	void generateWords(filesystem::path filepath)
	{
		ifstream file(filepath);

		if (!file)
		{
			cout << "File not found" << endl;
			return;
		}

		String word;

		while (!file.eof())
		{
			file >> word;
			words.push_back(word);
		}
	}

	Vector<String> getWords()
	{
		return words;
	}
};

struct SLLNode
{
	char data;
	SLLNode* next;

	SLLNode(char data)
	{
		this->data = data;
		this->next = nullptr;
	}

	SLLNode()
	{
		this->data = NULL;
		this->next = nullptr;
	}
};

class SinglyLinkedList
{
	SLLNode* head;
public:
	SinglyLinkedList()
	{
		this->head = nullptr;
	}

	void insert(char c)
	{
		SLLNode* newNode = new SLLNode(c);

		if (!head)
		{
			head = newNode;
			return;
		}

		SLLNode* temp = head;

		while (temp->next)
			temp = temp->next;

		temp->next = newNode;

		return;

	}
};

struct Node
{
	char data;
	Node* next;
	Node* prev;
	Node* up;
	Node* down;

	Node() : data(NULL), next(nullptr), prev(nullptr), up(nullptr), down(nullptr) {}

	char getData()
	{
		return data;
	}
};

template <typename T>
struct SNode 
{
	T data;
	SNode<T>* next;

	SNode(T value) : data(value), next(nullptr) {}
};

template <typename T>
struct N_ARY_NODE
{
	T data;
	N_ARY_NODE<T>* children[26];

	N_ARY_NODE(T value) : data(value)
	{
		for (int i = 0; i < 26; i++)
			children[i] = nullptr;
	}
};

class Menu				// Menu Class
{
private:
	char choice;
	filesystem::path filePath;
	fstream file;
public:
	Menu() :choice(NULL) {}

	void displayMenu()
	{
		cout << "\t\t\t\t\t\tWelcome to MAHAD'S Notepad\n\n\n" << endl;
		cout << "Please select one of the following options: \n\n";
		cout << "1. Create a Text File" << endl;
		cout << "2. Load a Text File" << endl;
		cout << "3. Exit" << endl;
		cout << "\nEnter your choice: ";
		cin >> choice;

		while (choice < '1' || choice > '3')
		{
			cout << "\nInvalid choice. Please enter a valid choice : \n";
			cin >> choice;
		}
	}

	int getChoice()
	{
		return choice;
	}

	void doAccordingly()
	{
		switch (choice)
		{
		case '1':
			system("cls");
			cout << "Creating a Text File : " << endl << "Enter name of file with .txt extension : ";
			cin >> filePath;
			break;
		case '2':
			system("cls");
			cout << "Loading a Text File" << endl;
			break;
		case '3':
			system("cls");
			cout << "Exiting the Program" << endl;
			break;
		}
	}

	void saveFile(Node* head)
	{
		file.open(filePath, ios::out);

		Node* tempRow = head;

		while (tempRow != nullptr)
		{
			Node* tempCol = tempRow;

			while (tempCol != nullptr)
			{
				file << tempCol->data;
				tempCol = tempCol->next;
			}

			tempRow = tempRow->down;
		}
	}
};

class TextEditor
{
private:
	int rows;
	int columns;
	HANDLE hWindow;
	CONSOLE_SCREEN_BUFFER_INFO WinInfo;
public:

	TextEditor()
	{
		hWindow = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hWindow, &WinInfo);
		columns = WinInfo.srWindow.Right - WinInfo.srWindow.Left + 1;
		rows = WinInfo.srWindow.Bottom - WinInfo.srWindow.Top + 1;
		columns = (columns * 50) / 100;
		rows = (rows * 50) / 100;
	}

	void displayTextArea()
	{
		setConsoleColor(7);

		gotoxy(0, 0);

		for (int i = 0; i < columns+2; i++)
		{
			gotoxy(i, 0);
			cout << "_";
		}

		for (int i = 0; i < rows; i++)
		{
			gotoxy(0, i+1);
			cout << "|";
			gotoxy(columns + 1, i+1);
			cout << "|";
		}

		for (int i = 0; i < columns + 2; i++)
		{
			gotoxy(i, rows + 1);
			cout << "-";
		}

		gotoxy(0, 0);
		cout << " ";

		gotoxy(columns + 1, 0);
		cout << " ";

		gotoxy(0, rows + 1);
		cout << " ";

		gotoxy(columns + 1, rows + 1);
		cout << " ";

		gotoxy(columns + 3, 1);
		cout << "Search : ";

		gotoxy(1, rows + 2);
		cout << "Word Suggestions : ";
	}

	int getRows()
	{
		return rows;
	}

	int getColumns()
	{
		return columns;
	}
};

template <typename T>
class Stack 
{
private:
	SNode<T>* top;

public:
	Stack() : top(nullptr) {}

	~Stack() 
	{
		while (!isEmpty()) 
			pop();
	}

	void push(T value) 
	{
		SNode<T>* newNode = new SNode<T>(value);
		newNode->next = top;
		top = newNode;
	}

	T pop() 
	{
		if (isEmpty()) 
			return NULL;

		SNode<T>* temp = top;
		top = top->next;
		T value = temp->data;
		delete temp;
		return value;
	}

	T peek()
	{
		if (isEmpty())
			return NULL;

		return top->data;
	}

	bool isEmpty()
	{
		return top == nullptr;
	}
};

class TwoDLinkedList
{
private:
	Node* head;
	Node* current;
	int numRows;
	int numCols;
	int *numNodesinEachRow;
	Stack<char> undoRedoStack;
	int spaceCount;
public:

	Node* getHead()
	{
		return head;
	}

	TwoDLinkedList(int r, int c)
	{
		head = nullptr;
		current = nullptr;
		numCols = c;
		numRows = r;
		numNodesinEachRow = new int[numRows];
		spaceCount = 0;

		for (int i = 0; i < numRows; i++)
			numNodesinEachRow[i] = 0;
	}

	void moveCurrentToLastRow()
	{
		connectUpDown();

		current = head;

		if (!current)
			return;

		while (current->down != nullptr)
			current = current->down;
	}

	void moveCurrentToLastColumn()
	{
		connectUpDown();

		if (!current)
			return;

		while (current->next != nullptr)
			current = current->next;
	}

	void insertAtEnd(char data)
	{
		Node* newNode = new Node;
		newNode->data = data;
		newNode->next = nullptr;
		newNode->prev = nullptr;
		newNode->up = nullptr;
		newNode->down = nullptr;

		if (head == nullptr)
		{
			head = newNode;
			current = head;
		}
		else
		{
			moveCurrentToLastRow();
			moveCurrentToLastColumn();
			current->next = newNode;
			newNode->prev = current;
			current = newNode;
		}

		connectUpDown();
	}


	void printList()
	{
		int x = 1, y = 1;
		Node* tempRow = head;  

		while (tempRow != nullptr) 
		{
			Node* tempCol = tempRow;

			while (tempCol != nullptr )
			{
				gotoxy(x, y);

				setConsoleColor(5);

				if (tempCol->data == '\n')
					cout << "!";
				else
					cout << tempCol->data;

				x++;

				tempCol = tempCol->next;
			}

			x = 1;
			y++;
			tempRow = tempRow->down;
		}
	}

	void insertAt(int x, int y, char data)
	{

		if (x < 1 || y < 1 ) 
			return;

		Node* newNode = new Node;
		newNode->data = data;
		newNode->next = nullptr;
		newNode->prev = nullptr;
		newNode->up = nullptr;
		newNode->down = nullptr;

		Node* temp = head;

		if (x == 1)
		{
			if (y == 1)
			{
				if (head == nullptr)
					head = newNode;
				else
				{
					newNode->next = head;
					head->prev = newNode;

					newNode->down = head->down;

					if (head->down)
						head->down->up = newNode;

					head = newNode;
				}

				if (numNodesinEachRow[y - 1] < numCols)
					numNodesinEachRow[y - 1]++;

				return;
			}

			for (int i = 1; i < (y - 1); i++)
			{
				if (temp->down)
					temp = temp->down;
			}

			if (!temp->down)
			{
				temp->down = newNode;
				newNode->up = temp;
			}
			else if (temp->down->data=='\n')
			{
				temp->down->data = data;
			}
			else
			{
				newNode->next = temp->down;

				if (temp->down->down)
					temp->down->down->up = newNode;

				temp->down->prev = newNode;
				temp->down = newNode;
				newNode->up = temp;
			}

			if (numNodesinEachRow[y - 1] < numCols)
				numNodesinEachRow[y - 1]++;


			return;
		}

		for (int i = 1; i < y && temp != nullptr; i++)
			temp = temp->down;

		for (int i = 1; i < (x - 1) && temp != nullptr; i++)
			temp = temp->next;

		if (temp && temp->next != nullptr)
		{
			newNode->next = temp->next;
			newNode->prev = temp;
			temp->next->prev = newNode;
			temp->next = newNode;
		}
		else if(temp && ! temp->next)
		{
			temp->next = newNode;
			newNode->prev = temp;
		}

		if (numNodesinEachRow[y - 1] < numCols)
			numNodesinEachRow[y - 1]++;

	}

	int countNodes(Node* temp)
	{
		int i = 0;
		while (temp != nullptr)
		{
			i++;
			temp = temp->next;
		}
		return i;
	}
	
	void shiftLastNodetoNextLine(Node* temp) 
	{
		Node* tempHead = head;		 // tempHead is the head of the 2D list
		Node* lastNode = temp;		 // lastNode is the last node of the row but cuurently it is the node to be traversed
		Node* prevNode = nullptr;		// prevNode is the node before the last node
		int row = 1;					// To track the current row

		while (tempHead && tempHead != temp) 
		{
			row++;
			tempHead = tempHead->down;
		}

		while (lastNode && lastNode->next != nullptr) 
		{
			prevNode = lastNode;
			lastNode = lastNode->next;
		}

		if (!lastNode || lastNode == temp)
			return;

		insertAt(1, row + 1, lastNode->data);

		if (prevNode)
			prevNode->next = nullptr;

		delete lastNode;
	}

	void moveExtraNodeToNextLine()
	{
		Node* temp = head;

		while (temp) 
		{
			int NumNodes = countNodes(temp);  

			while (NumNodes > numCols) 
			{
				shiftLastNodetoNextLine(temp);  
				NumNodes--;  
			}

			temp = temp->down;  
		}

		connectUpDown();
	}


	bool movecurrentTo(int x, int y)
	{
		if (x > numCols || y > numRows)
			return false;

		Node* temp = head;

		for (int i = 1; i < y; i++)
			temp = temp->down;

		for (int i = 1; i < x; i++)
			temp = temp->next;

		current = temp;
		return true;
	}

	void connectUpDown()
	{
		Node* topRow = head;  

		while (topRow != nullptr && topRow->down != nullptr)
		{
			Node* upperNode = topRow;
			Node* lowerNode = topRow->down;

			while (upperNode != nullptr && lowerNode != nullptr)
			{
				upperNode->down = lowerNode;
				lowerNode->up = upperNode;

				upperNode = upperNode->next;
				lowerNode = lowerNode->next;
			}

			topRow = topRow->down;
		}
	}

	int moveWordsToNextLine(int x)
	{
		Node* temp = head;			// node to end of upper row
		Node* tempHead = head;		 // node to start of upper row
		Node* temp2 = head ? head->down : nullptr;	 // node to start of lower row
		bool spaceFlag = false;		 // flag to check if space is found
		int shiftLimit = 0;

		int i = 0;

		while(temp && temp2)
		{
			tempHead = temp;

			while (temp->next)
			{
				temp = temp->next;

				if (temp->data == ' ')
					spaceFlag = true;
			}

			if (temp->data != ' ' && temp2->data != ' ' && spaceFlag && numNodesinEachRow[i] == numCols)
			{
				shiftLimit = 0;

				while (temp && temp->data != ' ' && shiftLimit < numCols)
				{
					temp = temp->prev;
					shiftLastNodetoNextLine(tempHead);
					shiftLimit++;
				}
			}

			temp = temp2;
			temp2 = temp2->down;
			i++;
			spaceFlag = false;
		}

		connectUpDown();
		
		if (x == 2)
			return shiftLimit;

		return 0;
	}

	void moveNodestoNextLineForEnter()
	{
		Node* temp = head;			  // node to end of upper row
		Node* tempHead = head;		 // node to start of upper row
		bool enterFlag = false;		// flag to check if enter is found


		while (temp)
		{
			while (temp->next)
			{
				if (temp->data == '\n')
					enterFlag = true;

				temp = temp->next;
			}

			if (temp->data != '\n' && enterFlag)
			{
				while (temp && temp->data != '\n')
				{
					temp = temp->prev;
					shiftLastNodetoNextLine(tempHead);
				}

				if(temp->prev)
				{
					temp = temp->prev;
					delete temp->next;
					temp->next = nullptr;
				}
			}

			tempHead = tempHead->down;
			temp = tempHead;
			enterFlag = false;
		}

		connectUpDown();
	}

	int doEverything(int x)
	{
		connectUpDown();
		moveExtraNodeToNextLine();
		connectUpDown();
		int y = moveWordsToNextLine(x);
		connectUpDown();
		moveExtraNodeToNextLine();
		connectUpDown();
		return y;
	}

	void deleteNode(int x, int y) 
	{
		if (x < 1)
			return;

		Node* temp = head;

		for (int i = 1; i < y && temp != nullptr && temp->down; i++)
			temp = temp->down;

		if (x == 2)
		{
			if (y == 1)
			{
				if(head->next)
					head = head->next;
				else if (head->down)
				{
					Node* temp = head;
					head = head->down;
					delete temp;
					temp = nullptr;
					return;
				}
				else
				{
					delete head;
					head = nullptr;
					return;
				}

				if(head->prev->down)
					head->down = head->prev->down;

				delete head->prev;
				head->prev = nullptr;

				connectUpDown();
				return;
			}

			if (temp && temp->next)
			{
				if(temp->up)
					temp->up->down = temp->next;

				temp->next->up = temp->up;

				if(temp->down)
					temp->down->up = temp->next;

				temp->next->down = temp->down;

				delete temp;
				temp = nullptr;
				connectUpDown();
				return;
			}
			else if(temp)
			{
				if (temp->up && !temp->down)
					temp->up->down = nullptr;

				if (temp->down && temp->up)
				{
					temp->down->up = temp->up;
					temp->up->down = temp->down;
				}

				delete temp;
				temp = nullptr;
			}

			connectUpDown();
			return ;
		}

		for (int i = 1; i < x - 2 && temp != nullptr; i++)
			temp = temp->next;

		if (temp)
		{
			if (temp->next)
			{
				if (!temp->next->next)
				{
					delete temp->next;
					temp->next = nullptr;
					connectUpDown();
					return;
				}
				else
				{
					Node* temp2 = temp->next;
					temp->next = temp2->next;
					temp2->next->prev = temp;
					delete temp2;
					connectUpDown();
					return;
				}
			}
		}
	}

	int countNodes(int y)
	{
		Node* temp = head;

		for (int i = 1; i < y ; i++)
			temp = temp->down;

		return countNodes(temp);
	}

	int moveCursorY(int y)
	{
		connectUpDown();
		int yTemp = 1;

		current = head;

		for (int i = 1; i < y; i++)
		{
			if (current->down)
			{
				current = current->down;
				yTemp++;
			}
		}

		return yTemp;
	}

	int moveCursorX(int x, int y)
	{
		connectUpDown();

		int xTemp = 1;


		for (int i = 1; i < x; i++)
		{
			if (current->next)
			{
				current = current->next;
				xTemp++;
			}
		}

		if (!current->next)
			return ++xTemp;

		return xTemp;
	}

	void removeLatestNode()
	{
		connectUpDown();
		moveCurrentToLastRow();
		moveCurrentToLastColumn();
		
		if (current->prev)
		{
			current = current->prev;
			delete current->next;
			current->next = nullptr;
			connectUpDown();
			return;
		}
		else
		{
			if (current->up)
			{
				current->up->down = nullptr;
				delete current;
				current = nullptr;
				connectUpDown();
				return;
			}
			else
			{
				delete current;
				current = nullptr;
				head = nullptr;
				connectUpDown();
				return;
			}
		}
	}

	int AddtoStack()
	{
		if (spaceCount == 4)
			return 0;

		int tempX = 0;

		moveCurrentToLastRow();
		moveCurrentToLastColumn();


		while (current && current->data!=' ')
		{
			undoRedoStack.push(current->data);
			removeLatestNode();
			tempX++;
			moveCurrentToLastRow();
			moveCurrentToLastColumn();
		}

		moveCurrentToLastRow();
		moveCurrentToLastColumn();

		if (current && current->data == ' ')
		{
			undoRedoStack.push(current->data);
			tempX++;
			removeLatestNode();
		}


		if (!undoRedoStack.isEmpty() && undoRedoStack.peek() == ' ')
			spaceCount++;

		return tempX;
	}

	int removeFromStack()
	{
		int tempX = 0;

		if (spaceCount == 0 && undoRedoStack.isEmpty())
			return 0;

		if (undoRedoStack.peek() == ' ')
		{
			insertAtEnd(undoRedoStack.pop());
			tempX++;
		}

		while (!undoRedoStack.isEmpty() && undoRedoStack.peek() != ' ')
		{
			insertAtEnd(undoRedoStack.pop());
			tempX++;
			moveCurrentToLastRow();
			moveCurrentToLastColumn();
		}

		if (!undoRedoStack.isEmpty() && undoRedoStack.peek() == ' ')
			spaceCount--;

		return tempX;
	}

}; 

									// end of TwoDLinkedList class

class N_AryTree
{
private:
	N_ARY_NODE<char>* root;
public:
	N_AryTree()
	{
		root = new N_ARY_NODE<char>(NULL);
	}

	void makeTree(Vector<String> words)
	{
		int numWords = words.getSize();

		for (int i = 0; i < numWords; i++)
		{
			N_ARY_NODE<char>* temp = root;

			for (int j = 0; words[i][j] != '\0'; j++)
			{
				if (words[i][j] >= 'A' && words[i][j] <= 'Z')
					words[i][j] += 32;

				int index = words[i][j] - 'a';

				if (!temp->children[index])
					temp->children[index] = new N_ARY_NODE<char>(words[i][j]);

				temp = temp->children[index];
			}
		}
	}

};

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int main(int argc, char* argv[]) 
{
	TextEditor textEditor;
	Menu menu;
	TwoDLinkedList ListNode(textEditor.getRows(), textEditor.getColumns());
	SinglyLinkedList SLL;
	//menu.displayMenu();
	//menu.doAccordingly();

	system("cls");
	HANDLE  rhnd = GetStdHandle(STD_INPUT_HANDLE);  // handle to read console

	DWORD Events = 0;            // Event count
	DWORD EventsRead = 0;       // Events read from console

	bool Running = 1;
	bool Searching = 0;

	int x = 0, y = 0;

	gotoxy(x, y);

	textEditor.displayTextArea();

	x = 1, y = 1;

	gotoxy(x, y);

	while (Running) 
	{
		
		GetNumberOfConsoleInputEvents(rhnd, &Events);

		if (Events != 0) 
		{ 
			INPUT_RECORD eventBuffer[200];

			ReadConsoleInput(rhnd, eventBuffer, Events, &EventsRead);

			for (DWORD i = 0; i < EventsRead; ++i) 
			{
				if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown) 
				{
					switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode)
					{
					case VK_UP: 

						if (y - 1 != 0)
							y--;

						y = ListNode.moveCursorY(y);
						x = ListNode.moveCursorX(x,y);
						gotoxy(x, y);

						break;
					case VK_DOWN: 

						if (y + 1 < (textEditor.getRows() + 1))
							y++;

						y = ListNode.moveCursorY(y);
						x = ListNode.moveCursorX(x,y);
						gotoxy(x, y);

						break;
					case VK_RIGHT: 

						if (x + 1 < (textEditor.getColumns() + 2))
							x++;

						y = ListNode.moveCursorY(y);
						x = ListNode.moveCursorX(x,y);
						gotoxy(x, y);

						break;
					case VK_LEFT: 

						if (x - 1 != 0)
							x--;

						y = ListNode.moveCursorY(y);
						x = ListNode.moveCursorX(x, y);
						gotoxy(x, y);

						break;
					case VK_BACK:

						if (x != 1)
						{
							ListNode.deleteNode(x, y);
							x--;
							gotoxy(x, y);
						}
						else if (y != 1)
						{
							x = ListNode.countNodes(y-1);
							y--;
							gotoxy(x, y);
						}
						break;
					case VK_RETURN: 

						if (y + 1 < (textEditor.getRows() + 1))
						{
							ListNode.insertAt(x, y, '\n');
							ListNode.moveNodestoNextLineForEnter();
							x = 1;
							y++;
							x += ListNode.doEverything(x);
							gotoxy(x, y);
						}
						break;
					case 0x31:  // 1 on keyborad for undo

						x -= ListNode.AddtoStack();
						if (x < 1)
						{
							x = ListNode.countNodes(y - 1);
							y--;
							gotoxy(x, y);
						}
						gotoxy(x, y);
						break;

					case 0x32:  // 2 on keyboard for redo

						x += ListNode.removeFromStack();
						if (x > (textEditor.getColumns() + 2))
						{
							x = x - textEditor.getColumns();
							y++;
							gotoxy(x, y);
						}
						break;

					case VK_ESCAPE:

						menu.saveFile(ListNode.getHead());
						break;

					default:
						char inputChar = eventBuffer[i].Event.KeyEvent.uChar.AsciiChar;

						if ((inputChar >= 'A' && inputChar <= 'Z') || (inputChar >= 'a' && inputChar <= 'z') || inputChar == ' ')
						{
							if (Searching)
							{
								SLL.insert(inputChar);
							}
							else if (x != textEditor.getColumns() + 1)
								ListNode.insertAt(x, y, inputChar);
							else if (y + 1 <= textEditor.getRows())
							{
								x = 1;
								y++;
								ListNode.insertAt(x, y, inputChar);
								gotoxy(x, y);
							}
							else
								cout << "\a";
						}
						else
							break;

						if (x + 1 < (textEditor.getColumns() + 2))
							x++;

						system("cls");

						ListNode.moveExtraNodeToNextLine();
						x+= ListNode.moveWordsToNextLine(x);
						ListNode.moveExtraNodeToNextLine();
						textEditor.displayTextArea();
						ListNode.printList();

						gotoxy(x, y);
						break;
					}

					system("cls");
					textEditor.displayTextArea();
					ListNode.printList();
					x += ListNode.doEverything(x);
					gotoxy(x, y);
				}
			}				  
		}
	}					

	return 0;
}

void setConsoleColor(int color) 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}