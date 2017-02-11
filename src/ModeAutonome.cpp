/*
 * ModeAutonome.cpp
 *
 *  Created on: Jan 21, 2017
 *      Author: prg6robot
 */
#define _CRT_SECURE_NO_WARNINGS

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

}

ModeAutonome::~ModeAutonome() {
}

void ModeAutonome::Execute(int t)
{
	int i=commandeencours;

	std::cout << "commande en exécution: " << listecommande[i].nomdelacommande <<std::endl;

	if(listecommande[0].demarre==false)
	{
		std::cout<<"on démarre"<<std::endl;
		listecommande[0].demarre=true;
		listecommande[0].start(t);
	}

	if (listecommande[i].demarre==true && listecommande[i].termine==false && listecommande[i].isfinished(t)==true)
	{
		std::cout<<"commande finie"<<std::endl;
		listecommande[i].termine=true;
	}

	if (listecommande[i].termine==true && listecommande[i+1].demarre==false)
	{
		std::cout<<"entre deux commandes"<<std::endl;
		i=i+1;
		listecommande[i].demarre=true;
		listecommande[i].start(t);
	}
	commandeencours=i;
}

void ModeAutonome::choose_scenario(int n)
{
  // create a file-reading object
  ifstream fin;

  char str[MAX_TOKENS_PER_LINE];
  sprintf(str,"scenario%d.txt",n);
  fin.open(str); // open a file
  if (!fin.good())
    return; // exit if file not found

  // read each line of the file
  while (!fin.eof())
  {
    // read an entire line into memory
    char buf[MAX_CHARS_PER_LINE];
    fin.getline(buf, MAX_CHARS_PER_LINE);

    // parse the line into blank-delimited tokens
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
        if (!token[n]) break; // no more tokens
      }
    }

    // process (print) the tokens
    for (int i = 0; i < n; i++) // n = #of tokens
      cout << "Token[" << i << "] = " << token[i] << endl;
    cout << endl;
    std::string nomdelacommande;
    float param1=0;
    float param2=0;
    if(token[0])
    {
    	nomdelacommande=std::string(token[0]);
    }
    if(token[1])
       {
    		param1=atof(token[1]);
       }
    if(token[2])
       {
    		param2=atof(token[2]);
       }
    listecommande.push_back(Commande(systemesdecontrole,nomdelacommande,param1,param2));

  }
}
