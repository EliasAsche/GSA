import PySimpleGUI as sg # type: ignore
import subprocess
import os

def run_cpp_backend(sort_method):
    try:
        if sort_method == 'Merge Sort':
            sort_method = 'merge'
        else:
            sort_method = 'quick'

        env = os.environ
        data,tmp = os.pipe()
        os.write(tmp, bytes(sort_method + "\n", "utf-8"))
        os.close(tmp)

        # store output of c++ function
        result = subprocess.run("./out2", stdin=data, capture_output=True, env=env, text=True, check=True)

        # result = subprocess.run(['./main.cpp', sort_method], capture_output=True, text=True, check=True)
        return result.stdout  # This captures the standard output from the C++ program, which should be formatted correctly
    except subprocess.CalledProcessError as e:
        print(f"Error running C++ backend: {e}")
        return "Error occurred during processing."

def parse_output(output, method):
    lines = output.split('\n')
    if method == 'Merge Sort':
        transactions = [line for line in lines if "Transaction Type" in line]
        time = next((line for line in lines if "Merge Time" in line), "Time not found")
        return transactions, time
    elif method == 'Quick Sort':
        transactions = [line for line in lines if "Transaction Type" in line]
        time = next((line for line in lines if "Quick Time" in line), "Time not found")
        return transactions, time
    elif method == 'Stats':
        stats = [line for line in lines if "Total" in line or "Average" in line]
        return stats
    else:
        return "Invalid method selected"


def create_main_window():
    background_color = '#FDBAC5'  # Barbie pink for the window background
    text_background_color = '#FF0000'  # Pastel pink for text background sections
    title_font = ('Comic Sans MS', 24, 'bold')  # Updated font and style for title
    text_font = ('Calibri', 14)  # Updated font for text
    # sort_options = ['age', 'amount']  # Options for sorting
    dropdown_options = ['Merge Sort', 'Quick Sort', 'Stats']

    layout = [
        [sg.Text('Bogus Buster: Is it Fraudulent?', font=title_font, justification='center', background_color=background_color, size=(25, 1))],
        [
            sg.Column([
                # [sg.Text('Select Sort Field:', font=text_font, justification='left', background_color=text_background_color)],
                # [sg.Combo(sort_options, default_value='age', size=(20, 1), font=text_font, pad=(0, 5), key='-SORT_FIELD-')],
                [sg.Text('Select Analysis Method:', font=text_font, justification='left', background_color=text_background_color)],
                [sg.Combo(dropdown_options, default_value='Merge Sort', size=(20, 1), font=text_font, pad=(0, 5), key='-METHOD-')],
                [sg.Button('Run Analysis', font=text_font)],
                [sg.Text('Output:', font=text_font, justification='left', background_color=text_background_color)],
                [sg.Multiline(default_text='', size=(45, 10), key='-OUTPUT-', disabled=True, background_color='#FFFFFF')],
            ], background_color=background_color, pad=((10, 10), (10, 10)))
        ],
        [sg.Text('Execution Time:', font=text_font, justification='left', background_color=text_background_color)],
        [sg.InputText(default_text='0 ms', key='-EXEC_TIME-', disabled=True, justification='center', size=(20, 1), font=text_font)],
        [sg.Button('Restart', size=(10, 2), font=('Calibri', 12), button_color=('white', '#FF0000'))]
    ]
    return sg.Window('Bogus Buster', layout, background_color=background_color, size=(700, 700), element_justification='c')


def window_operations():
    main_window = create_main_window()
    while True:
        event, values = main_window.read()
        if event == sg.WINDOW_CLOSED:
            break
        if event == 'Run Analysis':
            file_path = values['-FILE_PATH-']
            # sort_field = values['-SORT_FIELD-']
            method = values['-METHOD-']
            output = run_cpp_backend(file_path)
            parsed_data, time_info = parse_output(output, method)
            if method in ['Merge', 'Quick']:
                main_window['-TRANSACTIONS-'].update("\n".join(parsed_data))
                main_window['-TIME-'].update(time_info)
            elif method == 'Stats':
                main_window['-STATS-'].update("\n".join(parsed_data))
            else:
                main_window['-OUTPUT-'].update("No valid output available")

    main_window.close()



# Function to create the welcome window
def create_welcome_window():
    pastel_pink = '#FDBAC5'  # Pastel pink for the welcome window background
    welcome_font = ('Comic Sans MS', 24, 'bold')  # Updated font, size, and bold for the welcome text
    layout = [
        [sg.Text('Welcome to Bogus Buster!', justification='center', size=(30, 2), background_color=pastel_pink, font=welcome_font, pad=(0,0))],
        [sg.Button('Start', size=(10, 2), font=('Calibri', 14), button_color=('white', '#E94196'), pad=(0,20))]
    ]
    return sg.Window('Welcome to Bogus Buster', layout, background_color=pastel_pink, size=(700, 700), element_justification='c')

# Main execution loop
def main():
    welcome_window = create_welcome_window()
    while True:
        event, values = welcome_window.read()
        if event == sg.WINDOW_CLOSED:
            break
        if event == 'Start':
            welcome_window.close()
            window_operations()
            break
    welcome_window.close()

# Run the main function to start the application
if __name__ == '__main__':
    main()
