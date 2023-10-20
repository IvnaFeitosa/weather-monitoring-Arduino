from flask import Flask, request
import csv

app = Flask(__name__)

# Create or open the CSV file
with open('sensor_data.csv', mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Timestamp', 'SensorValue'])  # Write header

@app.route('/sensor_data', methods=['POST'])
def receive_sensor_data():
    data = request.get_json()
    if 'sensorValue' in data:
        timestamp = data['timestamp']  # Add a timestamp if desired
        sensor_value = data['sensorValue']

        # Append data to the CSV file
        with open('sensor_data.csv', mode='a', newline='') as file:
            writer = csv.writer(file)
            writer.writerow([timestamp, sensor_value])

        return "Data received and saved to CSV."
    else:
        return "Invalid data format."

if __name__ == '__main__':
    app.run(host='localhost', port=80)  # Change host and port as needed
