import sqlite3
import pandas as pd


conn = sqlite3.connect("./data/data.db")
df = pd.read_sql_query("SELECT * FROM runs", conn)

print(df)