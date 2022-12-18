#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

/* shared data begin */
string fileArray[256];
string contentArray[256];
int maxArray = 0;
/* shared data end */

string filename;
string filetext;

/* thread functions */
void *make_file(void *arg);
void *delete_file(void *arg);
void *read_file(void *arg);
void *edit_file(void *arg);

int main()
{
	/* set all instances to 0 */
	for (int x = 0; x < 256; x++)
	{
		fileArray[x] = "0";
		contentArray[x] = "0";
	}
	/* create threads */
	pthread_t make_thread, delete_thread, read_thread, edit_thread;
	/* set up management menu and gather user input */
	label1:
		cout << "What operation would you like to perform?" << endl;
		cout << "1. Create file" << endl;
		cout << "2. Read file" << endl;
		cout << "3. Delete file" << endl;
		cout << "4. Edit file" << endl;

		int decision = cin.get();

		// infer decision
		if (decision == 49)
		{
			cin.ignore();
			cout << "Please enter the name of your file: " << endl;
			getline(cin, filename);

			cout << "Enter the text of your file: ";
			getline(cin, filetext);

			pthread_create(&make_thread, NULL, make_file, (void*) NULL);
			pthread_join(make_thread, NULL);
		}
		else if (decision == 50)
		{
			cin.ignore();
			cout << "Please enter the name of the file you wish to read: " << endl;
			getline(cin, filename);

			pthread_create(&read_thread, NULL, read_file, (void*) NULL);
			pthread_join(read_thread, NULL);
			//goto label1;
		}
		else if (decision == 51)
		{
			cin.ignore();
			cout << "Please enter the name of the file you wish to delete: " << endl;
			getline(cin, filename);

			pthread_create(&delete_thread, NULL, delete_file, (void*) NULL);
			pthread_join(delete_thread, NULL);
			goto label1;
		}
		else if (decision == 52)
		{
			cin.ignore();
			cout << "Please enter the name of the file you wish to edit: (You will have to press enter twice) " << endl;
			getline(cin, filename);

			pthread_create(&edit_thread, NULL, edit_file, (void*) NULL );
			pthread_join(edit_thread, NULL);
			goto label1;
		}
		else
		{
			cout << "Invalid input. Please try again." << endl;
			goto label1;
		}
		goto label1;
}

/* get user input, set value in empty array location */
void *make_file(void *arg)
{
	for (int p = 0; p <= maxArray; p++)
	{
		if (fileArray[p] == "0")
		{
			fileArray[p] = filename;
			contentArray[p] = filetext;
			maxArray++;
			cout << "File saved." << endl;
			break;
		}
	}
	return 0;
}

/* get user input, search for matching file and overwrite with placeholder values */
void *delete_file(void *arg)
{
	for (int j = 0; j <= maxArray; j++)
	{
		if (fileArray[j] == filename)
		{
			fileArray[j] == "0";
			cout << "File deleted." << endl;
			break;
		}
		else
		{
			cout << "No such file exists, try again." << endl;
		}
	}
	return 0;
}

/* search for matching file, print text content if found  */
void *read_file(void *arg)
{
	for (int h = 0; h <= maxArray; h++)
	{
		if (fileArray[h] == filename)
		{
			cout << "Your content is: " <<  contentArray[h] << endl;
			break;
		}
		else
		{
			cout << "No such file exists, try again." << endl;
		}
	break;
	}
	return 0;
}

/* search for matching file, overwrite text array with user input */
void *edit_file(void *arg)
{
	for (int l = 0; l <= maxArray; l++)
	{
		if (fileArray[l] == filename)
		{
			cin.ignore();
			cout << "Please enter the text you would like to add to the file: " << endl;
			getline(cin, filetext);
			contentArray[l] = filetext;
			break;
		}
		else
		{
			cout << "No such file exists, try again." << endl;
		}
	}
	return 0;
}
