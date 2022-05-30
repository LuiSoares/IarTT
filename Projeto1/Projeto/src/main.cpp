//============================================================================
// Name        : Projeto.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <iomanip>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Contribuidores.hpp"
#include "Projeto.hpp"
#include "card.hpp"
#include <algorithm>
#include <random>
#include <chrono>
#include <ctime>
#include <math.h>
using namespace std;


string getOppCard(string card)
{
if (card.compare("black")) return "red";
else return "true";
}

vector<Card> createCards()
{
vector<Card> cartas;
Card c("red");
int num = rand() % 10 + 1;
if( num <= 5){ c.setCard("red");}
cartas.push_back(c);
return cartas;
}

vector<Card> createOpp(vector<Card> cartas)
{
	vector<Card> retornado;
	string nome = getOppCard(cartas[1].getColor());
	Card c(nome);
	retornado.push_back(c);
	retornado.push_back(cartas[0]);
	retornado.push_back(cartas[1]);
	return retornado;
}

vector<Card> createBaralho()
{
vector<Card> baralho;

for(unsigned int i = 0; i< 200; i++)
{
Card c("red");
int num = rand() % 10 + 1;
if( num <= 5){ c.setCard("black");}
baralho.push_back(c);
}
return baralho;
}



vector<int> getRandomPos(vector<int> size)
{

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine e(seed);
	shuffle(size.begin(), size.end(), e);
	return size;

}

int findContributor(string skill, vector<Contribuidor> contribuidores, vector<int> pos)
{
	vector<int> returned;
	bool found=false;
	for(unsigned int i =0; i< contribuidores.size(); i++)
	{
		for(unsigned int j =0; j< contribuidores[i].getSkills().size();j++)
		{
			if((skill.compare(contribuidores[i].getSkills()[j]) == 0) || (contribuidores[i].getSkills()[j] == skill))
					{
						returned.push_back(i);
					}

		}
	}
	returned = getRandomPos(returned);
	for (unsigned int i=0; i< returned.size();i++)
	{
		for(unsigned int j=0;j<pos.size();j++)
			{	if(pos[j] == returned[i])
					{
						found = true;
					}
			}
		if(!found) { return returned[i];}
		found = false;
	}
	return returned[0];
}
int findSkill(Contribuidor contribuidor, string skill)
{
for(unsigned int i=0; i<contribuidor.getSkills().size();i++)
	{
	if (!skill.compare(contribuidor.getSkills()[i])) return i;
	}
return -1;
}
vector<int> nextNodeTabu(vector<int> solution, vector<Projeto> projetos, vector<Contribuidor> contribuidores, vector<int> tabu)
{
	vector<int> search;
	bool tab=false;
	int index =0, pos=0, ind =0, aux=0, auxiliar=0;
	int choice =0;
	bool finished=false;
	do
	{
	choice = rand() % solution.size();
	tab=false;
	for(unsigned int w =0; w<tabu.size();w++)
		{
		if(tabu[w]==choice) {tab=true;}
		}
	}while(tab);


	for(unsigned int i =0; i < projetos.size();i++)
		{

			choice=0;
			index = choice;
			ind = index;
			auxiliar = index;
			if(index == choice)
			{
				cout <<endl << " troca de projetos";
				do{
				ind = 0;
				pos = rand() % projetos.size();
				for(int j =0; j<pos;j++)
				{
					ind += projetos[j].getSkills().size()+1;
					cout<<endl <<ind;

				}
				cout<<endl<<"ele ";
				} while(ind == choice);
				cout <<endl<<" qlq coisa";
				aux = solution[ind];
				solution[ind] = solution[choice];
				solution[choice] = aux;
				//break;


			}
			else if(choice <= (projetos[i].getSkills().size()+ind))
			{
				cout<< endl <<"troca de contribuidores";
				for(unsigned int j =1; j<projetos[i].getSkills().size()+1;j++)
					{

						ind += 1;
						if(ind == choice)
							{
							for(unsigned int w =0; w<projetos[i].getSkills().size();w++)
								{

									search.push_back(solution[auxiliar+w+1]);

								}
							solution[ind] = findContributor(projetos[i].getSkills()[j-1], contribuidores, search);

							}

					}
					break;
			}
			index += projetos[i].getSkills().size()+1;

		}
	cout<<"a sair";
	solution.push_back(choice);
	cout<<"a sair";
	return solution;
}


