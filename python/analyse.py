import sqlite3
import pandas as pd


conn = sqlite3.connect("/var/tmp/pidtune.db")
df1 = pd.read_sql_query("SELECT * FROM Pose", conn)
df2 = pd.read_sql_query("SELECT * FROM PIDParam", conn)
df3 = df1.merge(df2, on='timestamp',how='inner')
print(df3)