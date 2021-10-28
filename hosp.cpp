#include <stdio.h>
#include <cstring>
#include <fstream>
#include <conio.h>
#include <string.h>
#include <iostream>
using namespace std;

int no = 0;
char rec_ind[5], rec_gender[5], rec_app[5], rec_desc[55];
int rec_flag = 0;

struct record
{
	char age[5], ind[5];
	char name[30];
	char id[20];
	char gender[10];
	char app[10];
	char description[100];
} rec[20];

struct index
{
	char id[20], ind[20];
} in[20], temp;

void sort_index()
{
	int i, j;
	for (i = 0; i < no - 1; i++)
		for (j = 0; j < no - i - 1; j++)
			if (strcmp(in[j].id, in[j + 1].id) > 0)
			{
				temp = in[j];
				in[j] = in[j + 1];
				in[j + 1] = temp;
			}
}

void retrive_record(char *ind)
{
	int flag = 0, i = 0;
	fstream f9;
	f9.open("record.txt", ios::in);
	while (!f9.eof())
	{
		f9.getline(rec[i].ind, 5, '|');
		f9.getline(rec[i].id, 20, '|');
		f9.getline(rec[i].name, 30, '|');
		f9.getline(rec[i].age, 5, '|');
		f9.getline(rec[i].gender, 10, '|');
		f9.getline(rec[i].app, 10, '|');
		f9.getline(rec[i].description, 100, '\n');
		i++;
	}
	for (int j = 0; j < i; j++)
	{
		if (strcmp(rec[j].ind, ind) == 0)
		{
			strcpy(rec_ind, ind);
			rec_flag = 1;
			std::cout << "Patient record found\n";
			std::cout << "ID \t NAME\t AGE \t GENDER \t APPOINTMENT \t DESCRIPTION \n";
			std::cout << rec[j].id << "\t" << rec[j].name << "\t " << rec[j].age << "\t   " << rec[j].gender << "\t \t  " << rec[j].app << "\t \t  " << rec[j].description << "\n";
			return;
		}
	}
}

int search_index(char *id)
{
	int flag = 0;
	fstream ff;
	ff.open("index.txt", ios::in);
	int i = 0;
	while (!ff.eof())
	{
		ff.getline(in[i].id, 20, '|');
		ff.getline(in[i].ind, 20, '\n');
		i++;
	}
	for (int j = 0; j < i; j++)
	{
		if (strcmp(in[j].id, id) == 0)
		{
			retrive_record(in[j].ind);
			flag = 1;
		}
	}

	//cout <<"flag is"<< flag ;

	if (flag)
	{
		return 1;
	}
	else
		return -1;
}

int search_id(char *id, int j)
{
	int flag = 0;
	for (int i = 0; i < j; i++)
		if (strcmp(rec[i].id, id) == 0)
		{
			flag = 1;
			break;
		}
	if (flag)
		return 1;
	else
		return -1;
}

int search_app(char *app, int j)
{
	int flag = 0;
	for (int i = 0; i < j; i++)
		if (strcmp(rec[i].app, app) == 0)
		{
			flag = 1;
			break;
		}
	if (flag)
		return 1;
	else
		return -1;
}

void delet(char *st_id)
{
	int fr = 0;
	rec_flag = 1;
	if (!rec_flag)
	{
		std::cout << "deletion failed record not found\n";
		return;
	}

	for (int i = 0; i < no; i++)
	{
		if (strcmp(rec[i].ind, rec_ind) == 0)
		{
			fr = i;
			break;
		}
	}
	for (int i = fr; i < no - 1; i++)
	{
		rec[i] = rec[i + 1];
		char str[3];
		sprintf(str, "%d", i);
		strcpy(rec[i].ind, str);
	}
	no--;

	fstream f1, f2, f3;
	f1.open("record.txt", ios::out);
	f2.open("index.txt", ios::out);
	f3.open("no.txt", ios::out);
	f3 << no;
	f3.close();

	for (int i = 0; i < no; i++)
	{

		strcpy(in[i].id, rec[i].id);
		strcpy(in[i].ind, rec[i].ind);
	}
	sort_index();

	for (int i = 0; i < no; i++)
	{
		f1 << rec[i].ind << "|" << rec[i].id << "|" << rec[i].name << "|" << rec[i].age << "|" << rec[i].gender << "|" << rec[i].app << "|" << rec[i].description << "\n";
		f2 << in[i].id << "|" << in[i].ind << "\n";
	}

	f1.close();
	f2.close();
}

int owner_authen()
{
	char o_username[20], o_password[20];
	char o_user[20] = "admin", o_pass[20] = "***";
	cout << endl
		 << endl;
	cout.width(25);
	cout << "Enter Doctors User id and Password\n"
		 << "------------------------------------------------------------------------------------\n";
	cout << endl
		 << "username: ";
	cin >> o_username;
	cout << "password: ";
	cin >> o_password;
	cout << "------------------------------------------------------------------------------------\n";
	if (strcmp(o_username, o_user) == 0 && strcmp(o_password, o_pass) == 0)
		return 1;
	else
		return 0;
}

