/*
 * ModeAutonome.cpp
 *
 *  Created on: Jan 21, 2017
 *      Author: prg6robot
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ModeAutonome.h>
#include <cstring>

using std::ifstream;
using std::cout;
using std::endl;

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = " ";

ModeAutonome::ModeAutonome(SystemesDeControle * _systemesdecontrole)
{
	commandeencours=0;
	systemesdecontrole=_systemesdecontrole;
	bEndOfExecution = false;
}

ModeAutonome::~ModeAutonome()
{
}

void ModeAutonome::Execute(int t)
{
	unsigned int i=commandeencours;
	static int n=0;
	if(listecommande.size()==0){
		std::cout << "liste commande vide" << std::endl;
		return;
	}
	n++;

	if(bEndOfExecution==true)
		{
			return;
		}

	if(listecommande[0].demarre==false)
		{
			listecommande[0].demarre=true;
			listecommande[0].start(t);
		}

	if (listecommande[i].demarre==true && listecommande[i].termine==false && listecommande[i].isfinished(t)==true)
		{
			listecommande[i].termine=true;
			if(i==listecommande.size()-1)
				{
					bEndOfExecution = true;
				}
		}

	if (bEndOfExecution==false && listecommande[i].termine==true && listecommande[i+1].demarre==false)
		{
			i=i+1;
			listecommande[i].demarre=true;
			listecommande[i].start(t);
		}

	commandeencours=i;
}

// ON NE REGARDE PAS //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ModeAutonome::choose_scenario(std::string nomScenario )
{
	std::cout<<"Scenario "<<nomScenario<<std::endl;
	listecommande.clear();
	bEndOfExecution=false;
	commandeencours=0;
	if(nomScenario=="NONE")
		return;

	ifstream fin;	//create a file-reading object

	char str[MAX_TOKENS_PER_LINE];

	sprintf(str,"/home/lvuser/%s.txt",nomScenario.c_str());

	fin.open(str);	//open a file

	if (!fin.good())
		{
			return;	//exit if file not found
		}

	bool bCommentaire=false;

	while (!fin.eof())	//read each line of the file
		{
			//read an entire line into memory
			char buf[MAX_CHARS_PER_LINE];
			fin.getline(buf, MAX_CHARS_PER_LINE);

			//parse the line into blank-delimited tokens
			int n = 0; // a for-loop index

			// array to store memory addresses of the tokens in buf
			const char* token[MAX_TOKENS_PER_LINE] = {}; // initialize to 0

			// parse the line
			token[0] = strtok(buf, DELIMITER); // first token
			if (token[0]) // zero if line is blank
				{
					for (n = 1; n < MAX_TOKENS_PER_LINE; n++)
						{
							token[n] = strtok(0, DELIMITER); // subsequent tokens
							if (!token[n])
								{
									break; // no more tokens
								}
						}
				}

			// process (print) the tokens
			//for (int i = 0; i < n; i++) // n = #of tokens
			//cout << "Token[" << i << "] = " << token[i] << endl;
			//cout << endl;
			std::string nomdelacommande;
			float param1=0;
			float param2=0;
			bCommentaire=false;
			if(token[0])
				{
				    if(strlen(token[0])<2)
				    	{
				    		bCommentaire=true;
				    	}

				    else if(token[0][0]=='/')
				    	{
				    		bCommentaire=true;
				    	}
				    else
					    {
				    		nomdelacommande=std::string(token[0]);
					    }
				}

			if(token[1])
				{
					param1=atof(token[1]);
				}

			if(token[2])
				{
					param2=atof(token[2]);
				}

			if(bCommentaire==false)
				{
					listecommande.push_back(Commande(systemesdecontrole,nomdelacommande,param1,param2));
					std::cout << "creating cmd " << nomdelacommande << " with params " << param1 << " " << param2 <<std::endl;
				}
		}

	//std::cout << listecommande.size() << " commandes lues" << std::endl;
	for (unsigned int j=0; j<listecommande.size(); j++)
	std::cout << listecommande[j].nomdelacommande << std::endl;
}
