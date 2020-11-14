#include "silaba.h"
#include "fstream"
#include <list>
#define pb push_back
#define pf push_front

int ascii_especial[] = { 192, 193, 194, 195, 199, 201, 202, 205, 211, 212, 213, 218 };
int string_especial[] = { 224, 225, 226, 227, 231, 233, 234, 237, 243, 244, 245, 250 };

vector<Silaba*> Silabas;
vector<Silaba*> Ultimas;
Silaba* espaco = new Silaba(" ");

typedef std::list<Silaba*> Palavra;
typedef std::list<std::list<Silaba*>> NomeCompleto;

bool temDicionario = false;

int maximoSilabas = 10;

//Gera uma palavra a partir de uma silaba final e com seu maximo tamanho
Palavra geraPalavra(Silaba* terminacao, int maxTamanho);
//Carrega o banco de palavras, gerando o grafo.
void setup(string nomeDoArquivo);

int main(){
	srand(time(NULL));
	
	//Definindo o "genero" do nome a ser gerado. Atualmente, trabalhando com Masculino, Feminino e Neutro.
	int genero;
	do {
		genero = rand();
	} while (genero >= (RAND_MAX - RAND_MAX % 3));
	genero %= 3;

	string dicionario;
	switch (genero) {
	case 0: dicionario = "nomesM.txt"; break;
	case 1: dicionario = "nomesF.txt"; break;
	case 2: dicionario = "nomesN.txt"; break;
	}

	//Runtime dos setups com os dicionarios providos deve ser por volta de 1 segundo.
	setup(dicionario);

	NomeCompleto nomeCompleto;
	
	//Poucas pessoas tem nome de 1 silaba ou mais de 8, pelo menos em paises lusofonos.
	int qtdSilabas = 0;
	do { qtdSilabas = rand() ; } while (qtdSilabas >= RAND_MAX - RAND_MAX % 5);
	qtdSilabas %= 6;
	qtdSilabas += 2;

	nomeCompleto.pb(geraPalavra(Ultimas.at(rand() % Ultimas.size()), qtdSilabas));

	setup("sobrenomes.txt");

	//Dado o possivel tamanho dos sobrenomes, dois devem ser o suficiente. Tem espaco para nomes sem sobrenome.
	int numSobrenomes;
	do {
		numSobrenomes = rand();
	} while (numSobrenomes >= (RAND_MAX - RAND_MAX % 3));
	numSobrenomes %= 3;


	for (int i = 0; i < numSobrenomes; i++) {
		//Evitamos sobrenomes de uma silaba
		do { qtdSilabas = rand(); } while (qtdSilabas >= RAND_MAX - RAND_MAX % 7);
		qtdSilabas %= 6;
		qtdSilabas+= 2;
		nomeCompleto.pb(geraPalavra(Ultimas.at(rand() % Ultimas.size()), qtdSilabas));
	}
	
	ofstream nome;
	nome.open("nomeGerado.txt");


	NomeCompleto::iterator iteradorExterno = nomeCompleto.begin();
	//Iterando por cada nome do nome completo
	while (iteradorExterno != nomeCompleto.end()) {
		Palavra fracaoAtual = (*iteradorExterno);
		Palavra::iterator iteradorInterno = fracaoAtual.begin();

		//Iterando por cada silaba de cada nome
		while (iteradorInterno != fracaoAtual.end()) {
			string silaba = (*iteradorInterno)->getEscrita();

			//Iterando por cada letra de cada silaba
			for (int i = 0; i < silaba.length(); i++) {

				//Conversao de caracteres especiais
				for (int w = 0; w < 12; w++) {
					if ((int)(unsigned char)silaba[i] == string_especial[w]) {
						silaba[i] = tolower((unsigned char)ascii_especial[w]);
					}
				}
				//Nomes comecam com letra maiuscula
				if (iteradorInterno == fracaoAtual.begin() && i == 0) nome << (unsigned char) toupper(silaba[i]);
				else nome << silaba[i];
			}
			iteradorInterno++;
		}
		nome << "\n";
		iteradorExterno++;
	}
	nome << "\n";


    return 0;
}

Palavra geraPalavra(Silaba* terminacao, int maxTamanho){
	//A opcao por uma list em vez de um vector se deve ao metodo "push_front" que o vector nao tem.
	Palavra palavra;
	
	//Geramos as palavras da ultima silaba para a primeira
	Silaba* adicionada = terminacao;
	for (int numSilabas = 0; numSilabas < maxTamanho; numSilabas++) {
		palavra.pf(adicionada);
		
		adicionada = palavra.front()->sorteiaPredecessora();
		//A quantidade de silabas deve ser mantida, mesmo se a silaba encontrada nao tem predecessoras.
		if (adicionada == NULL) {
//adicionada = Silabas.at(rand() % Silabas.size());
            break;
        }
	}
	return palavra;
}

void setup(string nomeDoArquivo) {
	//Verifica se eh uma inicializacao ou atualizacao de dicionarios. Se eh atualizacao, limpa os elementos.
	if (temDicionario) {
		Silabas.clear();
		Ultimas.clear();
	}
	
	ifstream Arquivo;
	string ler;
	Arquivo.open(nomeDoArquivo);
	while (Arquivo) {
		Arquivo >> ler;
		string silaba;
		Silaba* silabaO;
		Silaba* anteriorO;
		bool comecoDePalavra = true;

		for (int i = 0; i < (int)ler.size(); i++) {
			ignoraBit = false;
			ler[i] = tolower(ler[i]); //Trabalhamos apenas com letras minusculas
			int bitsIgnorados[] = {-17, -69, -65}; //BOM de um arquivo UTF-8
			for (int j = 0;!ignoraBit && j < 3; j++){
				if ((int)ler[i] == bitsIgnorados[j]) ignoraBit = true;
			}
			if (ignoraBit) continue;
			if (ler[i] != '-' && ler[i] != '.') {//Formando a silaba
				silaba += ler[i];
			}
			else {//Silaba Formada
				bool jaExiste = false;
				//Verificando se a silaba ja existe
				unsigned int j;
				for (j = 0; j < Silabas.size() && !(jaExiste); j++) {
					if (silaba == Silabas.at(j)->getEscrita()) jaExiste = true; //Comparacao por nomes
				}

				if (jaExiste) {
					silabaO = Silabas.at(j - 1);
					/*Voltamos para o indice da silaba repetida. Nao podemos fazer j-- diretamente no laco ja que estamos lidando com uma variavel "unsigned".
					  Em caso de j == 0, causariamos underflow de j, o que daria problemas.
					*/
				}
				else {
					//Cria o elemento para usarmos posteriormente.
					silabaO = new Silaba(silaba);
					Silabas.push_back(silabaO);

				}
				silaba.clear();
				if (!comecoDePalavra) {
					silabaO->addPredecessora(anteriorO); //A funcao "addPredecessora()" ja lida com casos de silabas que ja sao predecessoras, adicionando 1 na sua frequencia como predecessora.
				}
				anteriorO = silabaO;

				comecoDePalavra = false;
			}

		}
		Ultimas.pb(silabaO);//silaba final de palavra, usaremos para rimar
		anteriorO = NULL;
		comecoDePalavra = true;
		//Finalizamos uma palavra, logo nao temos silabas antecessoras.
		ler.clear();
	}
	Arquivo.close();
	temDicionario = true;
}
