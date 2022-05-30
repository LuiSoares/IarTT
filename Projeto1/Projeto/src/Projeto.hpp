#include <string>
#include <vector>
#include <iostream>
#include <map>
using namespace std;

class Projeto
{
public:
	Projeto(string nome, int t , int score, int tf);
	int getT();
	int getTf();
	int getScore();
	string getNome();
	vector<string> getSkills();
	vector<int> getSkillsLevel();
	void setT(int t);
	void setTf(int tf);
	void setScore(int score);
	void setNome(string nome);
	void setSkills(vector<string> skills);
	void setSkillsLevels(vector<int> skillsLevels);
	void addSkill(string skill);
	void addLevel(int level);
	friend ostream& operator<<(ostream& os, const Projeto& dt);
private:
	vector<string> skills;
	vector<int> skillsLevels;
	string nome;
	int t,tf,score;
};
