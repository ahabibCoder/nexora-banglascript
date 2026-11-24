#!/usr/bin/env python3
"""
NEXORA - BanglaScript Desktop IDE
A lightweight, modern, responsive IDE for writing, testing, and debugging BanglaScript programs.
"""

import os
import sys
import subprocess
import tempfile
import tkinter as tk
from tkinter import ttk, messagebox, filedialog

# Sample Templates
TEMPLATES = {
    "01 - Hello World": """// Welcome to BanglaScript in NEXORA IDE!
sonkha a = 10;
sonkha b = 20;

sonkha result = a + b;

dekhao("Hello from BanglaScript!");
dekhao("Sum is: ");
dekhao(result);
""",
    "02 - Variables & Types": """// Data types in BanglaScript
sonkha age = 22;
dosomik gpa = 3.85;
bakya name = "Hujaifa";
sotti enrolled = true;

dekhao("Student: " + name);
dekhao("Age: ");
dekhao(age);
dekhao("GPA: ");
dekhao(gpa);
dekhao("Enrolled: ");
dekhao(enrolled);
""",
    "03 - If-Else Conditions": """// Conditional branching (jodi - nahole)
sonkha score = 88;

jodi (score >= 90) {
    dekhao("Grade: A+ (Outstanding)");
} nahole jodi (score >= 80) {
    dekhao("Grade: A (Very Good)");
} nahole jodi (score >= 70) {
    dekhao("Grade: B (Satisfactory)");
} nahole {
    dekhao("Grade: Needs Improvement");
}
""",
    "04 - Loops (jotokhon)": """// Loop with break (bondho) and continue (chaliyejao)
sonkha count = 0;
sonkha total = 0;

jotokhon (count < 8) {
    count = count + 1;
    jodi (count == 4) {
        chaliyejao; // skip 4
    }
    dekhao(count);
    total = total + count;
}

dekhao("Total Sum: ");
dekhao(total);
""",
    "05 - Functions & Math": """// Function definitions and calls
kaj jog(sonkha a, sonkha b) {
    ferot a + b;
}

kaj gun(sonkha a, sonkha b) {
    ferot a * b;
}

sonkha x = 12;
sonkha y = 8;

dekhao("Jogfol: ");
dekhao(jog(x, y));

dekhao("Gunfol: ");
dekhao(gun(x, y));
""",
    "06 - Recursive Factorial": """// Recursive Factorial algorithm
kaj factorial(sonkha n) {
    jodi (n <= 1) {
        ferot 1;
    }
    ferot n * factorial(n - 1);
}

sonkha res = factorial(6);
dekhao("Factorial of 6 is: ");
dekhao(res); // 720
""",
    "07 - Native Bengali Script": """// বাংলায় BanglaScript প্রোগ্রাম!
সংখ্যা সংখ্যা১ = ২৫;
সংখ্যা সংখ্যা২ = ১৫;

সংখ্যা মোট = সংখ্যা১ + সংখ্যা২;

যদি (মোট > ৩০) {
    দেখাও("মোট সংখ্যা ৩০ এর বেশি!");
} নাহলে {
    দেখাও("মোট সংখ্যা ৩০ বা তার কম।");
}

দেখাও("ফলাফল: ");
দেখাও(মোট);
"""
}

