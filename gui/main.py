from tkinter import *
from menu import opret_menu
from StyresystemKommunikation import StyresystemKommunikation

root = Tk()
root.title("Lyssystem kontrol")
root.geometry("520x360")

styresystem = StyresystemKommunikation()

def getSystemindstillinger():
    svar = styresystem.getSystemindstillinger()
    if svar is None:
        return {
            "Tidsfølsomhed_min": 20,
            "Lysintensitet": 80
        }
    return {
        "Tidsfølsomhed_min": svar.get("tidsfoelsomhed", 20),
        "Lysintensitet": svar.get("lysintensitet", 80)
    }



def setLysintensitet(lysintensitet: int) -> bool:
    return styresystem.setLysintensitet(lysintensitet)


def setTidsfoelsomhed(tidsfoelsomhed: int) -> bool:
    return styresystem.setTidsfoelsomhed(tidsfoelsomhed)


def anvendIndstilling(prefs: dict) -> bool:
    if "Lysintensitet" in prefs:
        return setLysintensitet(prefs["Lysintensitet"])
    elif "Tidsfølsomhed_min" in prefs:
        return setTidsfoelsomhed(prefs["Tidsfølsomhed_min"])
    return False


systemindstillinger = getSystemindstillinger()

tidsfoelsomhed = IntVar(value=systemindstillinger.get("Tidsfølsomhed_min", 20))
lysIntensitet = IntVar(value=systemindstillinger.get("Lysintensitet", 80))

opret_menu(root, tidsfoelsomhed, lysIntensitet, anvendIndstilling)

def on_close():
    styresystem.close()
    root.destroy()

root.protocol("WM_DELETE_WINDOW", on_close)

root.mainloop()
