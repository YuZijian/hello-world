#include<iostream>
#include<string>
#include<stack>
using namespace std;
int isOperator(char x);
int isOperand(char x);
int compareTwo(char o1, char o2, int* first);

int main()
{
	//first statement
	cout << "����������ʵ�����⹫ʽ������ʽ���沨��ʽ��ת��" << endl;
	cout << "����a~z,A~Z��ʾ�������" << endl;
	cout << "�ֱ��� ! & | ^ ~ ����񶨡���ȡ����ȡ���̺���˫���̺�" << endl;
	cout << "������һ�����⹫ʽ��";
	//�������ȼ�
	int first[200];
	first['!'] = 1;
	first['&'] = 2;
	first['|'] = 3;
	first['^'] = 4;
	first['~'] = 5;
	first['#'] = 6;
	//get data
	stack<char> s1, s2; //s1�洢��������s2�洢������
	char line[1000];
	char ans[1000];
	gets(line);
	s2.push('#');
	/*���㲨��ʽ*/
	//scan
	int i, flag = 0, num, len = strlen(line);
	i = len - 1;
	while(i >= 0)
	{
		if(!isOperand(line[i])&&!isOperator(line[i]))
		{
			flag = 1;
			break;
		}
	else{
		if(isOperand(line[i]))        //������ֱ�ӷ���s1
			s1.push(line[i]);
		else						//��Ϊ������
		{
			if(line[i] == ')')       //�������ţ�ֱ�ӷ���
				s2.push(line[i]);
			else if(line[i] == '(')     //�������ţ���s2��������ǰ������ε�������s1��������������
			{
				while(s2.top() != ')')
				{
					s1.push(s2.top());
					s2.pop();
				}
				s2.pop();
			}
			else                     //�����������
			{
				if(s2.top() == ')')      //s2����Ϊ�����ţ���ֱ��ѹ��s2
					s2.push(line[i]);
				else          
				{
					if(compareTwo(line[i], s2.top(), first) == 1 || compareTwo(line[i], s2.top(), first) == 0
						||(s2.top() == '!'&&line[i] == '!'))
						s2.push(line[i]);                   //���ȶ�����������Ȼ���ͬ���ΪһԪ�����
					else
					{
						while(!(compareTwo(line[i], s2.top(), first) == 1 || s2.top() == ')'))
						{
							s1.push(s2.top());
							s2.pop();
						}
						s2.push(line[i]);
					}
				}
			}
		}
	}
		i--;
	}
	while(s2.top() != '#')
	{
		s1.push(s2.top());
		s2.pop();
	}
	if(flag == 1)
	{
		cout << "�������⹫ʽ����"<< endl;
		system("pause");
		return 0;
	}
	else
	{
		cout << "����ʽΪ��  ";
		while(!s1.empty())
		{
			cout << s1.top();
			s1.pop();
		}
		cout << endl;
	}
	/*����ʽ�������*/
	//��ԭ����
	i = 0; 
	while(line[i] != '\0')
	{
		if(isOperand(line[i]))        //������ֱ�ӷ���s1
			s1.push(line[i]);
		else						//��Ϊ������
		{
			if(line[i] == '(')       //�������ţ�ֱ�ӷ���
				s2.push(line[i]);
			else if(line[i] == ')')     //�������ţ���s2��������ǰ������ε�������s1��������������
			{
				while(s2.top() != '(')
				{
					s1.push(s2.top());
					s2.pop();
				}
				s2.pop();
			}
			else                     //�����������
			{
				if(s2.top() == '(')      //s2����Ϊ�����ţ���ֱ��ѹ��s2
					s2.push(line[i]);
				else          
				{
					if(compareTwo(line[i], s2.top(), first) == 1 ||(s2.top() == '!'&&line[i] == '!'))
						s2.push(line[i]);                   //���ȶ�����������Ȼ��ΪһԪ�����
					else
					{
						while(!(compareTwo(line[i], s2.top(), first) == 1 || s2.top() == '('))
						{
							s1.push(s2.top());
							s2.pop();
						}
						s2.push(line[i]);
					}
				}
			}
		}
		i++;
	}
	while(s2.top() != '#')
	{
		s1.push(s2.top());
		s2.pop();
	}
	
		cout << "�沨��ʽΪ��";
		i = 0;
		while(!s1.empty())
		{
			ans[i] = s1.top();
			s1.pop();
			i++;
		}
		num = i - 1;
		for(i = num; i >= 0; i--)
			cout << ans[i];
		cout << endl;
	
	system("pause");
	return 0;
}

int isOperator(char x)
{
	if(x == '!' || x == '&' || x == '|' ||
		x == '^' || x == '~' || x == '(' || x == ')')
		return 1;
	else
		return 0;
}
int isOperand(char x)
{
	if((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z'))
		return 1;
	else
		return 0;
}
int compareTwo(char o1, char o2, int* first)
{
	if(first[o1] == first[o2])
		return 0;
	else if(first[o1] < first[o2])
		return 1;
	else
		return -1;
}