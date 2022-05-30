#include "Contribuidores.hpp"

//construtor
Contribuidor::Contribuidor(string nome)
	{
		this->nome=nome;
		this->data=0;
	}


//getters

vector<string> Contribuidor::getSkills()
	{
	return skills;
	}
 string Contribuidor::getName()
	{
		return nome;
	}

vector<int> Contribuidor::getSkillsLevel()
{
	return skillsLevels;
}


//setters
void Contribuidor::setName(string name)
	{nome = name;}


void Contribuidor::setSkills(vector<string> skills)
{
	this->skills = skills;
	}

void Contribuidor::setSkillsLevels(vector<int> skillLevel)
{
	this->skillsLevels = skillLevel;
}


//add
void Contribuidor::addSkill(string skill)
{
	this->skills.push_back(skill);
	}

void Contribuidor::addLevel(int level)
{
	this->skillsLevels.push_back(level);
}

void Contribuidor::addData(int days)
{
	this->data += days;
}

int Contribuidor::getData()
{
return data;
}

ostream& operator<<(ostream& os, const Contribuidor& dt)
{
    os << "O " << dt.nome << " tem as seguintes habilidades ";
    for (unsigned int i =0; i< dt.skills.size(); i++)
    {
    os << dt.skills[i] << " com o nivel " << dt.skillsLevels[i] << ", ";
    }
    os << endl;
    return os;
}
