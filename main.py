from tkinter import *
import ctypes
import re
import bs4
import Webelo
from datetime import datetime
import webbrowser
from tkinterweb import HtmlFrame # import the HtmlFrame widget

# Just to tell u guyz, all the project is written by me by hand except this file contains some portion written by AI
# All other files are 100% NON-AI :) AND THIS FILE ONLY CONSTITUES ABOUT 5% of the whole project (and code editor part of this file is not AI (JUST SOME DOM TREE PART))

with open("sample.html") as file:
    html_text = file.read()

ctypes.windll.shcore.SetProcessDpiAwareness(True)


root = Tk()
root.title("Webelo")

# So that it doesn't cover the fullscreen and gives some space lol :)
width = root.winfo_screenwidth() - 100
height = root.winfo_screenheight() - 200
root.geometry(f'{width}x{height}')


# Frame baby you will take care of code editor and dom tree ! oki ??
top_frame = Frame(root,width=width,height=height-100)
top_frame.pack(side="top", fill="both", expand=True)

left_frame = Frame(top_frame, bg="#282C34", width=width//2)
left_frame.pack(side="left", fill="y")
left_frame.pack_propagate(False)

right_frame = Frame(top_frame, bg="#282C34")
right_frame.pack(side="left", fill="both", expand=True)


# haha, here i got info about the text
bottom_frame = Frame(root, bg="#282C34")
bottom_frame.pack(side="bottom", fill="x")


# whoever reading this, don't even try !
# hella easy, and this just updates color and all for html markup
def changes(event=None):
    global previousText

    if editArea.get('1.0', END) == previousText:
        return

    # Remove all tags so they can be redrawn
    for tag in editArea.tag_names():
        editArea.tag_remove(tag, "1.0", "end")

    # Add tags where the search_re function found the pattern
    i = 0
    for pattern, color in html_repl:
        for start, end in search_re(pattern, editArea.get('1.0', END)):
            editArea.tag_add(f'{i}', start, end)
            editArea.tag_config(f'{i}', foreground=token_colors[color])
            i+=1

    previousText = editArea.get('1.0', END) 


# matching boi
def search_re(pattern, text, groupid=0):
    matches = []

    text = text.splitlines()
    for i, line in enumerate(text):
        for match in re.finditer(pattern, line):

            matches.append(
                (f"{i + 1}.{match.start()}", f"{i + 1}.{match.end()}")
            )

    return matches


def rgb(rgb):
    return "#%02x%02x%02x" % rgb


previousText = ''

# some nice color combinations chatgpt gave :)
background = rgb((40, 44, 52))       # Charcoal background: #282C34
normal = rgb((171, 178, 191))       # Light Gray text: #ABB2BF
keywords = rgb((224, 108, 117))     # Muted Red (Tags, Doctype): #E06C75
comments = rgb((92, 99, 112))       # Muted Gray (Comments, Tree Lines): #5C6370
string = rgb((152, 195, 121))       # Light Green (Strings): #98C379
function = rgb((97, 175, 239))      # Bright Blue (Attributes): #61AFEF
font = 'Consolas 12'


# this section defines the regex and colors for different tokens of html
token_colors = {
    'tag': keywords,
    'attribute': function,
    'string': string,
    'comment': comments,
    'doctype': keywords,
}

html_repl = [
    ['</?\\w+.*?>', 'tag'],
    ['\\w+(?=\\=)', 'attribute'],
    ['".*?"', 'string'],
    ["'.*?'", 'string'],
    ['<!--.*?-->', 'comment'],
    ['<!DOCTYPE.*?>', 'doctype'],
]


# the edit area where u write code
editArea = Text(
    left_frame,
    background=background,
    foreground=normal,
    insertbackground=normal,
    relief="solid",
    borderwidth=2,
    font=font,
    padx=10,
    pady=10,
)

# the edit area where extra info is provided
extraContent = Text(
    bottom_frame,
    background=background,
    foreground=normal,
    insertbackground=normal,
    relief="solid",
    borderwidth=2,
    font=font,
    height=10,
    padx=10,
    pady=10,
)


# Just getting it on the screen
editArea.pack(
    fill='both',
    side="top",
    anchor="nw",
    expand=1
)

extraContent.pack(
    fill='x',
    side="bottom",
    anchor="s",
)


editArea.insert('1.0',html_text)
editArea.bind('<KeyRelease>', changes) # Changes on key release :)

NODE_WIDTH = 90
NODE_HEIGHT = 40
X_SPACING = 4
Y_SPACING = 140

# AI color combos op !!
NODE_FILL_NORMAL = "#E5C07B" # Muted Yellow/Gold
NODE_FILL_HOVER = "#D19A66"  # Orange/Dark Gold
NODE_OUTLINE = "#ABB2BF"     # Light Gray
NODE_TEXT_COLOR = background # Dark Charcoal
EDGE_COLOR = comments        # Muted Gray


# Position based on screen size
def compute_positions(node, depth=0, x=0):
    if "children" not in node or not node["children"]:
        node["x"] = x
        node["y"] = depth * (NODE_HEIGHT + Y_SPACING)
        return x + NODE_WIDTH + X_SPACING
    child_x = x
    for child in node["children"]:
        child_x = compute_positions(child, depth + 1, child_x)
    left = node["children"][0]["x"]
    right = node["children"][-1]["x"]
    node["x"] = (left + right) // 2
    node["y"] = depth * (NODE_HEIGHT + Y_SPACING)

    return child_x

sctags = ["area","base","br","col","embed","hr","img","input","link","meta","param","source","track","wbr"]



# Draw it baby !!
def draw_tree(canvas, node):
    global extraContent
    tag = f"node_{id(node)}"

    x, y = node["x"], node["y"]
    rect_id = canvas.create_rectangle(
        x, y, x + NODE_WIDTH, y + NODE_HEIGHT,
        fill="#add8e6", outline=NODE_OUTLINE, width=2,
        tags=(tag,)
    )
    text_id = canvas.create_text(
        x + NODE_WIDTH//2, y + NODE_HEIGHT//2,
        text=node["name"], font=("Segoe UI", 10, "bold"),
        fill=NODE_TEXT_COLOR,
        tags=(tag,)
    )

    # Hover & click effects
    def on_enter(event, rect_id=rect_id):
        canvas.itemconfig(rect_id, fill="#87CEFA", width=4)
        root.config(cursor="hand2")
    def on_leave(event, rect_id=rect_id):
        canvas.itemconfig(rect_id, fill="#add8e6", width=2)
        root.config(cursor="arrow")
    def on_click(event, node=node):
        extraContent.delete('1.0','end')
        text = f"""Tag: {node['name']}\n\nAttributes:"""
        for i in node['attrs']:
            text+=f"\n\t{i}: {node['attrs'][i]}"
        if node['attrs']=={}:
            text+=f"\n\t\tNone"
        text += f"""\nSelf-Closing: {True if node['name'] in sctags else False}\n"""
        text += f"""\nCreated At: {datetime.now()}\n"""
        text += f"""\nChildren:"""
        bro = 0
        if node['children']==[]:
            text+=f" None"
        else:
            text+=f"\n\t\t"
        for i in node['children']:
            if bro!=0 and bro!=len(node['children']):
                text+=f", "
            bro+=1
            text+=f"{i['name']}"
        text += f"""\nContent:"""
        if node.get('content'):
            brot = node['content'].split('\n')
            for j in brot:
                text += "\n\t\t" + j
        else:
            text += "None"
        extraContent.insert('1.0',text)
        canvas.itemconfig(rect_id, fill="#98C379")

    canvas.tag_bind(tag, "<Enter>", on_enter)
    canvas.tag_bind(tag, "<Leave>", on_leave)
    canvas.tag_bind(tag, "<Button-1>", on_click)

    # Draw children + edges
    if "children" in node:
        for child in node["children"]:
            cx, cy = child["x"] + NODE_WIDTH//2, child["y"]
            canvas.create_line(
                x + NODE_WIDTH//2, y + NODE_HEIGHT,
                cx, cy, width=2, fill=EDGE_COLOR
            )
            draw_tree(canvas, child)

    content = editArea.get("1.0", "end-1c")
    with open("temp.html",'w') as ok:
        ok.write(content)


# This is a function i wrote to create the dictionary !!
def print_children(some,logs):
    logs = logs
    dom_tree = {}
    if (type(some)!=bs4.element.NavigableString):
        if some.name:
            dom_tree["name"] = some.name
            dom_tree["attrs"] = some.attrs
            dom_tree["content"] = ""
            if some.string:
                dom_tree['content'] = some.string
            dom_tree['children'] = []
            logs+=f"Created Element {some.name}\n"
        try:
            d = 0
            for child in some.children:
                if d==0: dom_tree["children"] = []
                d+=1
                pp,logs = print_children(child,logs)
                if pp!={}:
                    dom_tree["children"].append(pp)
        except:
            pass
    else:
        dom_tree["name"] = "Text"
        dom_tree['attrs'] = {}
        dom_tree["content"] = ""
        if some.string:
            dom_tree['content'] = some.string
        dom_tree['children'] = []
        logs+=f"Created Text Node\n"
    return dom_tree, logs


# I don't know how this works ! cause i didn't have time to learn this much depth of tkinter :)
# so ai bhai helped
def bind_mousewheel(canvas):
    canvas.bind("<MouseWheel>", lambda e: canvas.yview_scroll(int(-1*(e.delta/120)), "units"))
    canvas.bind("<Button-4>", lambda e: canvas.yview_scroll(-1, "units"))
    canvas.bind("<Button-5>", lambda e: canvas.yview_scroll(1, "units"))
    canvas.bind("<Shift-MouseWheel>", lambda e: canvas.xview_scroll(int(-1*(e.delta/120)), "units"))
    def on_scroll(event):
        if hasattr(event, "delta") and event.state & 0x0001:
            canvas.xview_scroll(int(-1*(event.delta/120)), "units")
    canvas.bind("<MouseWheel>", on_scroll, add="+")


def reload_dom(event=None):
    global dom_tree, logs
    canvas.delete("all")
    html_text = editArea.get("1.0", "end")
    soup = bs4.BeautifulSoup(html_text, 'html.parser')
    logs="Click on a tag in tree to get more info !\nAlso, use Ctrl+S to reload !\n\n"
    dom_tree, logs = print_children(soup, logs)
    extraContent.delete("1.0", "end")
    extraContent.insert("1.0", logs)
    Webelo.process_html(dom_tree)
    content = editArea.get("1.0",'end-1c')
    if content!="":
        canvas.create_text(100, 40, text="DOM Tree", font=("Arial", 24), fill="white")
    compute_positions(dom_tree)
    draw_tree(canvas, dom_tree)
    canvas.update_idletasks()
    canvas.config(scrollregion=canvas.bbox("all"))
        
        
# here I have parsed the html and got the canvas with it !!
soup = bs4.BeautifulSoup(html_text, 'html.parser')
logs = "Click on a tag in tree to get more info !\nAlso, use Ctrl+S to reload !\n\n"
dom_tree,logs = print_children(soup,logs)
# print(dom_tree)

extraContent.insert('1.0',logs)
root.bind('<Control-s>', reload_dom)

# Heiii ! Do you see my binding working ! hehe
Webelo.process_html(dom_tree)
# print(type(logs))
# print(logs)

def open_browser():
    root2 = Tk()
    root2.title("Running Demo Instance")
    frame = HtmlFrame(root2)
    try:
        with open("temp.html",'r') as f:
            data = f.read()
        frame.load_html(data)
    except:
        frame.load_html(html_text)
    frame.pack(fill="both", expand=True)
    root2.mainloop()
button = Button(root, text="RUN IT BOI !", command=open_browser, bg="#61AFEF", fg="white")
button.place(relx=1.0, y=10,x=-10, anchor="ne")

canvas = Canvas(right_frame, bg="black", relief="solid", borderwidth=2)
canvas.pack(fill="both", expand=True)
content = editArea.get("1.0",'end-1c')
if content!="":
    canvas.create_text(100, 40, text="DOM Tree", font=("Arial", 24), fill="white")

# positions and the baby tree :)
compute_positions(dom_tree)
draw_tree(canvas, dom_tree)

canvas.update_idletasks()
canvas.config(scrollregion=canvas.bbox("all"))
bind_mousewheel(canvas)

changes()

import tkinter.messagebox as msg

popup = Toplevel(root)
popup.title("Special Note")
popup.geometry("1000x380")
popup.resizable = False
popup.minsize = (1000,380)
popup.maxsize = (1000,380)

# Message text
msg = Label(popup, text="This is just a demonstration visualizing HTML the way browsers will !\nMy main project ain't this but the layer behind it\nLuckily, it's also a library which you can use like any c++ library\n\nWhy is it useful??\n\t\tWhether creating a web scraper of your own or a webbrowser or even\n a small URL finder the library will help you store the content in the most feasible way\nAlso, providing stuff for events & what not !!!\n\nBest Thing??\nIt even adheres (follows) the OG WHATWG documentation so that's how other browsers do it toooo", font=("Arial", 12))
msg.pack(pady=10)
# Clickable link
link = Label(popup, text="Documentation", fg="blue", cursor="hand2", font=("Arial", 12, "underline"))
link.pack()
link2 = Label(popup, text="Library Examples", fg="blue", cursor="hand2", font=("Arial", 12, "underline"))
link2.pack()
link3 = Label(popup, text="Github", fg="blue", cursor="hand2", font=("Arial", 12, "underline"))
link3.pack()

# Bind click to open URL
link.bind("<Button-1>", lambda e: webbrowser.open("https://webelo.onrender.com"))
link2.bind("<Button-1>", lambda e: webbrowser.open("https://example.com"))
link3.bind("<Button-1>", lambda e: webbrowser.open("https://github.com/YogyaChugh/Webelo.git"))

# it won't run without this as the documentation says
root.mainloop()