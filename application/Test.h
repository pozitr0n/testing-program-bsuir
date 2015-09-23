#ifndef _TEST_H_
#define _TEST_H_

#include "common.h"

using namespace std;

bool IsEmpty(string s)
{
	for(size_t i=0;i<s.length();i++)
	{
		if(s[i]!=' ' && s[i]!='\t')
			return false;
	}
	return true;
}

string Trim(string s)
{
	for(size_t i=0;i<s.length();i++)
	{
		if(s[i]!=' ' && s[i]!='\t')
		{
			if(!i)
				return s;
			else
			{
				return s.substr(i);
			}
		}
	}
	return s;
}

string GetCharBeforeDot(string s)
{
	string str;
	for(size_t i=0;i<s.length();i++)
	{
		if(s[i]=='.')
		{
			return Trim(s.substr(0, i));
		}
	}
	return "";
}

string GetCharAfterDot(string s)
{
	string str;
	for(size_t i=0;i<s.length();i++)
	{
		if(s[i]=='.')
		{
			return Trim(s.substr(i+1));
		}
	}
	return "";
}

struct CAnswerStruct
{
	char c;
	int bonus;
};

typedef vector<string> CQuestStrings;
typedef vector<CQuestStrings*> CQuest;
typedef vector<CAnswerStruct*> CAnswer;
typedef vector<CAnswer*> CAnswers;

class CTest
{
	string UserName;
	CQuest Questions;
	CAnswers Answers;
	int Bonus;

	void WriteQuest(int n)
	{
		for(size_t j=0;j<Questions[n]->size();j++)
		{
			cout<<(*Questions[n])[j]<<endl;
		}
	}

	void WriteAnswers()
	{
		for(size_t i=0;i<Answers.size();i++)
			cout<<Answers[i]<<endl;
	}

	void ReadTest(string test)		
	{
		string s;
		int nQ=-1;
		
		ifstream in(test.c_str());
		if(!in)
		{
			cout<<"Îøèáêà ïðè ÷òåíèè ôàéëà '"<<test<<"'"<<endl;
			throw 0;
		}
		while(!in.eof())
		{
			getline(in, s);
			
			if(!IsEmpty(s))
			{
				int n=atoi(GetCharBeforeDot(s).c_str());
				if(n)
				{					
					CQuestStrings* strs=new CQuestStrings();
					Questions.push_back(strs);										
					strs->push_back(s);					
					nQ=n-1;					
				}			
				else if(nQ!=-1)
				{
					Questions[nQ]->push_back(s);
				}
			}			
		}	
	}

	void ReadAnswers(string answers)
	{
		string s;
		int nA=-1;

		ifstream in(answers.c_str());
		if(!in)
		{
			cout<<"Îøèáêà ïðè ÷òåíèè ôàéëà '"<<answers<<"'"<<endl;
			throw 0;
		}
		while(!in.eof())
		{
			getline(in, s);
			
			if(!IsEmpty(s))
			{
				int n=atoi(GetCharBeforeDot(s).c_str());
				if(n)
				{
					CAnswer* answer=new CAnswer();
					Answers.push_back(answer);	
					nA=n-1;
				}
				else if(nA!=-1)
				{
					CAnswerStruct* as=new CAnswerStruct();
					Answers[nA]->push_back(as);
					as->c = GetCharBeforeDot(s)[0];
					int m=atoi(GetCharAfterDot(s).c_str());
					as->bonus = m;
				}
			}
		}
	}

	void RunQuest(int n)
	{
		WriteQuest(n);
		char c;
		cin>>c;
		for(size_t i=0;i<Answers[n]->size();i++)
		{
			if(c==Answers[n]->at(i)->c)
				Bonus+=Answers[n]->at(i)->bonus;			
		}
	}
	
public: 
	CTest(string userName)
	{
		UserName=userName;
		Bonus=0;
	}

	bool Open(string test, string answers)
	{	
		try
		{
			ReadTest(test);
			ReadAnswers(answers);	
			return true;
		}
		catch(...)
		{		
			return false;
		}			
	}
	
	void RunTest()
	{
		for(size_t i=0;i<Answers.size();i++)		
			RunQuest(i);						
		cout<<"Âû íàáðàëè "<<Bonus<<" áàë(à,îâ)"<<endl;		
		_getch();
	}	
};

#endif
