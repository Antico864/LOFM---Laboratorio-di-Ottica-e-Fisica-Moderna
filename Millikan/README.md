### Esperienza di Millikan

***
Per compilare: 
````
make
````
Per eseguire: 
````
./mlk <Nome_del_file_di_dati>
````
Il programma accetta in input un file così strutturato: ⋅⋅

| Carica [C]    | Errore [C]    |
| ------------- |:-------------:|
| C_0           | sigma_C_0     |
| C_1           | sigma_C_0     |
| ...           | ...           |

  Restituisce il valore della carica che minimizza lo scarto quadratico e l'errore associato a questo valore.   
  Inoltre, produce un grafico dello scarto quadratico della distribuzione inserita.   
  Il file datiprof.txt è fatto apposta per testare il buon funzionamento del programma: se tutto va bene si dovrebbe ottenere una parabola abbastanza perfetta e un valore della carica di circa _e_.   
  Il file MyDataTrue contiene i dati sperimentali che io, turbo e sick luke abbiamo rilevato perdendo la vista sui banchi del labo. Chi prova a modificarlo è muort. 