vector<int> nextNode(vector<int> solution, vector<Projeto> projetos, vector<Contribuidor> contribuidores)
{

vector<int> search;
int index =0, pos=0, ind =0, aux=0, auxiliar=0;
bool finished=false;
int choice = rand() % solution.size();
for(unsigned int i =0; i < projetos.size();i++)
	{
		ind = index;
		auxiliar = index;
		if ( index == choice)
		{
			do{
			ind = 0;
			pos = rand() % projetos.size();
			for(int j =0; j<pos;j++)
			{
				ind += projetos[j].getSkills().size()+1;
			}
			} while(ind == choice);
			aux = solution[ind];
			solution[ind] = solution[choice];
			solution[choice] = aux;
			break;

		}
		else if (choice <= (projetos[i].getSkills().size()+ind))
		{
			for(unsigned int j =1; j<projetos[i].getSkills().size()+1;j++)
				{

					ind += 1;
					if(ind == choice)
						{
						for(unsigned int w =0; w<projetos[i].getSkills().size();w++)
							{

								search.push_back(solution[auxiliar+w+1]);

							}
						solution[ind] = findContributor(projetos[i].getSkills()[j-1], contribuidores, search);
						finished = true;
						break;
						}

				}
		}
		if(finished) {break;}
		index += projetos[i].getSkills().size()+1;
	}
return solution;
}
int evalSolution(vector<int> solution,vector<Projeto> projetos, vector<Contribuidor> contribuidores)
{
int value=0,index=0,delay=0, aux=0;
bool resultado = true;
for( int i=0;i<projetos.size();i++)
	{
		for(unsigned int j =0;j<projetos.size();j++)
			{
				if(solution[index] == i)
					{
						for(unsigned int w = 0; w<projetos[j].getSkills().size();w++)
							{
								int skillpos = findSkill(contribuidores[solution[index+w+1]],projetos[j].getSkills()[w]);
								if(skillpos >=0)
									{
									if ( projetos[j].getSkillsLevel()[w] > contribuidores[solution[index+w+1]].getSkillsLevel()[skillpos]) {resultado = false;}
									contribuidores[solution[index+w+1]].addData(projetos[j].getT());
									delay = min(delay,projetos[j].getTf()-contribuidores[solution[index+w+1]].getData());
									}
								else {resultado = false;}
							}

						if(resultado)
							{
							delay = -delay;
							if(delay >= 0 && delay <= projetos[j].getScore()) {aux = projetos[j].getScore()-delay;}
							else if(delay >= projetos[j].getScore()) {aux = 0;}
							else {projetos[j].getScore();}
							if(aux >= 0) {value += aux;}
							}
						resultado = true;
						delay = 0;
						break;
					}
				index += projetos[j].getSkills().size() + 1 ;
			}
	index = 0;
	}

return value;
}

bool sorting(vector<int> const &a, vector<int> const &b, vector<Projeto> projetos, vector<Contribuidor> contribuidores){return evalSolution(a,projetos,contribuidores)>evalSolution(b,projetos,contribuidores);}
void swap(vector<vector<int>> & data, int i, int j)
{
	vector<int> tmp = data[i];
    data[i] = data[j];
    data[j] = tmp;
}

// An optimized version of Bubble Sort
void BubbleSort(vector<vector<int>> & data,vector<Projeto> projetos, vector<Contribuidor> contribuidores)
{
    int length = data.size();

    for (int i = 0; i < length; ++i)
    {
        bool swapped = false;
        for (int j = 0; j < length - (i+1); ++j)
        {
            if (evalSolution(data[j],projetos,contribuidores) < evalSolution(data[j+1],projetos,contribuidores))
            {
                swap(data, j, j+1);
                swapped = true;
            }
        }

        if (!swapped) break;
    }
}

