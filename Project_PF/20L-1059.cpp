#include<iostream>
#include<fstream>
#include <ctime>
#include<iomanip>
#pragma warning(disable : 4996)//it says to add this to run ctime library
using namespace std;
char unique_terms[10000][300];//no. of coloumns has been increased to contain words which have greater length
char stop_words[500][20];
char doc_list[50][30];
int term_frequency_in_all_documents[11][100];
int r = 0;
int r1 = 0;
int c = 0;
int sub_id = 0; //this check picks the next complete string not the previous which was already picked
int id_check = 0;//this check prints NOT FOUND only when id is -1



int my_strcmp(char arr1[], char arr2[])// self made string comparison function
{
	int x = 0;
	while (arr1[x] != '\0' || arr2[x] != '\0')
	{
		if (arr1[x] == arr2[x])
		{
			x++;
			if (arr1[x] == '\0' && arr2[x] == '\0')
			{
				return 0;
			}
		}
		else if (arr1[x] < arr2[x])
			return -1;
		else if (arr1[x] > arr2[x])
			return 1;
	}
	return 2;
}

void read_stop_words()
{
	int x = 0;
	ifstream fin;
	fin.open("stoplist.txt");
	for (x = 0; x < 500 && fin.eof() == false; x++)//loop for storing stopwrods
	{
		fin >> stop_words[x];
	}
	
	fin.close();
}
void read_docs_list()
{
	int x = 0, y = 0;
	ifstream fin;
	fin.open("doclist.txt");

	for (x = 0; x < 50 && fin.eof() == false; x++)//loop to store all doc list in a array
	{
		fin >> doc_list[x];

	}
	fin.close();                // closing file

}
void write_docs_with_IDs()
{
	int x = 0, y = 0;
	ofstream fout;
	fout.open("docids.txt");
	while (doc_list[x][0] != '\0' && x < 50)
	{
		fout << x << "	" << doc_list[x] << endl;
		x++;
	}
	fout.close();                       // closing file

}
void convert_to_tokens(char docname[])
{



	char cont[300];//picks term from document
	char arr[300];// a filtered word is stored in this array
	char a = 0;
	int x = 0, y = 0;
	ifstream fin;
	fin.open(docname);
	
	while (fin.eof() == false)
	{
		int count = 0;
		x = 0;
		fin >> cont;
		while (cont[x] != '\0')
		{
			if (cont[x] >= 'A' && cont[x] <= 'Z')
			{
				y = cont[x];
				y += 32;
				a = y;
				arr[count] = a;
				count++;
			}

			else if (cont[x] >= 'a' && cont[x] <= 'z')
			{
				arr[count] = cont[x];
				count++;
			}
			x++;
		}
		arr[count] = '\0';//adding NULL at the last index
	
		ifstream fin1;
		fin1.open("stoplist.txt");
		char stpwrd[15];
		int res = -2;
		bool found = false;
		while (fin1.eof() == false && found == false)//to check wether this word exists in stopword or not
		{

			fin1 >> stpwrd;
			res = my_strcmp(stpwrd, arr);//stopwrd keeps changing and arr is fixed

			if (res == 0)
			{
				found = true;

			}


		}




		if (res == -1 || res == 1)//only allows to enter when res!=0
		{
			int	m = 0, n = 0;
			bool found1 = false;
			
			while (found1 == false && m < 10000)//this loop check wether the coming word is pre-existing or not 
			{
				while (unique_terms[m][n] == arr[n] && unique_terms[m][n] != '\0' && arr[n] != '\0')
				{
					n++;

				}
				if (unique_terms[m][n] == '\0' && arr[n] == '\0')
				{
					found1 = true;

				}
				else if (unique_terms[m][n] != arr[n] && m < 10000)
				{
					m++;
					n = 0;

				}
			}
			if (found1 == false)//if the word is not pre existing it is added in unique_terms
			{
				c = 0;
				for (r; r < 10000 && arr[c] != '\0'; )
				{
					
					for (c = 0; c < 300 && arr[c] != '\0'; c++)
					{
						unique_terms[r][c] = arr[c];

					}
			
					r++;
				}



			}

		}
	}
}
void sort_terms_alphabetically()//to sort the terms alphebatically
{
	int pass = 0, cmp = 0, c = 0;
	char temp = 0;
	for (pass = 0; pass < 10000-1&& unique_terms[pass][0]!='\0'; pass++)
	{
		for (cmp = pass+1; cmp < 10000; cmp++)
		{
			if (my_strcmp(unique_terms[pass], unique_terms[cmp]) > 0)
			{
				for (c = 0; c < 300; c++)
				{
					temp = unique_terms[pass][c];          //swapping
					unique_terms[pass][c] = unique_terms[cmp][c];
					unique_terms[cmp][c] = temp;
				}
			}
		}
	}

	

}
void write_term_IDs()// to write termids.txt
{
	ofstream fout;
	fout.open("termids.txt");
	int index = 0;
	for (int j = 0; j < 10000; j++)
	{
		if (unique_terms[j][0] != '\0')
		{

			fout << index << "	" << unique_terms[j] << endl;
			index++;
		}
	}

}
void read_unique_terms()
{
	int x = 0, y = 0, id = 0;
	ifstream fin;
	fin.open("termids.txt");
	for (x = 0; fin.eof() == false && x < 10000; x++)
	{
		fin >> id;
		fin >> unique_terms[x];
	}
}
void write_doc_index()
{
	char cont[300];
	char cont1[300];
	ifstream fin;
	ifstream fin1;
	fin1.open("termids.txt");
	ofstream fout;
	fout.open("doc_index.txt");
	int x = 0, y = 0, z = 0, j = 0, res = 0, pos = 0, id = 0, i = 0;
	int c = 0, l = 0;
	char chr = 0;
	char sample[300];
	while (fin1.eof() == false)
	{
		fin1 >> id;
		fin1 >> cont1;

		y = 0;
		while (y < 11)
		{


			fin.open(doc_list[y]);

			while (fin.eof() == false)
			{
				fin >> cont;
				while (cont[c] != '\0')
				{
					if (cont[c] >= 'A' && cont[c] <= 'Z')
					{
						l = cont[c];
						l += 32;
						chr = l;
						sample[i] = chr;
						i++;
					}

					else if (cont[c] >= 'a' && cont[c] <= 'z')
					{
						sample[i] = cont[c];
						i++;
					}


					c++;
				}
				sample[i] = '\0';
				
				i = 0;
				c = 0;
				pos++;
				res = my_strcmp(cont1, sample);
				
				if (res == 0)
				{
					if (j == 0)
					{
						fout << endl;
						fout << y << "	" << id;
						j++;
					}
					fout << "	" << pos;
				}

			}



			fin.close();
			y++;
			j = 0;
			pos = 0;
		}

	}

}


