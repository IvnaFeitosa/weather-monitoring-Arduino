import serial
porta = "COM4"
baud = 9600
arquivo = "meteorologia.csv"

ser = serial.Serial(porta,baud)
ser.flushInput()
print("Abrindo Serial")

amostra = 4
linha = 1
while linha <= amostra:
    
    file = open(arquivo,"a")
    medida = str(ser.readline().decode("utf-8"))
    print(medida)
    file.write(medida + ";")
    linha = linha+1
print("Final de leituras")
file.close()
ser.close()