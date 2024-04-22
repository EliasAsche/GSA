import PySimpleGUI as sg

# Function to create the main application window
def create_main_window():
    background_color = '#FDBAC5' # Barbie pink for the window background
    text_background_color = '#FF0000'  # Pastel pink for text background sections
    title_font = ('Comic Sans MS', 24, 'bold')  # Updated font and style for title
    text_font = ('Calibri', 14)  # Updated font for text
    dropdown_options = ['Merge Sort', 'Quick Sort']

    layout = [
        [sg.Text('Bogus Buster: Is it Fraudulent?', font=title_font, justification='center', background_color=background_color, size=(25, 1))],
        [
            sg.Column([
                [sg.Text('Dropdown Menu:', font=text_font, justification='left', background_color=text_background_color)],
                [sg.Combo(dropdown_options, size=(20, 1), font=text_font, pad=(0, 5))],
                [sg.Text(' ', size=(50, 20), relief=sg.RELIEF_SUNKEN, key='-INFO-', background_color='#FFFFFF', pad=(0, 5))],
                [sg.Text('Runtime Info:', font=text_font, justification='left', background_color=text_background_color)],
                [sg.Text('Data about runtime', size=(50, 3), relief=sg.RELIEF_SUNKEN, key='-RUNTIME-', background_color='#FFFFFF')]
            ], background_color=background_color, pad=((10, 10), (10, 10)))
        ],
        [sg.Button('Restart', size=(10, 2), font=('Calibri', 12, ), button_color=('white', '#FF0000'))]
    ]
    return sg.Window('Bogus Buster', layout, background_color=background_color, size=(700, 700), element_justification='c')

# Function to handle window operations, including restart
def window_operations():
    main_window = create_main_window()
    while True:
        event, values = main_window.read()
        if event == sg.WINDOW_CLOSED:
            break
        if event == 'Restart':
            main_window.close()
            main_window = create_main_window()  # Restarting the application window
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
