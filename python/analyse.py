import sqlite3
import pandas as pd


conn = sqlite3.connect("../pidtime.db")
df = pd.read_sql_query("SELECT * FROM Pose", conn)
print(df)
df = pd.read_sql_query("SELECT * FROM PIDParam", conn)
print(df)