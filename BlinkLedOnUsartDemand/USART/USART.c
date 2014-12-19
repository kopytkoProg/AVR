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
    ////definiowanie parametr�w transmisji za pomoc� makr zawartych w pliku
    ////nag��wkowym setbaud.h. Je�eli wybierzesz pr�dko��, kt�ra nie b�dzie
    ////mo�liwa do realizacji otrzymasz ostrze�enie:
    ////#warning "Baud rate achieved is higher than allowed"
    //
    //#define BAUD 9600 //57600													//tutaj podaj ��dan� pr�dko�� transmisji
    //#include <util/setbaud.h>													//linkowanie tego pliku musi by� po zdefiniowaniu BAUD
    //
    //
    //
    //
    ////zmienne dot. odbioru danych
    //volatile unsigned char odb_x;												//odebrana liczba X
    //volatile unsigned char odb_flaga = 0;										//flaga informuj�ca main o odebraniu liczby
    //
    ////bufor znak�w ze wzorem funkcji, kt�ry wysy�amy po starcie programu
    //volatile unsigned int usart_bufor_ind;										//indeks bufora nadawania
    //char usart_bufor[30] = "y = 0.3187x^2 + 2x - 7";							//bufor nadawania
    //
    //void usart_inicjuj(void)
    //{
//
	    ////ustaw obliczone przez makro warto�ci
	    //UBRR0H = UBRRH_VALUE;
	    //UBRR0L = UBRRL_VALUE;
	    //#if USE_2X
	    //UCSR0A |=  (1<<U2X0);
	    //#else
	    //UCSR0A &= ~(1<<U2X0);
	    //#endif
	    //
	    //
	    ////Ustawiamy pozosta�e parametry modu� USART
	    //UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);  
		////bit�w danych: 8
	    ////bity stopu:  1
	    ////parzysto��:  brak
//
	    ////w��cz nadajnik i odbiornik oraz ich przerwania odbiornika
	    ////przerwania nadajnika w��czamy w funkcji wyslij_wynik()
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
	    //odb_x = UDR0;   //zapami�taj odebran� liczb�
	    //odb_flaga = 1; //ustaw flag� odbioru liczby dla main()
    //}
    //
    //
    ////--------------------------------------------------------------
    //
    //ISR(USART_UDRE_vect){
	    //
	    ////przerwanie generowane, gdy bufor nadawania jest ju� pusty,
	    ////odpowiedzialne za wys�anie wszystkich znak�w z tablicy usart_bufor[]
	    //
	    ////sprawdzamy, czy bajt do wys�ania jest znakiem ko�ca tekstu, czyli zerem
	    //if(usart_bufor[usart_bufor_ind]!= 0){
		    //
		    ////za�aduj znak do rejestru wysy�ki i ustaw indeks na nast�pny znak
		    //UDR0 = usart_bufor[usart_bufor_ind++];
		    //
		    //}else{
		    //
		    ////osi�gni�to koniec napisu w tablicy usart_bufor[]
		    //UCSR0B &= ~(1<<UDRIE0); //wy��cz przerwania pustego bufora nadawania
	    //}
    //}
    //
    //
    ////--------------------------------------------------------------
    //
    //
    //void wyslij_wynik(void){
	    //
	    ////funkcja rozpoczyna wysy�anie, wysy�aj�c pierwszy znak znajduj�cy si�
	    ////w tablicy usart_bufor[]. Pozosta�e wy�le funkcja przerwania,
	    ////kt�ra zostanie wywo�ana automatycznie po wys�aniu ka�dego znaku.
	    //
	    ////dodaj do tekstu wyniku znaki ko�ca linii (CR+LF), by na
	    ////ekranie terminala wyniki pojawia�y si� w nowych liniach
	    //unsigned char z;
	    //for(z=0; z<30; z++){
		    //if(usart_bufor[z]==0){   //czy to koniec takstu w tablicy
			    ////tak znaleziono koniec tekstu, dodajemy znak CR
			    //usart_bufor[z]   = 13;  //znak powrotu karetki CR (Carrige Return)
			    //usart_bufor[z+1]  = 10; //znak nowej linii LF (Line Feed)
			    //usart_bufor[z+2]  = 0;  //znak ko�ca ci�gu tekstu w tablicy
			    //break;
		    //}
	    //}
	    //
	    //
	    ////Zaczekaj, a� bufor nadawania b�dzie pusty
	    //while (!(UCSR0A & (1<<UDRE0)));
	    //
	    ////bufor jest pusty mo�na wys�a�
	    //
	    ////nast�pny znak do wysy�ki to znak nr 1
	    //usart_bufor_ind = 0;
	    //
	    ////w��cz przerwania pustego bufora UDR, co rozpocznie transmisj�
	    ////aktualnej zawarto�ci bufora
	    //UCSR0B |= (1<<UDRIE0);
	    //
    //}
    //
    ////--------------------------------------------------------------
    //
    //
    //int mainXYX(void)
    //{
	    //usart_inicjuj(); //inicjuj modu� USART (RS-232)
	    //sei();           //w��cz przerwania globalne
	    //
	    //wyslij_wynik();  //na pocz�tku wysy�amy text wzoru, kt�ry po
	    ////resecie jest w tablicy usart_bufor[]
	    //
	    //while(1){
		    //
		    ////tutaj Tw�j program ....
		    //
		    ////czekamy na informacj� o odebraniu danej nie blokuj�c mikrokontrolera
		    //if(odb_flaga){
			    //
			    //odb_flaga = 0; //zga� flag�
			    //
			    ////wykonaj obliczenia i wynik przekszta�� na znaki �aduj�c do
			    ////bufora usart_bufor[]
			    //sprintf(usart_bufor, "%f", 0.3187 * odb_x * odb_x + 2 * odb_x - 7);
			    //
			    //wyslij_wynik();  //rozpocznij wysy�anie wyniku przez RS-232
		    //}
		    //
		    ////w tym czasie mo�na wykonywa� dowolny program
		    ////umie�� go tutaj lub przed if() powy�ej
	    //}
    //}