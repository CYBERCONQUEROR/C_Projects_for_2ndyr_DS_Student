import ctypes
from tkinter import *

# Load the C library
# lib = ctypes.CDLL('./1.dll')
lib = ctypes.CDLL(r'C:\coding\DOWRY\1.dll')


# Define argument and return types
lib.calculate_min_dowry.argtypes = [ctypes.c_float, ctypes.c_float, ctypes.c_float]
lib.calculate_min_dowry.restype = ctypes.c_float

lib.calculate_max_dowry.argtypes = [ctypes.c_float, ctypes.c_float, ctypes.c_float]
lib.calculate_max_dowry.restype = ctypes.c_float

def calculate_dowry(minimum):
    salary = float(salary_entry.get())
    age = float(age_entry.get())
    net_worth = float(net_worth_entry.get())
    
    if minimum:
        result = lib.calculate_min_dowry(salary, age, net_worth)
    else:
        result = lib.calculate_max_dowry(salary, age, net_worth)
    
    result_label.config(text=f"Result: {result:.2f}")

# Set up the GUI
root = Tk()
root.title("Dowry Calculator")

Label(root, text="Monthly Salary:").pack()
salary_entry = Entry(root)
salary_entry.pack()

Label(root, text="Age:").pack()
age_entry = Entry(root)
age_entry.pack()

Label(root, text="Net Worth:").pack()
net_worth_entry = Entry(root)
net_worth_entry.pack()

Button(root, text="Calculate Min Dowry", command=lambda: calculate_dowry(True)).pack()
Button(root, text="Calculate Max Dowry", command=lambda: calculate_dowry(False)).pack()

result_label = Label(root, text="Result: ")
result_label.pack()

root.mainloop()