void ret_gender(char *gender)
{

	int flag = 0;
	for (int i = 0; i < no; i++)
	{
		if (strcmp(rec[i].gender, gender) == 0)
		{
			flag = 1;
		}
	}
	if (flag == 1)
	{
		std::cout << "* patient record found *\n";
		std::cout << "ID \t NAME\t AGE \t GENDER \t APPOINTMENT \t DESCRIPTION \n";
		for (int i = 0; i < no; i++)
		{
			if (strcmp(rec[i].gender, gender) == 0)
			{
				strcpy(rec_gender, gender);
				rec_flag = 1;
				std::cout << rec[i].id << "\t" << rec[i].name << "\t " << rec[i].age << "\t   " << rec[i].gender << "\t \t  " << rec[i].app << "\t \t  " << rec[i].description << "\n";
			}
		}
	}
	else
		std::cout << "* patient record not found *\n";
}

void ret_app(char *app)
{

	int flag = 0;
	for (int i = 0; i < no; i++)
	{
		if (strcmp(rec[i].app, app) == 0)
		{
			flag = 1;
		}
	}
	if (flag == 1)
	{
		std::cout << "* patient record found *\n";
		std::cout << "ID \t NAME\t AGE \t GENDER \t APPOINTMENT \t DESCRIPTION \n";
		for (int i = 0; i < no; i++)
		{
			if (strcmp(rec[i].app, app) == 0)
			{
				strcpy(rec_app, app);
				rec_flag = 1;
				std::cout << rec[i].id << "\t" << rec[i].name << "\t " << rec[i].age << "\t   " << rec[i].gender << "\t \t  " << rec[i].app << "\t \t  " << rec[i].description << "\n";
			}
		}
	}
	else
		std::cout << "* patient record not found *\n";
}

