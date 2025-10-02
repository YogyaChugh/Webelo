import tkinter as tk
import webbrowser

def show_note_with_link():
    # Create a new top-level window (popup)
    popup = tk.Toplevel(root)
    popup.title("Special Note")
    popup.geometry("300x150")
    
    # Message text
    msg = tk.Label(popup, text="This is a special message!\nVisit this link:", font=("Arial", 12))
    msg.pack(pady=10)

    # Clickable link
    link = tk.Label(popup, text="Click Here", fg="blue", cursor="hand2", font=("Arial", 12, "underline"))
    link.pack()
    
    # Bind click to open URL
    link.bind("<Button-1>", lambda e: webbrowser.open("https://example.com"))

    # Close button
    btn = tk.Button(popup, text="Close", command=popup.destroy)
    btn.pack(pady=10)

root = tk.Tk()
root.geometry("300x200")

btn = tk.Button(root, text="Show Note", command=show_note_with_link)
btn.pack(pady=50)

root.mainloop()
