    ///*
    //
    //*/
    //# define F_CPU 8000000UL
    ////#include <stddef.h>
    //#include <avr/io.h>
    //#include <stdio.h>
    //#include <avr/interrupt.h>
    //#include <util/delay.h>
    //
    ////definiowanie parametrów transmisji za pomoc¹ makr zawartych w pliku
    ////nag³ówkowym setbaud.h. Je¿eli wybierzesz prêdkoœæ, która nie bêdzie
    ////mo¿liwa do realizacji otrzymasz ostrze¿enie:
    ////#warning "Baud rate achieved is higher than allowed"
    //
    //#define BAUD 9600 //57600													//tutaj podaj ¿¹dan¹ prêdkoœæ transmisji
    //#include <util/setbaud.h>													//linkowanie tego pliku musi byæ po zdefiniowaniu BAUD
    //
    //
    //
    //
    ////zmienne dot. odbioru danych
    //volatile unsigned char odb_x;												//odebrana liczba X
    //volatile unsigned char odb_flaga = 0;										//flaga informuj¹ca main o odebraniu liczby
    //
    ////bufor znaków ze wzorem funkcji, który wysy³amy po starcie programu
    //volatile unsigned int usart_bufor_ind;										//indeks bufora nadawania
    //char usart_bufor[30] = "y = 0.3187x^2 + 2x - 7";							//bufor nadawania
    //
    //void usart_inicjuj(void)
    //{
//
	    ////ustaw obliczone przez makro wartoœci
	    //UBRR0H = UBRRH_VALUE;
	    //UBRR0L = UBRRL_VALUE;
	    //#if USE_2X
	    //UCSR0A |=  (1<<U2X0);
	    //#else
	    //UCSR0A &= ~(1<<U2X0);
	    //#endif
	    //
	    //
	    ////Ustawiamy pozosta³e parametry modu³ USART
	    //UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);  
		////bitów danych: 8
	    ////bity stopu:  1
	    ////parzystoœæ:  brak
//
	    ////w³¹cz nadajnik i odbiornik oraz ich przerwania odbiornika
	    ////przerwania nadajnika w³¹czamy w funkcji wyslij_wynik()
	    //UCSR0B = (1<<TXEN0) | (1<<RXEN0); //| (1<<RXCIE0);
    //}
    //
    //
    ////--------------------------------------------------------------
    //
    //
    //ISR(USART_RX_vect)
    //{
	    ////przerwanie generowane po odebraniu bajtu
	    //odb_x = UDR0;   //zapamiêtaj odebran¹ liczbê
	    //odb_flaga = 1; //ustaw flagê odbioru liczby dla main()
    //}
    //
    //
    ////--------------------------------------------------------------
    //
    //ISR(USART_UDRE_vect){
	    //
	    ////przerwanie generowane, gdy bufor nadawania jest ju¿ pusty,
	    ////odpowiedzialne za wys³anie wszystkich znaków z tablicy usart_bufor[]
	    //
	    ////sprawdzamy, czy bajt do wys³ania jest znakiem koñca tekstu, czyli zerem
	    //if(usart_bufor[usart_bufor_ind]!= 0){
		    //
		    ////za³aduj znak do rejestru wysy³ki i ustaw indeks na nastêpny znak
		    //UDR0 = usart_bufor[usart_bufor_ind++];
		    //
		    //}else{
		    //
		    ////osi¹gniêto koniec napisu w tablicy usart_bufor[]
		    //UCSR0B &= ~(1<<UDRIE0); //wy³¹cz przerwania pustego bufora nadawania
	    //}
    //}
    //
    //
    ////--------------------------------------------------------------
    //
    //
    //void wyslij_wynik(void){
	    //
	    ////funkcja rozpoczyna wysy³anie, wysy³aj¹c pierwszy znak znajduj¹cy siê
	    ////w tablicy usart_bufor[]. Pozosta³e wyœle funkcja przerwania,
	    ////która zostanie wywo³ana automatycznie po wys³aniu ka¿dego znaku.
	    //
	    ////dodaj do tekstu wyniku znaki koñca linii (CR+LF), by na
	    ////ekranie terminala wyniki pojawia³y siê w nowych liniach
	    //unsigned char z;
	    //for(z=0; z<30; z++){
		    //if(usart_bufor[z]==0){   //czy to koniec takstu w tablicy
			    ////tak znaleziono koniec tekstu, dodajemy znak CR
			    //usart_bufor[z]   = 13;  //znak powrotu karetki CR (Carrige Return)
			    //usart_bufor[z+1]  = 10; //znak nowej linii LF (Line Feed)
			    //usart_bufor[z+2]  = 0;  //znak koñca ci¹gu tekstu w tablicy
			    //break;
		    //}
	    //}
	    //
	    //
	    ////Zaczekaj, a¿ bufor nadawania bêdzie pusty
	    //while (!(UCSR0A & (1<<UDRE0)));
	    //
	    ////bufor jest pusty mo¿na wys³aæ
	    //
	    ////nastêpny znak do wysy³ki to znak nr 1
	    //usart_bufor_ind = 0;
	    //
	    ////w³¹cz przerwania pustego bufora UDR, co rozpocznie transmisjê
	    ////aktualnej zawartoœci bufora
	    //UCSR0B |= (1<<UDRIE0);
	    //
    //}
    //
    ////--------------------------------------------------------------
    //
    //
    //int mainXYX(void)
    //{
	    //usart_inicjuj(); //inicjuj modu³ USART (RS-232)
	    //sei();           //w³¹cz przerwania globalne
	    //
	    //wyslij_wynik();  //na pocz¹tku wysy³amy text wzoru, który po
	    ////resecie jest w tablicy usart_bufor[]
	    //
	    //while(1){
		    //
		    ////tutaj Twój program ....
		    //
		    ////czekamy na informacjê o odebraniu danej nie blokuj¹c mikrokontrolera
		    //if(odb_flaga){
			    //
			    //odb_flaga = 0; //zgaœ flagê
			    //
			    ////wykonaj obliczenia i wynik przekszta³æ na znaki ³aduj¹c do
			    ////bufora usart_bufor[]
			    //sprintf(usart_bufor, "%f", 0.3187 * odb_x * odb_x + 2 * odb_x - 7);
			    //
			    //wyslij_wynik();  //rozpocznij wysy³anie wyniku przez RS-232
		    //}
		    //
		    ////w tym czasie mo¿na wykonywaæ dowolny program
		    ////umieœæ go tutaj lub przed if() powy¿ej
	    //}
    //}