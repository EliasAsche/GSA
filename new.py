import PySimpleGUI as sg

def create_column_layout():
    text_font = ('Helvetica', 12)
    background_color = '#FDBAC5'
    text_background_color = '#FFC0CB'
    dropdown_options = ['Merge Sort', 'Quick Sort']

    return [
        [sg.Text('Choose Sorting Method:', font=text_font, background_color=text_background_color)],
        [sg.Combo(dropdown_options, default_value=dropdown_options[0], size=(20, 1), font=text_font, pad=(0, 5), key='-SORTING-')],
        [sg.Text(' ', size=(20, 1), relief=sg.RELIEF_SUNKEN, key='-INFO-', background_color='white', pad=(0, 5))],
        [sg.Text('Runtime Information:', font=text_font, background_color=text_background_color)],
        [sg.Text('No data yet', size=(20, 1), relief=sg.RELIEF_SUNKEN, key='-RUNTIME-', background_color='white')]
    ]

def create_main_window():
    title_font = ('Helvetica', 20, 'bold')
    background_color = '#FDBAC5'

    left_column = create_column_layout()
    right_column = create_column_layout()

    layout = [
        [sg.Text('Bogus Buster: Sorting Options', font=title_font, justification='center', background_color=background_color)],
        [
            sg.Column(left_column, background_color=background_color, pad=(10, 10)),
            sg.VSeparator(),
            sg.Column(right_column, background_color=background_color, pad=(10, 10))
        ],
        [sg.Button('[as]', font=('Helvetica', 12), button_color=('white', 'red'), pad=(10, 10))]
    ]

    return sg.Window('Bogus Buster GUI', layout, background_color=background_color, size=(600, 300))

def create_welcome_window():
    pastel_pink = '#FDBAC5'
    welcome_font = ('Comic Sans MS', 24, 'bold')
    layout = [
        [sg.Text('Welcome to Bogus Buster!', justification='center', size=(30, 2), background_color=pastel_pink, font=welcome_font, pad=(0,0))],
        [sg.Button('Start', size=(10, 2), font=('Calibri', 14), button_color=('white', '#E94196'), pad=(0,20))]
    ]
    return sg.Window('[as]', layout, background_color=pastel_pink, size=(700, 200), element_justification='c')

def main():
    welcome_window = create_welcome_window()
    main_window = None

    while True:
        if welcome_window is not None:
            event, values = welcome_window.read(timeout=100)
            if event == sg.WINDOW_CLOSED:
                break
            if event == 'Start':
                welcome_window.hide()
                if main_window is None:
                    main_window = create_main_window()
        if main_window is not None:
            event, values = main_window.read(timeout=100)
            if event == sg.WINDOW_CLOSED:
                break
            if event == 'Restart':
                main_window.close()
                main_window = create_main_window()

    if welcome_window:
        welcome_window.close()
    if main_window:
        main_window.close()

if __name__ == '__main__':
    main()
