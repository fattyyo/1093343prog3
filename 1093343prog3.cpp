#include<iostream>
#include<iomanip>
#include<vector>
#include<sstream>
#include<string>
#include<map>
using namespace std;
vector<string>result;//for input
map<string, string> RF = {
	{"F1","0"},{"F2","2"},{"F3","4"},{"F4","6"},{"F5","8"}
};
map<string, string>RAT = {
	{"F1",""},{"F2",""},{"F3",""},{"F4",""},{"F5",""}
};
map<string, char>operand = { {"ADDI",'+'},{"ADD",'+'} ,{"SUB",'-'} ,{"MUL",'*'} ,{"DIV",'/'} };
struct rs
{
	bool val = false;
	char oper;
	string n1;
	string n2;
	string n3;
	int cycletime;
};
rs temp[5];
rs buffer[2];
int cycle = 1;
int ndone;
bool dis = false;
bool exe[2] = { false,false };
void input();
void issue(int a);
void display();
void write(int tem,int buf);
void execute(int a);

int main()
{
	input();
	int writecount = 0;
	int cnt = result.size() / 4 ;
	for(int a=0;a<result.size();a+=4)
	{
		if (cycle - buffer[0].cycletime == 2&&(buffer[0].oper=='+'||buffer[0].oper=='-'))
		{
			buffer[0].n3.erase(0, 2);
			int tem = stoi(buffer[0].n3);
			write(tem,0);
			writecount++;
		}
		if (cycle - buffer[1].cycletime == 10 && buffer[1].oper == '*')
		{
			buffer[1].n3.erase(0, 2);
			int tem1 = stoi(buffer[1].n3);
			write(tem1, 1);
			writecount++;
		}
		else if (cycle - buffer[1].cycletime == 40 && buffer[1].oper == '/')
		{
			buffer[1].n3.erase(0, 2);
			int tem1 = stoi(buffer[1].n3);
			write(tem1, 1);
			writecount++;
		}
		for (int i = 0; i < 5; i++)
		{
				if (isalpha(temp[i].n1[0]) == 0 && isalpha(temp[i].n2[0])==0   && temp[i].val == true)
				{
					if (i < 3 && exe[0] == false)
						execute(i);
					else if (i > 2 && i < 5 && exe[1] == false)
						execute(i);
				}
		}
		if (ndone > 0)
			a = ndone;
		issue(a);
		if (dis == true)
		{
			display();
			dis = false;
		}
		cycle++;
	}
	while (writecount < cnt)
	{
		if (cycle - buffer[0].cycletime == 2 && (buffer[0].oper == '+' || buffer[0].oper == '-'))
		{
			buffer[0].n3.erase(0, 2);
			int tem = stoi(buffer[0].n3);
			write(tem, 0);
			writecount++;
		}
		if (cycle - buffer[1].cycletime == 10 && buffer[1].oper == '*')
		{
			buffer[1].n3.erase(0, 2);
			int tem1 = stoi(buffer[1].n3);
			write(tem1, 1);
			writecount++;
		}
		else if (cycle - buffer[1].cycletime == 40 && buffer[1].oper == '/')
		{
			buffer[1].n3.erase(0, 2);
			int tem1 = stoi(buffer[1].n3);
			write(tem1, 1);
			writecount++;
		}
		for (int i = 0; i < 5; i++)
		{
			if (isalpha(temp[i].n1[0]) == 0 && isalpha(temp[i].n2[0]) == 0 && temp[i].val == true)
			{
				if (i < 3 && exe[0] == false)
					execute(i);
				else if (i > 2 && i < 5 && exe[1] == false)
					execute(i);
			}
		}
		if (dis == true)
		{
			display();
			dis = false;
		}
		cycle++;
	}
}


void write(int tem,int buf)
{
	dis = true;
	int temp1, temp2, total;
	temp1 = stoi(buffer[buf].n1);
	temp2 = stoi(buffer[buf].n2);
	if (buffer[buf].oper == '+')
	{
		total = temp1 + temp2;
		exe[0] = false;
	}
	else if (buffer[buf].oper == '-')
	{
		total = temp1 - temp2;
		exe[0] = false;
	}
	else if (buffer[buf].oper == '*')
	{
		total = temp1 * temp2;
		exe[1] = false;
	}
	else
	{
		total = temp1 / temp2;
		exe[1] = false;
	}
	if (RAT[temp[tem-1].n3] == "RS" + to_string(tem))
	{
		RF[temp[tem-1].n3] = to_string(total);//update RF value
		RAT[temp[tem-1].n3] = "";//delete the val of RAT
	}
	for (int i = 0; i < 5; i++)
	{
		if (temp[i].n1 == "RS" + to_string(tem))
		{
			temp[i].n1 = to_string(total);
		}
		if (temp[i].n2 == "RS" + to_string(tem))
		{
			temp[i].n2 = to_string(total);
		}
	}
	temp[tem-1].n1 = "";///delete the val of RS buffer
	temp[tem-1].n2 = "";
	temp[tem-1].n3 = "";
	temp[tem-1].oper =' ';
	temp[tem-1].cycletime = 0;
	temp[tem-1].val = false;
	buffer[buf].n1 = "";
	buffer[buf].n2 = "";
	buffer[buf].n3 = "";
	buffer[buf].cycletime = 0;
	buffer[buf].oper = ' ';
	buffer[buf].val = false;
	//buffer[buf] = temp[tem];
}