vector<int> eliminateDuppContr(vector<int> solution,vector<Projeto> projetos, vector<Contribuidor> contribuidores)
{
vector<int> res,aux;
int index=0;
for(unsigned int i =0;i<projetos.size();i++)
{
	res.push_back(solution[index]);
	for(unsigned int j=0; j<projetos[i].getSkills().size();j++)
	{
		index += 1;

		bool exists = find(begin(aux), end(aux), solution[index]) != end(aux);
		if(exists)
		{
			int w = findContributor(projetos[i].getSkills()[j], contribuidores, aux);
			aux.push_back(w);
			res.push_back(w);
		}
		else
		{aux.push_back(solution[index]); res.push_back(solution[index]);}

	}
	aux.clear();
	index += 1;
}
return res;
}
vector<int> eliminateDuppProj(vector<int> solution,vector<Projeto> projetos, vector<Contribuidor> contribuidores)
{

	vector<int> res,pos;
	for(unsigned int i =0; i< projetos.size();i++)
	{
		pos.push_back(i);
	}
	int index=0;
	for(unsigned int i =0;i<projetos.size();i++)
	{
		bool exists = find(begin(pos), end(pos), solution[index]) != end(pos);
		if(exists)
		{
			pos[index]=-1;
		}
		else
		{
			res.push_back(index);
		}
		index +=projetos[i].getSkills().size();
		index += 1;
	}
	auto it = pos.begin();
	    while(it != pos.end()) {
	        // If element is even number then delete it
	        if(*it == -1) {
	            // Due to deletion in loop, iterator became
	            // invalidated. So reset the iterator to next item.
	            it = pos.erase(it);
	        } else {
	            it++;
	        }
	    }
	for(unsigned int i =0; i<res.size();i++)
	{
		solution[res[i]] = pos[i];

	}
		return solution;
}

vector<int> initialState(vector<Projeto> projetos, vector<Contribuidor> contribuidores)
{
int res=0;
vector<int> solution, pos, searched;
for(unsigned int i =0; i<projetos.size(); i++)
{
	pos.push_back(i);

}
pos = getRandomPos(pos);
for (unsigned int i =0 ; i<projetos.size();i++)
{
solution.push_back(pos[i]);
for(unsigned int j = 0; j<projetos[i].getSkills().size();j++)
{

	res = findContributor(projetos[i].getSkills()[j],contribuidores, searched);
	solution.push_back(res);
	searched.push_back(res);
}
searched.clear();
}
return solution;
}

