import tkinter as tk
from tkinter import messagebox
import ctypes
from tkinter import ttk

# Load the shared library
store_lib = ctypes.CDLL('./store.dll')  # Use 'store.dll' on Windows

# Define argument and return types for the C functions we will use
store_lib.addProduct.argtypes = [ctypes.c_int, ctypes.c_char_p, ctypes.c_float, ctypes.c_int]
store_lib.addProduct.restype = ctypes.c_int

store_lib.getProducts.argtypes = [ctypes.c_char_p]
store_lib.getProducts.restype = None

# GUI Class
class StoreApp:
    def __init__(self, root):
        self.root = root
        self.products_buffer = ctypes.create_string_buffer(1024)  # Buffer to store products' info
        self.root.title("Online Cosmetic Store")
        self.root.geometry("800x500")
        self.root.config(bg="#f0f0f0")  # Light gray background

        # Create title
        self.title_label = tk.Label(root, text="Online Cosmetic Store", font=("Helvetica", 24, "bold"), bg="#f0f0f0", fg="#333")
        self.title_label.pack(pady=20)

        # Frame for managing products
        self.frame = tk.Frame(root, bg="#f0f0f0")
        self.frame.pack(padx=10, pady=10)

        # Labels and Entries for product details
        self.product_id_label = self.create_label(self.frame, "Product ID:")
        self.product_id_entry = self.create_entry(self.frame)

        self.product_name_label = self.create_label(self.frame, "Product Name:")
        self.product_name_entry = self.create_entry(self.frame)

        self.product_price_label = self.create_label(self.frame, "Product Price:")
        self.product_price_entry = self.create_entry(self.frame)

        self.product_stock_label = self.create_label(self.frame, "Product Stock:")
        self.product_stock_entry = self.create_entry(self.frame)

        # Add and View buttons
        self.add_button = self.create_button(self.frame, "Add Product", self.add_product)
        self.view_button = self.create_button(self.frame, "View Products", self.view_products)

    def create_label(self, parent, text):
        label = tk.Label(parent, text=text, font=("Arial", 12), bg="#f0f0f0", anchor="w")
        label.grid(padx=5, pady=5, sticky="w")
        return label

    def create_entry(self, parent):
        entry = tk.Entry(parent, font=("Arial", 12), width=30)
        entry.grid(padx=5, pady=5, sticky="w")
        return entry

    def create_button(self, parent, text, command):
        button = tk.Button(parent, text=text, font=("Arial", 12, "bold"), bg="#4CAF50", fg="white", width=20, height=2,
                           relief="flat", command=command)
        button.grid(padx=5, pady=10)
        button.bind("<Enter>", self.on_hover_in)
        button.bind("<Leave>", self.on_hover_out)
        return button

    def on_hover_in(self, event):
        event.widget.config(bg="#45a049")

    def on_hover_out(self, event):
        event.widget.config(bg="#4CAF50")

    def add_product(self):
        product_id = self.product_id_entry.get()
        name = self.product_name_entry.get()
        price = self.product_price_entry.get()
        stock = self.product_stock_entry.get()

        if not product_id or not name or not price or not stock:
            messagebox.showerror("Error", "All fields must be filled!")
            return

        product_id = int(product_id)
        price = float(price)
        stock = int(stock)

        result = store_lib.addProduct(product_id, name.encode('utf-8'), price, stock)
        if result == -1:
            messagebox.showerror("Error", "Product list is full.")
        elif result == -2:
            messagebox.showerror("Error", "Product ID already exists.")
        else:
            messagebox.showinfo("Success", "Product added successfully!")

    def view_products(self):
        store_lib.getProducts(self.products_buffer)
        products_info = self.products_buffer.value.decode('utf-8')
        if products_info == "No products available.\n":
            messagebox.showinfo("No Products", "No products available.")
        else:
            self.show_product_window(products_info)

    def show_product_window(self, products_info):
        view_window = tk.Toplevel(self.root)
        view_window.title("Product List")
        view_window.geometry("600x400")
        view_window.config(bg="#f0f0f0")

        # Scrollbar for product list
        scroll_y = tk.Scrollbar(view_window)
        scroll_y.pack(side=tk.RIGHT, fill=tk.Y)

        # Treeview for displaying products
        tree = ttk.Treeview(view_window, columns=("ID", "Name", "Price", "Stock"), show="headings", yscrollcommand=scroll_y.set)
        tree.pack(padx=10, pady=10, expand=True, fill=tk.BOTH)

        tree.heading("ID", text="Product ID")
        tree.heading("Name", text="Product Name")
        tree.heading("Price", text="Product Price")
        tree.heading("Stock", text="Product Stock")

        # Insert products into the treeview
        for line in products_info.splitlines():
            product_details = line.split(" | ")
            if len(product_details) == 4:
                tree.insert("", "end", values=tuple(product_details))

        scroll_y.config(command=tree.yview)

def main():
    store_lib.loadProductsFromFile()  # Load products from file when app starts
    root = tk.Tk()
    app = StoreApp(root)
    root.mainloop()

if __name__ == "__main__":
    main()
