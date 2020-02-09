import subprocess
import time
process = subprocess.Popen([r"cmd"])

def strip_end(text, suffix):
    if not text.endswith(suffix):
        return text
    return text[:len(text)-len(suffix)]

def nome():
    sub = subprocess.Popen([r"./geraNome.exe"])
    arquivo = open("nomeGerado.txt", "r", encoding = "utf-8")
    novoNome = ""
    for line in arquivo:
        novoNome += line
        novoNome = strip_end(novoNome, "\n")
        novoNome += " "
        
    arquivo.close
    process.terminate()
    return novoNome.title()