int main()
{
	fstream file1, file2, file4;

	cout << "---------------------------------------------------------------------------------------------------------------------";
	std::cout << "\n\t\t\t \t     *    HOSPITAL MANAGEMENT SYSTEM    * \n";
	cout << "---------------------------------------------------------------------------------------------------------------------";

	int ch;
	char ind[5], st_id[20], name[20], age[5], gender[10], app[10], description[30], id[10];
	char ind1[5], st_id1[20], name1[30], age1[5], gender1[10], app1[10], description1[30], id1[20];
	int i = 0, user;
label:

	cout << "\n enter user : 1.Doctor \t    2.Patient \n";
	std::cin >> user;
	switch (user)
	{
	case 1:
	{
		int check;
		check = owner_authen();
		if (check == 1)
		{
			cout << "Welcome Doctor\n"
				 << "------------------------------------------------------------------------------------\n";
			while (1)
			{
				std::cout << " \n \t 1.Add \n \t 2.Search \n \t 3.Delete \n \t 4.Display  \n \t 5.Update \n \t 6.Appointment based search \n \t 7.Gender based search \n  \t 8.exit \n";
				std::cout << " \n\n \t Enter your choice :";
				cin >> ch;
				switch (ch)
				{
					//add
				case 1:
				{

					file1.open("record.txt", ios::app | ios::out);

					int n;
					cout << "\n Enter no of patients \t";
					cin >> n;
					cout << " Enter their details \n ";
					file4.open("no.txt", ios::in);
					file4 >> no;
					for (i = no; i < no + n; i++)
					{
						cout << "\n Enter " << i + 1 << " patient \n";

						cout << " \n enter patient's id \t";
						cin >> id1;
						std::cout << "\n Name: \t";
						cin >> name1;
						std::cout << "\n Gender[m/f]: \t";
						cin >> gender1;
						std::cout << "\n Age: \t";
						cin >> age1;
						std::cout << "\n Appointment: \t";
						cin >> app1;
						std::cout << "\n Description: \t";
						cin >> description1;

						int q = search_id(id1, i);
						int l = search_app(app1, i);
						if (q == 1 || l == 1)
						{
							if (q == 1)
							{
								std::cout << "\n Patient record with this ID already present.\n";
							}
							else
							{
								std::cout << "\n Patient record with this Appointment already present.\n";
							}
						}
						else
						{
							strcpy(rec[i].id, id1);
							strcpy(rec[i].name, name1);
							strcpy(rec[i].gender, gender1);
							strcpy(rec[i].age, age1);
							strcpy(rec[i].app, app1);
							strcpy(rec[i].description, description1);
							file1 << i << "|" << rec[i].id << "|" << rec[i].name << "|" << rec[i].age << "|" << rec[i].gender << "|" << rec[i].app << "|" << rec[i].description << "\n";
						}
					}
					file1.close();
					no = no + n;
					fstream file1, file3, file2;
					file3.open("no.txt", ios::out);
					file3 << no;
					file3.close();
					file2.open("index.txt", ios::out);
					file1.open("record.txt", ios::in);
					for (i = 0; i < no; i++)
					{
						file1.getline(ind, 5, '|');
						file1.getline(id, 20, '|');
						file1.getline(name, 30, '|');
						file1.getline(age, 10, '|');
						file1.getline(gender, 10, '|');
						file1.getline(app, 10, '|');
						file1.getline(description, 30, '\n');
						strcpy(rec[i].ind, ind);

						strcpy(in[i].id, id);

						strcpy(in[i].ind, ind);
					}

					sort_index();
					//std::cout << "\n After sorting,index file contents are:\n";
					for (i = 0; i < no; i++)
						//std::cout << in[i].id << " " << in[i].ind << endl;
						for (i = 0; i < no; i++)
						{
							file2 << in[i].id << "|" << in[i].ind << "\n";
						}
					file1.close();
					file2.close();

					break;
				}

					//search

				case 2:
				{
					fstream f4;
					f4.open("no.txt", ios::in);
					f4 >> no;
					//cout << no;
					cout << " \n Enter patient's id whose details are to be displayed:  \t";
					cin >> id;
					int q = search_index(id);
					if (q == 1)
						cout << "\n success search \n";
					else
						cout << "\n search failed \t";

					break;
				}

					//deletion

				case 3:
				{
					cout << "\n Enter patient  id who is to be deleted \n ";
					cin >> st_id;
					int q = search_index(st_id);
					if (q == 1)
					{
						cout << "\n  Successfully Deleted\n";
						delet(st_id);
					}
					else
						cout << "\n  failed to delete \t";
					break;
				}

					//display

				case 4:
				{
					fstream file1;
					file1.open("record.txt", ios::in);
					std::cout << "ID \t NAME\t AGE \t GENDER \t APPOINTMENT \t DESCRIPTION \n";

					while (!file1.eof())
					{
						file1.getline(ind, 5, '|');
						file1.getline(id, 20, '|');
						file1.getline(name, 30, '|');
						file1.getline(age, 10, '|');
						file1.getline(gender, 10, '|');
						file1.getline(app, 10, '|');
						file1.getline(description, 30, '\n');

						cout << id << "\t" << name << "\t" << age << "\t    " << gender << "\t \t   " << app << "\t \t   " << description << "\n"
							 << endl;
					}
					file1.close();
					break;
				}

					//exit

				case 8:
				{
					cout << "\n Ending program";
					goto label;
				}

					//gender

				case 7:
				{
					fstream f4;
					f4.open("no.txt", ios::in);
					f4 >> no;
					//cout << no;
					cout << "Enter the Gender to be searched upon: \t";
					cin >> gender;
					ret_gender(gender);
					break;
				}

					//description search

				case 6:
				{
					fstream f4;
					f4.open("no.txt", ios::in);
					f4 >> no;

					//cout << no;

					cout << "Enter the Appointment to be searched upon: \t";
					cin >> app;
					ret_app(app);
					break;
				}

					//update

				case 5:
				{

					rec_flag = 0;
					int fr = 0;
					cout << "\n Enter patient's id to be updated : \t";
					cin >> st_id;
					rec_flag = search_index(st_id);
					if (rec_flag == -1)
					{
						std::cout << "\n Failed record not found";
						break;
					}

					for (int i = 0; i < no; i++)
					{
						if (strcmp(rec[i].ind, rec_ind) == 0)
						{
							std::cout << "\nThe old values of the patient record  are ";
							std::cout << "\n id  = " << rec[i].id;
							std::cout << "\n name   = " << rec[i].name;
							std::cout << "\n age   = " << rec[i].age;
							std::cout << "\n gender   = " << rec[i].gender;
							std::cout << "\n appointment   = " << rec[i].app;

							std::cout << "\n description   = " << rec[i].description;

							std::cout << "\nEnter the new values \n";
							std::cout << "\n id  = ";
							cin >> rec[i].id;
							std::cout << "\n name   = ";
							cin >> rec[i].name;
							std::cout << "\n age    = ";
							cin >> rec[i].age;
							std::cout << "\n gender   = ";
							cin >> rec[i].gender;
							std::cout << "\n appointment   = ";
							cin >> rec[i].app;

							std::cout << "\n description   = ";
							cin >> rec[i].description;
							break;
						}
					}

					fstream f1, f2;
					f1.open("record.txt", ios::out);
					f2.open("index.txt", ios::out);

					for (int i = 0; i < no; i++)
					{

						strcpy(in[i].id, rec[i].id);
						strcpy(in[i].ind, rec[i].ind);
					}
					sort_index();
					for (int i = 0; i < no; i++)
					{
						f1 << rec[i].ind << "|" << rec[i].id << "|" << rec[i].name << "|" << rec[i].age << "|" << rec[i].gender << "|" << rec[i].app << "|" << rec[i].description << "\n";
						f2 << in[i].id << "|" << in[i].ind << "\n";
					}

					f1.close();
					f2.close();
					std::cout << "\n update successful\n";
				}
				}
			}
		}
		else
		{

			cout << "\n Invalid login";
		}

		break;
	}

	case 2:
	{
		fstream f4;
		f4.open("no.txt", ios::in);
		f4 >> no;
		cout << " \n Enter the  Patient's id whose details are to be displayed :\t";
		cin >> id;
		int q = search_index(id);
		if (q == 1)
			cout << "\n success search";
		else
		{
			cout << "\n unsuccess search,plz enter the details properly";
			goto label;
		}

		break;
	}
	}

	return 0;
}