class NexoraIDE:
    def __init__(self, root):
        self.root = root
        self.root.title("NEXORA IDE — BanglaScript Programming Language")
        self.root.geometry("1100x750")
        self.root.minsize(800, 600)

        # Find executable path
        self.executable = self.find_compiler_executable()
        self.current_file_path = None

        self.setup_styles()
        self.build_ui()
        self.load_template("01 - Hello World")

    def find_compiler_executable(self):
        script_dir = os.path.dirname(os.path.abspath(__file__))
        candidates = [
            os.path.join(script_dir, "..", "build", "bin", "banglascript.exe"),
            os.path.join(script_dir, "..", "bin", "banglascript.exe"),
            os.path.join(script_dir, "..", "build", "bin", "bs.exe"),
            "banglascript",
            "bs"
        ]
        for c in candidates:
            if os.path.exists(c):
                return os.path.abspath(c)
        return "banglascript"

    def setup_styles(self):
        self.bg_color = "#1e1e1e"
        self.editor_bg = "#1e1e1e"
        self.editor_fg = "#d4d4d4"
        self.panel_bg = "#252526"
        self.panel_fg = "#cccccc"
        self.accent_color = "#007acc"
        self.btn_bg = "#333333"
        self.btn_fg = "#ffffff"
        self.btn_active = "#0e639c"

        self.root.configure(bg=self.bg_color)

    def build_ui(self):
        # Top Toolbar
        toolbar = tk.Frame(self.root, bg=self.panel_bg, height=45, padx=8, pady=6)
        toolbar.pack(side=tk.TOP, fill=tk.X)

        title_lbl = tk.Label(toolbar, text="NEXORA", font=("Segoe UI", 12, "bold"), fg="#4EC9B0", bg=self.panel_bg)
        title_lbl.pack(side=tk.LEFT, padx=(4, 12))

        # Run Button
        self.run_btn = tk.Button(toolbar, text="▶ Run (F5)", font=("Segoe UI", 9, "bold"),
                                 bg="#0e639c", fg="#ffffff", activebackground="#1177bb", activeforeground="#ffffff",
                                 relief=tk.FLAT, padx=12, pady=4, cursor="hand2", command=self.run_code)
        self.run_btn.pack(side=tk.LEFT, padx=4)

        # Check Button
        self.check_btn = tk.Button(toolbar, text="🔍 Check (F7)", font=("Segoe UI", 9),
                                   bg=self.btn_bg, fg=self.btn_fg, activebackground=self.btn_active,
                                   relief=tk.FLAT, padx=10, pady=4, cursor="hand2", command=self.check_code)
        self.check_btn.pack(side=tk.LEFT, padx=4)

        # AST Button
        self.ast_btn = tk.Button(toolbar, text="🌳 AST Tree", font=("Segoe UI", 9),
                                 bg=self.btn_bg, fg=self.btn_fg, activebackground=self.btn_active,
                                 relief=tk.FLAT, padx=10, pady=4, cursor="hand2", command=self.view_ast)
        self.ast_btn.pack(side=tk.LEFT, padx=4)

        # TAC Button
        self.tac_btn = tk.Button(toolbar, text="⚡ TAC (IR)", font=("Segoe UI", 9),
                                 bg=self.btn_bg, fg=self.btn_fg, activebackground=self.btn_active,
                                 relief=tk.FLAT, padx=10, pady=4, cursor="hand2", command=self.view_tac)
        self.tac_btn.pack(side=tk.LEFT, padx=4)

        # Template Dropdown
        tk.Label(toolbar, text="Examples:", font=("Segoe UI", 9), fg="#9cdcfe", bg=self.panel_bg).pack(side=tk.LEFT, padx=(16, 4))
        self.template_var = tk.StringVar(value="01 - Hello World")
        self.template_menu = ttk.Combobox(toolbar, textvariable=self.template_var, values=list(TEMPLATES.keys()),
                                          state="readonly", width=22)
        self.template_menu.pack(side=tk.LEFT, padx=4)
        self.template_menu.bind("<<ComboboxSelected>>", lambda e: self.load_template(self.template_var.get()))

        # Clear Output Button
        clear_btn = tk.Button(toolbar, text="Clear", font=("Segoe UI", 9),
                              bg=self.btn_bg, fg=self.btn_fg, activebackground=self.btn_active,
                              relief=tk.FLAT, padx=8, pady=4, cursor="hand2", command=self.clear_output)
        clear_btn.pack(side=tk.RIGHT, padx=4)

        # Main Split Panes (Top: Editor, Bottom: Output)
        paned = tk.PanedWindow(self.root, orient=tk.VERTICAL, bg="#333333", sashwidth=5, sashrelief=tk.FLAT)
        paned.pack(fill=tk.BOTH, expand=True)

        # Upper Editor Frame
        editor_frame = tk.Frame(paned, bg=self.editor_bg)
        paned.add(editor_frame, height=420)

        # Line numbers
        self.line_numbers = tk.Text(editor_frame, width=4, font=("Consolas", 11),
                                    bg="#181818", fg="#858585", bd=0, padx=4, pady=6,
                                    takefocus=0, state=tk.DISABLED)
        self.line_numbers.pack(side=tk.LEFT, fill=tk.Y)

        # Code Editor Text Widget
        self.editor = tk.Text(editor_frame, font=("Consolas", 11),
                              bg=self.editor_bg, fg=self.editor_fg,
                              insertbackground="#ffffff", selectbackground="#264f78",
                              bd=0, padx=6, pady=6, undo=True)
        self.editor.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

        editor_scroll = tk.Scrollbar(editor_frame, command=self.sync_scroll, bg=self.panel_bg)
        editor_scroll.pack(side=tk.RIGHT, fill=tk.Y)
        self.editor.configure(yscrollcommand=editor_scroll.set)

        self.editor.bind("<KeyRelease>", self.on_content_changed)
        self.editor.bind("<MouseWheel>", self.on_scroll)
        self.root.bind("<F5>", lambda e: self.run_code())
        self.root.bind("<F7>", lambda e: self.check_code())

        # Configure Syntax Highlight Tags
        self.setup_syntax_tags()

        # Lower Output Frame with Tabs
        output_frame = tk.Frame(paned, bg=self.panel_bg)
        paned.add(output_frame, height=260)

        # Tab Notebook
        style = ttk.Style()
        style.theme_use('default')
        style.configure("TNotebook", background=self.panel_bg, borderwidth=0)
        style.configure("TNotebook.Tab", background="#2d2d2d", foreground="#cccccc", padding=[12, 4], font=("Segoe UI", 9))
        style.map("TNotebook.Tab", background=[("selected", "#1e1e1e")], foreground=[("selected", "#ffffff")])

        self.notebook = ttk.Notebook(output_frame)
        self.notebook.pack(fill=tk.BOTH, expand=True)

        # Tab 1: Console Output
        self.console_tab = tk.Frame(self.notebook, bg="#181818")
        self.notebook.add(self.console_tab, text="🖥 Program Output")
        self.console_text = tk.Text(self.console_tab, font=("Consolas", 10),
                                    bg="#181818", fg="#00ff66", insertbackground="#ffffff",
                                    bd=0, padx=8, pady=8)
        self.console_text.pack(fill=tk.BOTH, expand=True)

        # Tab 2: AST Tree
        self.ast_tab = tk.Frame(self.notebook, bg="#181818")
        self.notebook.add(self.ast_tab, text="🌳 Abstract Syntax Tree")
        self.ast_text = tk.Text(self.ast_tab, font=("Consolas", 10),
                                bg="#181818", fg="#9cdcfe", bd=0, padx=8, pady=8)
        self.ast_text.pack(fill=tk.BOTH, expand=True)

        # Tab 3: TAC (IR)
        self.tac_tab = tk.Frame(self.notebook, bg="#181818")
        self.notebook.add(self.tac_tab, text="⚡ Three-Address Code (TAC)")
        self.tac_text = tk.Text(self.tac_tab, font=("Consolas", 10),
                                bg="#181818", fg="#ce9178", bd=0, padx=8, pady=8)
        self.tac_text.pack(fill=tk.BOTH, expand=True)

        # Status Bar
        self.status_bar = tk.Label(self.root, text="Ready | Compiler: " + os.path.basename(self.executable),
                                   font=("Segoe UI", 8), bg="#007acc", fg="#ffffff", anchor=tk.W, padx=10, pady=2)
        self.status_bar.pack(side=tk.BOTTOM, fill=tk.X)

    def setup_syntax_tags(self):
        self.editor.tag_configure("type", foreground="#4EC9B0")       # Cyan
        self.editor.tag_configure("keyword", foreground="#C586C0")    # Purple
        self.editor.tag_configure("builtin", foreground="#DCDCAA")    # Yellow
        self.editor.tag_configure("boolean", foreground="#569CD6")    # Blue
        self.editor.tag_configure("string", foreground="#CE9178")     # Orange
        self.editor.tag_configure("number", foreground="#B5CEA8")     # Green
        self.editor.tag_configure("comment", foreground="#6A9955")    # Dim Green

    def update_syntax_highlight(self):
        content = self.editor.get("1.0", tk.END)
        for tag in ["type", "keyword", "builtin", "boolean", "string", "number", "comment"]:
            self.editor.tag_remove(tag, "1.0", tk.END)

        import re
        types = r'\b(sonkha|dosomik|bakya|sotti|shunno|সংখ্যা|দশমিক|বাক্য|সত্যি|শূন্য)\b'
        keywords = r'\b(jodi|nahole|jotokhon|bondho|chaliyejao|kaj|ferot|যদি|নাহলে|যতক্ষণ|বন্ধ|চালিয়েযাও|ফেরত)\b'
        builtins = r'\b(dekhao|nao|দেখাও|নাও)\b'
        booleans = r'\b(true|false|সত্য|মিথ্যা)\b'
        strings = r'\"([^\"\\\n]|\\.)*\"'
        comments = r'//.*$'
        numbers = r'\b[0-9]+(\.[0-9]+)?\b|[০-৯]+'

        for pattern, tag in [
            (types, "type"),
            (keywords, "keyword"),
            (builtins, "builtin"),
            (booleans, "boolean"),
            (numbers, "number"),
            (strings, "string"),
            (comments, "comment"),
        ]:
            for match in re.finditer(pattern, content, re.MULTILINE):
                start = f"1.0 + {match.start()} chars"
                end = f"1.0 + {match.end()} chars"
                self.editor.tag_add(tag, start, end)

    def sync_scroll(self, *args):
        self.editor.yview(*args)
        self.line_numbers.yview(*args)

    def on_scroll(self, event):
        self.line_numbers.yview_scroll(int(-1 * (event.delta / 120)), "units")

    def on_content_changed(self, event=None):
        self.update_line_numbers()
        self.update_syntax_highlight()

    def update_line_numbers(self):
        lines = self.editor.get("1.0", tk.END).count("\n")
        line_num_str = "\n".join(str(i) for i in range(1, lines + 1))
        self.line_numbers.config(state=tk.NORMAL)
        self.line_numbers.delete("1.0", tk.END)
        self.line_numbers.insert("1.0", line_num_str)
        self.line_numbers.config(state=tk.DISABLED)

    def load_template(self, name):
        if name in TEMPLATES:
            self.editor.delete("1.0", tk.END)
            self.editor.insert("1.0", TEMPLATES[name])
            self.update_line_numbers()
            self.update_syntax_highlight()
            self.status_bar.config(text=f"Loaded example: {name}")

    def clear_output(self):
        self.console_text.delete("1.0", tk.END)
        self.ast_text.delete("1.0", tk.END)
        self.tac_text.delete("1.0", tk.END)

    def save_temp_source(self):
        code = self.editor.get("1.0", tk.END)
        fd, path = tempfile.mkstemp(suffix=".bs", prefix="nexora_")
        with os.fdopen(fd, "w", encoding="utf-8") as f:
            f.write(code)
        return path

    def run_code(self):
        temp_file = self.save_temp_source()
        self.notebook.select(self.console_tab)
        self.console_text.delete("1.0", tk.END)
        self.status_bar.config(text="Executing BanglaScript program in TAC VM...", bg="#0e639c")

        try:
            cmd = [self.executable, "run", temp_file]
            result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, encoding="utf-8")
            
            output = result.stdout
            errors = result.stderr

            if output:
                self.console_text.insert(tk.END, output)
            if errors:
                self.console_text.insert(tk.END, "\n" + errors)

            if result.returncode == 0:
                self.status_bar.config(text="Program Finished (Exit Code: 0)", bg="#107c41")
            else:
                self.status_bar.config(text=f"Program Failed with errors (Exit Code: {result.returncode})", bg="#a80000")
        except Exception as e:
            self.console_text.insert(tk.END, f"\nExecution Error: {str(e)}\n")
            self.status_bar.config(text="Execution error", bg="#a80000")
        finally:
            try: os.remove(temp_file)
            except: pass

    def check_code(self):
        temp_file = self.save_temp_source()
        self.notebook.select(self.console_tab)
        self.console_text.delete("1.0", tk.END)
        self.status_bar.config(text="Validating syntax and semantic types...", bg="#0e639c")

        try:
            cmd = [self.executable, "check", temp_file]
            result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, encoding="utf-8")
            
            output = result.stdout + result.stderr
            self.console_text.insert(tk.END, output)

            if result.returncode == 0:
                self.status_bar.config(text="Syntax & Types Validated Successfully (0 Errors)", bg="#107c41")
            else:
                self.status_bar.config(text="Validation Failed - Review errors above", bg="#a80000")
        finally:
            try: os.remove(temp_file)
            except: pass

    def view_ast(self):
        temp_file = self.save_temp_source()
        self.notebook.select(self.ast_tab)
        self.ast_text.delete("1.0", tk.END)

        try:
            cmd = [self.executable, "ast", temp_file]
            result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, encoding="utf-8")
            self.ast_text.insert(tk.END, result.stdout or result.stderr)
            self.status_bar.config(text="Abstract Syntax Tree (AST) Generated", bg="#107c41")
        finally:
            try: os.remove(temp_file)
            except: pass

    def view_tac(self):
        temp_file = self.save_temp_source()
        self.notebook.select(self.tac_tab)
        self.tac_text.delete("1.0", tk.END)

        try:
            cmd = [self.executable, "tac", temp_file, "--opt"]
            result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, encoding="utf-8")
            self.tac_text.insert(tk.END, result.stdout or result.stderr)
            self.status_bar.config(text="Three-Address Code (TAC) Generated", bg="#107c41")
        finally:
            try: os.remove(temp_file)
            except: pass

def main():
    root = tk.Tk()
    app = NexoraIDE(root)
    root.mainloop()

if __name__ == "__main__":
    main()