int main() {
	srand(time(0));
	fstream my_file;
	vector<Contribuidor> contribuidores;
	vector<Projeto> projetos;
	vector<int> solution, node;
	int nomes,proj,skillevel, habilidades, t, score, tf, projs, value;
	string nome, skill;
	my_file.open("base_dados.txt", ios::in);
		if (!my_file) {
			cout << "No such file";
		}
		else {
			my_file >> nomes >> proj;
			for(int i =0; i < nomes ; i++)
			{
				my_file >> nome >> habilidades ;
				Contribuidor c(nome);
				for (int j =0; j < habilidades ; j++)
				{
					my_file >> skill >> skillevel;
					c.addSkill(skill);
					c.addLevel(skillevel);
				}
				contribuidores.push_back(c);

			}
			for(int i =0; i< proj; i++)
			{
				my_file >> nome >> t >> score >> tf >> projs;
				Projeto c(nome,t,score,tf);
				for (int j =0; j < projs ; j++)
				{
					my_file >> skill >> skillevel;
					c.addSkill(skill);
					c.addLevel(skillevel);
				}
				projetos.push_back(c);
			}

		}
		my_file.close();
		cout<< " Bem-vindo, foram carregados " << contribuidores.size();
		cout<< " contribuidores com sucesso e " << projetos.size();
		cout<< " projetos com sucesso." <<endl<< "Indique o algarismo correspondente ao algoritmo quer usar:";
		cout<< endl << "1- Hill Climbing" << endl << "2 - Simulated Annealing";
		cout<< endl<<"3- Tabo Search " << endl << "4 - Genetic Algorithm";
		cin>>t;
		switch(t) {
		  case 1:
		  {
			  char c;
			  int tamanho=0;
			  cout<<endl<< "Do you want to give the inputs? (s/n)"<<endl;
			  cin>>c;
			  if(c=='s')
			  {
				  cout<<endl<< "How many nodes to iterate?"<<endl;
				  cin>> tamanho;
			  			  }
			  			  else
			  			  {
			  				tamanho=contribuidores.size()+projetos.size();
			  			  }
			  auto start = chrono::high_resolution_clock::now();
			 bool stop = false, escape = false;
			 int res=0;
		    solution = initialState(projetos, contribuidores);
		    value = evalSolution(solution,projetos,contribuidores);
		    solution = nextNode(solution, projetos, contribuidores);
		    value = evalSolution(solution,projetos,contribuidores);
		    cout<< value;
			  solution = initialState(projetos,contribuidores);
			  value = evalSolution(solution,projetos,contribuidores);

			  while(!stop)
			  {
				for(unsigned int i =0; i< tamanho;i++)
				{
					node = nextNode(solution,projetos,contribuidores);
					res= evalSolution(node,projetos,contribuidores);
					if (res > value)
					{
						solution = node;
						value = res;
						escape=true;
						break;
					}
					escape = false;
				}
				if(escape) {stop = false;} else {stop = true;}
			  }
			  auto stopf = chrono::high_resolution_clock::now();
			  cout<<endl<<" Best solution value is : " << value<<endl;
			  auto duration = chrono::duration_cast<std::chrono::microseconds>(stopf - start).count();
			  cout <<endl<<"Duration : "<< duration << endl;
		    break;

		  }

		  case 2:
		  {
			  char c;
			  float temp=0, tf =0, alpha =0, niterations=0;
			  float diff=0, cond=0, random =0;
			  cout<<endl<< "Do you want to give the inputs? (s/n)"<<endl;
			  cin>>c;
			  if(c=='s')
			  {
				  cout<<endl<< "Whats the initial temperature?"<<endl;
			  	  cin>> temp;
				  cout<<endl<< "Whats the final temperature?"<<endl;
				  cin>> tf;
				  cout<<endl<< "Whats the alpha (the ratio to reduce temp)?"<<endl;
				  cin>> alpha;
				  cout<<endl<< "How many iterations per cycle?"<<endl;
				  cin>> niterations;
			  }
			  else
			  {
				  temp =1;
				  tf=0.0001;
				  alpha=0.9;
				  niterations= contribuidores.size()+projetos.size();
			  }
			  auto start = chrono::high_resolution_clock::now();
			  solution = initialState(projetos,contribuidores);
			  value = evalSolution(solution,projetos,contribuidores);
			  int res=0;
			  while(temp > tf)
			  {
				  for(int i=0; i<niterations;i++)
				  {
					  node = nextNode(solution,projetos,contribuidores);
					  res= evalSolution(node,projetos,contribuidores);
					  if (res > value)
					  	  {
						  	  solution = node;
						  	  value = res;
						  	  break;
					  	}
					  else
					  	  {
						  random = rand() % 100;
						  random = random/100;
						  diff = (value-res)/temp;
						  cond = exp(diff);
						  if(cond > random)
						  {
						  	solution = node;
						  	value = res;
						  	break;
						  }
					  	  }
				  }
				  temp *= alpha;
			  }
			  auto stopf = chrono::high_resolution_clock::now();
			  cout<<endl<<" Best solution value is : " << value<<endl;
			  auto duration = chrono::duration_cast<std::chrono::microseconds>(stopf - start).count();
			  cout <<endl<<"Duration : "<< duration << endl;
			  break;
		  }
		  case 3:
		  {
			  char c;
			  bool stop = false,escape=false;
			  int iterations=0, tenure=0, tab=0;
			  vector<int> tabu;
			  vector<int> aux;
			  int res;
			  cout<<endl<< "Do you want to insert the inputs? (s/n)"<<endl;
			  cin>>c;
			  if(c=='s')
			  {
				  cout<<endl<< "Whats the number of iterations?"<<endl;
				  cin>>iterations;
				  cout<<endl<<"Whats the tabue tenure?"<<endl;
				  cin>>tenure;
			  }
			  else
			  {
				  iterations = contribuidores.size()+projetos.size();
				  tenure = 1;
			  }
			  solution = initialState(projetos,contribuidores);
			  value = evalSolution(solution,projetos,contribuidores);

			  while(!stop)
			  {
				  for(int i =0; i< iterations;i++)
				  {
					  node = nextNodeTabu(solution,projetos,contribuidores,tabu);
					  aux = node;
					  tab = aux.back();
					  aux.erase(aux.end());
					  res= evalSolution(aux,projetos,contribuidores);
					  cout<< endl <<" Value is " << value << " and the evaluated value is " << res << endl;
					  if (res > value)
					  {
						  solution = aux;
						  value = res;
						  cout << endl << "Found a better solution :"<<endl;
						  for(unsigned int i = 0; i< solution.size();i++)
						  { cout <<endl<< "new node "<<solution[i] << endl ; }
						  escape=true;
						  tabu.push_back(tab);
						  if(tabu.size() > tenure)
						  {
							  tabu.erase(tabu.begin());
						  }

						  break;
					  }
					  escape = false;
				  }
				  if(escape) {stop = false;} else {stop = true;}
			  }
			  break;
		  }

		  case 4:
		  {
			  char c;
			  int gensize=0,iterations=0,mutation=0;
			  cout<<endl<< "Do you want to insert the inputs? (s/n)"<<endl;
			  cin>>c;
			  if(c=='s')
			  {
				  cout<<endl<< "Whats the number of iterations?"<<endl;
				  cin>>iterations;
				  cout<<endl<<"Whats the genome size?"<<endl;
				  cin>>gensize;
				  cout<<endl<<"Mutation rate (1000= 100% ; 1 = .01%)"<<endl;
				  cin>> mutation;

			  }
			  else
			  {
				  iterations = contribuidores.size()+projetos.size();
				  gensize = contribuidores.size();
				  mutation = 10;
			  }
			  auto start = chrono::high_resolution_clock::now();
			  vector<vector<int>> genoma = vector<vector<int>>(gensize);
			  cout << " 1" << endl;
			  for(unsigned int i =0; i<genoma.size();i++)
			  {
				  cout<<endl<<"2"<<endl;
				  genoma[i]=initialState(projetos,contribuidores);
			  }
			  while(iterations !=0)
			  	  {
				  cout<<endl<<iterations<<endl;

				  BubbleSort(genoma,projetos,contribuidores);
				  vector<vector<int>> parent{genoma[0],genoma[1]};

				  for(unsigned int i =0;i<genoma.size();i++)
				  {
					  for(unsigned int j=0; j<genoma[i].size();j++)
					  {
						  int TempSelection = rand() % parent.size();
						  genoma[i][j] = parent[TempSelection][j];
						  if(rand() % 1000 < mutation)
						  {
							  if(j==0)
							  {
								  genoma[i][j] = rand() % projetos.size();
							  }
							  else
							  {
								  genoma[i][j] = rand() % contribuidores.size();
							  }
						  }
					  }
				  }
				  iterations -=1;
				  }
			  auto stopf = chrono::high_resolution_clock::now();
			  cout<<endl<<" Best solution value is : " << evalSolution(genoma[0],projetos,contribuidores)<<endl;
			  auto duration = chrono::duration_cast<std::chrono::microseconds>(stopf - start).count();
			  cout <<endl<<"Duration : "<< duration << endl;
			  break;
		  }
		  default:
		  cout << "wrong choice";
		}





	return 0;
}

