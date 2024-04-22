import PySimpleGUI as sg # type: ignore
import subprocess
import os

def run_cpp_backend(sort_method):
    try:
        # Execute the C++ backend with the selected sorting method

        # create pipe for c++ function processing
        #data,temp = os.pipe()

        # add sort method as input for function
        #os.write(temp, bytes(sort_method + "\n", "utf-8"))
        #os.close(temp)
        
        # adjust input params to match what c++ wants
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


def create_main_window():
    background_color = '#FDBAC5'  # Barbie pink for the window background
    text_background_color = '#FF0000'  # Pastel pink for text background sections
    title_font = ('Comic Sans MS', 24, 'bold')  # Updated font and style for title
    text_font = ('Calibri', 14)  # Updated font for text
    dropdown_options = ['Merge Sort', 'Quick Sort']

    layout = [
        [sg.Text('Bogus Buster: Is it Fraudulent?', font=title_font, justification='center', background_color=background_color, size=(25, 1))],
        [
            sg.Column([
                [sg.Text('Select Algorithm:', font=text_font, justification='left', background_color=text_background_color)],
                [sg.Combo(dropdown_options, default_value='Merge Sort', size=(20, 1), font=text_font, pad=(0, 5), key='-ALGO-')],
                [sg.Button('Run Analysis', font=text_font)],
                [sg.Text('Top 10 Transactions:', font=text_font, justification='left', background_color=text_background_color)],
                [sg.Multiline(default_text='', size=(45, 5), key='-TOP_TRANS-', disabled=True, background_color='#FFFFFF')]
            ], background_color=background_color, pad=((10, 10), (10, 10)))
        ],
        [sg.Button('Restart', size=(10, 2), font=('Calibri', 12), button_color=('white', '#FF0000'))]
    ]
    return sg.Window('Bogus Buster', layout, background_color=background_color, size=(700, 700), element_justification='c')

def window_operations():
    main_window = create_main_window()
    while True:
        event, values = main_window.read()
        if event == sg.WINDOW_CLOSED:
            break
        if event == 'Restart':
            main_window.close()
            main_window = create_main_window()  # Restarting the application window
        if event == 'Run Analysis':
            output = run_cpp_backend(values['-ALGO-'])
            print(output)
            # Update the multiline text element with only the required data from the output
            main_window['-TOP_TRANS-'].update(output if output else "No output or an error occurred")

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
