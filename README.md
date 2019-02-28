# Self-driving-car-Arduino

Componente utilizate

Am folosit 4 motoare DC, cate unul pentru fiecare roata si 2 motoare servo pentru virarea celor doua roti frontale. Masina utilizeaza 4 senzori ultrasonici, pentru a masura distanta fata de obstacole, fiind amplasati in cele 4 directii, N,E,S,V. Am incercat sa amplasez senzorii astfel incat masina sa aiba o raza frontala de identificarea a obiectelor cat mai mare. Motoarele, senzorii, IR-ul si celelalte componente sunt alimentate cu curent de la placa Arduino, iar cele doua motoare servo au o sursa de curent separata, cu ajutorul unei alimentari pentru breadboard, amplasata pe partea inferioara a masinii. Pentru controlul acesteia de catre utilizator, am folosit o telecomanda si un receiver IR.

Descrierea proiectului

Acest proiect se numeste "Self driving car" si este o masina care evita obstacole si poate sa iasa din anumite situatii, atunci cand are mai multe obiecte in jurul acesteia. Utilizeaza 4 motoare pentru deplasare si 2 motoare servo pentru virare. Senzorii laterali evita coliziunea cu obiectele.

Descrierea codului

Cei 4 senzori de distanta masoara constant distantele, pentru fiecare senzor fiind facuta cate o functie. In momentul in care senzorul frontal identifica un obiecte ce se afla la o distanta mai mica de 25 cm fata de el, atunci masina merge cu spatele si se intoarce spre o alta directie. Acest mers cu spatele este controlat de senzorul amplasat in spatele masinii, care are grija ca sa nu se loveasca de vreun obiect, pastrand o distanta fata de obstacolele din spatele acesteia de 10 cm. Senzorii laterali mentin o distanta de 25 cm, iar in momentul in care se identifica o distanta mai mica de 25, masina se indeparteaza de acel obiect cu virarea opusa senzorului care a identificat aceasta distanta



