from flask import Flask, render_template, request, jsonify
import subprocess

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/run_cpp_program', methods=['GET'])
def run_cpp_program():
    command = request.args.get('command')
    try:
        output = subprocess.check_output(command, shell=True, text=True, stderr=subprocess.STDOUT)
        return jsonify({'output': output.strip()})
    except subprocess.CalledProcessError as e:
        return jsonify({'output': f'Error: {e.output.strip()}'})

if __name__ == '__main__':
    app.run(debug=True)
