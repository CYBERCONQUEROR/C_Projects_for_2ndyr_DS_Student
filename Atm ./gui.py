import tkinter as tk
from tkinter import ttk, messagebox, simpledialog


class ATMApp:
    def __init__(self, root):
        self.root = root
        self.root.title("ATM System")
        self.root.geometry("500x500")
        self.root.configure(bg="#e6f7ff")  # Light blue background

        # User data placeholders
        self.name = ""
        self.address = ""
        self.age = 0
        self.phone = ""
        self.account_number = ""
        self.pin = ""
        self.balance = 5000.0

        # Display the welcome screen
        self.welcome_screen()

    def welcome_screen(self):
        """Screen to collect user details."""
        self.clear_screen()

        title_label = tk.Label(
            self.root, text="Welcome to ATM System", font=("Helvetica", 20, "bold"),
            bg="#e6f7ff", fg="#004d99"
        )
        title_label.pack(pady=20)

        instruction_label = tk.Label(
            self.root, text="Please fill in your details below to proceed.",
            font=("Helvetica", 12), bg="#e6f7ff", fg="#004d99"
        )
        instruction_label.pack(pady=10)

        form_frame = ttk.Frame(self.root, padding=20)
        form_frame.pack(pady=10)

        # Form Fields
        ttk.Label(form_frame, text="Name:").grid(row=0, column=0, sticky=tk.W, pady=5)
        self.entry_name = ttk.Entry(form_frame, width=30)
        self.entry_name.grid(row=0, column=1, pady=5)

        ttk.Label(form_frame, text="Address:").grid(row=1, column=0, sticky=tk.W, pady=5)
        self.entry_address = ttk.Entry(form_frame, width=30)
        self.entry_address.grid(row=1, column=1, pady=5)

        ttk.Label(form_frame, text="Age:").grid(row=2, column=0, sticky=tk.W, pady=5)
        self.entry_age = ttk.Entry(form_frame, width=30)
        self.entry_age.grid(row=2, column=1, pady=5)

        ttk.Label(form_frame, text="Phone No:").grid(row=3, column=0, sticky=tk.W, pady=5)
        self.entry_phone = ttk.Entry(form_frame, width=30)
        self.entry_phone.grid(row=3, column=1, pady=5)

        ttk.Label(form_frame, text="Account Number:").grid(row=4, column=0, sticky=tk.W, pady=5)
        self.entry_account = ttk.Entry(form_frame, width=30)
        self.entry_account.grid(row=4, column=1, pady=5)

        ttk.Label(form_frame, text="PIN:").grid(row=5, column=0, sticky=tk.W, pady=5)
        self.entry_pin = ttk.Entry(form_frame, show="*", width=30)
        self.entry_pin.grid(row=5, column=1, pady=5)

        submit_button = tk.Button(self.root, text="Submit", font=("Helvetica", 14, "bold"), bg="#004d99",
                                  fg="white", command=self.collect_user_details)
        submit_button.pack(pady=20)

    def collect_user_details(self):
        """Collect and validate user details."""
        self.name = self.entry_name.get()
        self.address = self.entry_address.get()
        try:
            self.age = int(self.entry_age.get())
            self.phone = self.entry_phone.get()
            self.account_number = self.entry_account.get()
            self.pin = self.entry_pin.get()
        except ValueError:
            messagebox.showerror("Error", "Age must be a number.")
            return

        if not all([self.name, self.address, self.age, self.phone, self.account_number, self.pin]):
            messagebox.showerror("Error", "All fields are required.")
            return

        self.login_screen()

    def login_screen(self):
        """Screen for login/logout options."""
        self.clear_screen()

        title_label = tk.Label(
            self.root, text="Login Screen", font=("Helvetica", 20, "bold"),
            bg="#e6f7ff", fg="#004d99"
        )
        title_label.pack(pady=20)

        ttk.Label(self.root, text="Choose an option:", font=("Helvetica", 14)).pack(pady=10)

        login_button = tk.Button(self.root, text="Login", font=("Helvetica", 14), bg="#004d99", fg="white",
                                 command=self.atm_menu_screen)
        login_button.pack(pady=10)

        logout_button = tk.Button(self.root, text="Logout", font=("Helvetica", 14), bg="#ff6666", fg="white",
                                  command=self.logout)
        logout_button.pack(pady=10)

    def atm_menu_screen(self):
        """ATM Menu screen."""
        self.clear_screen()

        title_label = tk.Label(
            self.root, text="ATM Menu", font=("Helvetica", 20, "bold"),
            bg="#e6f7ff", fg="#004d99"
        )
        title_label.pack(pady=20)

        ttk.Label(self.root, text="Choose an option:", font=("Helvetica", 14)).pack(pady=10)

        balance_button = tk.Button(self.root, text="Check Balance", font=("Helvetica", 14), bg="#004d99", fg="white",
                                   command=self.check_balance)
        balance_button.pack(pady=10)

        withdraw_button = tk.Button(self.root, text="Withdraw", font=("Helvetica", 14), bg="#004d99", fg="white",
                                    command=self.withdraw)
        withdraw_button.pack(pady=10)

        deposit_button = tk.Button(self.root, text="Deposit", font=("Helvetica", 14), bg="#004d99", fg="white",
                                   command=self.deposit)
        deposit_button.pack(pady=10)

        exit_button = tk.Button(self.root, text="Exit", font=("Helvetica", 14), bg="#ff6666", fg="white",
                                command=self.logout)
        exit_button.pack(pady=10)

    def check_balance(self):
        """Show current balance."""
        messagebox.showinfo("Balance", f"Your current balance is: {self.balance:.2f}")

    def withdraw(self):
        """Withdraw money."""
        amount = self.get_amount("Withdraw")
        if amount is None:
            return

        if amount > self.balance:
            messagebox.showerror("Error", "Insufficient balance.")
        else:
            self.balance -= amount
            messagebox.showinfo("Success", f"Withdrawal successful. New balance: {self.balance:.2f}")

    def deposit(self):
        """Deposit money."""
        amount = self.get_amount("Deposit")
        if amount is None:
            return

        self.balance += amount
        messagebox.showinfo("Success", f"Deposit successful. New balance: {self.balance:.2f}")

    def get_amount(self, action):
        """Prompt for an amount."""
        amount_str = simpledialog.askstring(action, f"Enter amount to {action.lower()}:")
        try:
            amount = float(amount_str)
            if amount <= 0:
                messagebox.showerror("Error", "Amount must be positive.")
                return None
            return amount
        except (ValueError, TypeError):
            messagebox.showerror("Error", "Invalid amount.")
            return None

    def logout(self):
        """Logout and return to the welcome screen."""
        messagebox.showinfo("Logout", "You have logged out successfully.")
        self.welcome_screen()

    def clear_screen(self):
        """Remove all widgets from the current screen."""
        for widget in self.root.winfo_children():
            widget.destroy()


# Run the app
root = tk.Tk()
app = ATMApp(root)
root.mainloop()
