import serial
import csv
import pandas as pd
import openpyxl

porta = "COM4"
baud = 9600
arquivo = "meteorologia.csv"

ser = serial.Serial(porta, baud)
ser.flushInput()
print("Abrindo Serial")

amostra = 16
linha = 1

# Crie uma lista para armazenar as medidas
medidas = []

while linha <= amostra:
    medida = str(ser.readline().decode("utf-8")).strip()  # Remove espaços em branco
    print(medida)
    
    # Adicione a medida à lista de medidas
    medidas.append(medida)
    
    linha = linha + 1

# Abra o arquivo CSV em modo de escrita e escreva as medidas em células diferentes na mesma linha
with open(arquivo, "a", newline="") as file:
    writer = csv.writer(file, delimiter=',')
    writer.writerow(medidas)

print("Final de leituras")
ser.close()

# Ler o arquivo CSV em um DataFrame
arquivo_csv = "meteorologia.csv"
nomes_colunas = ["temperatura", "altitude", "uv", "pressao"]
df = pd.read_csv(arquivo_csv, names=nomes_colunas)

# Nome do arquivo XLSX de saída
arquivo_xlsx = "meteorologia.xlsx"

# Salvar o DataFrame em um arquivo XLSX
df.to_excel(arquivo_xlsx, index=False)

print(f"O arquivo CSV '{arquivo_csv}' foi convertido para XLSX e salvo como '{arquivo_xlsx}'.")
