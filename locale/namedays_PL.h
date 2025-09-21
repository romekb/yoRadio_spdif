#ifndef NAMEDAYS_PL_H
#define NAMEDAYS_PL_H
// clang-format off

/*-- Tabela imienin -- Imiona dla każdego dnia roku rozdzielone przecinkami.
Jeśli w danym dniu występuje wiele imion, należy pozostawić między nimi spację, a
program będzie je zamieniał co 4 sekundy.
*/

const char* nameday_label = "Imieniny:";

  // Tablica imienin - imiona oddzielone przecinkami na każdy dzień roku (rotacja co 4 sekundy) - źródło: kalbi.pl
const char* namedays[] = {
  // Styczeń (31 dni)
  "Mieczysław, Mieczysława, Mieszko", "Bazylego,Izydor,Makary ", "Daniel, Genowefa, Zdzisława", "Aniela, Eugeniusz, Rygobert", "Edwarda, Emiliana, Szymon", "Kacpra,Baltazara,Melchiora", "Julian, Kryspin, Lucjan", "Erhard, Seweryn, Wawrzyniec", "Adrian, Antoni, Piotr", "Agatona,Jana,Wilhelma",
  "Honorata, Krzesimir, Mechtylda", "Arkadiusz, Bernard, Greta ", "Bogumiły,Weroniki", "Niny,Feliksa", "Arnolda,Pawła", "Marcelego,Włodzimierza", "Rozalindy,Antoniego", "Małgorzaty,Beatrycze", "Mariusza,Henryka", "Sebastiana,Fabiana",
  "Agnieszki,Inez", "Wincentego,Anastazego", "Rajmunda,Ildefonsa", "Felicjana,Tymoteusza", "Tatiany,Miłosza,Pawła", "Pauli,Tutusa", "Witaliana,Jerzego", "Tomasza,Karola", "Anieli,Bolesławy,Franciszka", "Martyny,Macieja", "Ludwiki,Marceli,Jana",
  // Luty (29 dni - rok przestępny)
  "Brygidy,Sewera", "Kornela,Marii,Młosławy", "Błażeja,Oskara", "Józefa,Weroniki", "Agaty,Adelaide", "Doroty,Tytusa", "Ryszarda,Romualda", "Kaji,Hieronima", "Apollonii,Cyryla", "Jacka,Scholastyki",
  "Marcjanny,Łazarza", "Eulalii,Modesta", "Grzegorza,Jordana", "Walentego,Cyryla", "Faustyna,Zygfryda", "Daniel, Danuta, Samuel ", "Donata,Aleksego", "Szymona,Bernadety", "Konrada,Patrycji", "Leona,Eleonory",
  "Piotra,Roberta", "Margarit,Izabeli", "Romana,Polikarpa", "Macieja,Modesta", "Wiktora,Cezarego", "Nestora,Aleksandra", "Gabriela,Leandra", "Romana,Augustyna", "Hilarego,Oswałda",
  // Marzec (31 dni)
  "Albina,Dawida,Antonii", "Halszki,Heleny", "Kunegundy,Kamila", "Kazimierza,Adriana", "Adriana,Celiny", "Róży,Beaty", "Tomasza,Perpetuy,Felicyty", "Jana,Stefana", "Franciszki,Dominiki", "Macieja,Eugeniusza",
  "Konstantego,Benedykta", "Grzegorza,Maksyma", "Geralda,Krystyny", "Matyldy,Leona", "Klemensa,Longina", "Herberta,Izabeli", "Patryka,Gertrudy", "Cyryla,Anzelma", "Józefa,Oblubieńca", "Franciszka,Klaudii",
  "Benedykta,Fabia", "Oktawiana,Katarzyny", "Turybiusza,Wojciecha", "Gabriela,Aleksandra", "Ireneusz, Maria, Mariola", "Emanuela,Teodora", "Augusta,Ruperta", "Jana,Donata", "Eugeniusza,Helmuta", "Leonarda,Kwityna", "Beniamina,Balbiny",
  // Kwiecień (30 dni)
  "Hugona,Ireny", "Franciszka,Teodozji", "Ryszarda,Pankracego", "Izydora,Benedykta", "Wincentego,Ireny", "Wilhelma,Celestyna", "Jana,Rufina", "Julii,Waleriana", "Marty,Dymitra", "Magdaleny,Macieja",
  "Stanisława,Leona", "Julii,Juliusza", "Hermenegildy,Idy", "Lamberta,Justyna", "Anastazji,Bazylego", "Bernadety,Magnusa", "Roberta,Rudolfa", "Apolloniusza,Bogusława", "Leona,Emmy", "Czesława,Sulpicjusza",
  "Anzelma,Konrada", "Szotera,Kajetana", "Wojciecha,Jerzego", "Fidelisa,Aleksandra", "Marka,Erwina", "Kleta,Mariana", "Zygmunta,Piotra", "Piotra,Walerii", "Katarzyny,Roberta", "Piusa,Jakuba",
  // Maj (31 dni)
  "Józefa,Filipa", "Atanazego,Zygmunta", "Aleksandra,Moniki", "Moniki,Floriana", "Piusa,Ireny", "Benedykta,Franciszka", "Gizeli,Stanisława", "Stanisława,Benedykta", "Grzegorza,Beaty", "Antoniny,Izydora",
  "Ignacego,Mamerta", "Pankracego,Nereusza", "Serwacego,Roberta", "Bonifacego,Korony", "Zofii,Izydora", "Jana,Andrzeja", "Paskala,Ubalda", "Eryka,Feliksa", "Piotra,Walentego", "Bernardyna,Bazylego",
  "Konstancji,Wiktorii", "Heleny,Julii", "Dezyderiusza,Emilii", "Jana,Joanny", "Urbana,Magdaleny", "Filipa,Elżbiety", "Augusta,Augustyna", "Germana,Justa", "Magdaleny,Teodozji", "Ferdynanda,Emilii", "Petroneli,Anieli",
  // Czerwiec (30 dni)
  "Justyna,Nikodema", "Marianny,Erazma", "Klotyldy,Eugenio", "Franciszka,Karakiolo", "Bonifacego,Waldemara", "Norberta,Klaudiusza", "Roberta,Norberta", "Medarda,Maksyma", "Prymusa,Kolumbana", "Bogumiła,Marii",
  "Barnaby,Bartłomieja", "Jana,Terencjusza", "Antoniego,Padewskiego", "Elizusza,Bazylego", "Wita,Marii", "Benona,Aliny", "Adolfa,Emila", "Maryny,Elżbiety", "Romualda,Juliana", "Silverego,Rafała",
  "Alojzego,Stanisława", "Paulina,Tomasza", "Zenona,Józefiny", "Jana,Chrzciciela", "Prospera,Doroty", "Jana,Pawła", "Władysława,Ladysława", "Ireneusza,Leona", "Piotra,Pawła", "Pawła,Piotra",
  // Lipiec (31 dni)
  "Ottona,Haliny,Mariana", "Urbana,Jagody,Marii", "Jacka,Anatola,Tomasza", "Teodora,Malwiny", "Karoliny,Atanazego", "Łucjii,Dominika,Dominiki", "Benedykta,Odo", "Prokopa,Elżbiety,Adriana", "Weroniki,Sylwii,Zenona", "Amelii,Filipa,Almy",
  "Olgi,Piusa,Pelagi", "Bruno,Paulina", "Sary,Małgorzaty", "Angeliny,Stelli,Marcela,Kamila", "Bonawentury,Henryka,Dawida,Włodzimierza,Roksany", "Marii,Mariki", "Jadwigi,Bogdana,Anety", "Kamila,Emiliana,Szymona", "Wincentego,Radomiły,Makryny", "Małgorzaty,Hieronima,Czesława",
  "Daniela,Wiktora", "Magdaleny,Mileny,Leny", "Brygidy,Apolinarii,Bogny", "Krzesimira,Kingi,Krystyny", "Krzysztofa,Jakuba", "Grażyny,Anny,Hanny,Mirosławy", "Julii,Natalii", "Tiny,Wiktora", "Marty,Olafa", "Julity,Piotra", "Ignacego,Heleny",
  // Sierpień (31 dni)
  "Alfonsa,Piotra", "Juliana,Stefana", "Lidii,Augusta", "Jana,Dominika", "Oswalda,Marii", "Jakuba,Sławomira", "Kajetana,Klaudii", "Dominika,Cyriaka", "Teresy,Romany", "Wawrzyńca,Bogusława",
  "Klary,Zuzanny", "Euzebiusza,Hilarego", "Hipolita,Radosława", "Maksymiliana,Alfreda", "Marii,Stefana", "Rocha,Jacka", "Hiacynta,Anastazego", "Heleny,Agapita", "Jana,Tymoteusza", "Bernarda,Samuela",
  "Gracji,Joanny", "Filipa,Tymona", "Róży,Zygfryda", "Bartłomieja,Michała", "Ludwika,Patryka", "Samuela,Adama", "Moniki,Cezarego", "Augustyna,Juliana", "Sabiny,Jana", "Feliksa,Rufa", "Rajmunda,Pauliny",
  // Wrzesień (30 dni)
  "Idziego,Bronisława", "Stefana,Juliana", "Grzegorza,Serafiny", "Rozalii,Irmy", "Wiktorii,Justyny", "Zachariasza,Petry", "Reginy,Anastazji", "Marii,Adriana", "Piotra,Serafina", "Mikołaja,Pulcherii",
  "Prota,Hiacynta", "Grzegorza,Marii", "Jana,Chryzostoma", "Cypriana,Kornelii", "Ludmiły,Alicji", "Edyty,Eufemii", "Roberta,Franciszka", "Stanisława,Irmy", "Januarego,Emilii", "Eustachiusza,Fausta",
  "Mateusza,Ifigenii", "Maurycego,Tomy", "Tekli,Linusa", "Gerharda,Gerarda", "Władysława,Aureliusza", "Kosmy,Damiana", "Wincentego,Adolfa", "Wacława,Szczęsnego", "Michała,Gabriela", "Hieronima,Zofii",
  // Październik (31 dni)
  "Teresy,Remigiusza", "Leodgara,Marceliny", "Gerarda,Teresy", "Franciszka,Petroniusza", "Placyda,Flawii", "Brunona,Renaty", "Justyny,Marii", "Pelagii,Demetriusza", "Dionizego,Ludwina", "Franciszka,Daniela",
  "Aleksandry,Solochona", "Wilfryda,Maksymiliana", "Geralda,Edwarda", "Kalliksta,Fortunata", "Teresy,Aurelii", "Jadwigi,Gali", "Ignacego,Margarity", "Łukasza,Justyny", "Piotra,Jana", "Jana,Irenki",
  "Urszuli,Hilarego", "Korduli,Marii", "Jana,Sewera", "Rafała,Antoniego", "Kryspina,Chryzanta", "Lucjana,Dimitrego", "Sabiny,Frumentego", "Szymona,Tadeusza", "Narcyza,Zenobii", "Alfonsa,Marcelego", "Wolfganga,Quintyna",
  // Listopad (30 dni)
  "Seweryn,Andrzej,Benignus", "Bohdan, Jerzy", "Huberta,Sylwii", "Karola,Modesty", "Zachariasza,Elżbiety", "Leonarda,Wincentyny", "Ernesta,Engelberga", "Gotarda,Klaudiusza", "Oresta,Teodora", "Leona,Andrzeja",
  "Marcina,Meny", "Josafata,Łiwinii", "Stanisława,Homobonego", "Wawrzyńca,Sewery", "Alberta,Eugeniusza", "Otmara,Margarity", "Grzegorza,Hyldy", "Odona,Romana", "Elżbiety,Kseni", "Feliksa,Edwarda",
  "Janusza,Gelazego", "Cecylii,Filomeny", "Klemensa,Kolumba", "Flory,Jana", "Katarzyny,Mojżesza", "Konrada,Styliany", "Wirgilego,Jacentego", "Zosimusa,Stefana", "Saturnina,Radegundy", "Andrzeja,Frumencego",
  // Grudzień (31 dni)
  "Edmunda,Eligiusza", "Bibiany,Lucji", "Franciszka,Ksawerego", "Barbary,Jana", "Saby,Krispiny", "Mikołaja,Dionizego", "Ambrożego,Marcina", "Niepokalnego,Poczęcia", "Waleriusza,Piotra", "Julii,Melchiady",
  "Damiana,Daniela", "Spirydona,Syneziusza", "Łucji,Odylia", "Jana,Krzyża", "Walerii,Celestyna", "Euzebiusza,Albiny", "Łazarza,Olimpii", "Gracjana,Gatiana", "Urbana,Nemezjusza", "Juliusza,Dominika",
  "Tomasza,Apostoła", "Franciszki,Flaviany", "Wiktorii,Dagobertu", "Adama,Ewy", "Eugenia, Mateusz", "Stefana,Dionizego", "Jana,Ewangelisty", "Antoni, Teofila", "Dawid, Dominik, Tomasz", "Dawida,Proroków", "Sylwestra,Melanii"
};

#endif // NAMEDAYS_PL_H
// clang-format on