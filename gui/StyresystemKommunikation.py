import serial
import time


class StyresystemKommunikation:
    def __init__(self, port="COM3", baud=9600):
        # skaber Serial-objekt fra pyserial-biblioteket
        self.ser = serial.Serial(
            port=port,
            baudrate=baud,
            bytesize=serial.EIGHTBITS,
            parity=serial.PARITY_EVEN,
            stopbits=serial.STOPBITS_ONE,
            timeout=2
        )
        # Giv Arduino tid til reset, når COM-porten er blevet åbnet
        time.sleep(2.5)

        # Fjerne alt i inputbuffer, hvis den ikke allerede er tom
        self.ser.reset_input_buffer() # *

    def close(self):
        """Luk serielporten pænt."""
        if self.ser and self.ser.is_open:
            self.ser.close()

    def sendKommando(self, kommando: str) -> str | None:
        """
        Tager en string, omkoder string til bytes og sender til Arduino.
        Modtager fra svar fra Arduino, omkoder bytes til string.
        Returnerer svaret som string, 
        eller None ved timeout
        """
        
        # Send kommando
        self.ser.write(kommando.encode()) # .encode() = indbygget Python-metode. Konverterer string til bytes.
        self.ser.flush() # * sørger for at alle bytes i Python-buffer sendes med det samme

        # Læs svar (bytes)
        respons = self.ser.readline() # Venter på svar indtil linje slutter med '\n'. Hvis det ikke kommer, så returneres tom bytestring b"""
        if not respons: 
            return None  # ingen respons før timeout

        # Decode til string
        respons = respons.decode(errors="replace").strip().lower()  # * .strip() fjerne \n og
                                                                    # * errors="replace" -> erstatter ugyldige bytes med '?'
        return respons


    def getSystemindstillinger(self) -> dict | None:
        """
        Henter systemindstillinger fra Arduino.
        Returnerer dict med 'lysintensitet' og 'tidsfoelsomhed',
        eller None ved fejl.
        """
        # Beder Arduino om systemindstillinger. Gemmes is 'respons'
        respons = self.sendKommando("systemindstillinger\n")

        # Check om der overhovedet KOMMER svar fra Arduino
        if respons is None:
            return None

        # Håndter fejlsvar fra Arduino
        if respons.startswith("fejl"):
            return None

        try:
            # Forventet format: "lys=<int>tid=<int>\n"
            lys_start = respons.index("lys=") + 4  # Mulighed for IndexError
            lys_slut   = respons.index("tid=")      # Mulighed for IndexError
            lys_str   = respons[lys_start:lys_slut] # Slicing

            tid_start = respons.index("tid=") + 4  # Mulighed for IndexError
            tid_str   = respons[tid_start:]        # ':' = resten af linjen

            lys_int = int(lys_str)              # Mulighed for ValueError
            tid_int = int(tid_str)              # Mulighed for ValueError

            return {
                "lysintensitet": lys_int,       # Mulighed for TypeError, hvis slicing gik galt og lys er None
                "tidsfoelsomhed": tid_int       # Mulighed for TypeError, hvis slicing gik galt og tid er None
            }

        except (ValueError, TypeError, IndexError): # *
            return None
    

    def setLysintensitet(self, lysintensitet: int) -> bool:
        """
        Sender ny lysintensitet til Arduino.
        Returnerer True hvis opdatering lykkedes eller False ved fejl.
        OBS: lysintensitet skal være int
        
        """
        # Beder Arduino opdatere lysintensitet til værdi. Retur: 'anvendt\n' eller 'fejl\n'
        kommandoStr = f"lys={lysintensitet}\n"
        anvendt = self.sendKommando(kommandoStr)

        # Check om der overhovedet KOMMER svar fra Arduino
        if anvendt is None:
            return False    # Intet svar
        
        # Håndter fejlsvar fra Arduino
        if anvendt.startswith("fejl"):
            return False
        
        # Opdatering af lysintensitet lykkedes
        if anvendt.startswith("anvendt"):
            return True
        
        # Der kom uidentificerbart fra Arduino
        return False
        

    def setTidsfoelsomhed(self, tidsfoelsomhed: int) -> bool:
        """
        Sender ny tidsfoelsomhed til Arduino.
        Returnerer True hvis opdatering lykkedes eller False ved fejl.
        OBS: tidsfoelsomhed skal være int
        
        """
        # Beder Arduino opdatere lysintensitet til værdi. Retur: 'anvendt\n' eller 'fejl\n'
        kommandoStr = f"tid={tidsfoelsomhed}\n"
        anvendt = self.sendKommando(kommandoStr)

        # Check om der overhovedet KOMMER svar fra Arduino
        if anvendt is None:
            return False    # Intet svar
        
        # Håndter fejlsvar fra Arduino
        if anvendt.startswith("fejl"):
            return False
        
        # Opdatering af tidsfølsomhed lykkedes
        if anvendt.startswith("anvendt"):
            return True
        
        # Der kom uidentificerbart fra Arduino
        return False