void execute(int i)
{
	dis = true;
		if (temp[i].oper == '+' || temp[i].oper == '-')
		{
				buffer[0].oper = temp[i].oper;
				buffer[0].n1 = temp[i].n1;
				buffer[0].n2 = temp[i].n2;///////要執行的東西放進buffer
				buffer[0].n3 = "RS"+to_string(i+1);//紀錄buffer要回哪個RS		
				buffer[0].cycletime = cycle;
				temp[i].cycletime = cycle;
				exe[0] = true;
		}
		else if (temp[i].oper == '*')
		{
				buffer[1].oper = temp[i].oper;
				buffer[1].n1 = temp[i].n1;
				buffer[1].n2 = temp[i].n2;///////要執行的東西放進buffer
				buffer[1].n3 = "RS" + to_string(i + 1);//紀錄buffer要回哪個RS
				buffer[1].cycletime = cycle;
				temp[i].cycletime = cycle;
				exe[1] = true;
		}
		else
		{
				buffer[1].oper = temp[i].oper;
				buffer[1].n1 = temp[i].n1;
				buffer[1].n2 = temp[i].n2;///////要執行的東西放進buffer
				buffer[1].n3 = "RS" + to_string(i + 1);//紀錄buffer要回哪個RS
				buffer[1].cycletime = cycle;
				temp[i].cycletime = cycle;
				exe[1] = true;
		}
}
void issue(int i)
{
		if (result[i] == "ADD" || result[i] == "ADDI" || result[i] == "SUB")///放rs1-3
		{
			dis = true;
			if (temp[0].val == false)//放RS1
			{
				temp[0].oper = operand[result[i]];
				if (RAT[result[i + 2]] != "" && RAT[result[i + 3]] == "")//rat裡面有東西
				{
					temp[0].n1 = RAT[result[i + 2]];
					if (result[i] == "ADDI")
						temp[0].n2 = result[i + 3];
					else
						temp[0].n2 = RF[result[i + 3]];
					temp[0].n3 = result[i + 1];
					RAT[result[i + 1]] = "RS1";
					temp[0].val = true;
				}
				if (RAT[result[i + 3]] != "" && RAT[result[i + 2]] == "")//rat裡面有東西
				{
					temp[0].n1 = RF[result[i + 2]];
					if (result[i] == "ADDI")
						temp[0].n2 = result[i + 3];
					else
					{
						temp[0].n2 = RAT[result[i + 3]];
					}
					temp[0].n3 = result[i + 1];
					RAT[result[i + 1]] = "RS1";
					temp[0].val = true;
				}
				if (RAT[result[i + 3]] != "" && RAT[result[i + 2]] != "")////兩個的rat都有東西
				{
					temp[0].n1 = RAT[result[i + 2]];
					if (result[i] == "ADDI")
						temp[0].n2 = result[i + 3];
					else
					{
						temp[0].n2 = RAT[result[i + 3]];
					}
					temp[0].n3 = result[i + 1];
					RAT[result[i + 1]] = "RS1";
					temp[0].val = true;
				}
				if (temp[0].val == false)///看rat有沒有放東西進去 沒有的話放RF的值
				{
					temp[0].n1 = RF[result[i + 2]];
					if (result[i] == "ADDI")
						temp[0].n2 = result[i + 3];
					else
					{
						temp[0].n2 = RF[result[i + 3]];
					}
					temp[0].n3 = result[i + 1];
					RAT[result[i + 1]] = "RS1";
					temp[0].val = true;
				}


			}
			else if (temp[1].val == false)//放RS2
			{
				temp[1].oper = operand[result[i]];
				if (RAT[result[i + 2]] != "" && RAT[result[i + 3]] == "")//rat裡面有東西
				{
					temp[1].n1 = RAT[result[i + 2]];
					if (result[i] == "ADDI")
						temp[1].n2 = result[i + 3];
					else
					{
						temp[1].n2 = RF[result[i + 3]];
					}
					temp[1].n3 = result[i + 1];
					RAT[result[i + 1]] = "RS2";
					temp[1].val = true;
				}
				if (RAT[result[i + 3]] != "" && RAT[result[i + 2]] == "")//rat裡面有東西
				{
					temp[1].n1 = RF[result[i + 2]];
					if (result[i] == "ADDI")
						temp[1].n2 = result[i + 3];
					else
					{
						temp[1].n2 = RAT[result[i + 3]];
					}

					temp[1].n2 = RAT[result[i + 3]];
					temp[1].n3 = result[i + 1];
					RAT[result[i + 1]] = "RS2";
					temp[1].val = true;
				}
				if (RAT[result[i + 3]] != "" && RAT[result[i + 2]] != "")////兩個的rat都有東西
				{
					temp[1].n1 = RAT[result[i + 2]];
					if (result[i] == "ADDI")
						temp[1].n2 = result[i + 3];
					else
					{
						temp[1].n2 = RAT[result[i + 3]];
					}
					temp[1].n3 = result[i + 1];
					RAT[result[i + 1]] = "RS2";
					temp[1].val = true;
				}
				if (temp[1].val == false)
				{
					temp[1].n1 = RF[result[i + 2]];
					if (result[i] == "ADDI")
						temp[1].n2 = result[i + 3];
					else
					{
						temp[1].n2 = RF[result[i + 3]];
					}
					temp[1].n3 = result[i + 1];
					RAT[result[i + 1]] = "RS2";
					temp[1].val = true;
				}
				//	cycle++;
			}
			else if (temp[2].val == false)//放RS3
			{
				temp[2].oper = operand[result[i]];
				if (RAT[result[i + 2]] != "" && RAT[result[i + 3]] == "")//rat裡面有東西
				{
					temp[2].n1 = RAT[result[i + 2]];
					if (result[i] == "ADDI")
						temp[2].n2 = result[i + 3];
					else
					{
						temp[2].n2 = RF[result[i + 3]];
					}

					temp[2].n3 = result[i + 1];
					RAT[result[i + 1]] = "RS3";
					temp[2].val = true;
				}
				if (RAT[result[i + 3]] != "" && RAT[result[i + 2]] == "")//rat裡面有東西
				{
					temp[2].n1 = RF[result[i + 2]];
					if (result[i] == "ADDI")
						temp[2].n2 = result[i + 3];
					else
					{
						temp[2].n2 = RAT[result[i + 3]];
					}

					temp[2].n3 = result[i + 1];
					RAT[result[i + 1]] = "RS3";
					temp[2].val = true;
				}
				if (RAT[result[i + 3]] != "" && RAT[result[i + 2]] != "")////兩個的rat都有東西
				{
					temp[2].n1 = RAT[result[i + 2]];
					if (result[i] == "ADDI")
						temp[2].n2 = result[i + 3];
					else
					{
						temp[2].n2 = RAT[result[i + 3]];
					}

					temp[2].n3 = result[i + 1];
					RAT[result[i + 1]] = "RS3";
					temp[2].val = true;
				}
				if (temp[2].val == false)
				{
					temp[2].n1 = RF[result[i + 2]];
					if (result[i] == "ADDI")
						temp[2].n2 = result[i + 3];
					else
					{
						temp[2].n2 = RF[result[i + 3]];
					}

					temp[2].n3 = result[i + 1];
					RAT[result[i + 1]] = "RS3";
					temp[2].val = true;
				}
				//cycle++;
			}
		}
		else//乘法跟除法放RS4-5
		{
			if (temp[3].val == false)//放RS4
			{
				dis = true;
				temp[3].oper = operand[result[i]];
				if (RAT[result[i + 2]] != "" && RAT[result[i + 3]] == "")//rat裡面有東西
				{

					temp[3].n1 = RAT[result[i + 2]];
					temp[3].n2 = RF[result[i + 3]];
					temp[3].n3 = result[i + 1];
					RAT[result[i + 1]] = "RS4";
					temp[3].val = true;
					ndone = 0;
				}
				if (RAT[result[i + 3]] != "" && RAT[result[i + 2]] == "")//rat裡面有東西
				{
					temp[3].n1 = RF[result[i + 2]];
					temp[3].n2 = RAT[result[i + 3]];						temp[3].n3 = result[i + 1];
					RAT[result[i + 1]] = "RS4";
					temp[3].val = true;
					ndone = 0;
				}
				if (RAT[result[i + 3]] != "" && RAT[result[i + 2]] != "")////兩個的rat都有東西
				{
					temp[3].n1 = RAT[result[i + 2]];
					temp[3].n2 = RAT[result[i + 3]];
					temp[3].n3 = result[i + 1];
					RAT[result[i + 1]] = "RS4";
					temp[3].val = true;
					ndone = 0;
				}
				if (temp[3].val == false)
				{
					temp[3].n1 = RF[result[i + 2]];
					temp[3].n2 = RF[result[i + 3]];
					temp[3].n3 = result[i + 1];
					RAT[result[i + 1]] = "RS4";
					temp[3].val = true;
					ndone = 0;
				}
			}
		
			else if (temp[4].val == false)//放RS5
			{
				dis = true;
				temp[4].oper = operand[result[i]];
				if (RAT[result[i + 2]] != "" && RAT[result[i + 3]] == "")//rat裡面有東西
				{
					temp[4].n1 = RAT[result[i + 2]];
					temp[4].n2 = RF[result[i + 3]];
					temp[4].n3 = result[i + 1];
					RAT[result[i + 1]] = "RS5";
					temp[4].val = true;
					ndone = 0;
				}
				if (RAT[result[i + 3]] != "" && RAT[result[i + 2]] == "")//rat裡面有東西
				{
					temp[4].n1 = RF[result[i + 2]];
					temp[4].n2 = RAT[result[i + 3]];
					temp[4].n3 = result[i + 1];
					RAT[result[i + 1]] = "RS5";
					temp[4].val = true;
					ndone = 0;
				}
				if (RAT[result[i + 3]] != "" && RAT[result[i + 2]] != "")////兩個的rat都有東西
				{
					temp[4].n1 = RAT[result[i + 2]];
					temp[4].n2 = RAT[result[i + 3]];
					temp[4].n3 = result[i + 1];
					RAT[result[i + 1]] = "RS5";
					temp[4].val = true;
					ndone = 0;
				}
				if (temp[4].val == false)
				{
					temp[4].n1 = RF[result[i + 2]];
					temp[4].n2 = RF[result[i + 3]];
					temp[4].n3 = result[i + 1];
					RAT[result[i + 1]] = "RS5";
					temp[4].val = true;
					ndone = 0;
				}				
				
				//cycle++;
			}
			else
			{
				ndone = i;
			}

		
		}
	

}



