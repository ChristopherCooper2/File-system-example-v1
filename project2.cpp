#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <utility>
#include <array>
#include <map>

using namespace std;

/* shared data begin */
//int maxArray = 16;
const int size = 5;
string filetext;
string filename;
string newusername;
string username;
string permission;
string dline;
string eline;
string permissionError = "You don't have permission to perform this action";
/* shared data end */

int main()
{
	struct File
	{
		string fileName;
		string fileText;
		string canEdit[size];
		string canDelete[size];
	};
	map<string, File> fileMap;

	toplabel:
	cin.ignore();
	cout << "Please enter your User name: " << endl;
	getline(cin, newusername);

	/* set up management menu and gather user input */
	label1:
		cout << "What operation would you like to perform?" << endl;
		cout << "1. Create file" << endl;
		cout << "2. Read file" << endl;
		cout << "3. Delete file" << endl;
		cout << "4. Edit file" << endl;
		cout << "5. Change permissions" << endl;
		cout << "6. Change user" << endl;

		int decision = cin.get();

		// infer decision
		if (decision == 49)
		{
			cin.ignore();
			cout << "Please enter the name of your file: " << endl;
			getline(cin, filename);
			fileMap[filename].fileName = filename;

			cout << "Please enter the text of your file: " << endl;
			getline(cin, filetext);
			fileMap[filename].fileText = filetext;

			std::fill(fileMap[filename].canEdit, fileMap[filename].canEdit + 5, "0");
			std::fill(fileMap[filename].canDelete, fileMap[filename].canDelete + 5, "0");

			fileMap[filename].canEdit[0] = newusername;
			fileMap[filename].canDelete[0] = newusername;
			cout << "File created" << endl;

			goto label1;
		}
		else if (decision == 50)
		{
			cin.ignore();
			cout << "Please enter the name of the file you wish to read: " << endl;
			getline(cin, filename);
			cout << fileMap[filename].fileText << endl;

			goto label1;
		}
		else if (decision == 51)
		{
			deletelabel:
			cin.ignore();
			cout << "Please enter the name of the file you wish to delete: (EXIT to exit) " << endl;
			getline(cin, filename);

			if (filename == "EXIT")
			{
			goto label1;
			}

			for (int i = 0; i < size; i++)
			{
				if (fileMap[filename].canDelete[i] == newusername)
				{
					fileMap.erase(filename);
					cout << "File deleted" << endl;
					goto label1;
				}
			}
			cout << permissionError << endl;
			goto deletelabel;
			}
		else if (decision == 52)
		{
			editlabel:
			cin.ignore();
			cout << "Please enter the name of the file you wish to edit: (You may have to press enter twice) (EXIT to exit)" << endl;
			getline(cin, filename);

			if (filename == "EXIT")
			{
			goto label1;
			}

			cin.ignore();
			cout << "Please enter the text you'd like to replace with: " << endl;
			getline(cin, filetext);

			for (int i = 0; i < size; i++)
			{
				if (fileMap[filename].canEdit[i] == newusername)
				{
				fileMap[filename].fileText = filetext;
				cout << "File edited" << endl;
				goto label1;
				}
			}
			cout << permissionError << endl;
			goto editlabel;
		}
		else if (decision == 53)
		{
			cin.ignore();
			cout << "Please enter the name of the file you'd like to change permissions for: " << endl;
			getline(cin, filename);

			repeat:
			cin.ignore();
			cout << "Would you like to change deletion permissions (D), editing permissions (E), or exit (EXIT)?" << endl;
			getline(cin, permission);
			if (permission == "D")
			{
				cin.ignore();
				cout << "Would you like to add or remove deletion permissions? (A or R)" << endl;
				getline(cin, dline);
				if (dline == "A")
				{
					cin.ignore();
					cout << "Enter the name of the user you'd like to add deletion permissions for: " << endl;
					getline(cin, username);
					for (int i = 0; i < size; i++)
					{
						if (fileMap[filename].canDelete[i] == "0")
						{
							fileMap[filename].canDelete[i] = username;
							cout << "Named added" << endl;
							goto label1;
						}
					}
					cout << "Permission array is full, pleae remove someone before adding someone new" << endl;
					goto repeat;
				}
				if (dline == "R");
				{
					cin.ignore();
					cout << "Enter the name of the user you'd like to remove deletion permission for: " << endl;
					getline(cin, username);
					for (int i = 0; i < size; i++)
					{
						if (fileMap[filename].canDelete[i] == username)
						{
							fileMap[filename].canDelete[i] = "0";
							cout << "Name removed" << endl;
							goto label1;
						}
					}
				}
			}
			if (permission == "E")
			{
				cin.ignore();
				cout << "Would you like to add or remove editing permissions? (A or R)" << endl;
				getline(cin, eline);
				if (eline == "A")
				{
					cin.ignore();
					cout << "Enter the name of the user you'd like to add editing permissions for: " <<endl;
					getline(cin, username);
					for (int i = 0; i < size; i++)
					{
						if (fileMap[filename].canEdit[i] == "0")
						{
							fileMap[filename].canEdit[i] = username;
							cout << "Name added" << endl;
							goto label1;
						}
					}
					cout << "Permission array is full, please remove someone before adding someone new" << endl;
					goto repeat;
				}
				if (eline == "R");
				{
					cin.ignore();
					cout << "Enter the name of the user you'd like to remove editing permissions for: " << endl;
					getline(cin, username);
					for (int i = 0; i < size; i++)
					{
						if (fileMap[filename].canEdit[i] == username)
						{
							fileMap[filename].canEdit[i] == "0";
							cout << "Name removed" << endl;
							goto label1;
						}

					}
				}
			}
			if (permission == "EXIT")
			{
				goto label1;
			}
			else
			{
				goto repeat;
			}
		}
		else if (decision == 54)
		{
			goto toplabel;
		}
		else
		{
			cout << "Invalid input. Please try again." << endl;
			goto label1;
		}
		goto label1;
}
