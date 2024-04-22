import pandas as pd

if __name__ == '__main__':
    # Load the CSV file using a proper path format
    df = pd.read_csv(r"C:\Users\myakh\PycharmProjects\DSA Project 3\Fraudulent_E-Commerce_Transaction_Data.csv")

    # Select columns by their index (Python uses 0-based indexing)
    # Adjusting for 0-based index by using columns 2, 4, and 13 for 3, 5, and 14 respectively
    selected_columns = df.iloc[:, [2, 4, 13, 14]]

    # Display the selected columns
    print(selected_columns)

    # Write the selected columns to a new CSV file
    selected_columns.to_csv(r"C:\Users\myakh\PycharmProjects\DSA Project 3\new commerce data.txt", index=False)
