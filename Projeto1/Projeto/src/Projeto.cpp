#include "Projeto.hpp"

Projeto::Projeto(string nome, int t, int score, int tf)
{
	this->nome=nome;
	this->t=t;
	this->tf=tf;
	this->score=score;
	}


int Projeto::getT()
{
	return this->t;}

int Projeto::getTf()
{
	return this->tf;
}
int Projeto::getScore()
{return this->score;}

string Projeto::getNome()
{
	return this->nome;
}

void Projeto::setT(int t)
{
	this->t=t;
	}
void Projeto::setTf(int tf)
{
	this->tf=tf;
}
void Projeto::setScore(int score)
{
	this->score = score;
}

void Projeto::setNome(string nome)
{
	this->nome = nome;
}


void Projeto::setSkills(vector<string> skills)
{
	this->skills = skills;
	}

void Projeto::setSkillsLevels(vector<int> skillLevel)
{
	this->skillsLevels = skillLevel;
}


//add
void Projeto::addSkill(string skill)
{
	this->skills.push_back(skill);
	}

void Projeto::addLevel(int level)
{
	this->skillsLevels.push_back(level);
}


vector<int> Projeto::getSkillsLevel()
{
	return skillsLevels;
}

vector<string> Projeto::getSkills()
	{
	return skills;
	}

ostream& operator<<(ostream& os, const Projeto& dt)
{
    os << "O projeto " << dt.nome << " tem as seguintes roles ";
    for (unsigned int i =0; i< dt.skills.size(); i++)
    {
    os << dt.skills[i] << " com o nivel " << dt.skillsLevels[i] << ", ";
    }
    os << endl;
    return os;
}
