#ifndef SILABA_H
#define SILABA_H

#include <vector>
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;

class Silaba {
public:
	Silaba(string escrita);
	~Silaba();

	// FUNCOES PRATICAS
	/// Funcoes principais
	string getEscrita(); ///Retorna a silaba em texto.
	void addPredecessora(Silaba* predec); ///Adiciona uma silaba as predecessoras. Caso ja seja, aumenta seu "peso" para o sorteio em 1.
	Silaba* sorteiaPredecessora(); ///Sorteio dentro dos predecessores da silaba atual. Os sorteios condizem com a prob obtida por getProbPredecessora() e calculada a mao.

	///Funcoes de suporte
    bool hasPredecessora(string predec); ///Verifica se uma predecessora existe identificada por predec
	void aumentaPredecessora(Silaba* predec); ///
	void atualizaProbs(); /// Atualiza as probabilidades antes de sortear. Executada somente uma vez quando se sorteia a primeira silaba, ja que, no beaba, tudo eh resolvido antes do primeiro sorteio.


	// DEBUG/CURIOSIDADE
	Silaba* getPredecessora(string predec);///retorna a uma predecessora identificada por predec
	vector<Silaba*> getVecPredecessoras();///Fornece acesso ao vetor de predecessoras.
	float getProbPredecessora(string predec);///Retorna a probabilidade de uma determinada predecessora.


private:
	string escrita; ///Identificador, ou "a parte que interessa" de uma silaba
	vector<Silaba*> vecPredecessoras; ///Lista as predecessoras da Silaba atual
	vector<int> probPredecessoras; ///Lista inicialmente a frequencia de cada predecessora no dicionario. Se isAtualizado for true, lista o mais alto resultado(int) de um sorteio para que a predecessora seja a sorteada
	int somaParaProb; ///Mais alto resultado possivel para que alguma seja sorteada. Eh variavel de suporte, mas no fim eh igual a probPredecessoras.back()
	bool isAtualizado; ///Mostra se atualizaProbs() ja rodou, impedindo que rode de novo.
};
#endif
