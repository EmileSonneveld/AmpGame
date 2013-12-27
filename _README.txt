
-------- AMP-GAME van Emile Sonneveld --------
        (Gebaseert op de world of goo)
             emillo108@yahoo.com


---- Controls: ----


QDZS of Pijltjes	Besturing
SHIFT			3x stuwkracht
X		Linken tussen balletjes breken
C		Range om een link te leggen
B		Bouncen tussen dynamics switchen (snel klikken)
N		New Bal (heel veel)

A E		In- en uit-zoemen
LMB		magische magneet aan de muis
RMB		Nieuwe Bal maken


---- Doel ----
- Probeer met zo veel mogelijk bolletjes in 1 cluster beneden te geraken.
- Sandbox.


---- Belangrijke uitleg over het spel ----

Er zijn 3list classes en ze zitten elle drie in de Singleton MasterOfLists

- Dynamic list houd alle polymorfen van Dynamic bij
	- Bal
	- Player

- ObjectList houd alle andere objecten bij (die niet met elkaar interfereren)
	- Explotion
	- Magnet
	- EndPoint

- HitRegionList houd alle rotsstukken bij en regelt de rayCast





---- Dynamics ----

Als er te veel kracht word gezet op een link, dan breekt die.
Zodra de framerate daald, dan kan er een dynamics explotion ontstaan.
Links worden rood als ze gestretcht worden.