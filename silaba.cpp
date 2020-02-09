#include "silaba.h"

Silaba::Silaba(string escrita) : escrita (escrita)
{
	srand(time(NULL));
	somaParaProb = 0;
	isAtualizado = false;
}

Silaba::~Silaba()
{
}

string Silaba::getEscrita()
{
	return this->escrita;
}

vector<Silaba*> Silaba::getVecPredecessoras()
{
	return this->vecPredecessoras;
}

Silaba* Silaba::getPredecessora(string predec)
{
	for (unsigned int i = 0; i < vecPredecessoras.size(); i++) {
		if ((vecPredecessoras.at(i))->getEscrita() == predec) return vecPredecessoras.at(i);
	}
	return NULL;
}

float Silaba::getProbPredecessora(string predec)
{
	for (unsigned int i = 0; i < vecPredecessoras.size(); i++) {
		if (vecPredecessoras.at(i)->getEscrita() == predec) {
                if (i == 0 || !isAtualizado) return (float) probPredecessoras.at(i) / somaParaProb;
                else {
                        if(probPredecessoras.at(i) > probPredecessoras.at(i-1)) return (float) (probPredecessoras.at(i) - probPredecessoras.at(i-1)) / somaParaProb;
                        else return (float) (probPredecessoras.at(i-1) - probPredecessoras.at(i)) / somaParaProb;
                }
		}
	}

	return 0.0f;
}


bool Silaba::hasPredecessora(string predec){
    for(unsigned int i = 0; i < vecPredecessoras.size(); i++){
        if(vecPredecessoras.at(i)->getEscrita() == predec) return true;
    }
    return false;
}

Silaba * Silaba::sorteiaPredecessora()
{
	if (vecPredecessoras.size() > 0) {
        atualizaProbs();
		//Metodo usado, em oposicao ao metodo "rand() % somaParaProb", para evitar enviesar os resultados para numeros menores.
		//Mais informacoes sobre isso em https://stackoverflow.com/questions/10984974/why-do-people-say-there-is-modulo-bias-when-using-a-random-number-generator
		int sorteado;
		do {
			sorteado = rand();
		} while (sorteado >= (RAND_MAX - RAND_MAX % somaParaProb));
		sorteado %= somaParaProb;
		sorteado++; //Caso deixassemos sem o ++, deixariamos enviesado para as primeiras silabas adicionadas.

		for (unsigned int i = 0; i < probPredecessoras.size(); i++) {
			if (sorteado <= probPredecessoras.at(i)) {
                    return vecPredecessoras.at(i);
			}
		}
	}
	return NULL;
}

void Silaba::addPredecessora(Silaba * predec)
{
	//Tentando adicionar novamente, atualizamos a silaba ja existente
	if (hasPredecessora(predec->getEscrita())){
		aumentaPredecessora(predec);
	}
	else{
	vecPredecessoras.push_back(predec);
	probPredecessoras.push_back(1);
	somaParaProb++;
	}
}

void Silaba::aumentaPredecessora(Silaba * predec)
{
	//Encontramos a predecessora a ser aumentada, depois aumentamos seu valor
	for (unsigned int i = 0; i < vecPredecessoras.size(); i++) {
		if (vecPredecessoras.at(i) == predec) {
			probPredecessoras.at(i) = probPredecessoras.at(i) + 1;
			somaParaProb++; //Aumentamos somaParaProb para casos de getProbPredecessora() sem ter rodado atualizaProbs()
		}

	}
}

void Silaba::atualizaProbs()
{
	if (!isAtualizado){
        int soma = 0;
        for (unsigned int i = 0; i < probPredecessoras.size(); i++) {
            probPredecessoras.at(i) = soma + probPredecessoras.at(i);
            soma = probPredecessoras.at(i);
        }
        somaParaProb = soma;
        isAtualizado = true;
	}
}
