import tkinter as tk
from tkinter import messagebox
import subprocess

# Function to add a student by calling the C program
def add_student():
    student_id = entry_id.get()
    name = entry_name.get()
    age = entry_age.get()
    grade = entry_grade.get()

    if not student_id or not name or not age or not grade:
        messagebox.showerror("Error", "Please fill in all fields.")
        return

    try:
        result = subprocess.run(
            ["./school_management", "addStudent", student_id, name, age, grade],
            capture_output=True, text=True
        )
        messagebox.showinfo("Success", result.stdout)
    except Exception as e:
        messagebox.showerror("Error", f"Error: {e}")

# Function to display all students in a new window
def display_students():
    try:
        result = subprocess.run(
            ["./school_management", "displayStudents"],
            capture_output=True, text=True
        )
        # Create a new window to display the results
        result_window = tk.Toplevel(root)
        result_window.title("Student List")
        result_window.geometry("500x400")

        # Create a Listbox to show the result
        listbox = tk.Listbox(result_window, height=15, width=60, font=("Arial", 12), bg="#ffffff")
        listbox.pack(padx=20, pady=20)

        # Insert the result in the listbox
        students = result.stdout.splitlines()
        for student in students:
            listbox.insert(tk.END, student)
    except Exception as e:
        messagebox.showerror("Error", f"Error: {e}")

# Function to search a student by ID in a new window
def search_student():
    student_id = entry_search_id.get()

    if not student_id:
        messagebox.showerror("Error", "Please enter a student ID.")
        return

    try:
        result = subprocess.run(
            ["./school_management", "searchStudent", student_id],
            capture_output=True, text=True
        )
        # Create a new window to display the search result
        result_window = tk.Toplevel(root)
        result_window.title("Search Result")
        result_window.geometry("500x200")

        # Display the result in a label
        label = tk.Label(result_window, text=result.stdout, font=("Arial", 12), justify="left")
        label.pack(padx=20, pady=20)
    except Exception as e:
        messagebox.showerror("Error", f"Error: {e}")

# Create the main window
root = tk.Tk()
root.title("School Management System")
root.geometry("600x500")
root.configure(bg="#f0f0f0")

# Add a logo or header image (optional)
header = tk.Label(root, text="School Management System", font=("Arial", 20, "bold"), bg="#f0f0f0", fg="#4CAF50")
header.pack(pady=20)

# Create and pack widgets for the main interface
frame = tk.Frame(root, bg="#f0f0f0")
frame.pack(padx=20, pady=20)

# Add Student Section
tk.Label(frame, text="Student ID:", font=("Arial", 12), bg="#f0f0f0").grid(row=0, column=0, pady=5)
entry_id = tk.Entry(frame, font=("Arial", 12))
entry_id.grid(row=0, column=1, pady=5)

tk.Label(frame, text="Name:", font=("Arial", 12), bg="#f0f0f0").grid(row=1, column=0, pady=5)
entry_name = tk.Entry(frame, font=("Arial", 12))
entry_name.grid(row=1, column=1, pady=5)

tk.Label(frame, text="Age:", font=("Arial", 12), bg="#f0f0f0").grid(row=2, column=0, pady=5)
entry_age = tk.Entry(frame, font=("Arial", 12))
entry_age.grid(row=2, column=1, pady=5)

tk.Label(frame, text="Grade:", font=("Arial", 12), bg="#f0f0f0").grid(row=3, column=0, pady=5)
entry_grade = tk.Entry(frame, font=("Arial", 12))
entry_grade.grid(row=3, column=1, pady=5)

btn_add = tk.Button(frame, text="Add Student", command=add_student, font=("Arial", 12), bg="#4CAF50", fg="white", relief="raised", width=20)
btn_add.grid(row=4, columnspan=2, pady=10)

# Display Students Section
btn_display = tk.Button(frame, text="Display All Students", command=display_students, font=("Arial", 12), bg="#2196F3", fg="white", relief="raised", width=20)
btn_display.grid(row=5, columnspan=2, pady=10)

# Search Student Section
tk.Label(frame, text="Search by ID:", font=("Arial", 12), bg="#f0f0f0").grid(row=6, column=0, pady=5)
entry_search_id = tk.Entry(frame, font=("Arial", 12))
entry_search_id.grid(row=6, column=1, pady=5)

btn_search = tk.Button(frame, text="Search Student", command=search_student, font=("Arial", 12), bg="#FF5722", fg="white", relief="raised", width=20)
btn_search.grid(row=7, columnspan=2, pady=10)

# Run the Tkinter event loop
root.mainloop()