int get_term_ID(char term[])
{

	int x = 0, y = 0;
	int j = 0;
	char a = 0;

	while (term[x] != '\0')
	{
		if (term[x] >= 'A' && term[x] <= 'Z')
		{
			y = term[x];
			y += 32;
			a = y;
			term[x] = a;
		}
		x++;
	}
	x = 0;

	int m = 0, n = 0;
	char comp[300];
	ifstream fin;
	fin.open("termids.txt");
	while (fin.eof() == false)
	{
		fin >> m >> comp;
		int res = my_strcmp(term, comp);
		if (res == 0)
			return m;
	}

	return -1;
}

void find_term_in_document(int term_ID)
{
	int r1 = 0, c = 0;
	int doc = -2;
	int id = -2;
	int pos = -2;
	char peek = 0;
	int ignore = -2;
	int store=-1;
	ifstream fin;
	fin.open("doc_index.txt");
	if (id_check != -1)
	cout << "The word is found in the following Document ID(s)" << endl;
	while (fin.eof() == false)
	{

		fin >> doc;
		fin >> id;
		int check = 0;
		if (term_ID == id)
		{
			cout << setw(3) <<doc<< "   ";
			for (r1; r1 < 11 && fin.peek() == '\t'; )
			{

				for (int c = 0; c < 100 && fin.peek() == '\t';c++)
				{
					
					fin >> pos;
					term_frequency_in_all_documents[r1][c] = pos;


				}r1++;
			}

		}
		else
		{
			while (fin.peek() == '\t')
			{
				fin >> ignore;

			}
		}

	}

}

