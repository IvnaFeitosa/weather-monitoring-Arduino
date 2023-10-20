from flask import Flask, request, jsonify
import csv

app = Flask(__name__)

# Create or open the CSV file
with open('sensor_data.csv', mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Timestamp', 'SensorValue', 'BMP180_Temperature', 'BMP180_Pressure', 'BMP180_Altitude'])  # Escreve o cabeçalho

@app.route('/sensor_data', methods=['POST'])
def receive_sensor_data():
    data = request.get_json()
    if 'sensorValue' in data and 'bmp180Data' in data:
        timestamp = data['timestamp']
        sensor_value = data['sensorValue']
        bmp180_data = data['bmp180Data']
        temperature = bmp180_data['temperature']
        pressure = bmp180_data['pressure']
        altitude = bmp180_data['altitude']

        # Append data to the CSV file
        with open('sensor_data.csv', mode='a', newline='') as file:
            writer = csv.writer(file)
            writer.writerow([timestamp, sensor_value, temperature, pressure, altitude])

        return "Data received and saved to CSV."
    else:
        return "Invalid data format."

if __name__ == '__main__':
    app.run(host='localhost', port=80)  # Altere o host e a porta conforme necessário
