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

        return result.stdout  # captures the output from the C++ backend program, in the formatted file
    except subprocess.CalledProcessError as e:
        print(f"Error running C++ backend: {e}")
        return "Error occurred during processing."

def parse_time(output):
    time_info = {
        'Merge_Age': 'N/A', 
        'Quick_Age': 'N/A',
        'Merge_Amount': 'N/A', 
        'Quick_Amount': 'N/A'
    }

    # Parsing Merge Sort time by account age
    merge_age_start = output.find("Time to merge sort by account age:")
    if merge_age_start != -1:
        merge_age_start += len("Time to merge sort by account age:")
        merge_age_end = output.find("milliseconds", merge_age_start)
        time_info['Merge_Age'] = output[merge_age_start:merge_age_end].strip() + " ms"

    # Parsing Quick Sort time by account age
    quick_age_start = output.find("Time to quick sort by account age:")
    if quick_age_start != -1:
        quick_age_start += len("Time to quick sort by account age:")
        quick_age_end = output.find("milliseconds", quick_age_start)
        time_info['Quick_Age'] = output[quick_age_start:quick_age_end].strip() + " ms"

    # Parsing Merge Sort time by transaction amount
    merge_amount_start = output.find("Time to merge sort by transaction amount:")
    if merge_amount_start != -1:
        merge_amount_start += len("Time to merge sort by transaction amount:")
        merge_amount_end = output.find("milliseconds", merge_amount_start)
        time_info['Merge_Amount'] = output[merge_amount_start:merge_amount_end].strip() + " ms"

    # Parsing Quick Sort time by transaction amount
    quick_amount_start = output.find("Time to quick sort by transaction amount:")
    if quick_amount_start != -1:
        quick_amount_start += len("Time to quick sort by transaction amount:")
        quick_amount_end = output.find("milliseconds", quick_amount_start)
        time_info['Quick_Amount'] = output[quick_amount_start:quick_amount_end].strip() + " ms"

    return time_info


# funciton to parse through the rest of the data in the output
def parse_output(output, method):
    # intitialize empty results dictionary
    results = {}
    # merge sorting by age option
    if "Merge Sorted by Account Age" in output:
        start = output.find("Merge Sorted by Account Age")
        end = output.find("Merge Sorted by Transaction Amount", start)
        # add the entire output text block for merge
        results['Age'] = output[start:end].strip()

    # merge sorting by transaction option
    if "Merge Sorted by Transaction Amount" in output:
        start = output.find("Merge Sorted by Transaction Amount")
        end = output.find("Quick Sorted by Account Age", start)
        # add the entire output text block for merge
        results['Amount'] = output[start:end].strip()

    # quick sorting by age option
    if "Quick Sorted by Account Age" in output:
        start = output.find("Quick Sorted by Account Age")
        end = output.find("Quick Sorted by Transaction Amount", start)
        # add the entire output text block for quick
        results['Quick_Age'] = output[start:end].strip()

    # quick sorting by transaction amount option
    if "Quick Sorted by Transaction Amount" in output:
        start = output.find("Quick Sorted by Transaction Amount")
        end = output.find("Statistics of Fraudulent Transactions", start)
        # add the entire output text block for quick
        results['Quick_Amount'] = output[start:end].strip()

    # stats of averages for data option
    if "Statistics of Fraudulent Transactions" in output:
        start = output.find("Statistics of Fraudulent Transactions")
        end = len(output)
        # add the stats paragraph
        results['Fraud Stats'] = output[start:end].strip()
    

    return results.get(method, "No valid output available")

# function to create programs main window
def create_main_window():
    background_color = '#FDBAC5'  #pastel pink
    text_background_color = '#FF0000' #red
    title_font = ('Comic Sans MS', 24, 'bold') 
    text_font = ('Calibri', 14) 
    dropdown_options = ['Age', 'Amount', 'Fraud Stats']
    # drop down menu initialization 

    # layout using PySimpleGUI standard syntax
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
        [sg.Text('Merge Sort Time (Age):', font=text_font, justification='left', background_color=text_background_color)],
        [sg.InputText(default_text='0 ms', key='-MERGE_AGE_TIME-', disabled=True, justification='center', size=(20, 1), font=text_font)],
        [sg.Text('Quick Sort Time (Age):', font=text_font, justification='left', background_color=text_background_color)],
        [sg.InputText(default_text='0 ms', key='-QUICK_AGE_TIME-', disabled=True, justification='center', size=(20, 1), font=text_font)],
        [sg.Text('Merge Sort Time (Amount):', font=text_font, justification='left', background_color=text_background_color)],
        [sg.InputText(default_text='0 ms', key='-MERGE_AMOUNT_TIME-', disabled=True, justification='center', size=(20, 1), font=text_font)],
        [sg.Text('Quick Sort Time (Amount):', font=text_font, justification='left', background_color=text_background_color)],
        [sg.InputText(default_text='0 ms', key='-QUICK_AMOUNT_TIME-', disabled=True, justification='center', size=(20, 1), font=text_font)],
        [sg.Button('Restart', size=(10, 2), font=('Calibri', 12), button_color=('white', '#FF0000'))]
    ]
    return sg.Window('Bogus Buster', layout, background_color=background_color, size=(700, 700), element_justification='c')

# function to perform the window operations and events and implement the backend into the UI
def window_operations():
    main_window = create_main_window()
    while True:
        event, values = main_window.read()
        # closing window
        if event == sg.WINDOW_CLOSED:
            break
        # running sorting analysis
        if event == 'Run Analysis':
            method = values['-METHOD-']
            # getting output from the C++ backend code
            output = run_cpp_backend() 
            parsed_output = parse_output(output, method)
            # getting time info if necessary
            if method == 'Age' or method == 'Amount':
                time_info = parse_time(output)
            # update window
            main_window['-OUTPUT-'].update(parsed_output)
            # display calculated runtime
            # Example snippet to update the GUI with these times
            if 'Merge_Age' in time_info:
                main_window['-MERGE_AGE_TIME-'].update(time_info['Merge_Age'])
            if 'Quick_Age' in time_info:
                main_window['-QUICK_AGE_TIME-'].update(time_info['Quick_Age'])
            if 'Merge_Amount' in time_info:
                main_window['-MERGE_AMOUNT_TIME-'].update(time_info['Merge_Amount'])
            if 'Quick_Amount' in time_info:
                main_window['-QUICK_AMOUNT_TIME-'].update(time_info['Quick_Amount'])

        # restart button to restart analysis
        if event == 'Restart':
            main_window.close()
            main_window = create_main_window()
    main_window.close()

# function to create the welcome window
def create_welcome_window():
    pastel_pink = '#FDBAC5' 
    welcome_font = ('Comic Sans MS', 24, 'bold')
    # basic PySimpleGUI layout structure
    layout = [
        [sg.Text('Welcome to Bogus Buster!', justification='center', size=(30, 2), background_color=pastel_pink, font=welcome_font, pad=(0,0))],
        [sg.Button('Start', size=(10, 2), font=('Calibri', 14), button_color=('white', '#E94196'), pad=(0,20))]
    ]
    return sg.Window('Welcome to Bogus Buster', layout, background_color=pastel_pink, size=(700, 700), element_justification='c')

# main function to run program with front and back end connected
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