void print2DArray(int array[][100], int rows, int cols)
{
	cout << endl;
	if(id_check!=-1)
cout <<"The position(s) in each DOC-ID is shown in each horizontal line respectively." << endl;

	for (int row = 0; row < 11 && array[row][0] != '\0'; row++)
	{

		for (int col = 0; col < 100; col++)
		{
			

			if (array[row][col] != -1)
			{

				cout << setw(5) << array[row][col] << "	";
			}

		}
		cout << endl;
	}

}
void time_date(char word[])
{

	time_t now;
	struct tm nowLocal;
	now = time(NULL);//Getting time from OS
	nowLocal = *localtime(&now);
	ofstream fout;
	fout.open("history.txt", std::ios_base::app);
	fout << word;
	fout << "	" << nowLocal.tm_mday << " /" << nowLocal.tm_mon + 1 << " /" << nowLocal.tm_year + 1900;
	fout << "	" << nowLocal.tm_hour << ": " << nowLocal.tm_min << ": " << nowLocal.tm_sec;
	fout << endl;
	fout.close();
}
int get_Sub_Term_ID(char incomplete_word[])
{
	int x = 0, y = 0;
	while (unique_terms[x][0] != '\0')
	{
		while (incomplete_word[y] == unique_terms[x][y] && x > sub_id)
		{

			if (incomplete_word[y + 1] == '\0')
				return x;
			y++;
		}
		y = 0;
		x++;
	}

	return -1;
}
int get_Wrong_Word_ID(char wrong_word[])
{
	bool found = false;
	int x = 0, y = 0;
	int check = 0;
	while (unique_terms[x][0] != '\0')
	{
		check = 0;
		int i = 0;
		for (; check < 10 && wrong_word[i] != '\0' && unique_terms[x][i] != '\0'; i++)//this loop checks the distance
		{

			if (unique_terms[x][i] != wrong_word[i])
			{
				check++;
			}
		}
		if (check < 3 && unique_terms[x][i] == '\0' && wrong_word[i] == '\0')
		{
			cout << x << "	" << unique_terms[x] << endl;
			found = true;
		}
		x++;
	}
	if (found == true)
	{
		cout << "The above similar terms are found select the ID of term you want :" << endl;
		cin >> x;
		return x;
	}
	return -1;



}
int main()
{
	int choice = -1;
	int search = 1;
	cout << setw(50) << "            ***************HELLO USER**************" << endl;
	cout << "Do you want to skip part 1 ?" << endl;
	cout << "Press 1 for yes. " << endl << "Press 0 for NO." << endl;
	cin >> choice;
	//***************PART1************************
	if (choice == 1 || choice == 0)
	{
		if (choice != 1)
		{
			cout << "---->KINDLY WAIT A MOMENT........" << endl;
			read_stop_words();
			read_docs_list();
			write_docs_with_IDs();
			int x = 0;
			cout << setw(100) << "convert_to_tokens is going to call" << endl;
			while (doc_list[x][0] != '\0' && x < 50)
			{

				convert_to_tokens(doc_list[x]);

				x++;
			}
			cout << setw(100) << "convert_to_tokens has been called" << endl;
			cout << setw(100) << "sort_terms_alphabetically is going to call" << endl;
			sort_terms_alphabetically();
			cout << setw(100) << "sort_terms_alphabetically has been called" << endl;
			cout << setw(100) << "write_term_IDs is going to call" << endl;
			write_term_IDs();
			cout << setw(100) << "write_term_IDs has been called" << endl;
			cout << setw(100) << "write_doc_index is going to call" << endl;
			write_doc_index();
			cout << setw(100) << "write_doc_index has been called" << endl;
		}


		//***************PART2,3,4************************
		cout << setw(100) << "read_unique_terms is going to call" << endl;
		read_unique_terms();
		cout << setw(100) << "read_unique_terms has been called" << endl;
		while (search == 1)
		{
			int id = -2;
			char word[20];
			cout << "Enter a word you want to search : " << endl;
			cin >> word;
			cout << setw(100) << "time_date is going to call" << endl;
			time_date(word);
			cout << setw(100) << "time_date has been called" << endl;
			cout << setw(100) << "get_term_ID is going to call" << endl;
			get_term_ID(word);
			cout << setw(100) << "get_term_ID has been called" << endl;
			id = get_term_ID(word);
			for (int row = 0; row < 11; row++)
			{
				for (int col = 0; col < 100; col++)
				{
					term_frequency_in_all_documents[row][col] = -1;
				}
			}
			int x = 0, y = 0, res = -2, check = 0;;
			
			while (id == -1 && res != -1) // incomplete word serach
			{
				res = get_Sub_Term_ID(word);
				sub_id = res;
				if (res != -1)
				{
					cout << res << "	";
					cout << unique_terms[res] << endl;
					check++;
				}

			}
			if (check > 0)
			{
				cout << setw(100) << "get_Sub_Term_ID is going to call" << endl;
				int choice_id = -2;
				cout << "Which ID from above you want to search ? " << endl;
				cin >> choice_id;
				id = choice_id;
				cout << endl;
				cout << setw(100) << "get_Sub_Term_ID has been called" << endl;
			}
			
			int result = 0;
			
			if (id == -1)
			{
				cout << setw(100) << " get_Wrong_Word_ID is going to call" << endl;
				result = get_Wrong_Word_ID(word);
				id = result;
				id_check = id;//check to stop the output statements if word not found.
				if (result == -1)
				{

					cout << "No Word Found!!!!!!!!!!" << endl;

				}
				cout << setw(100) << "get_Wrong_Word_ID has been called" << endl;
			}
			

			cout << setw(100) << "find_term_in_document is going to call" << endl;
			find_term_in_document(id);
			cout << setw(100) << "find_term_in_document has been called" << endl;
			cout << setw(100) << "	print2DArray is going to call" << endl;
			print2DArray(term_frequency_in_all_documents, 11, 100);
			cout << setw(100) << "	print2DArray has been called" << endl;
			cout << endl << "Do you want to search more?" << endl << "---->Press 1 for YES." << endl << "---->Press 0 for NO." << endl;
			cin >> search;
		}
		ifstream history;
		history.open("history.txt");
		char hist[300];
		cout << "Your search history is : " << endl;
		while (history.eof() == false)
		{
			history.getline(hist, 300);
			cout << hist;
			cout << endl;

		}


		cout << "      *******************BYE BYE**********************" << endl;
	}
	else
		cout << "Sorry,but you have entered INVALID NO.!!!!!!" << endl;
	system("pause");
	return 0;
}
