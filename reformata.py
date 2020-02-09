import random
import nome
import titulo
num_sobrenomes = random.randint(1,3)
nomeCompleto = nome.nome()
print(nomeCompleto)
poema = []
arquivo = open("Poema.txt", 'r', encoding = "utf-8")
for linha in arquivo:
    poema.append(linha)
arquivo.close
tituloFeito = titulo.titulo()
arquivo = open("PoemaFormatado.txt", 'w', encoding = "utf-8")
arquivo.write(tituloFeito + "\n\n")
for verso in poema:
    arquivo.write(verso)
arquivo.write("\n\n"+nomeCompleto)
arquivo.close
