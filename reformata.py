import random
import titulo

def corta_do_fim(texto, sufixo):
    if not texto.endswith(sufixo):
        return texto
    return texto[:len(texto)-len(sufixo)]
def corta_do_comeco(texto, suffixo):
    if not text.startswith(sufixo):
        return texto
    return text[len(texto)-len(sufixo):]

#Conversão de minusculas para maiúsculas
dicionario = {"à":"À", "á":"Á", "â":"Â", "ã":"Ã", "ç":"Ç",
              "è":"È", "é":"É", "ê":"Ê", "ì":"Ì", "í":"Í",
              "î":"Î", "ñ":"Ñ", "ò":"Ò", "ó":"Ó", "ô":"Ô",
              "õ":"Õ", "ù":"Ù", "ú":"Ú", "û":"Û"}

def maiuscularComeco(texto):
    comeco = texto[0:1]
    ehEspecial = False
    for especial in dicionario:
        if comeco == especial:
            comeco = dicionario[especial]
            ehEspecial = True
    if not ehEspecial:
        comeco = comeco.upper()
    return comeco + texto[1:]



arquivo = open("nomeGerado.txt", "r", encoding="utf-8")

nomeCompleto = ""
for line in arquivo:
    nomeCompleto += line
    nomeCompleto = corta_do_fim(nomeCompleto, "\n")
    nomeCompleto = maiuscularComeco(nomeCompleto)
    nomeCompleto += " "
nomeCompleto = corta_do_comeco(nomeCompleto,"\n")   


print(nomeCompleto)
poema = []
arquivo = open("poema.txt", 'r', encoding = "utf-8")
            
for linha in arquivo:
    linha = maiuscularComeco(linha)
    poema.append(linha)

arquivo.close
tituloFeito = titulo.titulo()

arquivo = open("PoemaFormatado.txt", 'w', encoding = "utf-8")
arquivo.write(tituloFeito + "\n\n")

for verso in poema:
    arquivo.write(verso)
arquivo.write(nomeCompleto)
arquivo.close
