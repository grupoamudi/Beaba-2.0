import nltk
import pyphen
from nltk.probability import *
import nltk.corpus
import re
import string
import time
import itertools
import threading
import sys

#verificadores para excluir numerais. Especialmente importante com o corpus machado.
def hasNumbers(inputString):
    return any(char.isdigit() for char in inputString)
def roman_to_int(s):
        rom_val = {'I': 1, 'V': 5, 'X': 10, 'L': 50, 'C': 100, 'D': 500, 'M': 1000}
        allowed_chars = {'I', 'V', 'X', 'L', 'C', 'D', 'M'}
        int_val = 0
        for i in range(len(s)):
            if s[i] not in allowed_chars:
                return 0
            if i > 0 and rom_val[s[i]] > rom_val[s[i - 1]]:
                int_val += rom_val[s[i]] - 2 * rom_val[s[i - 1]]
            else:
                int_val += rom_val[s[i]]
        return int_val



done = False
#Telinha de Loading pra ficar bonitinho, ja que esse processo tende a demorar.
def animate():
    for c in itertools.cycle(['|', '/', '-', '\\']):
        if done:
            break
        sys.stdout.write('\rCarregando... ' + c)
        sys.stdout.flush()
        time.sleep(0.1)
    sys.stdout.write('\rCorpus carregado.     ')

t = threading.Thread(target=animate)
t.daemon = True
t.start()




#dicionarios de hifenizacao
dic = pyphen.Pyphen(lang='pt-BR')
dicEN = pyphen.Pyphen(lang='en-US')
dicFR = pyphen.Pyphen(lang='fr-FR')

escrita=[]
banco = open("banco.txt", 'w', encoding='utf-8')

corpus = nltk.corpus.machado #outros corpus: mac_morpho e floresta
corpus.ensure_loaded()
freq = nltk.FreqDist(corpus.words())
#pegamos as 100000 palavras mais frequentes. todos os corpus apresentados possuem menos que 100000 palavras.
for palavra, frequencia in freq.most_common(100000): 
    palavra = re.sub('['+string.punctuation+']', '', palavra)
    if palavra is not "" and not hasNumbers(palavra) and palavra not in escrita and roman_to_int(palavra.upper()) == 0: #excluindo palavras vazias, numeros e numerais.
        escrita.append(palavra.lower())
        escrita.append(".")
        escrita.append("\n")
for palavra in escrita: #hifenizacao
    palavra_hyphen = dic.inserted(palavra)
    if len(palavra_hyphen) > 4 and "-" not in palavra_hyphen:
        palavra_hyphen = dicEN.inserted(palavra_hyphen)
        palavra_hyphen = dicFR.inserted(palavra_hyphen)
    banco.write(palavra_hyphen)
done = True
banco.close


