import PySimpleGUI as sg # type: ignore
import subprocess
import os

def run_cpp_backend():
    #############
    # for this to work, COMPILE via "g++ main.cpp transactions.cpp -o out2" in terminal
    # should output a out2.exe file in directory
    #############
    try:

        env = os.environ
        # store output of c++ function
        result = subprocess.run("./out2", capture_output=True, env=env, text=True, check=True)

        return result.stdout  # This captures the standard output from the C++ program, which should be formatted correctly
    except subprocess.CalledProcessError as e:
        print(f"Error running C++ backend: {e}")
        return "Error occurred during processing."

def parse_time(output):
    time_info = {'Merge': 'N/A', 'Quick': 'N/A'}

    merge_time_start = output.find("Time to merge sort by")
    if merge_time_start != -1:
        merge_time_start = output.find(":", merge_time_start) + 1
        merge_time_end = output.find("milliseconds", merge_time_start)
        time_info['Merge'] = output[merge_time_start:merge_time_end].strip() + " ms"

    quick_time_start = output.find("Time to quick sort by")
    if quick_time_start != -1:
        quick_time_start = output.find(":", quick_time_start) + 1
        quick_time_end = output.find("milliseconds", quick_time_start)
        time_info['Quick'] = output[quick_time_start:quick_time_end].strip() + " ms"

    return time_info


def parse_output(output, method):
    results = {}

    if "Merge Sorted by Account Age" in output:
        start = output.find("Merge Sorted by Account Age")
        end = output.find("Merge Sorted by Transaction Amount", start)
        results['Age'] = output[start:end].strip()

    if "Merge Sorted by Transaction Amount" in output:
        start = output.find("Merge Sorted by Transaction Amount")
        end = output.find("Quick Sorted by Account Age", start)
        results['Amount'] = output[start:end].strip()

    if "Quick Sorted by Account Age" in output:
        start = output.find("Quick Sorted by Account Age")
        end = output.find("Quick Sorted by Transaction Amount", start) if "Quick Sorted by Transaction Amount" in output else len(output)
        results['Quick_Age'] = output[start:end].strip()

    if "Quick Sorted by Account Amount" in output:
        start = output.find("Quick Sorted by Transaction Amount")
        end = output.find("Statistics of Fraudulent Transactions", start) if "Statistics of Fraudulent Transactions" in output else len(output)
        results['Quick_Amount'] = output[start:end].strip()

    if "Statistics of Fraudulent Transactions" in output:
        start = output.find("Statistics of Fraudulent Transactions")
        end = len(output)
        results['Fraud Stats'] = output[start:end].strip()

    return results.get(method, "No valid output available")

def create_main_window():
    background_color = '#FDBAC5'  
    text_background_color = '#FF0000' 
    title_font = ('Comic Sans MS', 24, 'bold') 
    text_font = ('Calibri', 14) 
    dropdown_options = ['Age', 'Amount', 'Fraud Stats']

    layout = [
        [sg.Text('Bogus Buster: Is it Fraudulent?', font=title_font, justification='center', background_color=background_color, size=(25, 1))],
        [
            sg.Column([
                [sg.Text('Select Analysis Method:', font=text_font, justification='left', background_color=text_background_color)],
                [sg.Combo(dropdown_options, default_value='Age', size=(20, 1), font=text_font, pad=(0, 5), key='-METHOD-')],
                [sg.Button('Run Analysis', font=text_font)],
                [sg.Text('Output:', font=text_font, justification='left', background_color=text_background_color)],
                [sg.Multiline(default_text='', size=(45, 10), key='-OUTPUT-', disabled=True, background_color='#FFFFFF')],
            ], background_color=background_color, pad=((10, 10), (10, 10)))
        ],
        [sg.Text('Merge Sort Time:', font=text_font, justification='left', background_color=text_background_color)],
        [sg.InputText(default_text='0 ms', key='-MERGE_TIME-', disabled=True, justification='center', size=(20, 1), font=text_font)],
        [sg.Text('Quick Sort Time:', font=text_font, justification='left', background_color=text_background_color)],
        [sg.InputText(default_text='0 ms', key='-QUICK_TIME-', disabled=True, justification='center', size=(20, 1), font=text_font)],
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
            method = values['-METHOD-']
            output = run_cpp_backend() 
            parsed_output = parse_output(output, method)
            if method == 'Age' or method == 'Amount':
                time_info = parse_time(output)
            main_window['-OUTPUT-'].update(parsed_output)
            if 'Merge' in time_info:
                main_window['-MERGE_TIME-'].update(time_info['Merge'])
            if 'Quick' in time_info:
                main_window['-QUICK_TIME-'].update(time_info['Quick'])
        if event == 'Restart':
            main_window.close()
            main_window = create_main_window()
    main_window.close()
w
def create_welcome_window():
    pastel_pink = '#FDBAC5' 
    welcome_font = ('Comic Sans MS', 24, 'bold')
    layout = [
        [sg.Text('Welcome to Bogus Buster!', justification='center', size=(30, 2), background_color=pastel_pink, font=welcome_font, pad=(0,0))],
        [sg.Button('Start', size=(10, 2), font=('Calibri', 14), button_color=('white', '#E94196'), pad=(0,20))]
    ]
    return sg.Window('Welcome to Bogus Buster', layout, background_color=pastel_pink, size=(700, 700), element_justification='c')

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

if __name__ == '__main__':
    main()
