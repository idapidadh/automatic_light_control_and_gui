from tkinter import *
from tkinter import messagebox

def opret_menu(root, tidsfoelsomhed, lysIntensitet, anvendIndstilling):
    def show(frame):
        frame.tkraise()

    # anvend_tidsfoelsomhed()
    def anvend_tidsfoelsomhed():
        pref = {
            "Tidsfølsomhed_min": int(tidsfoelsomhed.get())
        }
        sucess = anvendIndstilling(pref)  

        if sucess:
            tidsfoelsomhed_status_label.config(text="Indstilling gemt", fg="green")
            tidsfoelsomhed_status_label.after(2000, lambda: tidsfoelsomhed_status_label.config(text=""))

        else:
            tidsfoelsomhed_status_label.config(text="Fejl: kunne ikke gemme", fg="red")
            messagebox.showerror("Tidsfølsomhed", "Tidsfølsomhed kunne ikke opdateres.")  
            tidsfoelsomhed_status_label.after(2000, lambda: tidsfoelsomhed_status_label.config(text=""))

    # anvend_lysintensitet() 
    def anvend_lysintensitet():
        pref = {
            "Lysintensitet": int(lysIntensitet.get())
        }
        sucess = anvendIndstilling(pref)  

        if sucess:
            lysintensitet_status_label.config(text="Indstilling gemt", fg="green")
            lysintensitet_status_label.after(2000, lambda: lysintensitet_status_label.config(text=""))

        else:
            lysintensitet_status_label.config(text="Fejl: kunne ikke gemme", fg="red")
            messagebox.showerror("Lysintensitet", "Lysintensitet kunne ikke opdateres.") 
            lysintensitet_status_label.after(2000, lambda: lysintensitet_status_label.config(text=""))

    mainFrame = Frame(root)
    mainFrame.grid(row=0, column=0, sticky="nsew", padx=10, pady=10)
    root.rowconfigure(0, weight=1)
    root.columnconfigure(0, weight=1)

    forside = Frame(mainFrame)
    tidsfoelsomhed_frame = Frame(mainFrame)
    lys_frame = Frame(mainFrame)

    for f in (forside, tidsfoelsomhed_frame, lys_frame):
        f.grid(row=0, column=0, sticky="nsew")

    # FORSIDE
    Label(forside, text="Vælg menu", font=("Arial", 12, "bold"))\
        .grid(row=0, column=0, pady=(0,10), sticky="w")

    Button(forside, text="Tidsfølsomhed",
           command=lambda: show(tidsfoelsomhed_frame), width=24)\
        .grid(row=1, column=0, pady=5, sticky="w")

    Button(forside, text="Lysintensitet",
           command=lambda: show(lys_frame), width=24)\
        .grid(row=2, column=0, pady=5, sticky="w")

    try:
        img = PhotoImage(file="logo.png")
        img = img.subsample(4, 4)
        img_label = Label(forside, image=img)
        img_label.image = img
        img_label.grid(row=0, column=1, rowspan=5, padx=40, pady=10)
    except:
        Label(forside, text="[No image found]")\
            .grid(row=0, column=1, padx=40, pady=10)

    # Tidsfølsomhed-menu
    Label(tidsfoelsomhed_frame, text="Tidsfølsomhed", font=("Arial", 12, "bold"))\
        .grid(row=0, column=0, sticky="w", pady=(0,10))

    Label(tidsfoelsomhed_frame, text="Tidsfølsomhed (min):", font=("Arial", 8, "bold"))\
        .grid(row=1, column=0, sticky="w")

    Spinbox(tidsfoelsomhed_frame, from_=1, to=120, width=5, textvariable=tidsfoelsomhed)\
        .grid(row=1, column=1, sticky="w", padx=(5,5))

    Label(tidsfoelsomhed_frame, text="min")\
        .grid(row=1, column=2, sticky="w")

    Button(tidsfoelsomhed_frame, text="Anvend",
           command=anvend_tidsfoelsomhed, width=20)\
        .grid(row=2, column=0, columnspan=3, sticky="w", pady=(10,0))

    tidsfoelsomhed_status_label = Label(tidsfoelsomhed_frame, text="", font=("Arial", 8))
    tidsfoelsomhed_status_label.grid(row=3, column=0, columnspan=3, sticky="w", pady=(5,0))

    Button(tidsfoelsomhed_frame, text="Tilbage",
           command=lambda: show(forside), width=12)\
        .grid(row=99, column=0, sticky="w", pady=10)

    # Lysintensitet-menu
    Label(lys_frame, text="Lysintensitet", font=("Arial", 12, "bold"))\
        .grid(row=0, column=0, sticky="w", pady=(0,10))
    
    Label(lys_frame, text="Indstil lysstyrke:", font=("Arial", 8, "bold"))\
        .grid(row=1, column=0, sticky="w", pady=(0,10))

    Scale(lys_frame, from_=0, to=100, orient=HORIZONTAL, length=150, variable=lysIntensitet)\
        .grid(row=2, column=0, sticky="w", pady=(10))

    Button(lys_frame, text="Anvend",
           command=anvend_lysintensitet, width=20)\
        .grid(row=3, column=0, sticky="w", pady=(10,0))

    lysintensitet_status_label = Label(lys_frame, text="", font=("Arial", 8))
    lysintensitet_status_label.grid(row=4, column=0, sticky="w", pady=(5,0))

    Button(lys_frame, text="Tilbage",
           command=lambda: show(forside), width=12)\
        .grid(row=99, column=0, sticky="w", pady=10)

    show(forside)
    return mainFrame