void input()
{

	string temp;
	string temp1;
	vector<string>input;
	stringstream ss;
	while (getline(cin, temp) && temp != "")
	{
		input.push_back(temp);
	}
	for (int i = 0; i < input.size(); i++)
	{
		ss << input[i];
		while (getline(ss, temp1, ' '))
			result.push_back(temp1);
		ss.clear();
	}
}


void display()
{
	cout << "cycle :　" << cycle << endl;
	cout << endl;
	cout << "   --RF--" << endl;
	cout << "F1|  " << setw(4) << RF["F1"] << "  |" << endl;
	cout << "F2|  " << setw(4) << RF["F2"] << "  |" << endl;
	cout << "F3|  " << setw(4) << RF["F3"] << "  |" << endl;
	cout << "F4|  " << setw(4) << RF["F4"] << "  |" << endl;
	cout << "F5|  " << setw(4) << RF["F5"] << "  |" << endl;
	cout << "  --RAT--" << endl;
	cout << "F1|  " << setw(4) << RAT["F1"] << "  |" << endl;
	cout << "F2|  " << setw(4) << RAT["F2"] << "  |" << endl;
	cout << "F3|  " << setw(4) << RAT["F3"] << "  |" << endl;
	cout << "F4|  " << setw(4) << RAT["F4"] << "  |" << endl;
	cout << "F5|  " << setw(4) << RAT["F5"] << "  |" << endl;
	cout << "    --RS--------------" << endl;
	cout << "RS1|  " << setw(4) << temp[0].oper << "  |  " << setw(4) << temp[0].n1 << "  |  " << setw(4) << temp[0].n2 << "  |" << endl;
	cout << "RS2|  " << setw(4) << temp[1].oper << "  |  " << setw(4) << temp[1].n1 << "  |  " << setw(4) << temp[1].n2 << "  |" << endl;
	cout << "RS3|  " << setw(4) << temp[2].oper << "  |  " << setw(4) << temp[2].n1 << "  |  " << setw(4) << temp[2].n2 << "  |" << endl;
	cout << "    ------------------" << endl;
	cout << "buffer:(" <<buffer[0].n3<<")" << buffer[0].n1 << buffer[0].oper << buffer[0].n2 << endl;
	cout << "RS4|  " << setw(4) << temp[3].oper << "  |  " << setw(4) << temp[3].n1 << "  |  " << setw(4) << temp[3].n2 << "  |" << endl;
	cout << "RS5|  " << setw(4) << temp[4].oper << "  |  " << setw(4) << temp[4].n1 << "  |  " << setw(4) << temp[4].n2 << "  |" << endl;
	cout << "    ------------------" << endl;
	cout << "buffer:(" << buffer[1].n3 <<")" << buffer[1].n1 << buffer[1].oper << buffer[1].n2 << endl;

}