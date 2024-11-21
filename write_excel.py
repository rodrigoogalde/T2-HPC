import pandas as pd
import matplotlib.pyplot as plt
import re

def convert_to_decimal(time_str):
    match = re.match(r"(\d+)m(\d+\.\d+)s", time_str)
    if match:
        minutes = int(match.group(1))
        seconds = float(match.group(2))
        return minutes*60 + seconds#/ 60
    else:
        return None

def txt_to_excel(txt_file, excel_file):
    hilos = []
    real_times = []
    user_times = []
    sys_times = []

    try:
        with open(txt_file, 'r') as f:
            lines = f.readlines()

            real_time = ""
            user_time = ""
            sys_time = ""
            hilos_count = 0

            for line in lines:
                if "Fue ejecutado con" in line:
                    hilos_count = int(line.split()[3])  
                    hilos.append(hilos_count)  

                if line.startswith("real"):
                    real_time = line.split("\t")[1].strip()  
                    real_times.append(convert_to_decimal(real_time))

                elif line.startswith("user"):
                    user_time = line.split("\t")[1].strip() 
                    user_times.append(convert_to_decimal(user_time))  

                elif line.startswith("sys"):
                    sys_time = line.split("\t")[1].strip()  
                    sys_times.append(convert_to_decimal(sys_time)) 

        # Crear un DataFrame de pandas con los datos
        data = {
            'Hilos': hilos,
            'Real': real_times,
            'User': user_times,
            'Sys': sys_times
        }
        df = pd.DataFrame(data)

        df.to_excel(excel_file, index=False, engine='openpyxl')

        print(f"Archivo Excel guardado en: {excel_file}")

    except Exception as e:
        print(f"Error al procesar el archivo: {e}")

def generate_grafics(excel_file, folder):
    df = pd.read_excel(excel_file)

    # Crear un gráfico de 'Real', 'User' y 'Sys' contra 'Hilos'
    plt.figure(figsize=(8, 6))

    # Graficar cada columna
    plt.plot(df['Hilos'], df['Real'], label='Real', marker='o')
    plt.plot(df['Hilos'], df['User'], label='User', marker='o')
    plt.plot(df['Hilos'], df['Sys'], label='Sys', marker='o')

    # Añadir títulos y etiquetas
    plt.title('Tiempo de Ejecución por Cantidad de Hilos')
    plt.xlabel('Número de Hilos')
    plt.ylabel('Tiempo (segundos)')
    plt.legend()

    # Guardar el gráfico como PDF
    plt.savefig(f'{folder}/grafico_tiempos.pdf', format='pdf')

    # Mostrar el gráfico
    plt.show()

txt_file = 'data/txt/time.txt'  
excel_file = 'data/xlsx/resultado.xlsx' 
folder = 'data/grafics/' 

txt_to_excel(txt_file, excel_file)
generate_grafics(excel_file, folder)
