#include <string>
#include <vector>
#include <iostream>
#include <map>
using namespace std;

class Contribuidor
{
public:
	Contribuidor(string nome);
	vector<string> getSkills();
	vector<int> getSkillsLevel();
	string getName();
	void setSkills(vector<string> skills);
	void setSkillsLevels(vector<int> skillsLevels);
	void addData(int days);
	int getData();
	void setName(string name);
	void addSkill(string skill);
	void addLevel(int level);
	friend ostream& operator<<(ostream& os, const Contribuidor& dt);
private:
	vector<string> skills;
	vector<int> skillsLevels;
	string nome;
	int data;
};


