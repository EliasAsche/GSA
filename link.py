import pandas as pd

if __name__ == '__main__':
    #loading in the csv file from the path
    df = pd.read_csv(r"C:\Users\myakh\PycharmProjects\DSA Project 3\Fraudulent_E-Commerce_Transaction_Data.csv")

    #selecting the columns by index
    #they are indexed as one less than the actual column number
    selected_columns = df.iloc[:, [2, 4, 13, 14]]

    #displaying the isolated/separated columns
    print(selected_columns)

    #writing the columns to a new txt file
    selected_columns.to_csv(r"C:\Users\myakh\PycharmProjects\DSA Project 3\new commerce data.txt", index=False)
